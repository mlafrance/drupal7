<?php
/**
 * @file
 * Course Hub Resource - Moodle
 *
 * Renders a resource node.
 */
?>
<div class="moodle_resource">
  <h2><?php if ($moodle_url): print "<a href=\"$moodle_url\">"; endif; print $title; if ($moodle_url): print "</a>"; endif; ?></h2>

  <?php if ($moodle_url): ?>
  <div class="url"><a href="<?php print $moodle_url; ?>"><?php print $moodle_url; ?></a></div>
  <?php endif; ?>

  <?php if (!empty($sync_state)): ?>
  <div class="warning"><?php print $sync_state; ?></div>
  <?php endif; ?>

  <div class="content"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
    ?>
  </div>

  <?php if ($submitted): ?>
    <div class="submitted"><?php print $submitted; ?></div>
  <?php endif; ?>
  
  <?php print render($content['links']); ?>

  <?php print render($content['comments']); ?>
</div>
