<?php
// $Id$

/**
 * @file
 * Configure and run updates from remote resources.
 */

/**
 * Form builder. Configure Course Hub Resources
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function course_hub_admin_overview() {
  $item = menu_get_item('admin/course_hub');
  $content = system_admin_menu_block($item);

  $output = theme('admin_block_content', $content);

  return $output;
}

/**
 * List sites in use
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function course_hub_admin_sites_in_use() {
  $header = array('Term', 'Title', 'Num Updates', 'Instructors', 'Latest Update');
  $rows = array();

  $sites_results = db_query(
"
SELECT
  s.*,
  GROUP_CONCAT(u.user_name SEPARATOR ',\n') AS user_names
FROM
  (SELECT
    t.mmtid,
    t.name,
    m.field_term_id_value AS term_id,
    m.field_term_label_value AS term_label,

    COUNT(DISTINCT(n.nid)) AS num_updates,
    MAX(n.created) AS latest_update
  FROM
    `mm_tree_flags` f
    INNER JOIN `mm_tree` t ON f.mmtid = t.mmtid
    LEFT JOIN `mm_node2tree` mn2t ON t.mmtid = mn2t.mmtid
    LEFT JOIN `content_type_course_metadata` m ON m.nid = mn2t.nid

    INNER JOIN `mm_tree_parents` p ON t.mmtid = p.parent
    INNER JOIN `mm_node2tree` n2t ON (n2t.mmtid = p.mmtid)
    INNER JOIN `node` n ON (n.nid = n2t.nid AND n.type = 'hub_update')

  WHERE
    f.flag = 'coursehub_site'
    AND n.type = 'hub_update'
  GROUP BY
    f.mmtid
  ) as s
  LEFT JOIN (
    SELECT
      t.mmtid,
      n.uid,
      u.name AS user_name
     FROM
      `mm_tree_flags` f
      INNER JOIN `mm_tree` t ON f.mmtid = t.mmtid

      INNER JOIN `mm_tree_parents` p ON t.mmtid = p.parent
      INNER JOIN `mm_node2tree` n2t ON (n2t.mmtid = p.mmtid)
      INNER JOIN `node` n ON (n.nid = n2t.nid)

      INNER JOIN `users` u ON n.uid = u.uid
    WHERE
      f.flag = 'coursehub_site'
      AND (
        n.type LIKE '%_resource'
        OR n.type = 'syllabus_text'
        OR n.type = 'media'
      )
    GROUP BY
      f.mmtid, n.uid
  ) u ON u.mmtid = s.mmtid
GROUP BY
  s.mmtid
ORDER BY
  latest_update DESC,
  term_id DESC,
  name ASC
  ");
  while ($site = db_fetch_object($sites_results)) {
    $row = array($site->term_label);
    $row[] = "<a href='" . url('mm/' . $site->mmtid) . "' target='_blank'>" . $site->name . "</a>";
    $row[] = $site->num_updates;
    $row[] = nl2br($site->user_names);
    if ($site->latest_update)
      $row[] = date('r', $site->latest_update);
    else
      continue;

    $rows[] = $row;
  }

  return theme('table', $header, $rows);
}