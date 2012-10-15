<div class="hub_dashboard">
  <h1><?php print drupal_get_title(); ?></h1>

  <p>Normally you do not need to create additional Course Hub Sites for lab and discussion sections since the Course Hub sites for the Lecture or Seminar sections suffice for most needs and reduce clutter in students' dashboards.</p>

  <p>Here are some cases where you may want to create Course Hub sites for labs or discussion sections:</p>
  <ul>
    <li>The lab is taught by a separate instructor with its own resources and syllabus.</li>
    <li>You wish to create separate resources (e.g. Moodle Sites) for each discussion section.</li>
  </ul>

<table class='instructor_sections'>
  <thead>
    <tr>
      <th>Section</th>
      <th>Title</th>
      <th>Type</th>
      <th>Operations</th>
    </tr>
  </thead>
  <tbody>
<?php
foreach ($sections as $s) {
	print "\n      <tr class='instructor_section instructor_section_".(($s['can_manage'])?'':'un')."managable'>";
	print "\n        <td>".$s['subject'].' '.$s['number'].$s['sectionIdentifier'].'</td>';
	print "\n        <td>";
	if ($s['exists'])
	  print l($s['title'], $s['path']);
	else
	print $s['title'];
	print '</td>';
	print "\n        <td>".$s['genusTypeName'].'</td>';
	print "\n        <td>";
	if ($s['can_add'])
	  print l(t("Add Course Hub Site"), 'dashboard/'.base64_encode($s['termId']).'/instructor/add/'.base64_encode($s['offeringId']));
	elseif ($s['can_delete'])
	  print l(t("Delete Course Hub Site"), 'dashboard/'.base64_encode($s['termId']).'/instructor/delete/'.base64_encode($s['offeringId']));
	elseif ($s['can_manage'] && $s['has_resources'])
	  print "Site has syllabus or resources, can't delete.";
	print '</td>';
	print "</tr>";
}
?>

  </tbody>
</table>
</div>