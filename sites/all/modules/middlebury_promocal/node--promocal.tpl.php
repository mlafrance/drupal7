<?php
/**
 * @file
 * A default template file for the Promotional Calendar node.
 */
?>
<article class="<?php print $classes; ?>">
  <header>
    <h1><?php print $title; ?></h1>
  </header>
  <script src="//25livepub.collegenet.com/scripts/spuds.js"></script>
  <script>
    $Trumba.addSpud({
      webName: "<?php print $webname; ?>",
      spudType: "<?php print $spudtype; ?>",
      teaserBase: "<?php !empty($teaserbase) ? print $teaserbase : print ''; ?>"
    });
  </script>
  <noscript>Your browser must support JavaScript to view this content. Please enable JavaScript in your browser settings then try again.</noscript>
  <?php print render($content['links']); ?>
</article>