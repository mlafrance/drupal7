<?php

/**
 * Form builder. Configure Course Hub Catalogs
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function hub_builder_catalogs_form(&$form_state) {
//   var_dump(__FUNCTION__);
//   var_dump($form_state);
  $form = array('#tree' => TRUE);
  foreach (hub_builder_get_catalogs() as $catalog) {
    $form[$catalog->id] = _hub_builder_catalog_fieldset($catalog);
  }
  if (!empty($form_state['storage']['add_new'])) {
    $catalog = new stdClass();
    $catalog->id = '';
    $catalog->class_group_base_dn = 'OU=Classes,OU=Groups,DC=example,DC=edu';
    $catalog->main_data_url = 'http://catalog.example.edu/offerings/searchxml/catalog/[CATALOG_ID]/term/[TERM_ID]';
    $catalog->instructor_course_list_url = 'http://catalog.example.edu/offerings/instructorxml/catalog/[CATALOG_ID]/term/[TERM_ID]/instructor/[INSTRUCTOR_ID]';
    $catalog->types_to_import = array('genera:offering/LCT', 'genera:offering/SEM');

    $form['new'] = _hub_builder_catalog_fieldset($catalog);
    $form['new']['#title'] = t('New Catalog');
    $form['new']['#collapsible'] = FALSE;
    $form['new']['#collapsed'] = FALSE;

  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Changes'),
  );
  $form['add_catalog'] = array(
    '#type' => 'submit',
    '#value' => t('Add a Catalog'),
    '#validate' => array('hub_builder_catalogs_form_add_new'),
  );
  if (!empty($form_state['storage']['add_new'])) {
    $form['add_catalog']['#disabled'] = TRUE;
  }
  return $form;
}

function hub_builder_catalogs_form_add_new($form, &$form_state) {
  $form_state['storage']['add_new'] = TRUE;
  $form_state['rebuild'] = TRUE; // Will cause the default submit function
                                 // to be skipped.
}

function hub_builder_catalogs_form_delete($form, &$form_state) {
  $catalog_id = $form_state['clicked_button']['#parents'][0];
  $catalog = hub_builder_get_catalog($catalog_id);
  $catalog->delete();
  $form_state['rebuild'] = TRUE; // Will cause the default submit function
                                 // to be skipped.
}

/**
 * Form builder. Configure Course Hub Catalogs
 *
 * @ingroup forms
 * @see system_settings_form().
 */
// function hub_builder_catalogs_form_validate($form, &$form_state) {
//   return TRUE;
// }

/**
 * Form builder. Configure Course Hub Catalogs
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function hub_builder_catalogs_form_submit($form, &$form_state) {

  foreach (hub_builder_get_catalogs() as $catalog) {
    $values = $form_state['values'][$catalog->id];
    $types_to_import = array_map('trim', explode("\n", trim($values['types_to_import'])));
    $catalog->id = $values['id'];
    $catalog->class_group_base_dn = $values['class_group_base_dn'];
    $catalog->main_data_url = $values['main_data_url'];
    $catalog->instructor_course_list_url = $values['instructor_course_list_url'];
    $catalog->types_to_import = $types_to_import;
    $catalog->save();
  }

  if (!empty($form_state['values']['new'])) {
    $values = $form_state['values']['new'];
    $types_to_import = array_map('trim', explode("\n", trim($values['types_to_import'])));
    $catalog = new HubBuilder_Catalog();
    $catalog->id = $values['id'];
    $catalog->class_group_base_dn = $values['class_group_base_dn'];
    $catalog->main_data_url = $values['main_data_url'];
    $catalog->instructor_course_list_url = $values['instructor_course_list_url'];
    $catalog->types_to_import = $types_to_import;
    $catalog->save();

    $form_state['storage']['add_new'] = FALSE;
  }
}

function _hub_builder_catalog_fieldset($catalog = NULL) {
  $fieldset = array(
    '#type' => 'fieldset',
    '#title' => t('@id', array('@id' => $catalog->id)),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $fieldset['id'] = array(
    '#title' => t('Catalog Id'),
    '#type' => 'textfield',
    '#default_value' => $catalog->id,
    '#size' => 25,
  );

  $fieldset['class_group_base_dn'] = array(
    '#title' => t('Class Group Base DN'),
    '#description' => 'The baseDN that should be appended to course codes to form course-group DNs.',
    '#type' => 'textfield',
    '#default_value' => $catalog->class_group_base_dn,
    '#size' => 110,
    '#maxlength' => 255,
  );

  $fieldset['main_data_url'] = array(
    '#title' => t('Main Course Data URL'),
    '#description' => 'The URL of the feed for all course sites to be generated. This should be limited to a single term search of all lectures and seminar sections (or a sub-set of these). Use placeholders [CATALOG_ID] and [TERM_ID] in the URL to have these replaced when building this URL for a specific term.',
    '#type' => 'textfield',
    '#default_value' => $catalog->main_data_url,
    '#size' => 110,
    '#maxlength' => 255,
  );

  $fieldset['instructor_course_list_url'] = array(
    '#title' => t('Instructor Course-List URL'),
    '#description' => 'The URL of the feed for the course sites taught by an instructor in a given term. Use placeholders [CATALOG_ID], [TERM_ID], and [INSTRUCTOR_ID] in the URL to have these replaced when building this URL for a specific term.',
    '#type' => 'textfield',
    '#default_value' => $catalog->instructor_course_list_url,
    '#size' => 110,
    '#maxlength' => 255,
  );

  $fieldset['types_to_import'] = array(
    '#title' => t('Course Types to Import'),
    '#description' => 'Course sections with types other than those listed here (one type-id per line) will be skipped on import and have to be individually requested by the instructor',
    '#type' => 'textarea',
    '#default_value' => implode("\n", $catalog->types_to_import),
    '#cols' => 110,
    '#rows' => 5,
  );

  if ($catalog->id) {
    $fieldset['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete this catalog'),
      '#validate' => array('hub_builder_catalogs_form_delete'),
    );
    if ($catalog->getNumTerms()) {
      $fieldset['delete']['#disabled'] = TRUE;
      $fieldset['delete']['#attributes']['title'] = t("Terms connected to this catalog must be deleted first.");
    }
  }

  return $fieldset;
}