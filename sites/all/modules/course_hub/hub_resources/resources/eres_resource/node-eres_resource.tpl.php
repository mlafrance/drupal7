<?php
/**
 * @file
 * Course Hub Resource - ERES
 *
 * Renders a resource node.
 */
?>
<div class="eres_resource">
  <h2><?php if ($eres_url): print "<a href=\"$eres_url\">"; endif; print $title; if ($eres_url): print "</a>"; endif; ?></h2>

  <?php if ($eres_url): ?>
  <div class="url"><a href="<?php print $eres_url; ?>"><?php print $eres_url; ?></a></div>
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
