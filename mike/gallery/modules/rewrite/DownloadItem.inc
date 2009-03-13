<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2007 Bharat Mediratta
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA.
 */

/**
 * Send a binary item as HTML instead.
 * This allows viewing via direct URL (browser will see it is HTML), but not using images directly
 * in a <img> tag on another site.
 *
 * @package Rewrite
 * @subpackage UserInterface
 * @author Alan Harder <alan.harder@sun.com>
 * @version $Revision: 15513 $
 */
class DownloadItemView extends GalleryView {

    /**
     * @see GalleryView::isImmediate
     */
    function isImmediate() {
	return true;
    }

    /**
     * @see GalleryView::isAllowedInEmbedOnly
     */
    function isAllowedInEmbedOnly() {
	return true;
    }

    /**
     * @see GalleryView::shouldSaveSession
     */
    function shouldSaveSession() {
	return false;
    }

    /**
     * @see GalleryView::renderImmediate
     */
    function renderImmediate($status, $error) {
	$itemId = GalleryUtilities::getRequestVariables('itemId');
	if (empty($itemId)) {
	    return GalleryCoreApi::error(ERROR_BAD_PARAMETER);
	}
	list ($ret, $image) = GalleryCoreApi::loadEntitiesById($itemId);
	if ($ret) {
	    return $ret;
	}

	header('Content-type: text/html; charset=UTF-8');
	header('Expires: ' . GalleryUtilities::getHttpDate(time() - 100));
	header('Cache-Control: no-store, no-cache, must-revalidate, post-check=0, pre-check=0');
	header('Pragma: no-cache');

	if (GalleryUtilities::isA($image, 'GalleryItem')) {
	    $item = $image;
	} else {
	    list ($ret, $item) = GalleryCoreApi::loadEntitiesById($image->getParentId());
	    if ($ret) {
		return $ret;
	    }
	}
	list ($ret, $albumId) = GalleryCoreApi::getDefaultAlbumId();
	if ($ret) {
	    return $ret;
	}
	list ($ret, $album) = GalleryCoreApi::loadEntitiesById($albumId);
	if ($ret) {
	    return $ret;
	}

	GalleryCoreApi::requireOnce('modules/core/classes/GalleryTemplate.class');
	$template = new GalleryTemplate(dirname(dirname(dirname(__FILE__))));
	$template->setVariable('l10Domain', 'modules_rewrite');
	$template->setVariable('item', (array)$item);
	$template->setVariable('image', (array)$image);
	$template->setVariable('gallery', (array)$album);

	$ret = $template->display('gallery:modules/rewrite/templates/DownloadItem.tpl');
	if ($ret) {
	    return $ret;
	}

	return null;
    }
}
?>
