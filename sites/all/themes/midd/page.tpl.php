<?php print render($page['header']); ?>
<?php include_once(drupal_get_path('theme', 'midd') . '/includes/header.inc'); ?>
<article id="midd_content" class="pagecontent container">
  <nav class="left blue">
    <?php print render($page['left']); ?>
  </nav>
  <section class="page">
    <?php print render($page['right']); ?>
    <section class="body">
      <?php print render($page['content']); ?>
    </section>
  </section>
  <?php print render($page['address']); ?>
  <div class="clear"></div>
</article>
<?php print render($page['carousel']); ?>
<?php include_once(drupal_get_path('theme', 'midd') . '/includes/footer.inc'); ?>
<?php print render($page['footer']); ?>