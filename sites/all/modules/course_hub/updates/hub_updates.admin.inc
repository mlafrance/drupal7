<?php
// $Id$

/**
 * @file
 * Configure and run updates from remote resources.
 */

/**
 * Implements hook_menu().
 */
function hub_updates_menu() {
  $items = array();

  $items['admin/course_hub/updates'] = array(
    'title' => t('Update Fetching'),
    'description' => t('Configure and run updates from remote resources.'),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('hub_updates_admin_settings'),
    'access arguments' => array('administer site configuration'),
    'type' => MENU_NORMAL_ITEM,
  );

  $items['admin/course_hub/updates/settings'] = array(
    'title' => t('Settings'),
    'description' => t('Configure updates from remote resources.'),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('hub_updates_admin_settings'),
    'access arguments' => array('administer site configuration'),
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'weight' => 1,
  );

  $items['admin/course_hub/updates/fetch'] = array(
    'title' => t('Fetch'),
    'description' => t('Fetch new updates.'),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('hub_updates_fetch_form'),
    'access arguments' => array('administer site configuration'),
    'type' => MENU_LOCAL_TASK,
    'weight' => 3,
  );

  $items['admin/course_hub/updates/disable'] = array(
    'title' => t('Enable/Disable'),
    'description' => t('Enable or disable updates for terms.'),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('hub_updates_disable_form'),
    'access arguments' => array('administer site configuration'),
    'type' => MENU_LOCAL_TASK,
    'weight' => 4,
  );

  return $items;
}


/**
 * Form builder. Configure Course Hub Updates
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function hub_updates_admin_settings() {
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Automatic Fetching'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['settings']['hub_updates_fetch_via_cron'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable update fetching via Cron'),
    '#default_value' => variable_get('hub_updates_fetch_via_cron', 0),
    '#description' => 'If unchecked, updates will only be fetched manually and not durning cron runs.',
  );

  $form['settings']['hub_updates_frequency'] = array(
    '#type' => 'textfield',
    '#title' => t('Update frequency'),
    '#size' => 6,
    '#default_value' => variable_get('hub_updates_frequency', '15'),
    '#description' => 'The number of minutes between fetching updates.',
  );

  $form['settings']['hub_updates_max_per_fetch'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum number to fetch each run'),
    '#size' => 6,
    '#default_value' => variable_get('hub_updates_max_per_fetch', ''),
    '#description' => 'The maximum number of course sites whose updates should be fetched each cron run. Leave empty for no limit (default). Set a limit here if your cron runs are timing out while fetching too many updates. Setting a limit here can also help stagger your fetches so that they are not all fetching at the same time.',
  );

  return system_settings_form($form);
}

/**
 * Form builder. Fetch Course Hub Updates
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function hub_updates_fetch_form() {

  $form['submit'] = array(
    '#type' => 'submit',
    '#title' => t('Fetch Updates'),
    '#default_value' => t('Fetch Updates'),
    '#description' => 'Fetch all enabled updates.',
  );

  $form['#submit'] = array('hub_updates_fetch');

  return $form;
}

/**
 * Form builder. Disable Course Hub Updates
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function hub_updates_disable_form() {

  $form['toggle_direction'] = array(
    '#type' => 'radios',
    '#title' => t('Enable/Disable'),
    '#options' => array('enable' => t('Enable'), 'disable' => t('Disable')),
    '#default_value' => 'disable',
    '#description' => 'Should we Enable or Disable update fetching?',
  );

  $form['path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path'),
    '#size' => 80,
    '#default_value' => 'MCUG/2010-2011/fall',
    '#description' => 'The path under which updates will be enabled/disabled.',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#title' => t('Submit'),
    '#default_value' => t('Submit'),
  );

  $form['#submit'] = array('hub_updates_disable_submit');

  return $form;
}

/**
 * Handle submissions of the Enable/Disable form.
 */
function hub_updates_disable_submit (&$form, &$form_state) {
  $mmtid = course_hub_tid_from_path($form_state['values']['path']);
  if (!$mmtid) {
    drupal_set_message(t('Path not found: @path', array('@path' => $form_state['values']['path'])), 'error');
    return;
  }

  if ($form_state['values']['toggle_direction'] == 'enable') {
    hub_updates_enable_update_fetching($mmtid);
  } else {
    hub_updates_disable_update_fetching($mmtid);
  }
}
