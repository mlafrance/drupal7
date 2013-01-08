<?php
/**
 * @file
 * Course Hub Resource - WordPress
 *
 * Renders a resource node.
 */
?>
<div class="wordpress_resource">
  <h2>WordPress: <?php if ($wp_site_url): print "<a href=\"$wp_site_url\">"; endif; print $title; if ($wp_site_url): print "</a>"; endif; ?></h2>

  <?php if ($wp_site_url): ?>
  <div class="url"><a href="<?php print $wp_site_url; ?>"><?php print $wp_site_url; ?></a></div>
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
