<?php

/**
 * Form builder. Configure Course Hub terms
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function hub_builder_terms_form(&$form_state) {
  $form = array();
  $form['add']['#value'] = l(t('+ Add a Term'), 'admin/course_hub/builder/terms/add');
  foreach (hub_builder_get_terms() as $term) {
    $form[$term->id] = _hub_builder_term_elements($term);
  }
  return $form;
}


function _hub_builder_term_elements($term = null) {
  $fieldset = array(
    '#attributes' => array(),
  );

  $fieldset['id']['#value'] = l(t('@id', array('@id' => $term->id)), 'admin/course_hub/builder/terms/' . base64_encode($term->id) . '/edit');
  $fieldset['display_name']['#value'] = t('@display_name', array('@display_name' => $term->display_name));
  $fieldset['import_path']['#value'] = l(t('@path', array('@path' => $term->import_path)), $term->import_path);
  $fieldset['last_built']['#value'] = $term->last_built;
  $fieldset['last_built_by']['#value'] = $term->last_built_by_name;

  $fieldset['operations']['test']['#value'] = l(t('Test'), 'admin/course_hub/builder/terms/' . base64_encode($term->id) . '/test');
  $fieldset['operations']['build']['#value'] = l(t('Build'), 'admin/course_hub/builder/terms/' . base64_encode($term->id) . '/build');
  return $fieldset;
}

/**
 * Theme the term overview form into a table.
 *
 * @ingroup themeable
 */
function theme_hub_builder_terms_form($form) {
  $header = array(
    t('Id'),
    t('Display Name'),
    t('Path'),
    t('Last Built'),
    t('Built By'),
    array('data' => t('Operations'), 'colspan' => '2'),
  );

  $rows = array();
  foreach (element_children($form) as $term_id) {
    if (isset($form[$term_id]['id'])) {
      $element = &$form[$term_id];
      // Build a list of operations.
      $operations = array();
      foreach (element_children($element['operations']) as $op) {
        $operations[] = drupal_render($element['operations'][$op]);
      }
      while (count($operations) < 2) {
        $operations[] = '';
      }

      $row = array();
      $row[] = drupal_render($element['id']);
      $row[] = drupal_render($element['display_name']);
      $row[] = drupal_render($element['import_path']);
      $row[] = drupal_render($element['last_built']);
      $row[] = drupal_render($element['last_built_by']);
      $row = array_merge($row, $operations);

      $row = array_merge(array('data' => $row), $element['#attributes']);
      $rows[] = $row;
    }
  }
  $output = '';
  if ($rows) {
    $output .= theme('table', $header, $rows, array('id' => 'terms'));
  }
  $output .= drupal_render($form);
  return $output;
}

/**
 * Form builder. Edut a course_hub term
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function hub_builder_term_edit_form(&$form_state, $term_id = null) {
  $form = array();
  if ($term_id) {
    $term_id = base64_decode($term_id);
    $term = hub_builder_get_term($term_id);
    $form['orig_id'] = array(
      '#type' => 'hidden',
      '#value' => $term_id,
    );
  }
  else {
    $term = new HubBuilder_Term();
  }

  $form['catalog_id'] = array(
    '#title' => t('Catalog'),
//     '#description' => '',
    '#type' => 'select',
    '#default_value' => $term->catalog_id,
    '#options' => array(),
  );
  foreach (hub_builder_get_catalogs() as $catalog) {
    $form['catalog_id']['#options'][$catalog->id] = $catalog->id;
  }

  $form['id'] = array(
    '#title' => t('Term Id'),
    '#description' => 'The term id will be inserted into data fetching URLS to replace the [TERM_ID] placeholder.',
    '#type' => 'textfield',
    '#default_value' => $term->id,
    '#size' => 25,
  );

  $form['display_name'] = array(
    '#title' => t('Display Name'),
    '#description' => 'Just for reference, not used in importing.',
    '#type' => 'textfield',
    '#default_value' => $term->display_name,
    '#size' => 50,
    '#maxlength' => 50,
  );

  $form['import_path'] = array(
    '#title' => t('Import Path'),
    '#description' => 'The path under which subjects pages and courses will be imported. This page must exist.',
    '#type' => 'textfield',
    '#default_value' => $term->import_path,
    '#size' => 100,
    '#maxlength' => 255,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Changes'),
  );

  if ($term_id) {
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
    );
  }

  return $form;
}

/**
 * Form builder. Configure Course Hub Catalogs
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function hub_builder_term_edit_form_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/course_hub/builder/terms';

  if ($form_state['values']['orig_id']) {
    $term = hub_builder_get_term($form_state['values']['orig_id']);
  }
  else {
    $term = new HubBuilder_Term();
  }

  if ($form_state['values']['op'] == 'Delete') {
    $term->delete();
    return;
  }

  $term->catalog_id = $form_state['values']['catalog_id'];
  $term->id = $form_state['values']['id'];
  $term->display_name = $form_state['values']['display_name'];
  $term->import_path = $form_state['values']['import_path'];
  $term->save();
}

/**
 * Test the url building for a term
 *
 * @param string $term_id
 * @return string
 */
function hub_builder_term_test($term_id) {
  $term_id = base64_decode($term_id);
  $term = hub_builder_get_term($term_id);
  $results = array();

  $result = array('title' => "Import Path");
  $destinationTID = course_hub_tid_from_path($term->import_path);
  if ($destinationTID > 0) {
    $result['success'] = true;
    $result['content'] = t('@path exists with mmtid @tid', array('@path' => $term->import_path, '@tid' => $destinationTID));
  }
  else {
    $result['success'] = false;
    $result['content'] = t('@path doesn\'t exist.', array('@path' => $term->import_path));
  }
  $results[] = $result;

  $result = array('title' => "Main Data Url: Validation");
  $url = $term->getMainCourseDataUrl();
  $result['success'] = is_string(filter_var($url, FILTER_VALIDATE_URL));
  $result['content'] = $url;
  $results[] = $result;

  $result = array('title' => "Main Data Url: XML Response");
  try {
    $xpath = hub_builder_get_xpath($url);
    $result['content'] = t('Successfully loaded the data document');
    $result['success'] = true;
  } catch (Exception $e) {
    $result['content'] = $e->getMessage();
    $result['success'] = false;
  }
  $results[] = $result;

  $result = array('title' => "Main Data Url: Includes Subjects");
  try {
    if (empty($xpath))
      throw new Exception("Not continuing test due to previoius errors.");

    $subjects = hub_builder_get_subjects($xpath);
    if (!is_array($subjects))
      throw new Exception("Subjects should have been an array.");
    if (!count($subjects))
      throw new Exception("No subjects found.");

    ob_start();
    print count($subjects) . ' subjects found: ';
    $i = 0;
    print "<pre>";
    foreach ($subjects as $subject) {
      print_r($subject);
      $i++;
      if ($i >= 4)
        break;
    }
    if (count($subjects) > 4)
      print "\n...";
    print "</pre>";
    $result['content'] = ob_get_clean();
    $result['success'] = true;
  } catch (Exception $e) {
    $result['content'] = $e->getMessage();
    $result['success'] = false;
  }
  $results[] = $result;

  $result = array('title' => "Main Data Url: Sections");
  try {
    if (empty($subjects))
      throw new Exception("Not continuing test due to previoius errors.");
    $subjectsWithSections = 0;
    $totalSections = 0;
    $validSections = 0;
    $invalidSections = 0;
    $exampleInstructorId = null;
    $exampleInstructorName = null;
    $missingGroups = array();
    $errors = array();
    foreach ($subjects as $subject) {
      $sectionElements = hub_builder_get_section_elements_in_subject($xpath, $subject['id']);
      if ($sectionElements->length) {
        $subjectsWithSections++;
        $totalSections += $sectionElements->length;
        foreach ($sectionElements as $sectionElement) {
          try {
            $data = hub_builder_get_section_data($term, $sectionElement, $xpath);
            $validSections++;
          } catch (Exception $e) {
            $invalidSections++;
            $errors[] = $e->getMessage();
          }

          try {
            $info = casmm_group_mapper_get_info_for_group_external_id($data['instructorGroupDN']);
            if (empty($exampleInstructorId)) {
              if (!empty($info['id'])) {
                $instructors = mm_content_get_users_in_group($info['id'], NULL, FALSE, 1);
                if (count($instructors)) {
                  $exampleInstructorId = key($instructors);
                  $exampleInstructorName = current($instructors);
                }
              }
              else {
                $missingGroups[] = $data['instructorGroupDN'];
              }
            }
          } catch (Exception $e) {
            $missingGroups[] = $data['instructorGroupDN'];
          }
          try {
            $info = casmm_group_mapper_get_info_for_group_external_id($data['classGroupDN']);
            if (empty($info['id']))
              $missingGroups[] = $data['classGroupDN'];
          } catch (Exception $e) {
            $missingGroups[] = $data['classGroupDN'];
          }
        }
      }
    }
    if (!$subjectsWithSections)
      throw new Exception("All subjects are empty, none have sections.");
    $result['content'] = t("@with of @total subjects contain sections. <br/>@sections sections were found. @valid sections were valid and @invalid sections had errors.", array('@with' => $subjectsWithSections, '@total' => count($subjects), '@sections' => $totalSections, '@valid' => $validSections, '@invalid' => $invalidSections));
    if (count($errors) > 5) {
      $errors = array_slice($errors, 0, 5);
      $errors[] = '...';
    }
    if (count($errors)) {
      $result['content'] .= "\n<br/><strong>Errors:</strong>\n<br/>" . implode("\n<br/>", $errors);
    }
    $result['success'] = ($invalidSections == 0);
  } catch (Exception $e) {
    $result['content'] = $e->getMessage();
    $result['success'] = false;
  }
  $results[] = $result;

  $result = array('title' => "Main Data Url: Groups");
  if (count($missingGroups)) {
    $result['success'] = false;
    $result['content'] = count($missingGroups) . " class-groups are missing: <br/><br/>" . implode("\n<br/>", $missingGroups);
  }
  else {
    $result['success'] = true;
    $result['content'] = t('All class groups exist');
  }
  $results[] = $result;

  /*********************************************************
   * Instructor Course list URL
   *********************************************************/
  $result = array('title' => "Instructor Course List Url: Validation");
  try {
    if (empty($exampleInstructorId))
      throw new Exception("No instructor was found in any course section in this term.");

    $instructor = user_load($exampleInstructorId);
    $url = $term->getInstructorCourseListUrl($instructor->init);
    $result['success'] = is_string(filter_var($url, FILTER_VALIDATE_URL));
    $result['content'] = t('Instructor: @id (@name) <br/> @url', array('@id' => $exampleInstructorId, '@name' => $exampleInstructorName, '@url' => $url));
  } catch (Exception $e) {
    $result['content'] = $e->getMessage();
    $result['success'] = false;
  }
  $results[] = $result;

  $result = array('title' => "Instructor Course List Url: XML Response");
  try {
    $xpath = hub_builder_get_xpath($url);
    $result['content'] = t('Successfully loaded the data document');
    $result['success'] = true;
  } catch (Exception $e) {
    $result['content'] = $e->getMessage();
    $result['success'] = false;
  }
  $results[] = $result;

  $result = array('title' => "Instructor Course List Url: Includes Subjects");
  try {
    if (empty($xpath))
      throw new Exception("Not continuing test due to previoius errors.");

    $subjects = hub_builder_get_subjects($xpath);
    if (!is_array($subjects))
      throw new Exception("Subjects should have been an array.");
    if (!count($subjects))
      throw new Exception("No subjects found.");

    ob_start();
    print count($subjects) . ' subjects found: ';
    $i = 0;
    print "<pre>";
    foreach ($subjects as $subject) {
      print_r($subject);
      $i++;
      if ($i >= 4)
        break;
    }
    if (count($subjects) > 4)
      print "\n...";
    print "</pre>";
    $result['content'] = ob_get_clean();
    $result['success'] = true;
  } catch (Exception $e) {
    $result['content'] = $e->getMessage();
    $result['success'] = false;
  }
  $results[] = $result;

  $result = array('title' => "Instructor Course List Url: Sections");
  try {
    if (empty($subjects))
      throw new Exception("Not continuing test due to previoius errors.");
    $subjectsWithSections = 0;
    $totalSections = 0;
    $validSections = 0;
    $invalidSections = 0;
    $sectionInfo = array();
    $errors = array();
    foreach ($subjects as $subject) {
      $sectionElements = hub_builder_get_section_elements_in_subject($xpath, $subject['id']);
      if ($sectionElements->length) {
        $subjectsWithSections++;
        $totalSections += $sectionElements->length;
        foreach ($sectionElements as $sectionElement) {
          try {
            $data = hub_builder_get_section_data($term, $sectionElement, $xpath);
            $sectionInfo[] = $data['uniqueId'] . ' ' . $data['offeringId'] . ' ' . $data['title'] . ' - ' . $data['genusTypeName'];
            $validSections++;
          } catch (Exception $e) {
            $invalidSections++;
            $errors[] = $e->getMessage();
          }
        }
      }
    }
    if (!$subjectsWithSections)
      throw new Exception("All subjects are empty, none have sections.");
    $result['content'] = t("@with of @total subjects contain sections. <br/>@sections sections were found. @valid sections were valid and @invalid sections had errors.", array('@with' => $subjectsWithSections, '@total' => count($subjects), '@sections' => $totalSections, '@valid' => $validSections, '@invalid' => $invalidSections));

    if (count($sectionInfo) > 10) {
      $sectionInfo = array_slice($sectionInfo, 0, 10);
      $sectionInfo[] = '...';
    }
    if (count($sectionInfo)) {
      $result['content'] .= "\n<br/><strong>Sections:</strong>\n<br/>" . implode("\n<br/>", $sectionInfo);
    }

    if (count($errors) > 5) {
      $errors = array_slice($errors, 0, 5);
      $errors[] = '...';
    }
    if (count($errors)) {
      $result['content'] .= "\n<br/><strong>Errors:</strong>\n<br/>" . implode("\n<br/>", $errors);
    }
    $result['success'] = ($invalidSections == 0);
  } catch (Exception $e) {
    $result['content'] = $e->getMessage();
    $result['success'] = false;
  }
  $results[] = $result;



  $title = t('Configuration tests for: @name (@id)', array('@name' => $term->display_name, '@id' => $term->id));
  return theme('hub_builder_term_tests', $title, $results);
}

/**
 * Theme the term tests
 *
 * @ingroup themeable
 */
function theme_hub_builder_term_tests($display_name, $results) {
  drupal_add_css(drupal_get_path('module', 'hub_builder') . '/hub_builder_terms_admin.css');

  ob_start();
  print "\n<h1 class='term_test_header'>" . $display_name . "</h1>";
  foreach ($results as $result) {
    print "\n<div class='term_test term_test_" . ((empty($result['success']))?"failure":"success") . "'>";
    print "\n\t<h2>" . $result['title'] . "</h2>";
    print "\n\t<div class='term_test_content'>" . $result['content'] . "</div>";
    print "\n</div>";
  }
  return ob_get_clean();
}
