<?php
/*
Template Name: BarePage
*/
?>
<?php get_header(); ?>

	<div id="content_box">
	
		<div id="content" class="pages">

			<?php if (have_posts()) : while (have_posts()) : the_post(); ?>
			
			<h2><?php the_title(); ?></h2>	
			<div class="entry">		
				<?php the_content('<p>Read the rest of this page &rarr;</p>'); ?>
				<?php link_pages('<p><strong>Pages:</strong> ', '</p>', 'number'); ?>
			</div>
			<?php if ('open' == $post-> comment_status) { ?>
			<p class="tagged"><a href="<?php the_permalink() ?>#comments"><?php comments_number('No Comments', '1 Comment', '% Comments'); ?></a></p>
			<div class="clear"></div>
			<?php } else { ?>
			<div class="clear rule"></div>
			<?php } ?>
			
			<?php endwhile; endif; ?>
			
			<?php if ('open' == $post-> comment_status) { comments_template(); } ?>

		</div>
		
		<?php include (TEMPLATEPATH . '/r_sidebar.php'); ?>

	</div>

<?php get_footer(); ?>
