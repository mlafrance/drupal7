<?php

/**
 * @file
 * Codecs and regular expressions used to parse input content in the middlebury_video_filter module.
 */

function middlebury_video_filter_codec_info() {
  $codecs = array();

  $codecs['middmedia'] = array(
    'name' => t('MiddMedia'),
    'callback' => 'middlebury_video_filter_middmedia',
    'regexp' => '/middmedia\.middlebury\.edu\/(media|vod)\/([a-zA-Z0-9\-_]+)\/(mp3\/|mp4\/|webm\/)?([a-zA-Z0-9\-_\.%]+)\.([a-zA-Z0-9]+)$/i',
    'ratio' => 425 / 355,
  );

  return $codecs;
}

function middlebury_video_filter_middmedia($video) {
  $video['source'] = $video['codec']['matches'][4];
  $video['user'] = $video['codec']['matches'][2];
  $video['filename'] = $video['codec']['matches'][4];
  $video['extension'] = $video['codec']['matches'][5];

  return middlebury_video_filter_flash($video);
}

function middlebury_video_filter_codec_alter(&$codecs) {
  if (isset($codecs['youtube'])) {
    $codecs['youtube']['regexp'] = '/youtube\.com\/watch\?v=([a-z0-9\-_]+)([^\s]*&amp;(p|list)=([a-zA-Z0-9\-_]+))?/i';
    $codecs['youtube']['callback'] = 'middlebury_video_filter_youtube';
    $codecs['youtube']['ratio'] = 425 / 355;
  }
}

function middlebury_video_filter_youtube($video) {
  $url = $video['codec']['matches'][1];

  if (isset($video['codec']['matches'][3])) $url = 'p/' . $video['codec']['matches'][4];

  $video['source'] = 'http://www.youtube.com/embed/' . $url . '?' . ($video['autoplay'] ? '&amp;autoplay=1' : '') . ($video['related'] ? '' : '&amp;rel=0');

  return middlebury_video_filter_iframe($video);
}