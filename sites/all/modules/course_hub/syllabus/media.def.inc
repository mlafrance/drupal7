<?php

$content['type']  = array(
  'name' => 'File upload',
  'type' => 'media',
  'description' => 'Upload images, PDFs, audio and other media files (after uploading files, you can insert them in articles).',
  'title_label' => 'Title',
  'body_label' => 'Body',
  'min_word_count' => 0,
  'help' => '',
  'node_options' =>
  array(
    'status' => TRUE,
    'promote' => TRUE,
    'sticky' => FALSE,
    'revision' => FALSE,
  ),
  'old_type' => 'media',
  'orig_type' => 'media',
  'module' => 'media',
  'custom' => FALSE,
  'modified' => FALSE,
  'locked' => TRUE,
  'reset' => 'Reset to defaults',
  'comment' => 2,
  'comment_default_mode' => 4,
  'comment_default_order' => 1,
  'comment_default_per_page' => 50,
  'comment_controls' => 3,
  'comment_anonymous' => 0,
  'comment_subject_field' => 1,
  'comment_preview' => 1,
  'comment_form_location' => 0,
  'ant' => '0',
  'ant_pattern' => 'Syllabus',
  'ant_php' => 0,
);
$content['fields']  = array(
  0 =>
  array(
    'label' => 'Who can view the file?',
    'field_name' => 'field_hub_perms',
    'type' => 'text',
    'widget_type' => 'optionwidgets_buttons',
    'change' => 'Change basic information',
    'weight' => '-2',
    'description' => '',
    'default_value' =>
    array(
      0 =>
      array(
        'value' => 'class',
      ),
    ),
    'default_value_php' => '',
    'default_value_widget' => NULL,
    'group' => FALSE,
    'required' => 1,
    'multiple' => '0',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'class|The Class
institution|Any Middlebury Person
public|Public / Anyone in the world.',
    'allowed_values_php' => '',
    'op' => 'Save field settings',
    'module' => 'text',
    'widget_module' => 'optionwidgets',
    'columns' =>
    array(
      'value' =>
      array(
        'type' => 'text',
        'size' => 'big',
        'not null' => FALSE,
        'sortable' => TRUE,
        'views' => TRUE,
      ),
    ),
    'display_settings' =>
    array(
      'weight' => '11',
      'parent' => '',
      'label' =>
      array(
        'format' => 'above',
      ),
      'teaser' =>
      array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' =>
      array(
        'format' => 'default',
        'exclude' => 1,
      ),
      4 =>
      array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
  ),
);
$content['extra']  = array(
  'title' => '-5',
  'body_field' => '-3',
  'revision_information' => '0',
  'author' => '-1',
  'options' => '1',
  'comment_settings' => '2',
  'menu' => '-4',
);
