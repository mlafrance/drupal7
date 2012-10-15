<div class="rss_resource">
  <h2>RSS Feed: <?php if ($site_url) { print "<a href=\"$site_url\">"; } print $title; if ($site_url) { print "</a>"; } ?></h2>

  <div class="url">Feed URL: <a href="<?php print $feed_url; ?>"><?php print $feed_url; ?></a></div>

  <?php print $content;?>


  <div class="clear-block">
    <?php if ($submitted): ?>
      <span class="submitted"><?php print $submitted; ?></span>
    <?php endif; ?>
    <?php if ($links): ?>
      <div class="links"><?php print $links; ?></div>
    <?php endif; ?>
  </div>
</div>
