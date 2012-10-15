<div class="hub_update">
  <h2><?php if (isset($url)) { print "<a href=\"$url\">"; } print $title; if ($url) { print "</a>"; } ?></h2>

  <div class='meta'>
    <div class='source'>Via
	<?php

	  if ($source_url)
		print "<a href=\"$source_url\">";
	  else
		print "<span>";

	  print $source_title;

	  if ($source_url)
		print "</a>";
	  else
		print "</span>";

	?></div>
    <div class='create_date'><?php print $date_created; ?></div>
  </div>

  <div class='teaser'>
  <?php print $teaser;?>
  </div>
</div>
