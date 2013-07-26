<?php print render($page['header']); ?>
<?php include_once(drupal_get_path('theme', 'midd') . '/includes/header.inc'); ?>
<div id="midd_waveform" class="waveform">
  <div class="slider">
    <ul id="midd_stories" class="stories nojs">
      <li class="disabled bar">
        <div class="bar_contents">
          <div class="bar_title">Welcome to Middlebury College</div>
          <div class="bar_target">
            <div class="bar_color">
              <img src="//cdn.middlebury.edu/middlebury.edu/2010/images/bar_nojs.jpg" alt="Students on Midd's Vermont campus" width="360" height="220" />
            </div>
          </div>
          <div class="bar_text">
            Please <a href="http://www.google.com/support/bin/answer.py?answer=23852" target="_blank">enable Javascript in your browser</a> and <a href="<?php print $base_path; ?>">reload the page</a> to view interactive content.
          </div>
        </div>
      </li>
    </ul>
  </div>
</div>
<div class="container">
  <?php include_once(drupal_get_path('theme', 'midd') . '/includes/navigation.inc'); ?>
  <nav id="midd_affiliates" class="affiliates">
    <h2>Programs &amp; Affiliates<span></span></h2>
    <ul>
      <li class="affiliates_languageschools"><a href="<?php print $base_path; ?>ls/">Middlebury Language Schools<span></span></a></li>
      <li class="affiliates_schoolsabroad"><a href="<?php print $base_path; ?>sa/">Middlebury Schools Abroad<span></span></a></li>
      <li class="affiliates_breadloaf"><a href="<?php print $base_path; ?>breadloaf/">Bread Loaf School of English &amp; Writers Conference<span></span></a></li>
      <li class="affiliates_mmla"><a href="http://mmla.middlebury.edu/">Middlebury-Monterey Language Academy<span></span></a></li>
      <li class="affiliates_miis"><a href="http://www.miis.edu/">Monterey Institute of International Studies<span></span></a></li>
    </ul>
    <div class="clear"></div>
  </nav>
</div>
<?php print render($page['carousel']); ?>
<?php include_once(drupal_get_path('theme', 'midd') . '/includes/footer.inc'); ?>
<?php print render($page['footer']); ?>