<div class='roster'>
	<h1><?php echo $short_name; ?> Class Roster</h1>
	<div><em>Visible to instructors only</em></div>

	<h2>Students</h2>
	<?php foreach ($students as $person) {
		print theme('course_hub_roster_person', $person);
	} ?>

	<?php if (count($audits)) { ?>
	<h2>Audits</h2>
		<?php foreach ($audits as $person) {
			print theme('course_hub_roster_person', $person);
		}
	}
	?>

</div>