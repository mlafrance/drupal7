<?php $search = str_replace('%20', ' ', $_GET['search']); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd"> 
<html lang="en" xml:lang="en" xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <style type="text/css">
      #searchbar { margin:0px; padding:0px 18px; width: 100%; height:30px; line-height:30px; font-size: 1em; font-family:Verdana,"Lucida Grande",Lucida,sans-serif; background-color: #BEDA90; color:#003468; }
      .closeBar {position:absolute; right:0;}
      .closeBar a {padding-right: 18px; text-decoration:none;}
    </style>
    <script type="text/javascript">
      var mainloc = parent.document.getElementById('contentFrame').src 
      function closeFrame() { window.top.document.location = mainloc; }
    </script>
  </head>
  <body class="fullwidth gateway search">
    <div id="searchbar"><span class="closeBar"><b><a href="javascript:closeFrame()">X</a></b></span>We think this is the right page for your search of <b><?php print $search; ?></b>, but if it's not, you can <b><a href="http://<?php print $_SERVER['HTTP_HOST']; ?>/search?q2=<?php print $_GET['search']; ?>&nocustom=true" target="_top">view all the results</a></b>.</div>
  </body>
</html>