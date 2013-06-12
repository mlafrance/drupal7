<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!empty($title)): ?>
    <header>
      <h1><?php print $title; ?></h1>
    </header>
  <?php endif; ?>
  <section class="contents">
    <?php hide($content['links']); ?>
    <?php print render($content); ?>
    <?php if ($node->field_rollyear[$language->language][0]['value'] == '2013'): ?>
      <?php if (!empty($reunion)): ?>
        <h3><?php print $reunion_title; ?></h3>
        <p><?php foreach ($reunion as $donor): ?>
          <?php print $donor; ?><br />
        <?php endforeach; ?></p>
      <?php endif; ?>
      <?php if (!empty($cane)): ?>
        <h3><?php print $cane_title; ?></h3>
        <p><?php foreach ($cane as $donor): ?>
          <?php print $donor; ?><br />
        <?php endforeach; ?></p>
      <?php endif; ?>
    <?php endif; ?>
    <?php if (!empty($donors)): ?>
      <h3><?php print $donors_title; ?></h3>
      <p><?php foreach ($donors as $donor): ?>
        <?php print $donor; ?><br />
      <?php endforeach; ?></p>
    <?php endif; ?>
    <?php if ($display_submitted): ?>
      <span class="submitted"><?php print $submitted; ?></span>
    <?php endif; ?>
    <?php print render($content['links']); ?>
  </section>
</article>