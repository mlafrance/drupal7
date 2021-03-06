<?php

/**
 * @file
 * Codecs and regular expressions used to parse input content in the middlebury_video_filter module.
 */

function middlebury_video_filter_codec_info() {
  $codecs = array();

  $codecs['hulu'] = array(
    'name' => t('Hulu'),
    'callback' => 'middlebury_video_filter_hulu',
    'regexp' => '/hulu.com\/embed\/([a-zA-Z0-9\-_]+)$/i',
    'ratio' => 512 / 288,
  );

  $codecs['middmedia'] = array(
    'name' => t('MiddMedia'),
    'callback' => 'middlebury_video_filter_middmedia',
    'regexp' => '/middmedia\.middlebury\.edu\/(media|vod)\/([a-zA-Z0-9\-_]+)\/(mp3\/|mp4\/|webm\/)?([a-zA-Z0-9\-_\.%]+)\.([a-zA-Z0-9]+)$/i',
    'ratio' => 425 / 355,
  );

  $codecs['wcax'] = array(
    'name' => t('WCAX'),
    'callback' => 'middmedia_video_filter_wcax',
    'regexp' => '/www\.wcax\.com\/story\/([0-9]+)\/.*clipId=([0-9]+)/i',
    'ratio' => 425 / 355,
  );

  return $codecs;
}

function middlebury_video_filter_hulu($video) {
  $video['source'] = 'http://www.hulu.com/embed/' . $video['codec']['matches'][1];

  return middlebury_video_filter_hulu_flash($video);
}

function middlebury_video_filter_middmedia($video) {
  $video['source'] = $video['codec']['matches'][4];
  $video['user'] = $video['codec']['matches'][2];
  $video['filename'] = $video['codec']['matches'][4];
  $video['extension'] = $video['codec']['matches'][5];

  return middlebury_video_filter_flash($video);
}

function middlebury_video_filter_wvax($video) {
  $video['clipid'] = $video['codec']['matches'][2];

  return middmedia_video_filter_wcaxscript($video);
}