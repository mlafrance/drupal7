<div class="middfiles_resource">
  <h2><?php if ($middfiles_url) { print "<a href=\"$middfiles_url\">"; } print $title; if ($middfiles_url) { print "</a>"; } ?></h2>

  <?php print $content;?>

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


  <div class="clear-block">
    <?php if ($submitted): ?>
      <span class="submitted"><?php print $submitted; ?></span>
    <?php endif; ?>
    <?php if ($links): ?>
      <div class="links"><?php print $links; ?></div>
    <?php endif; ?>
  </div>
</div>
