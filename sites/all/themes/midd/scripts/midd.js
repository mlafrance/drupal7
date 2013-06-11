var ie = jQuery.browser.msie,
  ie6 = jQuery.browser.msie&&jQuery.browser.version<7,
  ie7 = jQuery.browser.msie&&jQuery.browser.version>=7&&jQuery.browser.version<8,
  ie8 = jQuery.browser.msie&&jQuery.browser.version>=8&&jQuery.browser.version<9,
  ie9 = jQuery.browser.msie&&jQuery.browser.version>=9&&jQuery.browser.version<10;

var settings = {
    edgeWidth : 0.25, // width of hover area on right and left edges for scrolling (portion of frame)
    maxSpeed : 15, //maximum speed (pixels per frame)
    minSpeed : 0.5, // minimum speed (pixels per frame)
    fps : 60, // frames per second
    refreshRate : 100, // how often to listen for a mouse move event
    threshold : 20 // how many pixels does the mouse have to have moved to register the change?
  };

jQuery(document).ready(function(jQuery) {
  homepage = jQuery('body').is('#midd_homepage');

  // create the indexOf function if it does not exist
  if(!Array.indexOf) {
    Array.prototype.indexOf = function(obj) {
      for(var i=0; i<this.length; i++) {
        if(this[i]==obj) {
          return i;
        }
      }
      return -1;
    }
  }

  jQuery.easing.def = 'easeInOutQuad'; //set the default easing

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

  /**** WAVEFORM ****/
  // if there's a waveform, hide the stories
  var stories = document.getElementById('midd_stories');
  if(stories) stories.style.display = 'none';

  var header = jQuery('#midd_header'),
    headerWidth = 0,
    headerContent;
  if(header.length) {
    headerContent = header.html();
    headerWidth=0;
    if(ie) jQuery('#midd_stories').show();
    header.find('.header_photo').each(function() {
      headerWidth+=this.width+16;
    });
    if(ie) jQuery('#midd_stories').hide();
  }
  var waveform = jQuery('#midd_waveform'),
    waveformHeight = waveform.height(),
    stories = jQuery('#midd_stories').removeClass('nojs').empty().css({opacity:0,visibility:'visible'}).show(), // immediately hide the waveform and empty it
    pointer = jQuery('<div id="midd_bar_pointer" class="bar_pointer"></div>').appendTo('body'), // the pointer
    pointerArrow = jQuery('<div id="midd_bar_pointer_arrow" class="bar_pointer_arrow"></div>'), // and its arrow
    pointerWidth = 0, // and its width
    windowWidth, // the window width
    startOpen = new Array(),
    openedStories = new Array(),
    bar_color = 0,
    story_number = 0;
  if(ie6) pointer.add(pointerArrow).css('visibility','hidden'); // in IE 6, hide the pointer arrow
  if(window.waveformStories) {
    if (homepage) {
      var openStoryInterval = setInterval(function() {
        if (startOpen.length > 1) {
          var open = stories.find('.open'); // find any open story
          if(open.length) open.closeStory();
          next_id = '#' + open.attr('id');
          if(openedStories.length == startOpen.length) openedStories = new Array();
          while (next_id == '#' + open.attr('id') || openedStories.indexOf(next_id) > -1) {
            next_id = '#story'+startOpen[Math.floor(Math.random()*startOpen.length)]+'_bar';
          }
          openedStories.push(next_id);
          jQuery(next_id).openStory();
        }
      }, 8000);
      jQuery('a').click(function() {
        if (openStoryInterval)
          clearInterval(openStoryInterval);
      });
    }
    jQuery.each(waveformStories,function(index,details) { //with each story (from JSON)
      story_number++;
      if(!details.open && ie7 && waveformStories.length > 50 && story_number < (waveformStories.length*.25) || story_number > (waveformStories.length*.75)) {
        return true;
      }
      bar_color++;
      if(bar_color==4) bar_color=1;
      var dwidth = details.width ? details.width : 14;
      var story = jQuery('<li id="story'+details.id+'_bar" class="'+(details.image ? '' : (details.submit ? 'submit ' : 'disabled '))+'bar"><div class="bar_contents" id="'+details.id+'_bar_contents"><div class="bar_title"><div style="width:'+dwidth+'px;">'+details.title+'</div></div><div class="bar_target"><div class="bar_color" style="'+(details.color ? 'background-color:'+details.color+';' : '')+'height:'+details.height+'px;"><div class="bar_image_bw" style="margin-top:-'+(details.height/2)+'px;"></div><div class="bar_image" style="margin-top:-'+(details.height/2)+'px;">'+(details.video ? '<a href="'+details.video+'" class="open_video"></a><div class="video_extra">'+details.video_extra+'</div>' : '')+(details.url ? '<a href="'+details.url+'"></a>' : '')+'</div></div></div><div class="bar_text"><div style="width:'+dwidth+'px;">'+details.text+'</div></div></div>').appendTo(stories); // add the story bar
      var bar_contents = story.find('div#'+details.id+'_bar_contents');
      var bar_padding = Math.floor(Math.random()*6)*5;
      bar_contents.css('padding-'+(index%2==0 ? 'top' : 'bottom'),bar_padding);
      jQuery.extend(details,{ // precache elements we'll need to recall
        content_height : ie7 ? details.height+8+19+64+bar_padding : bar_contents.outerHeight(), // the total height of the contents
        bar_title : story.find('div.bar_title'), // the headline
        bar : story.find('div.bar_color'), // the bar color
        bar_image_bw : story.find('div.bar_image_bw'), // the BW image div
        bar_image : story.find('div.bar_image'), // the color image div
        bar_text : story.find('div.bar_text') // the caption
      });
      if(ie8) {
        details.bar_title.css('margin-bottom',3);
        details.bar_text.css({marginTop:3,visibility:'hidden'});
      }
      if(!details.color) details.color = details.bar.css('background-color');
      if(details.content_height>waveformHeight) {
        var overflow = details.content_height-waveformHeight;
        details.bar.css('height',Math.max(details.height-overflow,10));
      }
      story.find('.bar_target').hover(function(e) { // onmouseenter
        if(!story.is('.open,:animated,.disabled')) {
          details.bar.stop(true).animate({padding:3,margin:-3,backgroundColor:'#FFFFFF'},200); // glow
          pointerWidth = pointer.text(details.title).show().width(); // show the point, set its text, and story its width
          pointerArrow.appendTo(story).show();
        }
      },function() { // onmouseleave
        if(!story.is('.open,:animated')) {
          details.bar.stop(true).animate({padding:0,margin:0,backgroundColor:details.color},200); // reset glow
        }
        pointer.add(pointerArrow).hide();
      }).bind('mousemove mouseenter',function(e) { // onmousemove
        var pointerX = e.clientX-30,
          pointerY = e.clientY-50,
          offsetTop = waveform.offset().top-jQuery().scrollTop(),
          arrowLeft;
        if(pointerY<offsetTop-25) pointerY = offsetTop-25;
        if(pointerX<0) pointerX = 0;
        else if(pointerX+pointerWidth>windowWidth-12) pointerX = windowWidth-12-pointerWidth;
        pointer.css({left:pointerX,top:pointerY});
        pointerArrow.css({top:(pointerY-offsetTop+25)});
      }).click(function() { // onclick
        if (openStoryInterval)
          clearInterval(openStoryInterval);
        if(!story.is('.open,.submit')) {
          var open = stories.find('.open'); // find any open story
          if(open.length) open.closeStory();
          details.bar.animate({padding:0,margin:0,backgroundColor:details.color},200); // reset glow
          pointer.add(pointerArrow).hide(); // hide pointer and arrow
          story.openStory();
        } else if(story.is('.submit')) {
          var blackout = jQuery('<div class="blackout"/>').css('opacity',0.7).prependTo('body'),
            overlay = jQuery('<div class="submit_overlay"><div class="close_overlay">×</div><p class="opening">We\'ve designed this Web site to tell the stories of the people who make Middlebury a unique and vibrant place.</p><p>Here\'s a chance to share your story, or the stories of your students, teachers, and colleagues. Please include your name, e-mail address, two or three sentences that describe the story, and some keywords (tags) to help people find the story online. Don\'t forget to include links to Web sites that contain more information! <form method="post" action="middlebury_story/submit"><div style="float:left;"><label for="submit_name">Name:</label><input type="text" id="submit_name" name="name"/></div><div style="float:right;"><label for="submit_email">Email Address:</label><input type="text" id="submit_email" name="email"/></div><label for="submit_story">Your story:</label><textarea rows="2" columns="80" id="submit_story" name="story"></textarea><label for="submit_tags">Tags:</label><input type="text" id="submit_tags" name="tags"/><input type="submit" value="Submit your story" id="submit_submit"/></form></div>').prependTo('body');
          overlay.find('form').submit(function() {
            jQuery.ajax({
              type: "POST",
              url: jQuery(this).attr('action'),
              data: jQuery(this).serialize(),
              success: function(msg) {
                alert(msg);
                blackout.click();
              },
              error: function(XMLHttpRequest, textStatus, errorThrown) {
                if (XMLHttpRequest.status == 400 || XMLHttpRequest.status == 500) {
                  alert(XMLHttpRequest.responseText);
                } else if (XMLHttpRequest.status == 404) {
                  alert("My apologies, but story submission is not currently enabled.");
                } else {
                  alert("My apologies, but there is currently an error with story submission.");
                }
              }
            });
            return false;
          });
          overlay.css('top',Math.max((jQuery('html').scrollTop()+50),90));
          blackout.add('.close_overlay').click(function() { // clicking the blackout or close button
            blackout.add(overlay).remove(); // closes the overlay
          });
        }
      });
      if(ie6) details.bar.attr('title',details.bar_title.text()); // in IE6, add a title attribute
      story.data('details',details); // store the details data for later
      if(details.open) startOpen.push(details.id);
    });
    stories.find('.bar_title,.bar_text,.bar_glow,.bar_image_bw,.bar_image').css('opacity',0); // face out hidden features
    stories.find('.bar_contents:odd').css('bottom',0); // make stories alternate top vs. bottom attachment
    if(header.length) stories.children().eq(Math.ceil(stories.children().length/2)-1).after('<li id="midd_header" class="bar header" style="zoom:1;width:'+headerWidth+'px;">'+headerContent+'</li>');
    jQuery(window).resize(function() { // on window resize
      windowWidth = jQuery(window).width();
      if(homepage) { // if this is the homepage
        var windowHeight = jQuery(window).height(), // get the window height
          waveformRoom = windowHeight-361, // how much room is left for the waveform? 361 is the combined height of the other elements on the homepage
          waveformHeightNew = Math.max(Math.min(waveformRoom,300),200);
        if(waveformHeightNew!=waveformHeight) { // if we need to resize the waveform
          waveform.height(waveformHeightNew); // resize it
          waveformHeight = waveformHeightNew; // store the waveform height
          jQuery.each(waveformStories,function(index,details) { // then with each story
            if(details.content_height>waveformHeight) { // if it's taller than the waveform
              var overflow = details.content_height-waveformHeight; // calculate the overflow
              details.bar.css('height',Math.max(details.height-overflow,10)); // and shrink the bar
            } else if(details.bar) { //otherwise
              details.bar.css('height',details.height); // reset its height
            }
          });
        }
        jQuery('#midd_waveform').css('margin-top',Math.max((waveformRoom-waveformHeight)/2,0)); // and center the page vertically
        nudgeFooter();
      }
    }).resize(); // and do it now
    initVideos();
    // START WIPE-IN CODE
    if(homepage&&!ie) { // wip in the stories from the left
      stories.children()
        .css('opacity',0) // hide the on-screen stories
        .each(function(index) { // and on a delay
          jQuery(this).delay(index*25).fadeTo(150,1); // fade them each in
        });
    }
    // END WIPE-IN CODE
    stories.css('opacity',1);
    if(ie&&!ie7) stories.width((waveformStories.length*30)+headerWidth+16);
    if(ie7) stories.width(((waveformStories.length/2)*30)+headerWidth+16);
    waveform.slider();
    var permalinked = jQuery(window.location.hash+'_bar'); // check whether a story corresponds to the hash tag
    if(homepage&&permalinked.length) { // if it exists
      permalinked.openStory(); // show it
    } else if(homepage&&startOpen.length>0) { // otherwise, if a default story was specified
      open_id = '#story'+startOpen[Math.floor(Math.random()*startOpen.length)]+'_bar';
      jQuery(open_id).openStory(); // open it
      openedStories.push(open_id);
    }
  }

  /**** END WAVEFORM ****/

  // Carousel
  var carousel = jQuery('#midd_carousel');
  if (carousel.length) {
    carousel.slider();
    jQuery('#midd_content').append('<div class="carousel_arrow"></div>');
  }

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

  function initVideos() {
    
  }
});

jQuery.fn.extend({
  closeStory : function() {
    var story = this.removeClass('open'),
      details = story.data('details');
    details.bar_image.add(details.bar_image_bw).stop(true).find('img').unbind('load'); // stop any animations and remove any upcoming load events
    details.bar_image.fadeTo(500,0,function() { // fade out the full image
      details.bar_image.empty(); // and remove it
      details.bar_image_bw.fadeTo(500,0,function() { // fade out the BW image
        details.bar_image_bw.empty(); // and remove it
      });
    });
    details.bar_title.add(details.bar_text).fadeTo(500,0); // fade out headline, text
    details.bar_text.find('div').animate({top:'-30px'},1000,'easeOutSine',function () {
      if(ie8) details.bar_text.css('visibility','hidden');
    }); // fade out and slide up text
    story.animate({width:'14px'},1000); // slide the story closed
    return this; // return the original element for chaining
  },
  openStory : function() {
    var story = this.addClass('open'), // mark the story as open
      details = story.data('details');
    if(ie6) { // in IE6
      var img = new Image();
      jQuery(img).appendTo(details.bar_image).attr('src',details.image).attr('alt',details.title).width(details.width).height(details.height); // append the image
      details.bar_image.stop().css('opacity',1); // and show it
    } else { // in modern browsers
      var img = new Image();
      jQuery(img).appendTo(details.bar_image_bw) // append the BW image
        .load(function() { // and onload
          details.bar_image_bw.fadeTo(500,0.5,function() { // fade it in
            var imgColor = new Image();
            jQuery(imgColor).appendTo(details.bar_image) // then append the full image
              .load(function() { // and onload
                details.bar_image.fadeTo(750,1); // fade it in
              }).attr('src',details.image).attr('alt',details.title).width(details.width).height(details.height);
          });
        }).attr('src',details.bwimage).attr('alt',details.title).width(details.width).height(details.height);
    }
    var slider = story.parent().parent().parent(),
      stripWidth=slider.data('originalWidth')+details.width;
    if(ie) slider.children().children().width(stripWidth);
    slider.children().animate({width:stripWidth},1000,function() {
      slider.data('stripWidth',stripWidth);
    });
    story.animate({width:details.width},1100); // slide the story open
    details.bar_title.add(details.bar_text).fadeTo(1500,0.9); // fade in headline, text
    if(ie8) details.bar_text.css('visibility','visible');
    details.bar_text.find('div').animate({top:0},1000,'easeOutSine'); // drop down text
    window.location.hash = 'story'+details.id; // set the hash for permalinking
    return this; // return the original element for chaining
  },
  slider : function() {
    var self = this,
      strip = self.children(0),
      stripWidth = strip.width(),
      frameWidth = self.width(),
      offset = 0;
    if(!ie) leftEdge = 0, rightEdge = 0;
    self.data('stripWidth',stripWidth);
    self.data('originalWidth',stripWidth-12);
    strip.width(stripWidth);
    jQuery(window).resize(function() { // calculate the hover areas and the strip "center" on resize
      frameWidth = self.width();
      leftEdge = settings.edgeWidth*frameWidth;
      rightEdge = frameWidth-(settings.edgeWidth*frameWidth);
    }).resize(); // and do it now
    var header = jQuery('#midd_header'),
      title = header.find('img'),
      titletext = header.find('h1 img').css('position','relative'),
      headerGutter = (header.width()-40-title.width())/2,
      titleTextOffset = 0,
      titleTextModifier = 0;
    if(!self.is('#midd_waveform')||homepage) {
      offset = -1*((stripWidth-frameWidth)/2); // initial offset
      strip.css('left',offset);
    } else if(!ie && strip.width() - header.width() > jQuery(window).width()) {
      offset = -1*((stripWidth-header.width())/2-(jQuery(window).width()*0.4));
      strip.css('left',offset);
      titleTextModifier = offset*-1;
      titleTextOffset = 0;
    }
    // Attach mouseover behavior
    var destination,
      lastX=-100,
      lastTime=0;
    self.mousemove(function(e) {
      var curX = e.clientX,
        curTime = new Date().getTime(),
        modifier;
      if(Math.abs(curX-lastX)<settings.threshold||curTime-lastTime<settings.refreshRate) return; // if the mouse has moved less than 20 or less than 100ms have elapsed, don't fire
      lastX = curX;
      lastTime = curTime;
      stripWidth = self.data('stripWidth');
      if(curX<leftEdge) {
        modifier = Math.pow((leftEdge-curX)/leftEdge,3);
        destination = 0;
      } else if(curX>rightEdge) {
        modifier = Math.pow((curX-rightEdge)/(frameWidth-rightEdge),3);
        destination = -1*(stripWidth-frameWidth);
      } else {
        destination = offset;
        modifier = 0;
      }
      if(stripWidth>frameWidth) { // if the strip is narrower than the window
        desination = -1*((stripWidth-frameWidth)/2); // move toward the center
      }
      slide(settings.maxSpeed*modifier);
    })
    .mouseleave(function() { // on mouse exit
      if(destination>offset) {
        destination = Math.min(offset+100,destination);
      } else {
        destination = Math.max(offset-100,destination);
      }
    });
    var animation,
      sliderOffset = parseInt(jQuery('div.slider').css('left')),
      slide = function(speed) {
        clearInterval(animation);
        var direction = destination>offset ? 1 : -1;
        animation = setInterval(function() {
          jQuery().click();
          var distance = Math.abs(destination-offset), // distance remaining
            modifier = Math.pow(distance/stripWidth,0.3), // moderator decelerates as the destination approaches
            step = Math.max(speed*modifier,settings.minSpeed);
          if(distance<=step) { // if the destination is less than the next step
            offset=destination;
            clearInterval(animation);
          } else {
            offset+=step*direction;
          }
          var percentOff = Math.abs(offset/(stripWidth-frameWidth));
          if(ie) {
            title.css('left',offset*0.3);
          } else {
            title.css('left',titleTextOffset*0.3);
            titleTextOffset = offset+titleTextModifier;
          }
          if(ie9||ie7) {
            jQuery('#midd_stories li.bar').css('left',offset-sliderOffset);
          } else {
            strip.css('left',offset);
          }
        },1000/settings.fps);
      };
    return this;
  }
})