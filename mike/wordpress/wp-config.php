<?php
// ** MySQL settings ** //
define('DB_NAME', 'perham');     // The name of the database^M
define('DB_USER', 'mike');     // Your MySQL username^M
define('DB_PASSWORD', 'Password'); // ...and password^M
define('DB_HOST', 'localhost');     // 99% chance you won't need to change this value^M
define('DB_CHARSET', 'utf8');
define('DB_COLLATE', '');

define('WP_CACHE', true);

define('AUTH_KEY',        'g-n7tT<;49x(q:[.e[^CrWMNt>SrzpO5Z-@so6o?H>N]^)v$]ovE xqYdW.o2)Vv');
define('SECURE_AUTH_KEY', '0_{-6.,|%6TGe|AbColQtn!ofv {P|=P-Tm>5M+`G8~[vLv8js>/: Ynl9t5`4K>');
define('LOGGED_IN_KEY',   'z5X+%{J%m$TZw]0#+a-]!O^mEFG=UV_~xV/EN#U6rkKEOcUGjU5DD| }=B*,+]WU');
define('NONCE_KEY',       'e$/FZGp^8q[W)1!+l^*.qk#/%./2l1@EYr<#:N<E^}Y~6s9-Ur/n5/FU135^HC!+');

// You can have multiple installations in one database if you give each a unique prefix
$table_prefix  = 'wp_';   // Only numbers, letters, and underscores please!

// Change this to localize WordPress.  A corresponding MO file for the
// chosen language must be installed to wp-content/languages.
// For example, install de.mo to wp-content/languages and set WPLANG to 'de'
// to enable German language support.
define ('WPLANG', '');

/* That's all, stop editing! Happy blogging. */

define('ABSPATH', dirname(__FILE__).'/');
require_once(ABSPATH.'wp-settings.php');
?>
