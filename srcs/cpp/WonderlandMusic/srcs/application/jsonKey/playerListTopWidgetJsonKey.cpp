#include "playerListTopWidgetJsonKey.h"

#include "../appDataManage.h"
#include "../appInstance.h"

bool PlayerListTopWidgetJsonKey::init( ) {
	itemWidth = "width";
	itemSplitWidth = "split";
	itemIndexWidth = "index";
	itemMusicNameWidth = "name";
	itemMusicSingerWidth = "singer";
	itemMusicDurationWidth = "duration";
	itemWidgetBeforeWidth = "before";
	itemWidgetAfterWidth = "after";
	return true;
}

const QString & PlayerListTopWidgetJsonKey::getItemWidth( ) const {
	return itemWidth;
}

const QString & PlayerListTopWidgetJsonKey::getItemSplitWidth( ) const {
	return itemSplitWidth;
}

const QString & PlayerListTopWidgetJsonKey::getItemIndexWidth( ) const {
	return itemIndexWidth;
}

const QString & PlayerListTopWidgetJsonKey::getItemMusicNameWidth( ) const {
	return itemMusicNameWidth;
}

const QString & PlayerListTopWidgetJsonKey::getItemMusicSingerWidth( ) const {
	return itemMusicSingerWidth;
}

const QString & PlayerListTopWidgetJsonKey::getItemMusicDurationWidth( ) const {
	return itemMusicDurationWidth;
}

const QString & PlayerListTopWidgetJsonKey::getItemWidgetBeforeWidth( ) const {
	return itemWidgetBeforeWidth;
}

const QString & PlayerListTopWidgetJsonKey::getItemWidgetAfterWidth( ) const {
	return itemWidgetAfterWidth;
}
