<?php if (module_exists('profile')): ?>
  <?php profile_load_profile($user); ?>
<?php endif; ?>
<?php if ($tabs): ?>
  <?php if(isset($user->profile_new_edit_console) && $user->profile_new_edit_console == 1): ?>
    <?php $path = 'mm/'. arg(1); ?>
    <?php custom_url_rewrite_outbound($path, $path, $path); ?>
    <style>
      div#editconsole_wrapper a { color:#fff; border:none; }
      div#editconsole_wrapper a:hover { background:transparent; border-bottom:1px solid #fff; }
      div#editconsole_wrapper>ul { list-style-type:none; overflow:hidden; margin:0; padding:0; color:#fff; width:100%; }
    
      ul#editconsole { font-weight:bold; }
      ul#editconsole > li { text-align:center; float:left; margin:0; padding:5px 0px; width:25%; }
      ul#editconsole > li > ul { padding: 0; margin:5px 0 0 0; border-top: 1px dotted white; }
      ul#editconsole > li > ul > li { display: inline; margin:0px 5px; }
      
      li#editconsole_content { background-color:#184780; }
      li#editconsole_page { background-color:#669966; }
      li#editconsole_sub { background-color:#993300; }
      li#editconsole_help { background-color:#663366; }
      
      ul#page_link_settings { background-color:#6666FF; text-align:center; }
      ul#page_link_settings li { display:inline; margin:0; padding:5px 15px; }
      
      div#editconsole_wrapper ul.tabs { border:none; padding:10px 0px; }
      div#editconsole_wrapper ul.tabs.primary { background-color:#184780; }
      div#editconsole_wrapper ul.tabs.secondary,
        div#editconsole_wrapper ul.tabs.primary li.active { background-color:#669966; }
      div#editconsole_wrapper ul.tabs li { padding: 15px 15px; border:none; }
      div#editconsole_wrapper ul.tabs li a { background:transparent; border;none !important; }
    </style>
    <div id="editconsole_wrapper">
      <ul id="page_link_settings">Show Links
        <li><input id="editconsole_links_content" type="checkbox" <?php if (!isset($user->profile_show_links_content) || $user->profile_show_links_content == 1) print "checked"; ?> />&nbsp;<label for="editconsole_links_content">Content</label></li>
        <li><input id="editconsole_links_2" type="checkbox" <?php if (!isset($user->profile_show_links_2) || $user->profile_show_links_2 == 1) print "checked"; ?> />&nbsp;<label for="editconsole_links_2">Right Sidebar</label></li>
        <li><input id="editconsole_links_8" type="checkbox" <?php if (!isset($user->profile_show_links_8) || $user->profile_show_links_8 == 1) print "checked"; ?> />&nbsp;<label for="editconsole_links_8">Left Sidebar</label></li>
        <li><input id="editconsole_links_4" type="checkbox" <?php if (!isset($user->profile_show_links_4) || $user->profile_show_links_4 == 1) print "checked"; ?> />&nbsp;<label for="editconsole_links_4">Carousel</label></li>
        <li><input id="editconsole_links_5" type="checkbox" <?php if (!isset($user->profile_show_links_5) || $user->profile_show_links_5 == 1) print "checked"; ?> />&nbsp;<label for="editconsole_links_5">Quick Links</label></li>
        <li><input id="editconsole_links_6" type="checkbox" <?php if (!isset($user->profile_show_links_6) || $user->profile_show_links_6 == 1) print "checked"; ?> />&nbsp;<label for="editconsole_links_6">Address</label></li>
        <li><input id="editconsole_links_7" type="checkbox" <?php if (!isset($user->profile_show_links_7) || $user->profile_show_links_7 == 1) print "checked"; ?> />&nbsp;<label for="editconsole_links_7">Site Banner</label></li>
        <li><input id="editconsole_links_9" type="checkbox" <?php if (!isset($user->profile_show_links_9) || $user->profile_show_links_9 == 1) print "checked"; ?> />&nbsp;<label for="editconsole_links_9">Juice Bar</label></li>
      </ul>
      <?php if ((!arg(3) || !is_numeric(arg(3)))&& arg(0) != 'user'): ?>
        <ul id="editconsole">
          <li id="editconsole_content">Content
            <ul>
              <li><a href="<?php print $base_path . $path; ?>">View</a></li>
              <?php if (_mm_menu_access_add(arg(1))): ?>
                | <li><a href="<?php print $base_path . $path; ?>/contents/add">Add</a></li>
              <?php endif; ?>
              <?php if (_mm_menu_access_node_reorder(arg(1))): ?>
                | <li><a href="<?php print $base_path . $path; ?>/contents/reorder">Reorder</a></li>
              <?php endif; ?>
            </ul>
          </li>
          <?php if (_mm_menu_access_settings_tab(arg(1))): ?>
            <li id="editconsole_page">Page (<?php print arg(1); ?>)
              <ul>
                <?php if (_mm_menu_access_edit(arg(1))): ?>
                  <li><a href="<?php print $base_path . $path; ?>/settings/edit">Settings</a></li>
                <?php endif; ?>
                <?php if (_mm_menu_access_empty_bin(arg(1))): ?>
                  <li><a href="<?php print $base_path . $path; ?>/settings/empty">Empty recycle bin</a></li>
                <?php endif; ?>
                <?php if (_mm_menu_access_copy(arg(1))): ?>
                  | <li><a href="<?php print $base_path . $path; ?>/settings/copymove">Copy/Move</a></li>
                <?php endif; ?>
                <?php if (_mm_menu_access_delete(arg(1))): ?>
                  | <li><a href="<?php print $base_path . $path; ?>/settings/delete">Delete</a></li>
                <?php endif; ?>
                <?php if (_mm_menu_access_restore(arg(1))): ?>
                  | <li><a href="<?php print $base_path . $path; ?>/settings/restore">Restore</a></li>
                <?php endif; ?>
              </ul>
            </li>
          <?php endif; ?>
          <?php if (_mm_menu_access_sub(arg(1)) || _mm_menu_access_menu_reorder(arg(1))): ?>
            <li id="editconsole_sub">Sub-pages
              <ul>
                <?php if (_mm_menu_access_sub(arg(1))): ?>
                  <li><a href="<?php print $base_path . $path; ?>/settings/sub">Add Sub-page</a></li> |
                <?php endif; ?>
                <?php if (_mm_menu_access_menu_reorder(arg(1))): ?>
                  <li><a href="<?php print $base_path . $path; ?>/settings/reorder">Reorder Menu</a></li>
                <?php endif; ?>
              </ul>
            </li>
          <?php endif; ?>
          <li id="editconsole_help">Help
            <ul>
              <li><a href="http://go.middlebury.edu/drupal" target="_blank">Documentation</a></li> |
              <li><a href="<?php print $base_path . 'user/' . $user->uid . '/edit/Interface%20Settings'; ?>">Old Edit Console</a></li>
            </ul>
          </li>
        </ul>
      <?php else: ?>
        <?php print $tabs; ?>
      <?php endif; ?>
    </div>
  <?php else: ?>
    <?php print '<div id="tabs-wrapper" onmouseover="ecMouseOver();"><span id="tabs-title" ondblclick="ecDoubleClick();" unselectable="on">&nbsp;&nbsp;Edit Console&nbsp;for ' . $title . ' (' . arg(1) . ')</span>'; ?>
    <?php print '<div id="tabs-content">'; ?>
    <p style="padding:3px;"><input type="checkbox" id="livepreview" />&nbsp;<label for="livepreview">Preview Live Site</label> <?php if (module_exists('profile')): ?>| <a href="<?php print $base_path .'user/'. $user->uid . '/edit/Interface%20Settings'; ?>">Try the new Edit Console</a><?php endif; ?></p>
    <?php print '<ul class="tabs primary">'. $tabs .'</ul></div></div>'; ?>
  <?php endif; ?>
<?php endif; ?>