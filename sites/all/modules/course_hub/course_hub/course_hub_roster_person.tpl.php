<?php
/**
 * @file
 * Course Hub Roster view
 *
 * Provides a means for viewing the class roster. Available only to instructors.
 */
?>

 <div class='course_hub_roster_person'>
	<img src='<?php print $person->roster_photo_url; ?>' class='course_hub_roster_photo'/>
	<h3><?php print $person->profile_display_name; ?></h3>
	<p><a href='mailto:<?php print $person->mail; ?>'><?php print $person->mail; ?></a></p>
</div>