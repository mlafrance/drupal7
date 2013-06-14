<?php print render($page['header']); ?>
<?php include_once(drupal_get_path('theme', 'midd') . '/includes/header.inc'); ?>
<article id="midd_content" class="pagecontent container">
  <nav class="taskbar">
    <a class="taskbar_back" href="<?php echo base_path(); ?>academics/">Return to <strong>Departments &amp; Programs</strong></a>
    <section class="taskbar_dropdowns">
      <div class="dropdown_label">Quick links for</div>
      <?php print render($page['quicklinks']); ?>
    </section>
  </nav>
  <nav class="left">
    <?php print render($page['left']); ?>
  </nav>
  <section class="page">
    <aside class="sidebar">
      <?php print render($page['right']); ?>
    </aside>
    <section class="body">
      <?php print render($breadcrumb); ?>
      <?php print render($page['content']); ?>
    </section>
  </section>
  <?php print render($page['address']); ?>
  <div class="clear"></div>
</article>
<section id="midd_carousel" class="carousel">
  <div class="slider">
    <?php print render($page['carousel']); ?>
  </div>
</section>
<?php include_once(drupal_get_path('theme', 'midd') . '/includes/footer.inc'); ?>
<?php print render($page['footer']); ?>