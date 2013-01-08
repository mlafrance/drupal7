<?php
/**
 * @file
 * Course Hub Resource - Link
 *
 * Renders a resource node.
 */
?>
<div class="link_resource">
  <h2>Link: <?php if ($url): print "<a href=\"$url\">"; endif; print $title; if ($url): print "</a>"; endif; ?></h2>

  <div class="url">
  <?php if ($url): ?>
    <a href="<?php print $url; ?>"><?php print $url; ?></a>
  <?php else: ?>
    No link added.
  <?php endif; ?>
  </div>

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
