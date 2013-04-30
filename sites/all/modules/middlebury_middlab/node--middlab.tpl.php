<?php
/**
 * @file
 * A default template file for the MiddLab Widget node.
 */
?>
<article class="<?php print $classes . ' c' . rand(1, 14); ?>">
  <header>
    <h1><a href="<?php print $middlab_link; ?>"><?php print $middlab_title; ?></a></h1>
  </header>
  <section class="description"><?php print $middlab_description; ?></section>
  <section class="department"><a href="<?php print $middlab_link; ?>">Discuss in Midd<b>Lab</b> &raquo;</a></section>
</article>
<?php print render($content['links']); ?>