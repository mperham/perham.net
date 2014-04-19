<?php get_header(); ?>

	<div id="content_box">
	
		<!--?php include (TEMPLATEPATH . '/l_sidebar.php'); ?-->
		
		<div id="content" class="posts">
			
		<?php if (have_posts()) : while (have_posts()) : the_post(); ?>
		
		<?php include (TEMPLATEPATH . '/navigation.php'); ?>
						
			<h2><?php the_title(); ?></h2>
			<h4><?php the_time('F jS, Y') ?><!-- by <?php the_author() ?> --> &middot; <a href="<?php the_permalink() ?>#comments"><?php comments_number('No Comments', '1 Comment', '% Comments'); ?></a></h4>
			<div class="entry">
				<?php the_content('<p>Read the rest of this entry &raquo;</p>'); ?>
				<?php link_pages('<p><strong>Pages:</strong> ', '</p>', 'number'); ?>
			</div>
			<p class="tagged"><strong>Tags:</strong> <?php the_category(' &middot; ') ?></p>
			<div class="clear"></div>
			
			<?php comments_template(); ?>
			
		<?php endwhile; else: ?>
		
			<h2 class="page_header">Uh oh.</h2>
			<div class="entry">
				<p>Sorry, no posts matched your criteria. Wanna search instead?</p>
				<?php include (TEMPLATEPATH . '/searchform.php'); ?>
			</div>
			
		<?php endif; ?>
		
		</div>
		
		<?php include (TEMPLATEPATH . '/r_sidebar.php'); ?>
			
	</div>

<?php get_footer(); ?>