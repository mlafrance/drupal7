<div class="hub_updates">
  <h2><?php print $title; ?></h2>

  <?php print $content; ?>

  <div class="clear-block">
    <?php if ($submitted): ?>
      <span class="submitted"><?php print $submitted; ?></span>
    <?php endif; ?>
    <?php if ($links): ?>
      <div class="links"><?php print $links; ?></div>
    <?php endif; ?>
  </div>

  <hr/>

  <?php if ($updates_list): ?>
  <div class="hub_updates_list">
    <?php print $updates_list; ?>
  </div>
  <?php endif; ?>

</div>
