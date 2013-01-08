<?php
/**
 * @file
 * Course Hub Resource - MiddFiles
 *
 * Renders a resource node.
 */
?>
<div class="middfiles_resource">
  <h2><?php if ($middfiles_url): print "<a href=\"$middfiles_url\">"; endif; print $title; if ($middfiles_url): print "</a>"; endif; ?></h2>

  <div class="content"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
    ?>
  </div>

  <?php if ($middfiles_url): ?>
  <dl>
    <dt>Web:</dt>
    <dd><a href="<?php print $middfiles_url; ?>"><?php print $middfiles_url; ?></a></dd>
    <dt>Windows:</dt>
    <dd><input type="text" value="<?php print $middfiles_unc_path; ?>" size="50"/> (<a href="http://mediawiki.middlebury.edu/wiki/LIS/Using_File_Servers_-_Windows" target="_blank">help</a>)</dd>
    <dt>Mac:</dt>
    <dd><input type="text" value="<?php print $middfiles_afp_path; ?>" size="50"/> (<a href="http://mediawiki.middlebury.edu/wiki/LIS/Using_File_Servers_-_Macintosh" target="_blank">help</a>)</dd>
  </dl>

  <?php endif; ?>

  <?php if ($submitted): ?>
    <div class="submitted"><?php print $submitted; ?></div>
  <?php endif; ?>
  
  <?php print render($content['links']); ?>

  <?php print render($content['comments']); ?>
</div>
