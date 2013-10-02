<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!empty($title)): ?>
    <header>
      <h1><?php print $title; ?></h1>
    </header>
  <?php endif; ?>
  <section class="contents">
    <form id="midd_google_custom_search" action="<?php print request_uri(); ?>" method="GET">
      <input type="text" id="midd_google_custom_search_text" class="x-webkit-speech" name="q2"<?php if (!empty($q2)) print ' value="' . urldecode($q2) . '" class="filled"'; ?> x-webkit-speech />
      <?php if (!empty($node->field_google_custom_search_go[$language->language][0]['value']) && $node->field_google_custom_search_go[$language->language][0]['value'] != 1): ?>
        <input type="hidden" name="nocustom" value="true" />
      <?php endif; ?>
      <input type="submit" id="midd_google_custom_search_submit" value="Search" />
    </form>
    <?php if (isset($q2) && ((!empty($node->field_google_custom_search_cat[$language->language][0]['value']) && $node->field_google_custom_search_cat[$language->language][0]['value'] != null) || (!empty($node->field_google_custom_search_dir[$language->language][0]['value']) && $node->field_google_custom_search_dir[$language->language][0]['value'] != null))): ?>
      <?php if (!empty($node->field_google_custom_search_dir[$language->language][0]['value'])): ?>
        <div class="box filled"><span id="midd_search_callback_url"><?php print base_path() . drupal_get_path('module', 'middlebury_google_custom_search'); ?>/</span>
          <p>Directories &raquo;</p>
          <ul id="directories">
            <?php foreach ($node->field_google_custom_search_dir[$language->language] as $id => $directory): ?>
              <li><a id="<?php print $directory['value']; ?>" href="#"><?php print $directory['view']; ?></a></li>
            <?php endforeach; ?>
          </ul>
        <?php endif; ?>
        <?php if (!empty($node->field_google_custom_search_cat[$language->language][0]['value'])): ?>
          <p>Course Catalogs &raquo;</p>
          <ul id="catalogs">
            <?php foreach($node->field_google_custom_search_cat[$language->language] as $id => $catalog): ?>
              <li><a id="<?php print $catalog['value']; ?>" href="#"><?php print $catalog['view']; ?></a></li>
            <?php endforeach; ?>
          </ul>
        <?php endif; ?>
      </div>
    <?php endif; ?>
    <?php if (!empty($q2)): ?>
      <div id="cse" style="width:100%;">Loading</div>
    <?php endif; ?>
    <div id="midd_catalog_directory_results"></div>
    <span id="midd_google_custom_search_id"><?php print $node->field_google_custom_search_id[$language->language][0]['value']; ?></span>
    <script src="http://www.google.com/jsapi" type="text/javascript"></script>
    <?php if (!empty($node->field_google_custom_search_feed[$language->language][0]['value']) && $node->field_google_custom_search_feed[$language->language][0]['value'] == 1): ?>
      <div class="box filled">
        <p>Help us make our search results better by giving us your <a href="mailto:webmaster@middlebury.edu?subject=Search Feedback for <?php print !empty($q2) ? $q2 : ''; ?>">feedback.</a></p>
      </div>
    <?php endif; ?>
    <?php if ($display_submitted): ?>
      <span class="submitted"><?php print $submitted; ?></span>
    <?php endif; ?>
    <?php print render($content['links']); ?>
  </section>
</article>