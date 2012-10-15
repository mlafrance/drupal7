<?php
// $Id$

/**
 * @file
 * Configure and run updates from remote resources.
 */

/**
 * Implements hook_menu().
 */
function wordpress_resource_menu() {
  $items = array();

  $items['admin/course_hub/resources/wordpress'] = array(
    'title' => 'WordPress Resource',
    'description' => 'Configure the Wordpress Resource.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('wordpress_resource_admin_settings'),
    'access arguments' => array('administer site configuration'),
    'type' => MENU_NORMAL_ITEM,
    'weight' => 11,
  );

  return $items;
}


/**
 * Form builder. Configure Course Hub Updates
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function wordpress_resource_admin_settings() {
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Course Hub update settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['settings']['wordpress_resource_scheme'] = array(
    '#type' => 'radios',
    '#title' => t('Scheme'),
    '#options' => array('http' => 'http://', 'https' => 'https://'),
    '#default_value' => variable_get('wordpress_resource_scheme', 'http'),
    '#description' => 'The URL Scheme',
  );
  $form['settings']['wordpress_resource_host'] = array(
    '#type' => 'textfield',
    '#title' => t('Host'),
    '#size' => 25,
    '#default_value' => variable_get('wordpress_resource_host', 'blogs.middlebury.edu'),
    '#description' => 'The wordpress host.',
  );
  $form['settings']['wordpress_resource_base_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Base Path'),
    '#size' => 25,
    '#default_value' => variable_get('wordpress_resource_base_path', '/'),
    '#description' => 'The root path of the wordpress installation.',
  );
  $form['settings']['wordpress_resource_is_subdomain_install'] = array(
    '#type' => 'radios',
    '#title' => t('Subdomain or Subdirectory installation?'),
    '#options' => array(0 => 'Subdirectories', 1 => 'Subdomains'),
    '#default_value' => variable_get('wordpress_resource_is_subdomain_install', '0'),
    '#description' => 'Choose whether blogs are subdomains (e.g. blog1.example.com, blog2.example.com) or subdirectories (e.g. blogs.example.com/blog1/, blogs.example.com/blog2/)',
  );
  $form['settings']['rss_authentication'] = array(
    '#type' => 'fieldset',
    '#title' => t('Wordpress RSS Authentication'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['settings']['rss_authentication']['key'] = array(
    '#type' => 'fieldset',
    '#title' => t('GET Parameter[s]'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => 'Configure if your wordpress allows authenticated access to RSS feeds when a particular GET parameter is passed.',
  );
  $form['settings']['rss_authentication']['key']['wordpress_resource_auth_param'] = array(
    '#type' => 'textfield',
    '#title' => t('Authentication Parameter'),
    '#size' => 25,
    '#default_value' => variable_get('wordpress_resource_auth_param', ''),
    '#description' => 'A key-value pair. Example: VIEW_ALL_RSS_KEY=8423jsf08u2lsdf02 or multiple parameters: key1=value1&key2=value2',
  );
  $form['settings']['rss_authentication']['http'] = array(
    '#type' => 'fieldset',
    '#title' => t('Username/Password'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => 'Configure if your wordpress allows authenticated access to RSS feeds when a username and passed via http authentication. Example: http://username:password@blogs.example.com/blogname/feed/',
  );
  $form['settings']['rss_authentication']['http']['wordpress_resource_http_user'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#size' => 25,
    '#default_value' => variable_get('wordpress_resource_http_user', ''),
//     '#description' => '',
  );
  $form['settings']['rss_authentication']['http']['wordpress_resource_http_pass'] = array(
    '#type' => 'textfield',
    '#title' => t('Password'),
    '#size' => 25,
    '#default_value' => variable_get('wordpress_resource_http_pass', ''),
//     '#description' => '',
  );

  return system_settings_form($form);
}