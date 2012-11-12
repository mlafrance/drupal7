<?php
/**
 * @file
 * Course Hub Stats screens
 *
 * Provides statistics on Course Hub resource usage and updates.
 */

/**
 * Show graphs of resource utilization.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function course_hub_stats_resource_stats() {
  drupal_add_css(drupal_get_path('module', 'course_hub') . '/stats.css', 'module', 'all', FALSE);

  if (empty($_GET['page'])) {
    $pages = course_hub_stats_get_pages();
    $current_page = key($pages);
  }
  else {
    $pages = course_hub_stats_get_pages($_GET['page']);
    $current_page = $_GET['page'];
  }

  ob_start();
  print "\n<form action='' method='get'>";
  print "\n<label for='term'>Term/Path: </label>";
  print "\n<select name='page' onchange='this.form.submit()'>";
  foreach ($pages as $mmtid => $path) {
    print "\n\t<option value='" . $mmtid . "' " . (($mmtid == $current_page)?'selected="selected"':'') . ">" . $path . "</option>";
  }
  print "\n</select>";
  print "\n</form>";

  $header = array(
    array(
      'data' => 'Module',
      'class' => 'course_hub_stats_table_name',
    ),
    array(
      'data' => 'Usage',
      'class' => 'course_hub_stats_table_graph',
    ),
  );
  $rows = array();
  $stats = array();

  $resource_types = module_invoke_all('hub_get_resource_types');
  // Add syllabus nodes
  $resource_types[] = 'syllabus_text';
  $resource_types[] = 'media';
  array_unshift($resource_types, 'all');

  // Loop through once and build our stats.
  foreach ($resource_types as $type) {
    $stats[$type] = course_hub_stats_get_resource_stats($type, $current_page);
  }
  course_hub_stats_normalize_stats($stats);
  // Loop through a second time and build the graphs
  foreach ($stats as $type => $t_stats) {
    if ($type == 'all') {
      $name = t('Any/All Resources');
    }
    else {
      $name = node_type_get_name($type);
      if ($type == 'media')
        $name = 'Syllabus Upload';
    }

    // Add links to the stats array.
    $stats[$type]['resource_list_url'] = url('admin/course_hub/stats/usage/resources/' . $current_page . '/' . $type);
    $stats[$type]['resource_sites_url'] = url('admin/course_hub/stats/usage/sites/' . $current_page . '/' . $type);
    $stats[$type]['resource_instructors_url'] = url('admin/course_hub/stats/usage/instructors/' . $current_page . '/' . $type);
    $stats[$type]['resource_students_url'] = url('admin/course_hub/stats/usage/students/' . $current_page . '/' . $type);

    $rows[] = array($name, theme('course_hub_stats_bars', $stats[$type]));
  }

  print theme('table', $header, $rows);

  return ob_get_clean();
}

/**
 * Show lists of resource nodes
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function course_hub_stats_resource_list($mmtid, $resource_type) {
  $path = course_hub_get_path($mmtid);
  drupal_set_title(t('%type Resources under @path', array('%type' => node_type_get_name($resource_type), '@path' => $path)), PASS_THROUGH);

  $stats = course_hub_stats_get_resource_stats($resource_type, $mmtid);
  $header = array(
    array(
      'data' => 'Path',
      'class' => 'course_hub_stats_path',
    ),
    array(
      'data' => 'Site',
//       'class' => '',
    ),
    array(
      'data' => 'Node',
//       'class' => '',
    ),
  );
  $rows = array();
  $paths = array();
  foreach ($stats['resource_nids'] as $nid) {
    $row = array();
    try {
      $site_tid = course_hub_get_course_site_tid_for_nid($nid);
      $site_page = mm_content_get($site_tid);
      $path = course_hub_get_path($site_tid);
      $paths[] = $path;
      $row[] = dirname($path);
      $row[] = l($site_page->name, $path);
    } catch (Exception $e) {
      $paths[] = 'error';
      $row[] = 'error';
      $row[] = 'error';
    }
    $node = node_load($nid);
    $row[] = node_view($node, TRUE);
    $rows[] = $row;
  }
  array_multisort($paths, $rows);
  return theme('table', $header, $rows);
}

/**
 * Answer a JSON object containing a list of publicly accessible resources of the specified type.
 */
function course_hub_stats_resource_list_public($mmtid) {
  $cache = cache_get('course_hub_list_public');
  if (!empty($cache->data)) {
    drupal_json(unserialize($cache->data));
  }
  else {
    $resources = array();
    $resource_types = module_invoke_all('hub_get_resource_types');
    foreach ($resource_types as $resource_type) {
      switch ($resource_type) {
        case 'wordpress_resource':
          $select = db_query('field_data_field_wp_sitename', 'w');
          $select->addJoin('LEFT OUTER', 'node', 'n', 'w.entity_id = n.nid');
          $select->addJoin('LEFT OUTER', 'mm_recycle', 'r', 'n.nid = r.id AND r.type = :type', array(':type' => 'node'));
          $select->addJoin('LEFT OUTER', 'mm_node2tree', 'n2t', "n.nid = n2t.nid");
          $select->addJoin('LEFT OUTER', 'mm_tree', 't', "n2t.mmtid = t.mmtid");
          $select->addJoin('LEFT OUTER', 'mm_tree_parents', 'p', "t.mmtid = p.mmtid");
          $select->addField('w', 'field_wp_sitename_value', 'site');
          $select->addField('n', 'nid');
          $select->distinct();
          $select->isNull('r.id');
          $select->condition('n.type', $resource_type);
          $select->condition(db_or()
            ->condition('t.mmtid', $mmtid)
            ->condition('t.parent', $mmtid)
            ->condition('p.parent', $mmtid)
          );
          $results = $select->execute();
          while ($row = $results->fetchObject()) {
            $resources[$row->nid] = 'http://blogs.middlebury.edu/' . $row->site . '/';
          }
          break;
        default:
          break;
      }
    }

    $sites = array();
    foreach ($resources as $nid => $site) {
      try {
        $response = drupal_http_request($site, array('method' => 'HEAD'));
        if ($response->code == '200') {
          $course = course_hub_get_course_site_metadata(course_hub_get_course_site_tid_for_nid($nid));
          if (!empty($course)
            && !empty($course->field_catalog_id[0]['value'])
            && !empty($course->field_term_id[0]['value'])
            && !empty($course->field_short_name[0]['value'])) {
            $sites[$course->field_catalog_id[0]['value']][$course->field_term_id[0]['value']][$course->field_short_name[0]['value']][$course->title] = $site;
          }
        }
      } catch (Exception $e) {
      }
    }
    cache_set('course_hub_list_public', serialize($sites), 'cache', CACHE_PERMANENT);
    drupal_json($sites);
  }
}

/**
 * Show lists of course hub sites
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function course_hub_stats_resource_sites($mmtid, $resource_type) {
  $path = course_hub_get_path($mmtid);
  drupal_set_title(t('Sites with %type Resources under @path', array('%type' => node_type_get_name($resource_type), '@path' => $path)), PASS_THROUGH);

  $stats = course_hub_stats_get_resource_stats($resource_type, $mmtid);
  $header = array(
    array(
      'data' => 'Path',
//       'class' => '',
    ),
    array(
      'data' => 'Site',
//       'class' => '',
    ),
  );
  $rows = array();
  $paths = array();
  foreach ($stats['site_mmtids'] as $site_tid) {
    $row = array();
    $site_page = mm_content_get($site_tid);
    $path = course_hub_get_path($site_tid);
    $paths[] = $path;
    $row[] = dirname($path);
    $row[] = l($site_page->name, $path);
    $rows[] = $row;
  }
  array_multisort($paths, $rows);
  return theme('table', $header, $rows);
}

/**
 * Show lists of course hub sites
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function course_hub_stats_resource_instructors($mmtid, $resource_type) {
  $path = course_hub_get_path($mmtid);
  drupal_set_title(t('Instructors using %type Resources under @path', array('%type' => node_type_get_name($resource_type), '@path' => $path)), PASS_THROUGH);

  $stats = course_hub_stats_get_resource_stats($resource_type, $mmtid);
  $header = array(
    array(
      'data' => 'Name',
//       'class' => '',
    ),
    array(
      'data' => 'Email',
//       'class' => '',
    ),
  );
  $rows = array();
  $names = array();
  foreach ($stats['instructor_uids'] as $uid) {
    $row = array();
    $user = user_load($uid);
    if (!empty($user->profile_display_name)) {
      $names[] = $user->profile_display_name;
      $row[] = $user->profile_display_name;
    }
    else {
      $names[] = $user->name;
      $row[] = $user->name;
    }

    $row[] = $user->mail;
    $rows[] = $row;
  }
  array_multisort($names, $rows);
  $using = theme('table', $header, $rows);

  $all_instructors = course_hub_stats_instructors_in_cat($mmtid);
  $rows = array();
  $names = array();
  foreach ($all_instructors as $uid) {
    if (!in_array($uid, $stats['instructor_uids'])) {
      $row = array();
      $user = user_load($uid);
      if (!empty($user->profile_display_name)) {
        $names[] = $user->profile_display_name;
        $row[] = $user->profile_display_name;
      }
      else {
        $names[] = $user->name;
        $row[] = $user->name;
      }

      $row[] = $user->mail;
      $rows[] = $row;
    }
  }
  array_multisort($names, $rows);
  $not_using = theme('table', $header, $rows);

  return $using . "\n<h2>" . t('Instructors NOT using %type Resources under @path', array('%type' => node_type_get_name($resource_type), '@path' => $path)) . "</h2> \n" . $not_using;
}

/**
 * Answer an array of pages that maps the the page hierarchy for courses.
 *
 * @param int $mmtid The selected page_id.
 * @return array
 */
function course_hub_stats_get_pages($selected_tid = NULL) {
  $hub_root_tid = course_hub_tid_from_path('hub');
  $tree = mm_content_get_tree($hub_root_tid, array(
    MM_GET_TREE_DEPTH => 4,
    MM_GET_TREE_RETURN_FLAGS => TRUE,
    MM_GET_TREE_WHERE => "theme!='coursehub_site' AND alias NOT IN ('about', 'updates', 'resources', 'syllabus')",
  ));
  $pages = array();
  $in_term = FALSE;
  foreach ($tree as $i => $page) {
    // Skip subjects not under the currently selected term.
    if ($in_term && $page->level <= 3)
      $in_term = FALSE;
    if ($page->mmtid == $selected_tid && $page->level == 3)
      $in_term = TRUE;
    if ($page->level > 3 && !$in_term && $page->mmtid != $selected_tid)
      continue;

    $pages[$page->mmtid] = course_hub_get_path($page->mmtid);
  }
  // Dummy Data
  return $pages;
}

/**
 * Answer an array of resource utilization info under a particular path.
 *
 * @param string $resource_type
 * @param int $mmtid
 * @return array
 */
function course_hub_stats_get_resource_stats($resource_type, $mmtid) {
  // Any/All resources
  if ($resource_type == 'all')
    return course_hub_stats_get_resource_stats_for_all($mmtid);

  // Total number of nodes
  $select = db_select('node', 'n');
  $select->addJoin('LEFT OUTER', 'mm_recycle', 'r', "n.nid = r.id AND r.type = :type", array(':type' => 'node'));
  $select->addJoin('LEFT OUTER', 'mm_node2tree', 'n2t', "n.nid = n2t.nid");
  $select->addJoin('LEFT OUTER', 'mm_tree', 't', "n2t.mmtid = t.mmtid");
  $select->addJoin('LEFT OUTER', 'mm_tree_parents', 'p', "t.mmtid = p.mmtid");
  $select->addField('n', 'nid');
  $select->distinct();
  $select->isNull('r.id');
  $select->condition('n.type', $resource_type);
  $select->condition(db_or()
    ->condition('t.mmtid', $mmtid)
    ->condition('t.parent', $mmtid)
    ->condition('p.parent', $mmtid)
  );
  $nids = $select->execute()->fetchCol();
  
  // Unique sites
  if (count($nids)) {
    $select = db_select('mm_node2tree', 'n2t');
    $select->addJoin('LEFT OUTER', 'mm_tree', 't', "n2t.mmtid = t.mmtid");
    $select->addJoin('LEFT OUTER', 'mm_tree_parents', 'p', "t.mmtid = p.mmtid");
    $select->addJoin('LEFT OUTER', 'mm_tree_flags', 'f', "p.parent = f.mmtid");
    $select->addField('f', 'mmtid');
    $select->distinct();
    $select->condition('n2t.nid', $nids, 'IN');
    $select->condition('f.flag', 'coursehub_site');
    $mmtids = $select->execute()->fetchCol();
  }
  else {
    $mmtids = array();
  }

  // Unique instructors
  $instructor_uids = array();
  if (count($mmtids)) {
    $select = db_select('mm_node2tree', 'n2t');
    $select->addJoin('INNER', 'field_data_field_instructors_dn', 'i', "n2t.nid = i.entity_id");
    $select->addJoin('INNER', 'casmmsync_group_map', 'm', "i.field_instructors_dn_value = m.group_id");
    $select->addJoin('INNER', 'mm_group', 'g', "m.mmtid = g.gid");
    $select->addField('g', 'uid');
    $select->distinct();
    $select->condition('n2t.mmtid', $mmtids, 'IN');
    $instructor_uids = $select->execute()->fetchCol();
  }
  $num_instructors = count($instructor_uids);
  $total_instructors = course_hub_stats_total_instructors_in_cat($mmtid);
  if ($total_instructors)
    $percent_of_instructors = round(($num_instructors / $total_instructors) * 100);
  else
    $percent_of_instructors = 0;

  // Unique Students
  $student_uids = array();
  if (count($mmtids)) {
    $select = db_select('mm_node2tree', 'n2t');
    $select->addJoin('INNER', 'field_data_field_students_dn', 's', "n2t.nid = s.entity_id");
    $select->addJoin('INNER', 'casmmsync_group_map', 'm', "s.field_students_dn_value = m.group_id");
    $select->addJoin('INNER', 'mm_group', 'g', "m.mmtid = g.gid");
    $select->addField('g', 'uid');
    $select->distinct();
    $select->condition('n2t.mmtid', $mmtids, 'IN');
    $student_uids = $select->execute()->fetchCol();
  }
  $num_students = count($student_uids);
  $total_students = course_hub_stats_total_students_in_cat($mmtid);
  if ($total_students)
    $percent_of_students = round(($num_students / $total_students) * 100);
  else
    $percent_of_students = 0;

  // Total sites.
  $total_sites = course_hub_stats_total_sites_in_cat($mmtid);
  if ($total_sites)
    $percent_of_all_sites = round((count($mmtids) / $total_sites) * 100);
  else
    $percent_of_all_sites = 0;
  return array(
    'num_resources' => count($nids),
    'resource_nids' => $nids,
    'uniq_sites' => count($mmtids),
    'site_mmtids' => $mmtids,
    'percent_of_sites_in_cat' => $percent_of_all_sites,
    'total_number_of_sites_in_cat' => $total_sites,
    'num_instructors' => $num_instructors,
    'total_number_of_instructors_in_cat' => $total_instructors,
    'percent_of_instructors_in_cat' => $percent_of_instructors,
    'instructor_uids' => $instructor_uids,
    'num_students' => $num_students,
    'total_number_of_students_in_cat' => $total_students,
    'percent_of_students_in_cat' => $percent_of_students,
    'student_uids' => $student_uids,
  );
}

/**
 * Answer the total number of course hub sites under an mmtid
 *
 * @param int $mmtid
 * @return int
 */
function course_hub_stats_total_sites_in_cat($mmtid) {
  static $counts = array();

  if (!isset($counts[$mmtid])) {
    // Total number of sites in this category.
    $select = db_select('mm_tree_flags', 'f');
    $select->addJoin('INNER', 'mm_tree', 't', 't.mmtid = f.mmtid');
    $select->addJoin('LEFT OUTER', 'mm_tree_parents', 'p', 't.mmtid = p.mmtid');
    $select->addField('f', 'mmtid');
    $select->distinct();
    $select->condition('f.flag', 'coursehub_site');
    $select->condition(db_or()
      ->condition('t.mmtid', $mmtid)
      ->condition('t.parent', $mmtid)
      ->condition('p.parent', $mmtid)
    );
    $counts[$mmtid] = intval($select->countQuery()->execute()->fetchField());
  }
  return $counts[$mmtid];
}

/**
 * Answer the total number of instructors under an mmtid
 *
 * @param int $mmtid
 * @return int
 */
function course_hub_stats_total_instructors_in_cat($mmtid) {
  static $counts = array();

  if (!isset($counts[$mmtid])) {
    // Total number of sites in this category.
    $select = db_select('mm_tree_flags', 'f');
    $select->addJoin('INNER', 'mm_tree', 't', 't.mmtid = f.mmtid');
    $select->addJoin('LEFT OUTER', 'mm_tree_parents', 'p', 't.mmtid = p.mmtid');
    $select->addJoin('INNER', 'mm_node2tree', 'n2t', "f.mmtid = n2t.mmtid");
    $select->addJoin('INNER', 'field_data_field_instructors_dn', 'i', "n2t.nid = i.entity_id");
    $select->addJoin('INNER', 'casmmsync_group_map', 'm', "i.field_instructors_dn_value = m.group_id");
    $select->addJoin('INNER', 'mm_group', 'g', "m.mmtid = g.gid");
    $select->addField('g', 'uid');
    $select->distinct();
    $select->condition('f.flag', 'coursehub_site');
    $select->condition(db_or()
      ->condition('t.mmtid', $mmtid)
      ->condition('t.parent', $mmtid)
      ->condition('p.parent', $mmtid)
    );
    $counts[$mmtid] = intval($select->countQuery()->execute()->fetchField());
  }
  return $counts[$mmtid];
}

/**
 * Answer the total number of instructors under an mmtid
 *
 * @param int $mmtid
 * @return int
 */
function course_hub_stats_instructors_in_cat($mmtid) {
  static $uids = array();

  if (!isset($uids[$mmtid])) {
    // Total number of sites in this category.
    $select = db_select('mm_tree_flags', 'f');
    $select->addJoin('INNER', 'mm_tree', 't', 't.mmtid = f.mmtid');
    $select->addJoin('LEFT OUTER', 'mm_tree_parents', 'p', 't.mmtid = p.mmtid');
    $select->addJoin('INNER', 'mm_node2tree', 'n2t', "f.mmtid = n2t.mmtid");
    $select->addJoin('INNER', 'field_data_field_instructors_dn', 'i', "n2t.nid = i.entity_id");
    $select->addJoin('INNER', 'casmmsync_group_map', 'm', "i.field_instructors_dn_value = m.group_id");
    $select->addJoin('INNER', 'mm_group', 'g', "m.mmtid = g.gid");
    $select->addField('g', 'uid');
    $select->distinct();
    $select->condition('f.flag', 'coursehub_site');
    $select->condition(db_or()
      ->condition('t.mmtid', $mmtid)
      ->condition('t.parent', $mmtid)
      ->condition('p.parent', $mmtid)
    );
    $uids[$mmtid] = $select->execute()->fetchCol();
  }
  return $uids[$mmtid];
}

/**
 * Answer the total number of instructors under an mmtid
 *
 * @param int $mmtid
 * @return int
 */
function course_hub_stats_total_students_in_cat($mmtid) {
  static $counts = array();

  if (!isset($counts[$mmtid])) {
    // Total number of sites in this category.
    $select = db_select('mm_tree_flags', 'f');
    $select->addJoin('INNER', 'mm_tree', 't', 't.mmtid = f.mmtid');
    $select->addJoin('LEFT OUTER', 'mm_tree_parents', 'p', 't.mmtid = p.mmtid');
    $select->addJoin('INNER', 'mm_node2tree', 'n2t', "f.mmtid = n2t.mmtid");
    $select->addJoin('INNER', 'field_data_field_students_dn', 's', "n2t.nid = s.entity_id");
    $select->addJoin('INNER', 'casmmsync_group_map', 'm', "s.field_students_dn_value = m.group_id");
    $select->addJoin('INNER', 'mm_group', 'g', "m.mmtid = g.gid");
    $select->addField('g', 'uid');
    $select->distinct();
    $select->condition('f.flag', 'coursehub_site');
    $select->condition(db_or()
      ->condition('t.mmtid', $mmtid)
      ->condition('t.parent', $mmtid)
      ->condition('p.parent', $mmtid)
    );
    $counts[$mmtid] = intval($select->countQuery()->execute()->fetchField());
  }
  return $counts[$mmtid];
}

/**
 * Answer an array of resource utilization info under a particular path.
 *
 * @param int $mmtid
 * @return array
 */
function course_hub_stats_get_resource_stats_for_all($mmtid) {
  $all_stats = array(
    'resource_nids' => array(),
    'site_mmtids' => array(),
  );

  $resource_types = module_invoke_all('hub_get_resource_types');
  // Add syllabus nodes
  $resource_types[] = 'syllabus_text';
  $resource_types[] = 'media';

  // Loop through once and build our stats.
  foreach ($resource_types as $type) {
    $type_stats = course_hub_stats_get_resource_stats($type, $mmtid);
    $all_stats['resource_nids'] = array_merge($all_stats['resource_nids'], $type_stats['resource_nids']);
    $all_stats['site_mmtids'] = array_merge($all_stats['site_mmtids'], $type_stats['site_mmtids']);
  }
  $all_stats['resource_nids'] = array_unique($all_stats['resource_nids']);
  $all_stats['num_resources'] = count($all_stats['resource_nids']);
  $all_stats['site_mmtids'] = array_unique($all_stats['site_mmtids']);
  $all_stats['uniq_sites'] = count($all_stats['site_mmtids']);

  $total_sites = course_hub_stats_total_sites_in_cat($mmtid);
  if ($total_sites)
    $all_stats['percent_of_sites_in_cat'] = round(($all_stats['uniq_sites'] / $total_sites) * 100);
  else
    $all_stats['percent_of_sites_in_cat'] = 0;
  $all_stats['total_number_of_sites_in_cat'] = $total_sites;

  // Unique instructors
  $instructor_uids = array();
  if (count($all_stats['site_mmtids'])) {
    $select = db_select('mm_node2tree', 'n2t');
    $select->addJoin('INNER', 'field_data_field_instructors_dn', 'i', "n2t.nid = i.entity_id");
    $select->addJoin('INNER', 'casmmsync_group_map', 'm', "i.field_instructors_dn_value = m.group_id");
    $select->addJoin('INNER', 'mm_group', 'g', "m.mmtid = g.gid");
    $select->addField('g', 'uid');
    $select->distinct();
    $select->condition('n2t.mmtid', $all_stats['site_mmtids'], 'IN');
    $instructor_uids = $select->execute()->fetchCol();
  }
  $all_stats['num_instructors'] = $num_instructors = count($instructor_uids);
  $all_stats['instructor_uids'] = $instructor_uids;
  $all_stats['total_number_of_instructors_in_cat'] = $total_instructors = course_hub_stats_total_instructors_in_cat($mmtid);
  if ($total_instructors)
    $all_stats['percent_of_instructors_in_cat'] = round(($num_instructors / $total_instructors) * 100);
  else
    $all_stats['percent_of_instructors_in_cat'] = 0;

  // Unique Students
  $student_uids = array();
  if (count($all_stats['site_mmtids'])) {
    $select = db_select('mm_node2tree', 'n2t');
    $select->addJoin('INNER', 'field_data_field_students_dn', 's', "n2t.nid = s.entity_id");
    $select->addJoin('INNER', 'casmmsync_group_map', 'm', "s.field_students_dn_value = m.group_id");
    $select->addJoin('INNER', 'mm_group', 'g', "m.mmtid = g.gid");
    $select->addField('g', 'uid');
    $select->distinct();
    $select->condition('n2t.mmtid', $all_stats['site_mmtids'], 'IN');
    $student_uids = $select->execute()->fetchCol();
  }
  $all_stats['num_students'] = $num_students = count($student_uids);
  $all_stats['student_uids'] = $student_uids;
  $all_stats['total_number_of_students_in_cat'] =  $total_students = course_hub_stats_total_students_in_cat($mmtid);
  if ($total_students)
    $all_stats['percent_of_students_in_cat'] = round(($num_students / $total_students) * 100);
  else
    $all_stats['percent_of_students_in_cat'] = 0;


  return $all_stats;
}

/**
 * Process the statistics array add normalized percentages.
 *
 * @param ref array $stats
 * @return void
 */
function course_hub_stats_normalize_stats(array &$stats) {
  // Find the max
  $max = 1;
  foreach ($stats as $set) {
    $max = max($max, $set['num_resources'], $set['uniq_sites']);
  }
  foreach ($stats as $type => $set) {
    $stats[$type]['num_resources_percent'] = round(($set['num_resources'] / $max) * 100);
    $stats[$type]['uniq_sites_percent'] = round(($set['uniq_sites'] / $max) * 100);
  }
}