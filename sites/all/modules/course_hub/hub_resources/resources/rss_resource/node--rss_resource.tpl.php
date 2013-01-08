<?php
/**
 * @file
 * Course Hub Resource - RSS
 *
 * Renders a resource node.
 */
?>
<div class="rss_resource">
  <h2>RSS Feed: <?php if ($site_url): print "<a href=\"$site_url\">"; endif; print $title; if ($site_url): print "</a>"; endif; ?></h2>

  <div class="url">Feed URL: <a href="<?php print $feed_url; ?>"><?php print $feed_url; ?></a></div>

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
