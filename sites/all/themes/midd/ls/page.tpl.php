<?php print render($page['header']); ?>
<header class="top_panel">
  <section class="container">
    <form class="search" action="<?php print $base_path; ?>search" method="get" target="_top">
      <label for="midd_search_query">Search LS</label>
      <input type="hidden" name="site2" value="www.middlebury.edu/ls">
      <input type="search" id="midd_search_query" class="search_query x-webkit-speech" name="q2" placeholder="Search LS" x-webkit-speech required>
      <input type="submit" id="midd_search_submit" class="search_submit" value="Go">
      <input type="hidden" id="midd_ajax_search_url" value="<?php print $base_path; ?>go/search">
    </form>
  </section>
  <h1 class="wordmark"><a href="<?php echo $base_path; ?>ls"><img src="//cdn.middlebury.edu/middlebury.edu/2010/images/ls/logo.png" width="830" height="64" alt="Middlebury Language Schools" /></a></h1>
  <section class="container">
    <nav id="midd_navigation" class="navigation">
      <ul>
        <li class="nav_applying"><a href="<?php print $base_path; ?>ls/apply">Applying<span></span></a></li>
        <li class="nav_approach"><a href="<?php print $base_path; ?>ls/approach">Our Approach<span></span></a></li>
        <li class="nav_aid"><a href="<?php print $base_path; ?>ls/aid">Financial Aid<span></span></a></li>
        <li class="nav_experience"><a href="<?php print $base_path; ?>ls/experience">The Experience<span></span></a></li>
        <li class="nav_graduate"><a href="<?php print $base_path; ?>ls/grad_programs">Graduate Programs<span></span></a></li>
        <li class="nav_news"><a href="<?php print $base_path; ?>ls/news">News &amp; Events<span></span></a></li>
        <li class="nav_schoolsabroad"><a href="<?php print $base_path; ?>sa">Schools Abroad<span></span></a></li>
      </ul>
    </nav>
    <nav class="languages_feature">
      <h2><a href="<?php print $base_path; ?>ls/approach/subtitles">(Life doesn't come with subtitles.)</a></h2>
      <ul>
        <li class="feature_arabic"><a href="<?php print $base_path; ?>ls/arabic">Arabic</a></li>
        <li class="feature_japanese"><a href="<?php print $base_path; ?>ls/japanese">Japanese</a></li>
        <li class="feature_french"><a href="<?php print $base_path; ?>ls/french">French</a></li>
        <li class="feature_german"><a href="<?php print $base_path; ?>ls/german">German</a></li>
        <li class="feature_hebrew"><a href="<?php print $base_path; ?>ls/hebrew">Hebrew</a></li>
        <li class="feature_italian"><a href="<?php print $base_path; ?>ls/italian">Italian</a></li>
        <li class="feature_chinese"><a href="<?php print $base_path; ?>ls/chinese">Chinese</a></li>
        <li class="feature_portuguese"><a href="<?php print $base_path; ?>ls/portuguese">Portuguese</a></li>
        <li class="feature_russian"><a href="<?php print $base_path; ?>ls/russian">Russian</a></li>
        <li class="feature_spanish"><a href="<?php print $base_path; ?>ls/spanish">Spanish</a></li>
      </ul>
    </nav>
  </section>
</header>
<article id="midd_content" class="pagecontent container">
  <section class="page">
    <section class="body">
      <div class="two split columns">
        <div class="first column">
          <?php print render($page['content']); ?>
        </div>
        <div class="last column gray">
          <div class="schools">
            <h2><img src="//cdn.middlebury.edu/middlebury.edu/2010/images/ls/the_language_schools.gif" alt="The Language Schools" /></h2>
            <nav>
              <ul>
                <li><a href="<?php print $base_path; ?>ls/arabic">Arabic</a></li>
                <li><a href="<?php print $base_path; ?>ls/chinese">Chinese</a></li>
                <li><a href="<?php print $base_path; ?>ls/french">French</a></li>
                <li><a href="<?php print $base_path; ?>ls/german">German</a></li>
                <li><a href="<?php print $base_path; ?>ls/hebrew">Hebrew</a></li>
              </ul>
              <ul>
                <li><a href="<?php print $base_path; ?>ls/italian">Italian</a></li>
                <li><a href="<?php print $base_path; ?>ls/japanese">Japanese</a></li>
                <li><a href="<?php print $base_path; ?>ls/portuguese">Portuguese</a></li>
                <li><a href="<?php print $base_path; ?>ls/russian">Russian</a></li>
                <li><a href="<?php print $base_path; ?>ls/spanish">Spanish</a></li>
              </ul>
            </nav>
          </div>
          <div class="clear"></div>
          <?php print render($page['right']); ?>
        </div>
        <div class="clear"></div>
      </div>
      <div class="clear"></div>
    </section>
  </section>
  <div class="clear"></div>
</article>
<section id="midd_carousel" class="carousel">
  <div class="slider">
    <?php print render($page['carousel']); ?>
  </div>
</section>
<?php include_once(drupal_get_path('theme', 'midd_ls') .'/includes/footer.inc'); ?>
<?php print render($page['footer']); ?>