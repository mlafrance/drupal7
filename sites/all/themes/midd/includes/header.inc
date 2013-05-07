<header class="container">
  <?php global $user; ?>
  <?php header('Parse-ESI: true'); ?>
  <esi:include src="<?php print base_path() . drupal_get_path('theme', 'midd'); ?>/head_links.html" />
  <form class="search" action="<?php print base_path(); ?>search" method="get" target="_top">
    <label for="midd_search_query">Search Midd</label>
    <input type="search" id="midd_search_query" class="search_query x-webkit-speech" name="q2" placeholder="Search Midd" x-webkit-speech required>
    <input type="submit" id="midd_search_submit" class="search_submit" value="Go">
    <input type="hidden" id="midd_ajax_search_url" value="<?php print base_path(); ?>go/search">
  </form>
  <h1 class="wordmark"><a href="<?php echo base_path(); ?>"><img src="<?php print base_path() . drupal_get_path('theme', 'midd'); ?>/images/logo.png" width="206" height="39" alt="Middlebury" /></a></h1>
  <?php $alias = middlebury_get_toplevel(arg(1)); ?>
  <nav id="midd_navigation" class="navigation container">
    <ul>
      <li class="nav_admissions top <?php if ($alias == 'admissions') print 'active'; ?>"><a href="<?php print base_path(); ?>admissions/">Admissions<span></span></a></li>
      <li class="nav_academics top <?php if ($alias == 'academics') print 'active'; ?>"><a href="<?php print base_path(); ?>academics/">Academics<span></span></a></li>
      <li class="nav_studentlife top <?php if ($alias == 'studentlife') print 'active'; ?>"><a href="<?php print base_path(); ?>studentlife/">Student Life<span></span></a></li>
      <li class="nav_athletics top <?php if ($alias == 'athletics') print 'active'; ?>"><a href="<?php print base_path(); ?>athletics/">Athletics<span></span></a></li>
      <li class="nav_arts top <?php if ($alias == 'arts') print 'active'; ?>"><a href="<?php print base_path(); ?>arts/">Arts<span></span></a></li>
      <li class="nav_international top <?php if ($alias == 'international') print 'active'; ?>"><a href="<?php print base_path(); ?>international/">Middlebury International<span></span></a></li>
      <li class="nav_middlab top <?php if ($alias == 'middlab') print 'active'; ?>"><a href="<?php print base_path(); ?>middlab/">MiddLab<span></span></a></li>
      <li class="nav_about bottom <?php if ($alias == 'about') print 'active'; ?>"><a href="<?php print base_path(); ?>about/">About Middlebury<span></span></a></li>
      <li class="nav_sustainability bottom <?php if ($alias == 'sustainability') print 'active'; ?>"><a href="<?php print base_path(); ?>sustainability/">Sustainability<span></span></a></li>
      <li class="nav_giving bottom <?php if ($alias == 'giving') print 'active'; ?>"><a href="<?php print base_path(); ?>giving/">Giving<span></span></a></li>
      <li class="nav_news bottom <?php if ($alias == 'news') print 'active'; ?>"><a href="<?php print base_path(); ?>news/">News Room<span></span></a></li>
      <li class="nav_events bottom <?php if ($alias == 'events') print 'active'; ?>"><a href="<?php print base_path(); ?>events/">Calendar of Events<span></span></a></li>
      <li class="nav_offices bottom <?php if ($alias == 'offices') print 'active'; ?>"><a href="<?php print base_path(); ?>offices/">Offices &amp; Services<span></span></a></li>
    </ul>
  </nav>
</header>