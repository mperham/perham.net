<?php
/*
Template Name: Archives
*/
?>

<?php get_header(); ?>
		
	<div id="content_box">
	
		<!--?php include (TEMPLATEPATH . '/l_sidebar.php'); ?-->

		<div id="content" class="pages">
		
			<h2>Browse the Archives...</h2>
			<div class="entry">
				<h3 class="top">by month:</h3>
				<ul>
					<?php wp_get_archives('type=monthly'); ?>
				</ul>
				<h3>by Category:</h3>
				<ul>
					<?php wp_list_categories('title_li=0'); ?>
				</ul>
			</div>
			<div class="clear rule"></div>
			
		</div>	
				
		<?php include (TEMPLATEPATH . '/r_sidebar.php'); ?>
			
	</div>
		
<?php get_footer(); ?>