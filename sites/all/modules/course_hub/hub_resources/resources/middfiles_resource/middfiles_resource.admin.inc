<?php
/**
 * @file
 * Configure and run updates from remote resources.
 */


/**
 * Form builder. Configure Middfiles resource
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function middfiles_resource_admin_settings() {
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Middfiles Connection Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['settings']['middfiles_resource_base_url'] = array(
    '#type' => 'textfield',
    '#size' => 80,
    '#title' => t('Middfiles Base URL'),
    '#default_value' => variable_get('middfiles_resource_base_url', 'https://middfiles.middlebury.edu/Classes/'),
    '#description' => 'The base-URL for WebDAV access.',
  );

  $form['settings']['middfiles_resource_base_fs_path'] = array(
    '#type' => 'textfield',
    '#size' => 80,
    '#title' => t('Middfiles File-system Path'),
    '#default_value' => variable_get('middfiles_resource_base_fs_path', '/mnt/classes/'),
    '#description' => 'The base-URL for file-system access.',
  );

  $form['settings']['middfiles_resource_scan_interval'] = array(
    '#type' => 'textfield',
    '#size' => 10,
    '#title' => t('Middfiles Scan Interval'),
    '#default_value' => variable_get('middfiles_resource_scan_interval', 3600),
    '#description' => 'The minimum number of seconds between each scan of Middfiles. During the scan, if the HANDOUTS or SHARE directories for a class contain files a Middfiles Resource will automatically be added.',
  );

  $form['middfiles_resource_terms_enabled'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Terms to scan for files'),
    '#default_value' => variable_get('middfiles_resource_terms_enabled', array()),
    '#description' => 'The checked terms will be scanned for files and if files are found but not Middfiles Resource exists, then a Middfiles Resource will be automatically added.',
  );
  $terms = hub_builder_get_terms();
  foreach ($terms as $term) {
    $form['middfiles_resource_terms_enabled']['#options'][$term->id] = t('@catalog: @name (@id)', array('@name' => $term->display_name, '@id' => $term->id, '@catalog' => $term->catalog_id));
  }

  return system_settings_form($form);
}