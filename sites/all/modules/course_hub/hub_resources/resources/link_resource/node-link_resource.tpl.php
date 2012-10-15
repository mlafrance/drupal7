<div class="link_resource">
  <h2>Link: <?php if ($url) { print "<a href=\"$url\">"; } print $title; if ($url) { print "</a>"; } ?></h2>

  <div class="url">
  <?php if ($url): ?>
    <a href="<?php print $url; ?>"><?php print $url; ?></a>
  <?php else: ?>
    No link added.
  <?php endif; ?>
  </div>

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
