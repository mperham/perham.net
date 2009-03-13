<?php if (is_single()) : ?>

<div class="navigation">
	<span class="previous"><?php previous_post_link('&larr; %link') ?></span>
	<span class="next"><?php next_post_link('%link &rarr;') ?></span>
</div>
<div class="clear whitespace"></div>

<?php else : ?>

<div class="navigation">
	<div class="previous"><?php next_posts_link('&larr; Previous Entries') ?></div>
	<div class="next"><?php previous_posts_link('Next Entries &rarr;') ?></div>
</div>
<div class="clear flat"></div>

<?php endif; ?>