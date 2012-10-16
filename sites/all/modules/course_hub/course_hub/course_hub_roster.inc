<?php
/**
 * @file
 * Course Hub Roster view
 *
 * Provides a means for viewing the class roster. Available only to instructors.
 */

/**
 * View the roster
 *
 * @return string
 */
function course_hub_roster_view($course_site_tid = NULL) {
  if (is_null($course_site_tid))
    $course_site_tid = course_hub_get_course_site_tid();

  if (!course_hub_roster_visible($course_site_tid))
    return "<h2>" . t('Access Denied') . "</h2><p>" . t('You must be logged in as an instructor of the course to view the roster.') . "</p>";

  drupal_add_css(drupal_get_path('module', 'course_hub') . '/course_hub_roster.css');

  $metadata = course_hub_get_course_site_metadata($course_site_tid);
  $photo_base_path = course_hub_get_path($course_site_tid) . '/roster/photo';
  $students_mmtid = casmmsync_get_group_by_dn($metadata->field_students_dn[0]['value']);
  if ($students_mmtid)
    $students = course_hub_roster_get_people($students_mmtid, $photo_base_path);
  else
    $students = array();
  $audits_mmtid = casmmsync_get_group_by_dn($metadata->field_audits_dn[0]['value']);
  if ($audits_mmtid)
    $audits = course_hub_roster_get_people($audits_mmtid, $photo_base_path);
  else
    $audits = array();
  return theme('course_hub_roster', t('@title', array('@title' => $metadata->field_short_name[0]['value'])), $students, $audits);
}

/**
 * Get a list of students in the course.
 *
 * @param int $group_tid
 * @param string $photo_base_path;
 * @return array
 */
function course_hub_roster_get_people($group_tid, $photo_base_path) {
  $uids = mm_content_get_uids_in_group($group_tid);
  $users = array();
  $names = array();
  foreach ($uids as $uid) {
    $user = user_load($uid);
    $user->roster_photo_url = url($photo_base_path . '/' . $uid, array('absolute' => TRUE));
    $users[] = $user;
    $names[] = $user->profile_display_name;
  }
  array_multisort($names, $users);
  return $users;
}

/**
 * Answer a roster photo
 *
 * @param int $mmtid
 * @param int $uid
 * @return void
 */
function course_hub_roster_photo($mmtid, $uid) {
  if (!course_hub_roster_visible()) {
    cas_login_check();
    course_hub_roster_photo_error(403, 'Forbidden', 'Only instructors are authorized to view roster photos.');
  }

  // Return from cache if exists.
  $cache_key = 'course_hub_roster_photo_' . $mmtid . '_' . $uid;
  $photo = cache_get($cache_key);
  if (!empty($photo)) {
    // Output the photo
    header('Content-Type: ' . $photo->data['type']);
    header('Content-Length: ' . $photo->data['size']);
    header('Cache-Control: private,max-age=3600');
    print $photo->data['data'];
    exit;
  }

  // Fetch from the directory
  $user = user_load($uid);
  if (empty($user))
    course_hub_roster_photo_error(404, 'Not Found', 'The user was not found.');
  if (empty($user->profile_login_handle))
    course_hub_roster_photo_error(404, 'Not Found', 'The username for the user was not found.');

  if (!defined('COURSE_HUB_ROSTER_PHOTO_URL'))
    course_hub_roster_photo_error(500, 'Configuration Error', 'COURSE_HUB_ROSTER_PHOTO_URL is not defined.');
  if (!defined('COURSE_HUB_ROSTER_PHOTO_KEY'))
    course_hub_roster_photo_error(500, 'Configuration Error', 'COURSE_HUB_ROSTER_PHOTO_KEY is not defined.');

  $get_data = http_build_query(
    array(
      'show' => 'TRUE',
      'username' => $user->profile_login_handle
    ),
    NULL,
    '&');
  $post_data = http_build_query(
    array(
      'coursehub' => COURSE_HUB_ROSTER_PHOTO_KEY,
    ),
    NULL,
    '&');
  $result = drupal_http_request(
    COURSE_HUB_ROSTER_PHOTO_URL . '?' . $get_data,
    array('Content-Type' => 'application/x-www-form-urlencoded'),
    'POST',
    $post_data
  );
  if ($result->code == 302) {
    $parts = parse_url(COURSE_HUB_ROSTER_PHOTO_URL);
    $redirect = $parts['scheme'] . '://' . $parts['host'] . $result->redirect_url;
    $result = drupal_http_request($redirect);
  }
  if ($result->code != 200) {
    course_hub_roster_photo_error($result->code, 'Error fetching photo', t('@data', array('@data' => $result->data)));
  }

  // Cache the photo for later use.
  $expires = REQUEST_TIME + 3600;
  cache_set(
    $cache_key,
    array(
      'type' => $result->headers['Content-Type'],
      'size' => $result->headers['Content-Length'],
      'data' => $result->data,
    ),
    'cache',
    $expires
  );

  // Output the photo
  header('Content-Type: ' . $result->headers['Content-Type']);
  header('Content-Length: ' . $result->headers['Content-Length']);
  header('Cache-Control: private,max-age=3600');
  print $result->data;
  exit;
}

/**
 * Give an error response for problematic photos.
 *
 * @param int $status
 * @param string $title
 * @param string $message
 * @return void
 */
function course_hub_roster_photo_error($status, $title, $message) {
  watchdog('course_hub_roster', $message, array(), WATCHDOG_WARNING);
  header('HTTP/1.1 ' . $status . ' ' . $title);
    print '<html>
<head>
  <title>' . $title . '</title>
</head>
<body>
  <h1>' . $title . '</h1>
  <p>' . $message . '</p>
</body>
</html>';
    exit;
}