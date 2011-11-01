var ec = null;
var ecc = null;
var ecIsInit = false;
var ecIsMove = false;
var ecX = 0;
var ecY = 0;
 
var ecPWindow = null;

function ecDoubleClick()
{
	if (ecc.style.display == "none")
		ecc.style.display = "block";
	else
		ecc.style.display = "none";
}
 
function ecMouseOver()
{
	if (!ecIsInit)
		ecInit();
}
 
function ecInit()
{
	ec = document.getElementById("tabs-wrapper");
	ecc = document.getElementById("tabs-content");
	ecIsInit = true;
	
	ec.onmousedown = ecMouseHandler;
	document.onmousemove = ecMouseHandler;
	document.onmouseup = ecMouseHandler;
}
 
function ecMouseHandler(ev)
{
	if (ev == null)
		ev = event;
	
	switch (ev.type)
	{
		case "mousedown":
			ecIsMove = true;
			
			if (!isNaN(parseInt(ec.style.left)))
			{
				ecX = (ev.pageX?ev.pageX:ev.clientX) - parseInt(ec.style.left);
				ecY = (ev.pageY?ev.pageY:ev.clientY) - parseInt(ec.style.top);
			}
			else
			{
				ecX = (ev.pageX?ev.pageX:ev.clientX);
				ecY = (ev.pageY?ev.pageY:ev.clientY);
			}
			break;
			
		case "mouseup":
			ecIsMove = false;
			break;
			
		case "mousemove":
			if (ecIsMove)
			{
				ec.style.left = (ev.pageX?ev.pageX:ev.clientX) - ecX;
				ec.style.top = (ev.pageY?ev.pageY:ev.clientY) - ecY;
			}
			break;
			
		default:
			break;
	}
}

var classes = '.mm-block-links,div.links,ul.links,.hidden-cat,.hidden-entry,.recycle-bin,.preview';

$(function() { // on DOM ready
  $('#livepreview').click(function() {
    var options = { path: '/', expires: 10 };
    if ($('#livepreview').is(':checked')) {
      $.cookie("midd_live_preview","preview", options);
      $(classes).hide();
    } else {
      $.cookie("midd_live_preview", null, options);
      $(classes).show();
    }
  });
  if ($.cookie("midd_live_preview") == "preview") {
    $('#livepreview').attr('checked', true);
    $(classes).hide();
  } else if ($('#livepreview').is(':checked')) {
    $('#livepreview').attr('checked', false);
    $(classes).show();
  }
  $('#login').click(function() {
    var options = { path: '/', expires: 10 };
    $.cookie("midd_live_preview", null, options);
  });

  $('#editconsole_links_content').click(function() { show_hide_links($(this).is(':checked'), 'div#body>div.node', 'profile_show_links_content'); });
  $('#editconsole_links_2').click(function() { show_hide_links($(this).is(':checked'), '#block-monster-menus-2', 'profile_show_links_2'); });
  $('#editconsole_links_4').click(function() { show_hide_links($(this).is(':checked'), '#block-monster-menus-4', 'profile_show_links_4'); });
  $('#editconsole_links_5').click(function() { show_hide_links($(this).is(':checked'), '#block-monster-menus-5', 'profile_show_links_5'); });
  $('#editconsole_links_6').click(function() { show_hide_links($(this).is(':checked'), '#block-monster-menus-6', 'profile_show_links_6'); });
  $('#editconsole_links_7').click(function() { show_hide_links($(this).is(':checked'), '#block-monster-menus-7', 'profile_show_links_7'); });
  $('#editconsole_links_8').click(function() { show_hide_links($(this).is(':checked'), '#block-monster-menus-8', 'profile_show_links_8'); });
  $('#editconsole_links_9').click(function() { show_hide_links($(this).is(':checked'), '#block-monster-menus-9', 'profile_show_links_9'); });
  if ($('#editconsole_links_content').length != 0) {
    show_hide_links($('#editconsole_links_content').is(':checked'), 'div#body>div.node');
  }
  for (i = 0; i < 13; i++) {
    if ($('#editconsole_links_'+i).length != 0) {
      show_hide_links($('#editconsole_links_'+i).is(':checked'), '#block-monster-menus-'+i);
    }
  }

  function show_hide_links(checked, region, profile) {
    if (checked) {
      $(region).find(classes).show();
    } else {
      $(region).find(classes).hide();
    }
    
    if (region == 'div#body>div.node') {
      if (checked) {
        $('div#body > ul.links').show();
      } else {
        $('div#body > ul.links').hide();
      }
    }
    
    if (profile) {
      var show = checked ? 1 : 0;
      
      $.ajax({
        type: 'GET',
        url: Drupal.settings.basePath + 'middlebury_monster_menus/show_hide_links',
        dataType: 'json',
        success: '',
        data: 'show='+show+'&profile='+profile
      });
    }
  }
});