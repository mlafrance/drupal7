<?php

/**
 * @file
 * Documentation for the Course Resources Hub API.
 */

/**
 * Hook hook_hub_resource_visibility().
 *
 * A hook that fires when the visibility of a resources has been changed.
 *
 * @param object $resource_node
 *      The resource node that was updated.
 * @param string $visibility
 *      The new visibility value for the node.
 * @return void
 */
function hook_hub_resource_visibility($resource_node, $visibility) {
  // An example implementation from the Course Hub Updates module:

  // Update the visibility of the updates from this resource.
  $update_nids = hub_updates_update_nids_for_resource($resource_node->nid);

  $updates_page_mmtid = course_hub_get_course_site_tid('updates');
  $visibility_pages = array(course_hub_get_visibility_page($updates_page_mmtid, 'class') => 'Class');
  if (in_array($visibility, array('institution', 'public')))
    $visibility_pages[course_hub_get_visibility_page($updates_page_mmtid, $visibility)] = $visibility;

  foreach ($update_nids as $update_nid) {
    $node = node_load($update_nid);
    $node->mm_catlist = $visibility_pages;
    node_save($node);
  }
}