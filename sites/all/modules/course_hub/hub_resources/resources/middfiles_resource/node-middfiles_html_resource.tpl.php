<div class="middfiles_resource">
  <h2><?php if ($middfiles_url): print "<a href=\"$middfiles_url\">"; endif; print $title; if ($middfiles_url): print "</a>"; endif; ?></h2>

  <?php print $content;?>

  <?php print $middfiles_html_help;?>

  <div class="clear-block">
    <?php if ($submitted): ?>
      <span class="submitted"><?php print $submitted; ?></span>
    <?php endif; ?>
    <?php if ($links): ?>
      <div class="links"><?php print $links; ?></div>
    <?php endif; ?>
  </div>
</div>
