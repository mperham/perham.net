<div id="l_sidebar">
<!--a href="http://en.oreilly.com/railseurope2008/">
<img src="/images/railseurope2008_att_210x60.gif" width="210" height="60"  border="0"  alt="RailsConf Europe 2008" title="RailsConf Europe 2008"  />
</a>
<a href="http://www.lonestarrubyconf.com"><img src="/images/LSRC_2008_presenter.png" width="157" height="109" border="0" /></a>
<a href="http://conferences.oreilly.com/oscon">
<img src="/images/oscon2008_banner_speaker_210x60.gif" width="210" height="60"  border="0"  alt="OSCON 2008" title="OSCON 2008"  />
</a>
	<img src="/images/aac_sm.jpg" style="padding: 5px 0;"/>
	<img src="/images/RubyConf2007.png" style="padding-bottom: 5px;"/>
	<img src="/images/lonestar.jpg"/-->
	<ul class="sidebar_list">
                <?php if (!function_exists('dynamic_sidebar') || !dynamic_sidebar(1)) : ?>
		<li class="widget">
			<h2>Categories</h2>
			<ul>
				<?php wp_list_cats('sort_column=name'); ?>
			</ul>
		</li>
		<li class="widget">
			<h2>Archives</h2>
			<ul>
				<?php wp_get_archives('type=monthly'); ?>
			</ul>
		</li>
		<li class="widget">
			<h2>Admin</h2>
			<ul>
				<?php wp_register(); ?>
				<li><?php wp_loginout(); ?></li>
				<li><a href="http://www.wordpress.org/">WordPress</a></li>
				<?php wp_meta(); ?>
				<li><a href="http://validator.w3.org/check?uri=referer">XHTML</a></li>
			</ul>
		</li>
		<?php endif; ?>
	</ul>
</div>
