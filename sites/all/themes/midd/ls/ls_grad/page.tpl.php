<?php print render($page['header']); ?>
<header class="container">
  <form class="search" action="<?php print $base_path; ?>search" method="get" target="_top">
    <label for="midd_search_query">Search LS</label>
    <input type="hidden" name="site2" value="www.middlebury.edu/ls">
    <input type="search" id="midd_search_query" class="search_query x-webkit-speech" name="q2" placeholder="Search LS" x-webkit-speech required>
    <input type="submit" id="midd_search_submit" class="search_submit" value="Go">
    <input type="hidden" id="midd_ajax_search_url" value="<?php print $base_path; ?>go/search">
  </form>
  <h1 class="wordmark"><a href="<?php echo $base_path; ?>ls"><img src="//cdn.middlebury.edu/middlebury.edu/2010/images/ls/logo.png" width="830" height="64" alt="Middlebury Language Schools" /></a></h1>
  <nav id="midd_navigation" class="navigation">
    <ul>
      <li class="nav_applying"><a href="<?php print $base_path; ?>ls/grad_programs/apply/">Applying<span></span></a></li>
      <li class="nav_approach"><a href="<?php print $base_path; ?>ls/grad_programs/approach/">Our Approach<span></span></a></li>
      <li class="nav_aid"><a href="<?php print $base_path; ?>ls/grad_programs/finaid/">Financial Aid<span></span></a></li>
      <li class="nav_experience"><a href="<?php print $base_path; ?>ls/grad_programs/experience/">The Experience<span></span></a></li>
      <li class="nav_languageschools"><a href="<?php print $base_path; ?>ls/">Language Schools<span></span></a></li>
      <li class="nav_news"><a href="<?php print $base_path; ?>ls/grad_programs/news/">News &amp; Events<span></span></a></li>
      <li class="nav_schoolsabroad"><a href="<?php print $base_path; ?>sa/">Schools Abroad<span></span></a></li>
    </ul>
  </nav>
</header>
<article id="midd_content" class="pagecontent container">
  <nav class="taskbar">
    <a class="taskbar_back" href="<?php print $base_path; ?>ls/grad_programs">Return to <strong>Graduate Programs Home</strong></a>
    <?php if (!empty($page['quicklinks'])): ?>
      <section class="taskbar_dropdowns">
        <div class="dropdown_label">Quick links to</div>
      </section>
    <?php endif; ?>
  </nav>
  <section class="banner">
    <?php print render($page['banner']); ?>
  </section>
  <nav class="left">
    <?php print render($page['left']); ?>
  </nav>
  <section class="page">
    <aside class="sidebar">
      <?php print render($page['right']); ?>
    </aside>
    <section class="body">
      <?php print render($breadcrumb); ?>
      <?php print render($page['content']); ?>
    </section>
  </section>
  <?php print render($page['address']); ?>
  <div class="clear"></div>
</article>
<section id="midd_carousel" class="carousel">
  <div class="slider">
    <?php print render($page['carousel']); ?>
  </div>
</section>
<?php include_once(drupal_get_path('theme', 'midd_ls') .'/includes/footer.inc'); ?>
<?php print render($page['footer']); ?>