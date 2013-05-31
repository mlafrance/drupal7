<header class="container">
  <?php global $user; ?>
  <?php header('Parse-ESI: true'); ?>
  <esi:include src="<?php print base_path() . drupal_get_path('theme', 'midd'); ?>/includes/head_links.html"></esi:include>
  <form class="search" action="<?php print base_path(); ?>search" method="get" target="_top">
    <label for="midd_search_query">Search Midd</label>
    <input type="search" id="midd_search_query" class="search_query x-webkit-speech" name="q2" placeholder="Search Midd" x-webkit-speech required>
    <input type="submit" id="midd_search_submit" class="search_submit" value="Go">
    <input type="hidden" id="midd_ajax_search_url" value="<?php print base_path(); ?>go/search">
  </form>
  <h1 class="wordmark"><a href="<?php echo base_path(); ?>"><img src="<?php print base_path() . drupal_get_path('theme', 'midd'); ?>/images/logo.png" width="206" height="39" alt="Middlebury" /></a></h1>
  <?php $alias = middlebury_get_toplevel(arg(1)); ?>
  <?php if (empty($is_front) || !$is_front): ?>
    <?php include_once(drupal_get_path('theme', 'midd') . '/includes/navigation.inc'); ?>
  <?php endif; ?>
</header>