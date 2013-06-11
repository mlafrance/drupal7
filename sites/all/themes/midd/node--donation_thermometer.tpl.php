<article id="node-<?php print $node->nid; ?>" class="<?php print $classes . ' ' . $type; ?>"<?php print $attributes; ?>>
  <?php if (!empty($title)): ?>
    <header>
      <h1>
        <span class="amount"><?php print round($percent, 0); ?>%</span>
        <span class="label"> of our goal!</span>
      </h1>
    </header>
  <?php endif; ?>
  <section class="contents">
    <div class="gauge">
      <div class="value" style="<?php print $type == 'classic-m' ? 'height' : 'width'; ?>:<?php print $percent; ?>%;"><?php print $percent; ?></div>
    </div>
    <?php print render($content['links']); ?>
  </section>
</article>