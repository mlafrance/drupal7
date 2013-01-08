<?php
/**
 * @file
 * Course Hub Resource - ERES
 *
 * Renders a resource node.
 */
?>
<div class="eres_resource">
  <h2><?php if ($eres_url): print "<a href=\"$eres_url\">"; endif; print $title; if ($eres_url): print "</a>"; endif; ?></h2>

  <?php if ($eres_url): ?>
  <div class="url"><a href="<?php print $eres_url; ?>"><?php print $eres_url; ?></a></div>
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
