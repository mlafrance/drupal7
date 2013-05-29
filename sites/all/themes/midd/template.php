<?php

/**
 * Implements hook_preprocess_html().
 */
function midd_preprocess_html(&$vars) {
  $args = arg();
  if (!empty($args[1])) {
    //$vars['classes_array'][] = middlebury_get_color_scheme($args[1]);
  }

  if ($vars['is_front']) {
    $vars['classes_array'][] = 'homepage';
    $vars['attributes_array']['id'] = 'midd_homepage';
  }
}

/**
 * Implements hook_preprocess_page().
 */
function midd_preprocess_page(&$vars) {
  if ($vars['is_front']) {
    drupal_add_js(base_path() . 'middlebury_story/get/Home');
    drupal_add_library('system', 'effects');
  }
}