<?php print render($page['header']); ?>
<?php include_once(drupal_get_path('theme', 'midd_sa') . '/includes/header.inc'); ?>
<article id="midd_content" class="pagecontent container">
  <section class="page">
    <section class="body">
      <div class="three split columns">
        <div class="first column">
          <?php print render($page['content']); ?>
        </div>
        <div class="column gray">
          <div class="schools">
            <?php print render($page['center']); ?>
          </div>
        </div>
        <div class="last column">
          <?php print render($page['right']); ?>
        </div>
        <div class="clear"></div>
      </div>
      <div class="clear"></div>
    </section>
  </section>
  <div class="clear"></div>
</article>
<section id="midd_carousel" class="carousel">
  <div class="slider">
    <?php print render($page['carousel']); ?>
  </div>
</section>
<?php include_once(drupal_get_path('theme', 'midd_sa') .'/includes/footer.inc'); ?>
<?php print render($page['footer']); ?>