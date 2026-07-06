#include "playerListTopWidgetJsonKey.h"

#include "../appDataManage.h"
#include "../appInstance.h"

bool PlayerListTopWidgetJsonKey::init( ) {
	objectName = "app.play.window.item.top";
	width = "width";
	itemSplitWidth = "item.split";
	itemIndexWidth = "item.index";
	itemMusicNameWidth = "item.name";
	itemMusicSingerWidth = "item.singer";
	itemMusicDurationWidth = "item.duration";
	itemWidgetBeforeWidth = "item.before";
	itemWidgetAfterWidth = "item.after";
	return true;
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

const QString & PlayerListTopWidgetJsonKey::getObjectName( ) const {
	return objectName;
}

const QString & PlayerListTopWidgetJsonKey::getWidth( ) const {
	return width;
}
