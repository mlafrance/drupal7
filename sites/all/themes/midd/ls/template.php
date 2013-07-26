<?php

/**
 * Prepares variables for html.tpl.php.
 *
 * @see html.tpl.php
 */
function midd_ls_preprocess_html(&$variables) {
  drupal_add_css('//cdn.middlebury.edu/middlebury.edu/2010/css/ls.css', 'external');
}