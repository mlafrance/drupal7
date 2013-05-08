#!/bin/env php
<?php

$submodules_to_ignore = array(
  'sites/all/libraries/CAS',
);

exec('git submodule foreach', $submodules, $status);
if ($status)
  throw new Exception('`git submodule foreach` failed with status '.$status, $status);

$root = getcwd();
foreach ($submodules as $submodule) {
  try {
    $path = preg_replace('/^Entering \'(.+)\'$/', '\1', $submodule);
    $project_name = basename($path);
    chdir($root.'/'.$path);
    
    if (in_array($path, $submodules_to_ignore)) {
      continue;
    }
    
    // Check that we have drupal.org as one of our remotes.
    $remotes = explode("\n", shell_exec('git remote -v'));
    if (!$remotes)
      throw new Exception('`git remote -v` failed');
    $has_drupal_dot_org = false;
    $drupal_dot_org_remote_name = null;
    foreach ($remotes as $remote) {
      if (preg_match('/^([^\t]+)\t([^\s]+) \(fetch\)$/', $remote, $matches)) {
        $name = $matches[1];
        $url = $matches[2];
        
        if (preg_match('#^http://git\.drupal\.org/#', $url)) {
          $has_drupal_dot_org = true;
          $drupal_dot_org_remote_name = $name;
        }
      }
    }
    
    // Add the drupal.org remote if we only have a custom repository as our origin.
    if (!$has_drupal_dot_org) {    
      $command = 'git remote add d.o http://git.drupal.org/project/'.$project_name.'.git';
      exec($command, $out, $status);
      if ($status)
        throw new Exception('`'.$command.'` failed with status '.$status, $status);
        
      $command = 'git fetch d.o';
      exec($command, $out, $status);
      if ($status)
        throw new Exception('`'.$command.'` failed with status '.$status, $status);  
    }
    
    print "\n$path\n";
    
    // Look at our branches, make sure that we aren't on a detached HEAD since that will
    // confuse git_deploy
    $command = 'git branch -a --contains HEAD';
    unset($branches);
    exec($command, $branches, $status);
    if ($status)
      throw new Exception('`'.$command.'` failed with status '.$status, $status);
    
    $current_branch = null;
    $best_branch = null;
    $has_midd = false;
    foreach ($branches as $branch) {
      preg_match('/^(\*)?\s*(.+)$/', $branch, $matches);
      $is_current = strlen($matches[1]) > 0;
      $branch_name = $matches[2];
      
      if ($is_current)
        $current_branch = $branch_name;
      
      if (preg_match('/^.+-midd$/', $branch_name)) {
        $best_branch = $branch_name;
        $has_midd = true;
      } else if (!$has_midd && is_null($best_branch) && preg_match('/7\.x-[0-9]+\.x$/', $branch_name)) {
        $best_branch = $branch_name;
      }
    }
    // Check out a real branch and set it's commit to the current head commit.
    if ($current_branch == '(no branch)' && strlen($best_branch)) {
      $current_sha1 = trim(shell_exec('git rev-parse HEAD'));
      $has_changes = strlen(trim(shell_exec('git status --porcelain')));
      if (!$has_changes) {
        $new_branch_name = basename($best_branch);
        
        $command = 'git checkout --track '.$best_branch.' -B '.$new_branch_name;
        unset($out, $status);
        exec($command, $out, $status);
        if ($status)
          throw new Exception('`'.$command.'` failed with status '.$status, $status);
          
        $command = 'git reset --hard '.$current_sha1;
        unset($out, $status);
        exec($command, $out, $status);
        if ($status)
          throw new Exception('`'.$command.'` failed with status '.$status, $status); 
      }
    }
  } catch (Exception $e) {
    print $e->getMessage()."\n";
  }
}