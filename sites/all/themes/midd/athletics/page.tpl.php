<?php
  $sections = array(
    '72112' => array(
      'name' => 'Athletics',
      'width' => '873',
      'image' => '//cdn.middlebury.edu/middlebury.edu/2010/images/headers/athletics.png',
      'images' => array(array(
        '304' => '//cdn.middlebury.edu/middlebury.edu/2010/images/headers/athletics_1_1.jpg',
        '334' => '//cdn.middlebury.edu/middlebury.edu/2010/images/headers/athletics_1_2.jpg',
        '439' => '//cdn.middlebury.edu/middlebury.edu/2010/images/headers/athletics_1_3.jpg',
        '244' => '//cdn.middlebury.edu/middlebury.edu/2010/images/headers/athletics_1_4.jpg',
        '415' => '//cdn.middlebury.edu/middlebury.edu/2010/images/headers/athletics_1_5.jpg',
      ), array(
        '250' => '//cdn.middlebury.edu/middlebury.edu/2010/images/headers/athletics_2_1.jpg',
        '581' => '//cdn.middlebury.edu/middlebury.edu/2010/images/headers/athletics_2_2.jpg',
        '315' => '//cdn.middlebury.edu/middlebury.edu/2010/images/headers/athletics_2_3.jpg',
        '205' => '//cdn.middlebury.edu/middlebury.edu/2010/images/headers/athletics_2_4.jpg',
        '385' => '//cdn.middlebury.edu/middlebury.edu/2010/images/headers/athletics_2_5.jpg',
      ), array(
        '265' => '//cdn.middlebury.edu/middlebury.edu/2010/images/headers/athletics_3_1.jpg',
        '349' => '//cdn.middlebury.edu/middlebury.edu/2010/images/headers/athletics_3_2.jpg',
        '565' => '//cdn.middlebury.edu/middlebury.edu/2010/images/headers/athletics_3_3.jpg',
        '280' => '//cdn.middlebury.edu/middlebury.edu/2010/images/headers/athletics_3_4.jpg',
        '277' => '//cdn.middlebury.edu/middlebury.edu/2010/images/headers/athletics_3_5.jpg',
      )),
    ),
  );

  $section = $sections[arg(1)];
  $arg_nid = arg(3);
?>
<?php print render($page['header']); ?>
<?php include_once(drupal_get_path('theme', 'midd') . '/includes/header.inc'); ?>
<?php if (empty($arg_nid)): ?>
  <div id="midd_waveform" class="waveform">
    <div class="slider">
      <ul id="midd_stories" class="stories">
        <li id="midd_header" class="bar header">
          <h1><img src="<?php print $section['image']; ?>" alt="<?php print $section['name']; ?>" width="<?php print $section['width']; ?>" /></h1>
          <?php $set = rand(0, count($section['images']) - 1); ?>
          <?php if (is_array($section['images'][$set])): ?>
            <?php foreach($section['images'][$set] as $width => $url): ?>
              <img src="<?php print $url; ?>" width="<?php print $width; ?>" height="240" alt="Header photo" class="header_photo" />
            <?php endforeach; ?>
          <?php endif; ?>
        </li>
      </ul>
    </div>
  </div>
<?php endif; ?>
<article id="midd_content" class="pagecontent container">
  <div class="panther"></div>
  <nav id="midd_taskbar" class="taskbar">
    <?php if (!empty($page['quicklinks'])): ?>
      <section class="taskbar_dropdowns">
        <?php print render($page['quicklinks']); ?>
      </section>
    <?php endif; ?>
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