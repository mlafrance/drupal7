<div class="hub_updates">
  <h2><?php print $title; ?></h2>

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

  <hr/>

  <?php if ($updates_list): ?>
  <div class="hub_updates_list">
    <?php print $updates_list; ?>
  </div>
  <?php endif; ?>

</div>
