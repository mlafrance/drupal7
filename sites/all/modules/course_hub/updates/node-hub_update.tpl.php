<div class="hub_update">
  <h2><?php if ($url) { print "<a href=\"$url\">"; } print $title; if ($url) { print "</a>"; } ?></h2>

  <div class='meta'>
    <div class='source'>Via <?php if ($source_url) { print "<a href=\"$source_url\">"; } print $source_title; if ($source_url) { print "</a>"; } ?></div>
    <div class='create_date'><?php print $date_created; ?></div>
  </div>

  <div class='full_content'>
  <?php print $content;?>
  </div>

  <div class="clear-block">
    <?php if ($submitted): ?>
      <span class="submitted"><?php print $submitted; ?></span>
    <?php endif; ?>
    <?php if ($links): ?>
      <div class="links"><?php print $links; ?></div>
    <?php endif; ?>
  </div>
</div>
