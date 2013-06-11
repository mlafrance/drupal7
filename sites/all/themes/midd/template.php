<?php

/**
 * Returns HTML for a breadcrumb.
 *
 * @param array $variables
 *   An associative array containing:
 *   - breadcrumb: An array containing the breadcrumb links.
 *
 * @ingroup themeable
 */
function midd_breadcrumb($variables) {
  if (!empty($variables)) {
    $breadcrumb = $variables['breadcrumb'];
    $title = drupal_get_title();
    if (!empty($title)) {
      $breadcrumb[] = $title;
    }
    return '<nav class="breadcrumb">' . implode(' &raquo; ', $breadcrumb) . '</nav>';
  }
}

/**
 * Prepares variables for html.tpl.php.
 *
 * @see html.tpl.php
 */
function midd_preprocess_html(&$variables) {
  $args = arg();
  if (!empty($args[1])) {
    $variables['classes_array'][] = middlebury_get_color_scheme($args[1]);
  }

  if ($variables['is_front']) {
    $variables['classes_array'][] = 'homepage';
    $variables['attributes_array']['id'] = 'midd_homepage';
  }
}

/**
 * Prepares variables for node.tpl.php
 *
 * @see node.tpl.php
 */
function midd_preprocess_node(&$variables) {
  $function = __FUNCTION__ . '__' . $variables['node']->type;
  if (function_exists($function)) {
    $function($variables);
  }
}

/**
 * Prepares variables for node--donation_thermometer.tpl.php
 *
 * @see node.tpl.php
 */
function midd_preprocess_node__donation_thermometer(&$variables) {
  drupal_add_js(drupal_get_path('theme', 'midd') . '/scripts/donation_thermometer.js');

  $variables['currency'] = '$';

  $wrapper = $variables['node'];
  try {
    $wrapper = entity_metadata_wrapper('node', $variables['node']);
  } catch(UnexpectedValueException $e) {
  }

  $target = $wrapper->field_donation_target->value();
  $amount = $wrapper->field_donation_amount->value();
  if (!empty($target) && !empty($amount)) {
    $variables['percent'] = ($amount/$target)*100;
  }

  $type = $wrapper->field_donation_type->value();
  $variables['type'] = empty($type) ? "classic-m" : $type;
}

/**
 * Prepares variables for node--qa.tpl.php
 *
 * @see node.tpl.php
 */
function midd_preprocess_node__qa(&$variables) {
  $selector = preg_replace("/[^a-zA-Z0-9\.\*#>\+~:\[\]\(\)\-_=;&,!\^$|\/\s]/", "", $variables['node']->field_selector['und'][0]['value']);
  $script = "jQuery(function() { jQuery('input.quickaccess').quickaccess({selector:'" . $selector . "',maxresults:15}); });";
  drupal_add_js($script, 'inline');
  drupal_add_js(drupal_get_path('theme', 'midd') . '/scripts/quickaccess.js');
}

/**
 * Prepares variables for page.tpl.php
 *
 * @see page.tpl.php
 */
function midd_preprocess_page(&$variables) {
  $page = mm_content_get(arg(1), array(MM_GET_FLAGS));

  if ($variables['is_front'] || (!empty($page->flags) && in_array('has_waveform', array_keys($page->flags)))) {
    drupal_add_js(base_path() . 'middlebury_story/get/' . ($variables['is_front'] ? 'Home' : drupal_get_title()));
    drupal_add_library('system', 'ui');
    drupal_add_library('system', 'effects');
  }
}