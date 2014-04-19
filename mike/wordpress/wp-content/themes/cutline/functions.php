<?php
/* blast you red baron! */
require_once (ABSPATH . WPINC . '/class-snoopy.php');

if ( function_exists('register_sidebars') )
    register_sidebars(2);

$current = 'r167';
function k2info($show='') {
global $current;
	switch($show) {
	case 'version' :
    	$info = 'Beta Two '. $current;
    	break;
    case 'scheme' :
    	$info = bloginfo('template_url') . '/styles/' . get_option('k2scheme');
    	break;
    }
    echo $info;
}

function k2update() {
	if ( !empty($_POST) ) {
		if ( isset($_POST['k2scheme_file']) ) {
			$k2scheme_file = $_POST['k2scheme_file'];
			update_option('k2scheme', $k2scheme_file, '','');
		}
		if ( isset($_POST['livesearch']) ) {
			$search = $_POST['livesearch'];
			update_option('k2livesearch', $search, '','');
		}
		if ( isset($_POST['livecommenting']) ) {
			$commenting = $_POST['livecommenting'];
			update_option('k2livecommenting', $commenting, '','');
		}
		if ( isset($_POST['widthtype']) ) {
			$widthtype = $_POST['widthtype'];
			update_option('k2widthtype', $widthtype, '','');
		}
		if ( isset($_POST['asides_text']) ) {
			$asides_text = $_POST['asides_text'];
			update_option('k2asidescategory', $asides_text, '','');
		}
		if ( isset($_POST['asidesposition']) ) {
			$asidesposition = $_POST['asidesposition'];
			update_option('k2asidesposition', $asidesposition, '','');
		}
		if ( isset($_POST['asidesnumber']) ) {
			$asidesnumber = $_POST['asidesnumber'];
			update_option('k2asidesnumber', $asidesnumber, '','');
		}
		if ( isset($_POST['about_text']) ) {
			$about = $_POST['about_text'];
			update_option('k2aboutblurp', $about, '','');
		}
		if ( isset($_POST['deliciousname']) ) {
			$name = $_POST['deliciousname'];
			update_option('k2deliciousname', $name, '','');
		}
		if ( isset($_POST['archives']) ) {
			$add = $_POST['archives'];
			update_option('k2archives', $add, '','');
			create_archive();
		} else {
		// thanks to Michael Hampton, http://www.ioerror.us/ for the assist
			$remove = '';
			update_option('k2archives', $remove, '','');
			delete_archive();
		}

		if ( isset($_POST['configela']) ) {
			if (!setup_archive()) unset($_POST['configela']);
		}
	}
}

function create_archive() {
global $wpdb, $user_ID;
get_currentuserinfo();
	$check = $wpdb->query("SELECT * from $wpdb->posts WHERE post_title = 'Archives'");
		if(!$check) {
	$message = "Do not edit this page";
	$title_message = 'Archives';
	$content = apply_filters('content_save_pre', $message);
	$post_title = apply_filters('title_save_pre', $title_message);
	$now = current_time('mysql');
	$now_gmt = current_time('mysql', 1);
	$post_author = $user_ID;
	$id_result = $wpdb->get_row("SHOW TABLE STATUS LIKE '$wpdb->posts'");
	$post_ID = $id_result->Auto_increment;
	$post_name = sanitize_title($post_title, $post_ID);
	$ping_status = get_option('default_ping_status');
	$comment_status = get_option('default_comment_status');
	
	$postquery ="INSERT INTO $wpdb->posts
			(ID, post_author, post_date, post_date_gmt, post_content, post_title, post_excerpt,  post_status, comment_status, ping_status, post_password, post_name, to_ping, post_modified, post_modified_gmt, post_parent, menu_order)
			VALUES
			('$post_ID', '$post_author', '$now', '$now_gmt', '$content', '$post_title', '', 'static', '$comment_status', '$ping_status', '', '$post_name', '', '$now', '$now_gmt', '', '')";
	$result = $wpdb->query($postquery);
	$metaquery = "INSERT INTO $wpdb->postmeta(meta_id, post_id, meta_key, meta_value) VALUES('', '$post_ID', '_wp_page_template', 'archives.php')";
	$result2 = $wpdb->query($metaquery);
	}
}

function delete_archive() {
global $wpdb;
	$check = $wpdb->query("SELECT * from $wpdb->posts WHERE post_title = 'Archives'");
		if($check) {
	$burninate = $wpdb->query("DELETE from $wpdb->posts WHERE post_title = 'Archives' and post_status = 'static'");
	$result = $wpdb->query($burninate);
	}
}

function setup_archive() {
	global $wpdb;

	if (file_exists(ABSPATH . 'wp-content/plugins/UltimateTagWarrior/ultimate-tag-warrior-core.php') && in_array('UltimateTagWarrior/ultimate-tag-warrior.php', get_option('active_plugins'))) {
		$menu_order="chrono,tags,cats";
	} else {
		$menu_order="chrono,cats";
	}

	$initSettings = array(

	// we always set the character set from the blog settings
		'newest_first' => 0,
		'num_entries' => 1,
		'num_entries_tagged' => 0,
		'num_comments' => 1,
		'fade' => 1,
		'hide_pingbacks_and_trackbacks' => 1,
		'use_default_style' => 1,
		'paged_posts' => 1,
		'selected_text' => '',
		'selected_class' => 'selected',
		'comment_text' => '<span>%</span>',
		'number_text' => '<span>%</span>',
		'number_text_tagged' => '(%)',
		'closed_comment_text' => '<span>%</span>',
		'day_format' => 'jS',
		'error_class' => 'alert',
	// allow truncating of titles
		'truncate_title_length' => 0,
		'truncate_cat_length' => 25,
		'truncate_title_text' => '&#8230;',
		'truncate_title_at_space' => 1,
		'abbreviated_month' => 1,
		'tag_soup_cut' => 0,
		'tag_soup_X' => 0,
	// paged posts related stuff
		'paged_post_num' => 15,
		'paged_post_next' => '&laquo; previous 15 posts',
		'paged_post_prev' => 'next 15 posts &raquo;',
	// default text for the tab buttons
		'menu_order' => $menu_order,
		'menu_month' => 'Chronology',
		'menu_cat' => 'Taxonomy',
		'menu_tag' => 'Folksonomy',
		'before_child' => '&nbsp;&nbsp;&nbsp;',
		'after_child' => '',
		'loading_content' => '<img src="'.get_bloginfo('template_url').'/images/spinner.gif" class="elaload" alt="Spinner" />',
		'idle_content' => '',
		'excluded_categories' => '0');

	if (function_exists('af_ela_set_config')) {
		$ret = af_ela_set_config($initSettings);
	}

	return $ret;
}

// if we can't find k2 installed lets go ahead and install all the options that run K2.  This should run only one more time for all our existing users, then they will just be getting the upgrade function if it exists.

if (!get_option('k2installed')) {
add_option('k2installed', $current, 'This options simply tells me if K2 has been installed before', $autoload);
add_option('k2aboutblurp', 'This is the about text', 'Allows you to write a small blurp about you and your blog, which will be put on the frontpage', $autoload);
add_option('k2asidescategory', '0', 'A category which will be treated differently from other categories', $autoload);
add_option('k2asidesposition', '0', 'Whether to use inline or sidebar asides', $autoload);
add_option('k2livesearch', 'live', "If you don't trust JavaScript and Ajax, you can turn off LiveSearch. Otherwise I suggest you leave it on", $autoload); // (live & classic)
add_option('k2asidesnumber', '3', 'The number of Asides to show in the Sidebar. Default is 3.', $autoload);
add_option('k2widthtype', 'flexible', "Determines whether to use flexible or fixed width.", $autoload); // (flexible & fixed)
add_option('k2deliciousname', '', 'Makes use of Alexander Malovs Delicious plugin to show the delicious links on the sidebar.', $autoload);
add_option('k2archives', '', 'Set whether K2 has a Live Archive page', $autoload);
add_option('k2scheme', '', 'Choose the Scheme you want K2 to use', $autoload);
add_option('k2livecomments', '0', "If you don't trust JavaScript and Ajax, you can turn off Live Commenting. Otherwise I suggest you leave it on", $autoload);
}

// Here we handle upgrading our users with new options and such.  If k2installed is in the DB but the version they are running is lower than our current version, trigger this event.

	elseif (get_option('k2installed') < $current) {
	/* Do something! */
	//add_option('k2upgrade-test', 'this is the text', 'Just testing', $autoload);
}

// Let's add the options page.
add_action ('admin_menu', 'k2menu');

$k2loc = '../themes/' . basename(dirname($file)); 

function k2menu() {
	add_submenu_page('themes.php', 'Cutline Options', 'Cutline Options', 5, $k2loc . 'functions.php', 'menu');
}

function menu() {
	load_plugin_textdomain('k2options');
	//this begins the admin page
?>

<?php if (isset($_POST['Submit'])) : ?>
	<div class="updated">
		<p><?php _e('Cutline Options have been updated'); ?></p>
	</div>
<?php endif; ?>

<div class="wrap">

	<h2><?php _e('Cutline Options'); ?></h2>
	<form name="dofollow" action="" method="post">
	  <input type="hidden" name="action" value="<?php k2update(); ?>" />
	  <input type="hidden" name="page_options" value="'dofollow_timeout'" />
		<table width="700px" cellspacing="2" cellpadding="5" class="editform">
			<?php if (function_exists('delicious')) { ?> 
			<tr valign="top">
			<th scope="row"><?php echo __('Delicious User Name'); ?></th>
			<td>
				<label for="deliciousname"><?php echo __('Delicious User Name'); ?></label>
				<input name="deliciousname" style="width: 300px;" id="deliciousname" value="<?php echo get_option('k2deliciousname'); ?>">
				<p><small>Enter your delicious username here, to make use of <a href="http://www.w-a-s-a-b-i.com/archives/2004/10/15/delisious-cached/">Alexander Malov's del.icio.us plugin</a></small></p>
			</td>
			</tr>
			<?php } ?>
			<tr valign="top">
			<th scope="row"><?php echo __('Archives Page'); ?></th>
			<td>
				<input name="archives" id="add-archive" type="checkbox" value="add_archive" <?php checked('add_archive', get_option('k2archives')); ?> />
				<label for="add-archives"><?php _e('Enable the Cutline Archives page') ?></label>
				<p><small>Enabling this checkbox will create an Archives Page, which will show up in your blog menu as the first page.</small></p>
			</td>
			</tr>
		</table>
	
		<p class="submit"><input type="submit" name="Submit" value="<?php _e('Update Options') ?> &raquo;" /></p>
	
	</form>
</div>

<div class="wrap">
	<p style="text-align: center;">Get help with Cutline at <a href="http://cutline.tubetorial.com">the Cutline support site</a>.</p>
</div>

<?php } // this ends the admin page ?>
