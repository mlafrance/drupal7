<?php
/**
 * @file
 * Configure and run updates from remote resources.
 */

/**
 * Implements hook_menu().
 */
function moodle_resource_menu() {
  $items = array();

  $items['admin/course_hub/resources/moodle'] = array(
    'title' => 'Moodle Resource',
    'description' => 'Configure the Moodle Resource.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('moodle_resource_admin_settings'),
    'access arguments' => array('administer site configuration'),
    'type' => MENU_NORMAL_ITEM,
    'weight' => 10,
  );

  return $items;
}


/**
 * Form builder. Configure Course Hub Updates
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function moodle_resource_admin_settings() {
  $form['connection'] = array(
    '#type' => 'fieldset',
    '#title' => t('Moodle Connection Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['connection']['moodle_resource_enable'] = array(
    '#type' => 'radios',
    '#title' => t('Enable Connection'),
    '#options' => array(
      1 => t('Enabled'),
      0 => t('Disabled. No creation, validation or synchronization will be done.'),
    ),
    '#default_value' => variable_get('moodle_resource_enable', 1),
    '#description' => 'If disabled only links to existing Moodle sites will be made. No validation of site existance will be performed on Resource-save.',
  );

  $form['connection']['moodle_resource_wsdl'] = array(
    '#type' => 'textfield',
    '#size' => 80,
    '#title' => t('Moodle SOAP WSDL'),
    '#default_value' => variable_get('moodle_resource_wsdl', 'http://moodle.example.edu/wspp/wsdl_pp2.php'),
    '#description' => 'The URL to the Moodle SOAP service\'s WSDL file.',
  );

  $form['connection']['moodle_resource_soap_user'] = array(
    '#type' => 'textfield',
    '#title' => t('SOAP User'),
    '#default_value' => variable_get('moodle_resource_soap_user', ''),
    '#description' => 'The username to use when communicating with Moodle via SOAP.',
  );

  $form['connection']['moodle_resource_soap_password'] = array(
    '#type' => 'textfield',
    '#title' => t('SOAP Password'),
    '#default_value' => variable_get('moodle_resource_soap_password', ''),
    '#description' => 'The password for the user above.',
  );


  $form['other'] = array(
    '#type' => 'fieldset',
    '#title' => t('Other Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['other']['moodle_resource_base_url'] = array(
    '#type' => 'textfield',
    '#size' => 80,
    '#title' => t('Moodle Base URL'),
    '#default_value' => variable_get('moodle_resource_base_url', 'http://moodle.middlebury.edu/'),
    '#description' => 'The URL to the Moodle installation. Used to build links to courses.',
  );

  $form['other']['moodle_resource_sync_frequency'] = array(
    '#type' => 'textfield',
    '#size' => 10,
    '#title' => t('Enrollment Sync Frequency'),
    '#default_value' => variable_get('moodle_resource_sync_frequency', 10800),
    '#description' => 'The number of seconds between each user synchronization. E.g. 3600 (1 hour), 7200 (2 hours), 10800 (3 hours). User synchronization will also happen whenever a Moodle Resource is saved, so this is just to capture new adds or drops.',
  );

  $form['other']['moodle_resource_max_bytes'] = array(
    '#type' => 'textfield',
    '#size' => 10,
    '#title' => t('Max Bytes'),
    '#default_value' => variable_get('moodle_resource_max_bytes', 52428800),  // 50 MB
    '#description' => 'This setting defines the largest size of file that can be uploaded by students in this course, limited by the site wide setting created by the administrator.',
  );

  return system_settings_form($form);
}