<?php if ($content && variable_get('middlebury_alert_power', 0)): ?>
  <div id="alert_bar" style="background-color:<?php print middlebury_alert_background(); ?>; color:<?php print middlebury_alert_text(); ?>">
    <?php print render($content); ?>
  </div>
<?php endif; ?>