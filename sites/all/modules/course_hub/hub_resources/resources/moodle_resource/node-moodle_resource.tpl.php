<div class="moodle_resource">
  <h2><?php if ($moodle_url): print "<a href=\"$moodle_url\">"; endif; print $title; if ($moodle_url): print "</a>"; endif; ?></h2>

  <?php if ($moodle_url): ?>
  <div class="url"><a href="<?php print $moodle_url; ?>"><?php print $moodle_url; ?></a></div>
  <?php endif; ?>

  <?php if (!empty($sync_state)): ?>
  <div class="warning"><?php print $sync_state; ?></div>
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
