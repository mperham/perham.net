<?php get_header(); ?>

	<div id="content_box">
	
		<?php include (TEMPLATEPATH . '/l_sidebar.php'); ?>
	
		<div id="content" class="pages">
			<h2>Easy, tiger. This is a 404 page.</h2>
			<div class="entry">
				<p>You are <em>totally</em> in the wrong place. Do not pass GO; do not collect $200.</p>
				<p>Instead, try one of the following:</p>
				<ul>
					<li>Hit the "back" button on your browser.</li>
					<li>Head on over to the <a href="<?php bloginfo('url'); ?>">front page</a>.</li>
					<li>Try searching using the form in the sidebar.</li>
					<li>Click on a link in the sidebar.</li>
					<li>Use the navigation menu at the top of the page.</li>
					<li>Punt.</li>
				</ul>
			</div>
		</div>
		
		<?php include (TEMPLATEPATH . '/r_sidebar.php'); ?>
		
	</div>

<?php get_footer(); ?>