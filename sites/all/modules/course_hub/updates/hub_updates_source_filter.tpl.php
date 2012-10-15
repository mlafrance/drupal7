<select class="resource_filter" onchange="window.location=this.value;">
<?php foreach ($sources as $source): ?>
  <option value="<?php print $source->filter_url; ?>" <?php if ($current_filter == $source->id) { print 'selected="selected" class="selected"'; } ?>>
  <?php print $source->title; ?> (<?php print $source->num_updates; ?>)
  </option>
<?php endforeach; ?>
</select>