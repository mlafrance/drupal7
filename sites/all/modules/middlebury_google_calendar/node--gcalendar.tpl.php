<article class="<?php print $classes; ?>">
  <h1><?php print $title; ?></h1>
  <?php print render($content['body']); ?>
  <?php for ($i = 0; $i < count($embed); $i++): ?>
    <p id="middlebury-google-calendar-<?php print $i; ?>" class="middlebury_google_calendar">
      <iframe src="<?php print $embed[$i]; ?>" style="border-width:0" width="<?php print $content['gcalendar_width']['#items'][0]['safe_value']; ?>" height="<?php print $content['gcalendar_height']['#items'][0]['safe_value']; ?>" scrolling="no"></iframe>
    </p>
  <?php endfor; ?>
  <?php print render($content['links']); ?>
</div>