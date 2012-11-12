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
 * @param object $resourceNode
 *      The resource node that was updated.
 * @param string $visibility
 *      The new visibility value for the node.
 * @return void
 */
function hook_hub_resource_visibility($resourceNode, $visibility) {
  // An example implementation from the Course Hub Updates module:
  
  // Update the visibility of the updates from this resource.
  $updateNIDs = hub_updates_update_nids_for_resource($resourceNode->nid);

  $updatesPageTID = course_hub_get_course_site_tid('updates');
  $visibilityPages = array(course_hub_get_visibility_page($updatesPageTID, 'class') => 'Class');
  if (in_array($visibility, array('institution', 'public')))
    $visibilityPages[course_hub_get_visibility_page($updatesPageTID, $visibility)] = $visibility;

  foreach ($updateNIDs as $updateNID) {
    $node = node_load($updateNID);
    $node->mm_catlist = $visibilityPages;
    node_save($node);
  }
}