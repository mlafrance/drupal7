<?php

/**
 * Prepares variables for html.tpl.php.
 *
 * @see html.tpl.php
 */
function midd_sa_preprocess_html(&$variables) {
  drupal_add_css('//cdn.middlebury.edu/middlebury.edu/2010/css/sa.css', 'external');
}