<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php if (!empty($title)): ?>
    <header>
      <h1><?php print $title; ?></h1>
    </header>
  <?php endif; ?>
  <section class="contents">
    <?php hide($content['links']); ?>
    <?php print render($content); ?>
    <?php if ($display_submitted): ?>
      <span class="submitted"><?php print $submitted; ?></span>
    <?php endif; ?>
    <?php print render($content['links']); ?>
  </section>
</article>