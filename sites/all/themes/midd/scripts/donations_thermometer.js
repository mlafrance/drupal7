jQuery(document).ready(function(jQuery) {
  jQuery('.node-donation-thermometer').each(function() {
    var horizontal = jQuery(this).is('.march-general') || jQuery(this).is('.young-alumni');
    var progress = jQuery(this).find('.value');
    if (horizontal) {
      progress.width(400 * progress.html() / 100);
    } else {
      progress.height(123 * progress.html() / 100 + 30);
    }
  });
});