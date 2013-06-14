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

  $variables['classes_array'][] = monster_menus_custom_theme();
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
 * Prepares variables for node--donors.tpl.php
 *
 * @see node.tpl.php
 */
function midd_preprocess_node__donors(&$variables) {
  $wrapper = $variables['node'];
  try {
    $wrapper = entity_metadata_wrapper('node', $variables['node']);
  } catch(UnexpectedValueException $e) {
  }

  try {
    $conn = '';
    try {
      $conn = new PDO('oci:dbname=' . MIDDLEBURY_BANNER_SNAP, MIDDLEBURY_BANNER_USER, MIDDLEBURY_BANNER_PASS);
    } catch(Exception $ex) {
      $conn = new PDO('oci:dbname=' . MIDDLEBURY_BANNER_PNTR, MIDDLEBURY_BANNER_USER, MIDDLEBURY_BANNER_PASS);
    }

    $ug = $table = '';

    $rolltype = $wrapper->field_rolltype->value();
    switch ($rolltype) {
      case 'Parents':
        $table = 'AYBDNPR';
        break;
      case 'Language School Alumni':
        $table = 'AYBDNLS';
        break;
      case 'Bread Loaf Alumni':
        $table = 'AYBDNBW';
        break;
      case 'Faculty and Staff':
        $table = 'AYBDNFS';
        break;
      case '1800 Society':
        $table = 'AYBDNFS';
        break;
      default:
        $table = 'AYBDNRL';
        break;
    }

    if ($rolltype == 'Undergraduates') {
      $comm = $conn->prepare('SELECT * FROM ALUMNI_MIDD.AYBCLRC WHERE AYBCLRC_CLASS = :year AND AYBCLRC_ROLL_YEAR = :rollyear ORDER BY UPPER(AYBCLRC_SORT_NAME)');
      $comm->bindValue(':year', $wrapper->field_year->value());
      $comm->bindValue(':rollyear', $wrapper->field_rollyear->value());
      $comm->execute();
      foreach ($comm->fetchAll() as $donor) {
        $name = $donor['AYBCLRC_DONOR_NAME'];

        $is_reunion = ($wrapper->field_rollyear->value() - $wrapper->field_year->value()) % 5 == 0;

        if (!empty($donor['AYBCLRC_CO_CHAIR_IND']) && $donor['AYBCLRC_CO_CHAIR_IND'] == 'Y' && $is_reunion) {
          $name .= ' (Co-chair)';
        }

        if (!empty($donor['AYBCLRC_LEAD_CLASS_AGENT']) && $donor['AYBCLRC_LEAD_CLASS_AGENT'] == 'Y' && !$is_reunion) {
          $name .= ' (Lead)';
        }

        if (!empty($donor['AYBCLRC_DECEASED_IND']) && $donor['AYBCLRC_DECEASED_IND'] == 'Y') {
          $name .= ' (deceased)';
        }

        if (!empty($donor['AYBCLRC_CANE_REPRESENTATIVE']) && $donor['AYBCLRC_CANE_REPRESENTATIVE'] == 'Y') {
          $variables['cane'][] = $name;
        }

        if ($is_reunion) {
          if (!empty($donor['AYBCLRC_CO_CHAIR_IND']) && $donor['AYBCLRC_CO_CHAIR_IND'] == 'Y') {
            $name = '<b>' . $name . '</b>';
          }

          $variables['reunion'][] = $name;
        }
        else {
          if (!empty($donor['AYBCLRC_CLASS_AGENT']) && $donor['AYBCLRC_CLASS_AGENT'] == 'Y') {
            $name = '<b>' . $name . '</b>';
          }

          $variables['agent'][] = $name;
        }
      }

      $ug = $conn->prepare('SELECT * FROM ALUMNI_MIDD.AYBDNRL WHERE AYBDNRL_CLASS = :year AND AYBDNRL_ROLL_YEAR = :rollyear ORDER BY UPPER(AYBDNRL_SORT_NAME)');
      $ug->bindValue(':year', $wrapper->field_year->value());
      $ug->bindValue(':rollyear', $wrapper->field_rollyear->value());
      $ug->execute();
    }
    else {
      $ug = $conn->prepare('SELECT * FROM ALUMNI_MIDD.' . $table . ' WHERE ' . $table . '_ROLL_YEAR = :rollyear ORDER BY UPPER(' . $table . '_SORT_NAME)');
      $ug->bindValue(':rollyear', $wrapper->field_rollyear->value());
      $ug->execute();
    }

    foreach ($ug->fetchAll() as $donor) {
      $name = $donor[$table . '_DONOR_NAME'];

      if (!empty($donor[$table . '_CANE_SOCIETY_IND']) && $donor[$table . '_CANE_SOCIETY_IND'] == 'Y') {
        $name .= '<img src="' . base_path() . drupal_get_path('theme', 'midd') . '/images/1800_icon_STAR.png" />';
      }

      if (!empty($donor[$table . '_WIDOW_WIDOWER_IND']) && $donor[$table . '_WIDOW_WIDOWER_IND'] == 'Y') {
        $name .= ' (W)';
      }

      if (!empty($donor[$table . '_HONORARY_IND']) && $donor[$table . '_HONORARY_IND'] == 'Y') {
        $name .= ' (H)';
      }

      if (!empty($donor[$table . '_DECEASED_IND']) && $donor[$table . '_DECEASED_IND'] == 'Y') {
        $name .= ' (deceased)';
      }

      if (!empty($donor[$table . '_GOOD_GIVER_IND']) && $donor[$table . '_GOOD_GIVER_IND'] == 'Y') {
        $name = '<b>' . $name . '</b>';
      }

      if (!empty($donor[$table . '_1800_SOCIETY_IND']) && $donor[$table . '_1800_SOCIETY_IND'] == 'Y') {
        $name .= '<img src="' . base_path() . drupal_get_path('theme', 'midd') . '/images/1800_icon.png" />';
      }

      if ($rolltype != 'Undergraduates' && !empty($donor[$table . '_DONOR_NAME'])) {
        if (!empty($donor[$table . '_EXEC_COMM_IND']) && $donor[$table . '_EXEC_COMM_IND'] == 'Y') {
          $variables['exec'][] = $donor[$table . '_DONOR_NAME'];
        }

        if (!empty($donor[$table . '_PARENTS_COMM_IND']) && $donor[$table . '_PARENTS_COMM_IND'] == 'Y') {
          $variables['parents'][] = $donor[$table . '_PARENTS_COMM_IND'];
        }
      }

      $variables['donors'][] = $name;
    }
  } catch (Exception $e) {
    // Log the error to the php error log rather than watchdog for monitoring by
    // system admins when they help troubleshoot.
    user_error($e->getMessage(), E_USER_WARNING);
  }

  if ('2013' == $wrapper->field_year->value()) {
    $variables['reunion_title'] = 'Senior Class Gift Committee Member';
  }
  else {
    $variables['reunion_title'] = 'Reunion Committee Member';
  }

  if (!empty($variables['reunion']) && count($variables['reunion']) > 1) {
    $variables['reunion_title'] .= 's';
  }

  $variables['agent_title'] = !empty($variables['agent']) && count($variables['agent']) > 1 ? 'Class Agents' : 'Class Agent';

  $variables['cane_title'] = !empty($variables['cane']) && count($variables['cane']) > 1 ? 'Cane Society Representatives' : 'Cane Society Representative';

  $variables['donors_title'] = !empty($variables['donors']) && count($variables['donors']) > 1 ? 'Donors' : 'Donor';
}

/**
 * Prepares variables for node--qa.tpl.php
 *
 * @see node.tpl.php
 */
function midd_preprocess_node__qa(&$variables) {
  $wrapper = $variables['node'];
  try {
    $wrapper = entity_metadata_wrapper('node', $variables['node']);
  } catch(UnexpectedValueException $e) {
  }

  $selector = preg_replace("/[^a-zA-Z0-9\.\*#>\+~:\[\]\(\)\-_=;&,!\^$|\/\s]/", "", $wrapper->field_selector->value());
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
  drupal_add_library('system', 'ui');
  drupal_add_library('system', 'effects');

  $page = mm_content_get(arg(1), array(MM_GET_FLAGS));

  if ($variables['is_front'] || (!empty($page->flags) && in_array('has_waveform', array_keys($page->flags)))) {
    drupal_add_js(base_path() . 'middlebury_story/get/' . ($variables['is_front'] ? 'Home' : drupal_get_title()));
  }
}