<?php

/**
 * @file
 * Documentation for the Course Hub API.
 */

/**
 * Hook hub_get_content_types().
 *
 * This returns an array of content types other than resources.
 *
 * @return array
 *      An array of node-type strings
 */
function hook_hub_get_content_types() {
  return array('syllabus_text', 'media', 'syllabus_link');
}

/**
 * Hook hook_hub_get_resource_types()
 *
 * @return array
 *    An array of node-type strings.
 */
function hook_hub_get_resource_types() {
  return array('rss_resource');
}

/**
 * Hook hook_hub_get_resource_updates().
 *
 * Answer an array of updates fetched by the resource. Each update must be an array
 * with the following items:
 *
 *  Required elements:
 *    'guid'      A globally unique identifier string for the update. Will be used to prevent duplicates.
 *    'title'     A title for the update.
 *
 *  Optional elements:
 *    'timestamp' An ISO 8601 date/time that reflects when the update item occurred.
 *                If not supplied, defaults to NOW().
 *    'visibility'  One of 'class', 'institution', or 'public'. If not supplied,
 *                  defaults to 'class'.
 *    'url'       A URL for the item.
 *    'body'      An HTML string representing the content of the update.
 *
 * @return array
 *    An array of updates
 */
function hook_hub_get_resource_updates($resource_node) {
  if ($resource_node->type != 'rss_resource')
    return array();

  if (!$resource_node->field_url[0]['value'])
    return array();

  try {
    $feed = rss_resource_fetch_feed($feed_url);

    if (isset($resource_node->field_hub_perms[0]['value']))
      $visibility = $resource_node->field_hub_perms[0]['value'];
    else
      $visibility = 'class';

    if (!in_array($visibility, array('class', 'institution', 'public')))
    throw new InvalidArgumentException(t('Unknown visibility @visibility.', array('@visibility' => $visibility)));

    $updates = array();
    foreach ($feed->get_items() as $item) {
      $update = array(
        'title' => html_entity_decode($item->get_title(), ENT_QUOTES),
        'visibility' => $visibility,
      );
      if ($item->get_id())
        $update['guid'] = $item->get_id();
      else
        $update['guid'] = $item->get_link();

      if (!$update['title'])
        $update['title'] = 'Untitled';

      if ($timestamp = $item->get_date('c'))
        $update['timestamp'] = $timestamp;

      if ($url = $item->get_link())
        $update['url'] = $url;

      if ($content = $item->get_content()) {
        // @todo Ensure that html is safe.
        $update['body'] = $content;
      }

      $updates[] = $update;
    }

    return $updates;
  } catch (Exception $e) {
    watchdog('hub_updates', $e->getMessage(), array(), WATCHDOG_WARNING);
    form_set_error('hub_updates', $e->getMessage());
    return array();
  }
}

/**
 * Hook hook_hub_get_resource_url()
 *
 * @param object $resource_node
 * @return array
 *    An array of url strings.
 */
function hook_hub_get_resource_url($resource_node) {
  if ($resource_node->type == 'moodle_resource') {
    try {
      if ($node->type != 'moodle_resource')
    throw new InvalidArgumentException(t('@func expects and moodle_resource node, got @type', array('@func' => __FUNCTION__, '@type' => $node->type)));
    if (!isset($node->field_moodle_course_id[0]['value']))
    throw new UnexpectedValueException(t('@func expects the node to have a cid value, none found.', array('@func' => __FUNCTION__)));
    if (!$node->field_moodle_course_id[0]['value'])
    throw new UnexpectedValueException(t('@func expects the node to have a cid value, none found.', array('@func' => __FUNCTION__)));

    return variable_get('moodle_resource_base_url', 'http://moodle.middlebury.edu/') . 'course/view.php?id=' . $node->field_moodle_course_id[0]['value'];
    } catch (UnexpectedValueException $e) {
    }
  }
}

/**
 * Hook hook_hub_get_updates().
 *
 * Answer an array of updates related to a course site. Each update must be an array
 * with the following items:
 *
 *  Required elements:
 *    'guid'      A globally unique identifier string for the update. Will be used to prevent duplicates.
 *    'title'     A title for the update.
 *    'source_type'   The type of the node/module generating the update.
 *    'source_title'  The title of the source of the update.
 *    'source_id' The identifier of the node that generated the update.
 *
 *  Optional elements:
 *    'source_url'    The URL for the source of the update.
 *    'timestamp' An ISO 8601 date/time that reflects when the update item occurred.
 *                If not supplied, defaults to NOW().
 *    'visibility'  One of 'class', 'institution', or 'public'. If not supplied,
 *                  defaults to 'class'.
 *    'url'       A URL for the item.
 *    'body'      An HTML string representing the content of the update.
 *
 * @param int $courseSiteTID
 *      The course page id.
 * @return array
 *      An array of updates.
 */
function hook_hub_get_updates($courseSiteTID) {
  $all_updates = array();

  // Updates from each resource
  $resource_nodes = hub_updates_get_resource_nodes($courseSiteTID);
  foreach ($resource_nodes as $resource_node) {
    $type = $resource_node->type;
    $title = $resource_node->title;
    $urls = module_invoke_all('hub_get_resource_url', $resource_node);
    if (count($urls))
      $url = $urls[0];
    else
      $url = '';

    $resource_updates = module_invoke_all('hub_get_resource_updates', $resource_node);
    foreach ($resource_updates as $update) {
      $update['source_type'] = $type;
      $update['source_title'] = $title;
      $update['source_url'] = $url;
      $update['source_id'] = $resource_node->nid;
      $all_updates[] = $update;
    }
  }
  return $all_updates;
}