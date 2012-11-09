<?php
/**
 * @file
 * Course Hub Statistics bars.
 *
 * Renders the graph bars for each resource type.
 */
?>
<div class='course_hub_stats_bar course_hub_stats_bar_total'>
	<div class='course_hub_stats_bar_label'><a href="<?php print $stats['resource_list_url']; ?>">Total Resources:</a></div>
	<div class='course_hub_stats_bar_ammount'><?php print $stats['num_resources']; ?></div>
	<div class='course_hub_stats_bar_bar' style='width: <?php print $stats['num_resources_percent']; ?>%'></div>
</div>
<div class='course_hub_stats_bar course_hub_stats_bar_sites'>
	<div class='course_hub_stats_bar_label'><a href="<?php print $stats['resource_sites_url']; ?>">Unique Sites:</a></div>
	<div class='course_hub_stats_bar_ammount'><?php print $stats['uniq_sites']; ?></div>
	<div class='course_hub_stats_bar_percent'><?php print $stats['percent_of_sites_in_cat']; ?>% of <?php print $stats['total_number_of_sites_in_cat']; ?> sites</div>
	<div class='course_hub_stats_bar_bar' style='width: <?php print $stats['percent_of_sites_in_cat']; ?>%'></div>
</div>
<div class='course_hub_stats_bar course_hub_stats_bar_instructors'>
	<div class='course_hub_stats_bar_label'><a href="<?php print $stats['resource_instructors_url']; ?>">Unique Instructors:</a></div>
	<div class='course_hub_stats_bar_ammount'><?php print $stats['num_instructors']; ?></div>
	<div class='course_hub_stats_bar_percent'><?php print $stats['percent_of_instructors_in_cat']; ?>% of <?php print $stats['total_number_of_instructors_in_cat']; ?> instructors</div>
	<div class='course_hub_stats_bar_bar' style='width: <?php print $stats['percent_of_instructors_in_cat']; ?>%'></div>
</div>
<div class='course_hub_stats_bar course_hub_stats_bar_students'>
	<div class='course_hub_stats_bar_label'>Unique Students:</div>
	<div class='course_hub_stats_bar_ammount'><?php print $stats['num_students']; ?></div>
	<div class='course_hub_stats_bar_percent'><?php print $stats['percent_of_students_in_cat']; ?>% of <?php print $stats['total_number_of_students_in_cat']; ?> students</div>
	<div class='course_hub_stats_bar_bar' style='width: <?php print $stats['percent_of_students_in_cat']; ?>%'></div>
</div>