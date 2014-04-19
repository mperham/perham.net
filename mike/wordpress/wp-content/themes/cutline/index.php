<?php get_header(); ?>

	<div id="content_box">
	
		<!--?php include (TEMPLATEPATH . '/l_sidebar.php'); ?-->

		<div id="content" class="posts">

		<?php if (have_posts()) : ?>
			
			<?php while (have_posts()) : the_post(); ?>
					
			<h2><a href="<?php the_permalink() ?>" rel="bookmark" title="Permanent Link to <?php the_title(); ?>"><?php the_title(); ?></a></h2>
			<h4><?php the_time('F jS, Y') ?><!-- by <?php the_author() ?> --> &middot; <?php comments_popup_link('No Comments', '1 Comment', '% Comments'); ?></h4>
			<div class="entry">
				<?php the_content('[Read more &rarr;]'); ?>
			</div>	
			<p class="tagged"><span class="add_comment"><?php comments_popup_link('&rarr; No Comments', '&rarr; 1 Comment', '&rarr; % Comments'); ?></span><strong>Tags:</strong> <?php the_category(' &middot; ') ?></p>
			<div class="clear"></div>
			
			<?php endwhile; ?>
			
			<?php include (TEMPLATEPATH . '/navigation.php'); ?>
			
		<?php else : ?>
	
			<h2 class="page_header center">Not Found</h2>
			<div class="entry">
				<p class="center">Sorry, but you are looking for something that isn't here.</p>
				<?php include (TEMPLATEPATH . "/searchform.php"); ?>
			</div>
	
		<?php endif; ?>
		
		</div>
	
		<?php include (TEMPLATEPATH . '/r_sidebar.php'); ?>
	
	</div>

<?php get_footer(); ?>