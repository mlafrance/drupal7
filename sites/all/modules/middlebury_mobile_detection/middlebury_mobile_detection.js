// Make a request back to drupal to determine if we should redirect.
var detect_url = Drupal.settings.middlebury_mobile_detection.callback + '?user-agent=' + escape(navigator.userAgent);
$.getJSON(detect_url, function(data) {
  if (data.redirect_to_mobile) {
    middlebury_mobile_detection_display_dialog();
  }
});


function middlebury_mobile_detection_display_dialog () {
  var url = Drupal.settings.middlebury_mobile_detection.url;
  var short_url = url.replace(/^http:\/\//, '').replace(/\/$/, '');
  var blackout = $('<div class="blackout"/>').css('opacity',0.7).prependTo('body'),
    overlay = $('<div class="mobile_detect_overlay"><div class="close_overlay">×</div><p>We\'ve launched a new mobile dashboard!</p><p>Try it out at: <a href="' + url + '" style="font-weight: bold">' + short_url + '</a></p></div>').prependTo('body');
  overlay.css('top',Math.max(($('html').scrollTop()+50),90));
  blackout.add('.close_overlay').click(function() { // clicking the blackout or close button
    blackout.add(overlay).remove(); // closes the overlay
  });
}