<header class="container">
  <form class="search" action="<?php print $base_path; ?>search" method="get" target="_top">
    <label for="midd_search_query">Search SA</label>
    <input type="hidden" name="site2" value="www.middlebury.edu/sa">
    <input type="search" id="midd_search_query" class="search_query x-webkit-speech" name="q2" placeholder="Search SA" x-webkit-speech required>
    <input type="submit" id="midd_search_submit" class="search_submit" value="Go">
    <input type="hidden" id="midd_ajax_search_url" value="<?php print $base_path; ?>go/search">
  </form>
  <h1 class="wordmark"><a class="noborder" href="<?php echo $base_path; ?>sa"><img src="//cdn.middlebury.edu/middlebury.edu/2010/images/sa/logo.png" width="830" height="64" alt="Middlebury Schools Abroad"/></a></h1>
  <section class="header_callout">
    <h2>International Programs &amp;<br/>Off-campus Study Photo Contest</h2>
    <a href="http://go.middlebury.edu/sa?photocontest">See more student photos &raquo;</a>
  </section>
  <nav id="midd_navigation" class="navigation">
    <ul>
      <li class="nav_applying"><a href="<?php print $base_path; ?>sa/applying/">Applying<span></span></a></li>
      <li class="nav_whymidd"><a href="<?php print $base_path; ?>sa/whymidd/">Our Approach<span></span></a></li>
      <li class="nav_aid"><a href="<?php print $base_path; ?>sa/parents/">Parents<span></span></a></li>
      <li class="nav_health"><a href="<?php print $base_path; ?>sa/health/">Health &amp; Safety Abroad<span></span></a></li>
      <li class="nav_graduate"><a href="<?php print $base_path; ?>sa/grad/">Graduate Programs<span></span></a></li>
      <li class="nav_languageschools"><a href="<?php print $base_path; ?>sa/ls/">Language Schools<span></span></a></li>
    </ul>
  </nav>
</header>