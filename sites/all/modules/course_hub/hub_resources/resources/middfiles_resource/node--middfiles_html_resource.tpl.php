<?php
/**
 * @file
 * Course Hub Resource - Middfiles
 *
 * Renders a resource node.
 */
?>
<div class="middfiles_resource">
  <h2><?php if ($middfiles_url): print "<a href=\"$middfiles_url\">"; endif; print $title; if ($middfiles_url): print "</a>"; endif; ?></h2>

  <div class="content"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
    ?>
  </div>
  
  <?php print $middfiles_html_help;?>

  <?php if ($submitted): ?>
    <div class="submitted"><?php print $submitted; ?></div>
  <?php endif; ?>
  
  <?php print render($content['links']); ?>

  <?php print render($content['comments']); ?>
</div>
