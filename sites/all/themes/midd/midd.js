jQuery(document).ready(function() {
  function getFirstChild(el){
    var firstChild = el.firstChild;
    while(firstChild != null && firstChild.nodeType == 3){ // skip TextNodes
      firstChild = firstChild.nextSibling;
    }
    return firstChild;
  }

  var affiliates = document.getElementById('midd_affiliates'),
    search_submit = document.getElementById('midd_search_submit'),
    navigation = document.getElementById('midd_navigation');
  if(affiliates) affiliates.className=affiliates.className+' ir';
  if(search_submit) search_submit.className=search_submit.className+' ir';
  if(navigation) getFirstChild(navigation).className='ir';

  // Footer positioning and panel
  var footerPanel = jQuery('#midd_footer_panel');
  jQuery(window).resize(nudgeFooter).resize();
  jQuery('#midd_footer .quick_footer>a').click(function() {
    var windowHeight = jQuery(window).height(),
      li = jQuery(this).parent();
    if(!footerPanel.is(':visible')) {
      li.addClass('active');
      var fromTop = jQuery(this).offset().top;
      footerPanel.slideDown(1000);
      jQuery('html,body').animate({scrollTop:(fromTop+330-windowHeight)+'px'},1100);
    } else {
      if(li.is('.active')) {
        footerPanel.slideUp(1000,function() {
          jQuery('#midd_footer .quick_footer').removeClass('active');
        });
        jQuery('html,body').animate({scrollTop:(jQuery('body').height()-windowHeight-300)+'px'},900);
      } else {
        jQuery('#midd_footer .quick_footer').removeClass('active');
        li.addClass('active');
      }
    }
    return false;
  });

  function nudgeFooter() {
    var footer = jQuery('#midd_footer').css('visibility', 'visible');
    windowHeight = jQuery(window).height(), bodyHeight = windowHeight;
    if(footer.offset()) bodyHeight = footer.css('margin-top',30).offset().top+30;
    if(bodyHeight<windowHeight) {
      footer.css('margin-top',Math.max(30,windowHeight-bodyHeight+30)+'px');
    }
  }
});