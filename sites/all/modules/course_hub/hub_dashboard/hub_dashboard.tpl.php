<div class="hub_dashboard">
  <h1><?php print drupal_get_title(); ?></h1>

<?php
foreach ($sites as $site) {
	print theme('hub_dashboard_site', $site['mmtid'], $site['site_title'], $site['site_url']);
}
?>

<?php
if ($num_instructor_courses) {
  print "<div>".l(t("Manage Course Hub Sites"), 'dashboard/'.base64_encode($term_id).'/instructor')."</div>";
}
?>

</div>