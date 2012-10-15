<div class="site">
  <div class="content">
    <h2><a href="<?php print $site_url ?>"><?php print $site_title ?></a></h2>

    <?php if (strpos($resource_links, '</a>')) : ?>
      <div class="dropdown resource_links">
        <h3>Resources <span class="spinner">&#9660;</span></h3>
        <div class="contents">
          <?php print $resource_links ?>
        </div>
      </div>
    <?php endif; ?>

    <?php if ($node): ?>
      <div class='hub_update'>
        <div class='meta'>
          <div class='create_date'><?php print date('D, n M Y g:ia T', $node->created); ?></div>
          <div class='source'> via
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
        </div>
        <div class="content">
          <div class='title'><?php print $node->title; ?></div>
          <div class='teaser'><?php print $teaser; ?></div>
        </div>
      </div>
    <?php endif; ?>

    <div class="more">
      <a href="<?php print $site_url ?>">more &raquo;</a>
    </div>
  </div>

<?php
  if ($num_all_time) {
    print theme('hub_dashboard_site_stats', $num_day, $num_week, $num_all_time);
  }
?>
  <div class="clear"></div>
</div>

<?php
// var_dump($variables);