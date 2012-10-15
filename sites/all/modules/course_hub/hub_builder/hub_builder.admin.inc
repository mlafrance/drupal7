<?php
// $Id$

/**
 * Form builder. Configure Course Hub Resources
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function hub_builder_admin_settings() {
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['settings']['hub_builder_institution_dn'] = array(
    '#type' => 'textfield',
    '#title' => t('Institution Group DN'),
    '#size' => 100,
    '#default_value' => variable_get('hub_builder_institution_dn', "CN=All Staff,OU=General,OU=Groups,DC=middlebury,DC=edu"),
    '#description' => 'The group DN that should be used when setting "institution" permission.',
  );

  $form['settings']['hub_builder_max_execution_time'] = array(
    '#type' => 'textfield',
    '#title' => t('Build Timeout'),
    '#size' => 10,
    '#default_value' => variable_get('hub_builder_max_execution_time', "1200"),
    '#description' => 'The PHP max execution time (in seconds) for the build process.',
  );

  $form['settings']['hub_builder_read_only_support_groups'] = array(
    '#type' => 'textarea',
    '#title' => t('Read-Only Support Group DNs'),
    '#cols' => 100,
    '#rows' => 5,
    '#default_value' => variable_get('hub_builder_read_only_support_groups', ""),
    '#description' => 'The group DNs that should be able to see all content on course hub sites, but not make changes. On group DN per line.',
  );

  $form['settings']['hub_builder_add_content_support_groups'] = array(
    '#type' => 'textarea',
    '#title' => t('Add Content Support Group DNs'),
    '#cols' => 100,
    '#rows' => 5,
    '#default_value' => variable_get('hub_builder_add_content_support_groups', ""),
    '#description' => 'The group DNs that should be able to see add content to course hub sites. On group DN per line. What type of content they can add is determined by drupal role settings.',
  );

  $form['settings']['hub_builder_read_write_support_groups'] = array(
    '#type' => 'textarea',
    '#title' => t('Read-Write Support Group DNs'),
    '#cols' => 100,
    '#rows' => 5,
    '#default_value' => variable_get('hub_builder_read_write_support_groups', ""),
    '#description' => 'The group DNs that should be able to see and modify content on course hub sites. On group DN per line. What type of content they can add or modify is determined by drupal role settings.',
  );

  return system_settings_form($form);
}

/**
 * Form builder. Build a single Course Hub Site form
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function hub_builder_build_single_form() {
  $form['data'] = array(
    '#type' => 'fieldset',
    '#title' => t('Data'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['data']['destination_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Destination Path'),
    '#size' => 40,
    '#default_value' => 'hub/examples/testing',
    '#description' => 'The path to the page on which the course site should be built.',
  );
  $form['data']['subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#size' => 5,
    '#default_value' => 'TEST',
    '#description' => 'The Subject Code for the Section.',
  );
  $form['data']['number'] = array(
    '#type' => 'textfield',
    '#title' => t('Number'),
    '#size' => 5,
    '#default_value' => '0101',
    '#description' => 'The Course Number for the Section.',
  );
  $form['data']['sectionIdentifier'] = array(
    '#type' => 'textfield',
    '#title' => t('Sequence Identifier'),
    '#size' => 5,
    '#default_value' => 'A',
    '#description' => 'The sequence identifier code.',
  );
  $form['data']['uniqueId'] = array(
    '#type' => 'textfield',
    '#title' => t('Unique Section Id'),
    '#size' => 15,
    '#default_value' => 'TEST0101A-S11',
    '#description' => 'A unique identifier for this section that will be used to build the external_ids for nodes.',
  );
  $form['data']['sectionIdentifier'] = array(
    '#type' => 'textfield',
    '#title' => t('Sequence Identifier'),
    '#size' => 5,
    '#default_value' => 'A',
    '#description' => 'The sequence identifier code.',
  );
  $form['data']['offeringId'] = array(
    '#type' => 'textfield',
    '#title' => t('Offering Id'),
    '#size' => 15,
    '#default_value' => 'section/201200/00000',
    '#description' => 'The identifier of the offering in the system of reference.',
  );
  $form['data']['termId'] = array(
    '#type' => 'textfield',
    '#title' => t('Term Id'),
    '#description' => 'The term identifier for the course.',
    '#size' => 15,
    '#default_value' => 'term/test-2012',
  );
  $form['data']['termLabel'] = array(
    '#type' => 'textfield',
    '#title' => t('Term Label'),
    '#description' => 'A label for the term for the course.',
    '#size' => 10,
    '#default_value' => 'Test 2012',
  );
  $form['data']['termStart'] = array(
    '#type' => 'textfield',
    '#title' => t('Term Start Date'),
    '#description' => 'The start date for the term for the course.',
    '#size' => 15,
    '#default_value' => '2012-08-31',
  );
  $form['data']['termEnd'] = array(
    '#type' => 'textfield',
    '#title' => t('Term End Date'),
    '#description' => 'The end date for the term for the course.',
    '#size' => 15,
    '#default_value' => '2012-12-15',
  );
  $form['data']['termWeeks'] = array(
    '#type' => 'textfield',
    '#title' => t('Term Weeks'),
    '#description' => 'The number of weeks in the term for the course.',
    '#size' => 15,
    '#default_value' => '14',
  );
  $form['data']['catalogId'] = array(
    '#type' => 'textfield',
    '#title' => t('Catalog Id'),
    '#description' => 'A catalog Identifier for the course.',
    '#size' => 10,
    '#default_value' => 'catalog/TEST',
  );
  $form['data']['catalogUrl'] = array(
    '#type' => 'textfield',
    '#title' => t('Course Catalog URL'),
    '#description' => 'A catalog URL for the course.',
    '#size' => 60,
    '#default_value' => 'http://catalog.middlebury.edu/TEST',
  );
  $form['data']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => 'A title for the course.',
    '#size' => 60,
    '#default_value' => 'An Example Course',
  );
  $form['data']['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#description' => '',
    '#rows' => 5,
    '#cols' => 40,
    '#default_value' => '<p>
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Ut vitae nunc sed orci convallis posuere. Proin euismod placerat tincidunt. Quisque sit amet neque sed eros luctus lobortis. Maecenas posuere, sapien sit amet imperdiet tristique, mi sem vestibulum arcu, et vestibulum sapien quam at neque. Mauris tincidunt venenatis turpis quis tempor. In malesuada fringilla pretium? Suspendisse pulvinar luctus libero, at cursus mauris porta non. Phasellus in diam enim, et iaculis orci! Quisque nisi tortor; sagittis id posuere et, blandit id risus! Nunc volutpat dictum lacus fringilla fringilla? Suspendisse placerat gravida sapien non scelerisque!
</p>

<p>
Vestibulum eleifend, justo ut dictum tristique, felis diam accumsan diam, pharetra venenatis leo ante eget ipsum? Ut eleifend, dolor tristique elementum facilisis, erat purus convallis lorem, eget tristique neque erat sit amet nulla. Nunc posuere purus in turpis varius id mattis magna hendrerit. Donec neque libero, posuere vel adipiscing in, adipiscing vitae odio! Mauris ac vehicula leo. Phasellus et mi non libero accumsan tempor. Mauris aliquet scelerisque consequat. Morbi consectetur, felis eu bibendum sodales, neque justo porta est, quis fringilla justo orci vel risus. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Maecenas volutpat ornare libero eget dignissim? Nullam diam nulla, sagittis ultricies rhoncus vitae, interdum quis lorem. Integer imperdiet lorem non nulla ultrices non placerat lectus mollis. Morbi ut molestie erat. In gravida felis id tellus ultrices ac rhoncus nibh fringilla. Duis sed elit felis. Maecenas sed enim sed felis varius auctor. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Sed elementum urna ac nisi facilisis ut iaculis turpis porta. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos.
</p>

<p>
Proin odio dolor, dapibus ut pharetra sed, euismod sit amet augue. Etiam purus ipsum, vehicula facilisis rhoncus dignissim, scelerisque bibendum nunc. In hac habitasse platea dictumst. Integer vitae risus arcu. In hac habitasse platea dictumst. Nam a enim id lorem lobortis tempor? Donec fringilla arcu justo, in commodo nisi. Nullam venenatis facilisis tempor. Donec sit amet urna vel massa blandit imperdiet? Curabitur ut nunc nunc, nec bibendum justo. Suspendisse libero massa, aliquam quis malesuada vel, iaculis id dolor? Phasellus ut ipsum id tellus dictum molestie! Nam non aliquet tellus! In lacinia dictum odio, ac vehicula leo posuere id.
</p>',
  );
  $form['data']['classGroupDN'] = array(
    '#type' => 'textfield',
    '#title' => t('Class Group DN'),
    '#description' => 'The DN of the group for all class members for this course.',
    '#size' => 60,
    '#default_value' => 'CN=Course Hub Liaison Test Class,OU=MIDD,OU=web data,DC=middlebury,DC=edu',
  );
  $form['data']['studentGroupDN'] = array(
    '#type' => 'textfield',
    '#title' => t('Student Group DN'),
    '#description' => 'The DN of the group for all students for the course.',
    '#size' => 60,
    '#default_value' => 'CN=Course Hub Test Students,OU=MIDD,OU=web data,DC=middlebury,DC=edu',
  );
  $form['data']['auditGroupDN'] = array(
    '#type' => 'textfield',
    '#title' => t('Audit Group DN'),
    '#description' => 'The DN of the group for all audits for the course.',
    '#size' => 60,
    '#default_value' => 'CN=Course Hub Test Audits,OU=MIDD,OU=web data,DC=middlebury,DC=edu',
  );
  $form['data']['instructorGroupDN'] = array(
    '#type' => 'textfield',
    '#title' => t('Instructor Group DN'),
    '#description' => 'The DN of the group for all instructors for the course.',
    '#size' => 60,
    '#default_value' => 'CN=Course Hub Masqueraders,OU=MIDD,OU=web data,DC=middlebury,DC=edu',
  );
  $form['data']['instructors'] = array(
    '#type' => 'textarea',
    '#title' => t('Instructors'),
    '#description' => 'One per line or name|url',
    '#cols' => 40,
    '#rows' => 5,
    '#default_value' => 'John Doe|http://www.example.edu/john_doe',
  );
  $form['data']['location'] = array(
    '#type' => 'textfield',
    '#title' => t('Location'),
    '#description' => 'A location string.',
    '#size' => 30,
    '#default_value' => 'BIH 121',
  );
  $form['data']['schedule'] = array(
    '#type' => 'textarea',
    '#title' => t('Schedule'),
    '#description' => '',
    '#cols' => 40,
    '#rows' => 5,
    '#default_value' => 'Monday, Wednesday, Friday from 9am-10:30am',
  );

  $form['build'] = array(
    '#type' => 'submit',
    '#title' => 'build',
    '#default_value' => t('Build the Site'),
    '#description' => 'Build the site......',
  );

  $form['#submit'][] = 'hub_builder_single_form_submit';

  return $form;
}

/**
 * Implementation of hook_form_submit()
 *
 * Build a single course hub site.
 */
function hub_builder_single_form_submit (&$form, &$form_state) {
  if ($form_state['clicked_button']['#title'] == 'build') {
    try {
      $destinationTermPagePath = $form_state['values']['destination_path'];
      if (!$destinationTermPagePath)
        throw new InvalidArgumentException('Destination path is not defined.');
      $destinationTID = course_hub_tid_from_path($destinationTermPagePath);
      if (!$destinationTID)
        throw new InvalidArgumentException('Destination path is invalid.');


      $data = $form_state['values'];

      $instructors = array();
      foreach (explode("\n", $data['instructors']) as $instLine) {
        $parts = explode('|', $instLine);
        $instructors[$parts[0]] = $parts[1];
      }
      $data['instructors'] = $instructors;

      $data['institutionGroupDN'] = variable_get('hub_builder_institution_dn', false);


      $xml = hub_builder_build_site_xml_from_data($data);
      $xml = '<'.'?xml  version="1.0" ?>
<pages xmlns="http://www.middlebury.edu/nodeporter">
'.$xml.'
</pages>';

      $pages = mmporter_importer_import_string($destinationTID, $xml);
      drupal_set_message(t('@num Course site built', array('@num' => count($pages))));
    } catch (Exception $e) {
      drupal_set_message(t('Error building site: !message', array('!message' => $e->getMessage())), 'error');
    }
  }
}