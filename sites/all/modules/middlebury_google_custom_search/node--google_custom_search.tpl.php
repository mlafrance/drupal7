<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!empty($title)): ?>
    <header>
      <h1><?php print $title; ?></h1>
    </header>
  <?php endif; ?>
  <section class="contents">
    <form id="midd_google_custom_search" class="google_custom_search" action="<?php print request_uri(); ?>" method="GET">
      <input type="text" id="midd_google_custom_search_text" class="google_custom_search_text x-webkit-speech" name="q2"<?php if (!empty($q2)) print ' value="' . urldecode($q2) . '" class="filled"'; ?> x-webkit-speech />
      <?php if (!empty($content['field_google_custom_search_go']['#items'][0]['safe_value']) && $content['field_google_custom_search_go']['#items'][0]['safe_value'] != 1): ?>
        <input type="hidden" name="nocustom" value="true" />
      <?php endif; ?>
      <input type="submit" id="midd_google_custom_search_submit" class="google_custom_search_submit" value="Search" />
    </form>
    <?php if (isset($q2) && ((!empty($content['field_google_custom_search_cat']['#items'][0]['value']) && $content['field_google_custom_search_cat']['#items'][0]['value'] != null) || (!empty($content['field_google_custom_search_dir']['#items'][0]['value']) && $content['field_google_custom_search_dir']['#items'][0]['value'] != null))): ?>
      <?php if (!empty($content['field_google_custom_search_dir']['#items'][0]['value'])): ?>
        <div class="box filled">
          <p>Directories &raquo;</p>
          <ul id="directories">
            <?php foreach ($content['field_google_custom_search_dir']['#items'] as $id => $directory): ?>
              <li><a id="<?php print $directory['value']; ?>" href="#"><?php print $directory['value']; ?></a></li>
            <?php endforeach; ?>
          </ul>
        <?php endif; ?>
        <?php if (!empty($content['field_google_custom_search_dir']['#items'][0]['value'])): ?>
          <p>Course Catalogs &raquo;</p>
          <ul id="catalogs">
            <?php foreach($content['field_google_custom_search_cat']['#items'] as $id => $catalog): ?>
              <li><a id="<?php print $catalog['value']; ?>" href="#"><?php print $catalog['value']; ?></a></li>
            <?php endforeach; ?>
          </ul>
        <?php endif; ?>
      </div>
    <?php endif; ?>
    <?php if (!empty($q2)): ?>
      <div id="cse" style="width:100%;">Loading</div>
    <?php endif; ?>
    <div id="midd_catalog_directory_results" class="catalog_directory_results"></div>
    <span id="midd_google_custom_search_id" class="google_custom_search_id"><?php print $content['field_google_custom_search_id']['#items'][0]['safe_value']; ?></span>
    <script src="http://www.google.com/jsapi" type="text/javascript"></script>
    <?php if (!empty($content['field_google_custom_search_feed']['#items'][0]['value']) && $content['field_google_custom_search_feed']['#items'][0]['value'] == 1): ?>
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