<div id="sidebar">
	<ul class="sidebar_list">
		<li class="widget">
			<h2>Contact Me</h2>
<ul>
<li>Email: mperham AT gmail.com</li>
<li>Twitter: <a href="http://twitter.com/mperham">mperham</a></li>
</ul>
		</li>
		<?php if (!function_exists('dynamic_sidebar') || !dynamic_sidebar(2)) : ?>
		<!--li class="widget">
			<h2>Search It!</h2>
			<?php include (TEMPLATEPATH . '/searchform.php'); ?>
		</li>
		<li class="widget">
			<h2>Recent Entries</h2>
			<ul>
				<?php query_posts('showposts=10'); ?>
				<?php if (have_posts()) : while (have_posts()) : the_post(); ?>
				<li><a href="<?php the_permalink() ?>"><?php the_title() ?></a><span class="recent_date"><?php the_time('n.j') ?></span></li>
				<?php endwhile; endif; ?>
				<li><a href="<?php bloginfo('url'); ?>/archives" title="Visit the archives!">Visit the archives for more!</a></li>
			</ul>
		</li-->
		<?php if (function_exists('get_flickrrss')) { ?>
		<li class="widget">
			<h2><span class="flickr_blue">Flick</span><span class="flickr_pink">r</span></h2>
			<ul class="flickr_stream">
				<?php get_flickrrss(); ?>
			</ul>
		</li>
		<?php } ?>
		<?php get_links_list('id'); ?>
		<?php endif; ?>
	</ul>
</div>