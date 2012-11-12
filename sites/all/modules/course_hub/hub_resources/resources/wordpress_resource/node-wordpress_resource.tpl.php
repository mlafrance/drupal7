<div class="wordpress_resource">
  <h2>WordPress: <?php if ($wp_site_url): print "<a href=\"$wp_site_url\">"; endif; print $title; if ($wp_site_url): print "</a>"; endif; ?></h2>

  <?php if ($wp_site_url): ?>
  <div class="url"><a href="<?php print $wp_site_url; ?>"><?php print $wp_site_url; ?></a></div>
  <?php endif; ?>

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
