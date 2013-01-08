<div class="hub_update">
  <h2><?php if ($url) { print "<a href=\"$url\">"; } print $title; if ($url) { print "</a>"; } ?></h2>

  <div class='meta'>
    <div class='source'>Via <?php if ($source_url) { print "<a href=\"$source_url\">"; } print $source_title; if ($source_url) { print "</a>"; } ?></div>
    <div class='create_date'><?php print $date_created; ?></div>
  </div>

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
