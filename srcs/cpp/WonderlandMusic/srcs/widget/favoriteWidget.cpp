#include "favoriteWidget.h"
#include <QJsonObject>
#include <QMouseEvent>
#include "musicContreWidget.h"
#include "../application/appDataJsonKey.h"
#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appMusicManage.h"
#include "../application/appUserInterfaceManage.h"
#include "../application/jsonKey/favoriteWidgetJsonKey.h"
#include "../item/favoriteItem.h"
#include "../itemWidget/favoriteItemWidget.h"
#include "../mutex/userMutex.h"
#include "../scrollArea/musicContreScrollArea.h"
#include "../stackedWidget/mainStackedWidget.h"
#include "../window/mainWindow.h"
#include "../window/musicListWindow.h"
#include "../window/playerWindow.h"

FavoriteWidget::FavoriteWidget( QWidget *parent ) : QWidget( parent ) {
}

bool FavoriteWidget::deleteResource( ) {
	selectFavorite = nullptr;
	favoriteVector.clear( );
	return true;
}

FavoriteWidget::~FavoriteWidget( ) {
	deleteResource( );
}

void FavoriteWidget::setSelectFavorite( FavoriteItem *const select_favorite ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto musicContreWidget = appInstance->getAppUserInterfaceManage( )->getMainWindow( )->getMainStackedWidget( )->getPlayerWindow( )->getMusicListWindow( )->getMusicContreScrollArea( )->getMusicContreWidget( );

	if( selectFavorite && selectFavorite != rootItem ) {
		selectFavorite->disconnect( selectFavorite, &FavoriteItem::signal_change_name_finished, this, &FavoriteWidget::slot_change_name_finished );

		selectFavorite->disconnect( selectFavorite, &FavoriteItem::signal_change_vector_finished, this, &FavoriteWidget::slot_change_vector_finished );

		selectFavorite->disconnect( selectFavorite, &QObject::destroyed, this, &FavoriteWidget::slot_destroyed );
	}
	selectFavorite = select_favorite;
	if( selectFavorite && rootItem != selectFavorite ) {
		connect( selectFavorite, &FavoriteItem::signal_change_name_finished, this, &FavoriteWidget::slot_change_name_finished );
		connect( selectFavorite, &FavoriteItem::signal_change_vector_finished, this, &FavoriteWidget::slot_change_vector_finished );
		connect( selectFavorite, &QObject::destroyed, this, &FavoriteWidget::slot_destroyed );
		musicContreWidget->setMusicInfoVector( selectFavorite->getMusicItemvVector( ) );
		emit signal_click_favorite_Item( );
		return;
	}
	if( rootItem && ( selectFavorite == nullptr || rootItem == select_favorite ) ) {
		selectFavorite = select_favorite;
		musicContreWidget->setMusicInfoVector( selectFavorite->getMusicItemvVector( ) );
		emit signal_click_favorite_Item( );
		return;
	}
}

void FavoriteWidget::updateAppMusicManageInof( const std::vector< FavoriteItem * > &vector ) {
	// 顶部
	FavoriteItemWidget *itemWidget = rootItem->getFavoriteItemWidget( );
	itemWidget->setParent( this );
	itemWidget->show( );
	setSelectFavorite( rootItem );
	// 排序后续
	size_t count = vector.size( );
	favoriteVector.resize( count );
	if( count == 0 )
		return;
	auto vectorData = vector.data( );
	auto favoriteData = favoriteVector.data( );
	size_t index = 0;
	for( ; index < count; index += 1 ) {
		favoriteData[ index ] = vectorData[ index ];
		itemWidget = favoriteData[ index ]->getFavoriteItemWidget( );
		itemWidget->setParent( this );
		itemWidget->show( );
	}

	emit signal_update_item_over( );
	updateLayout( );
}

bool FavoriteWidget::getJsonData( QJsonObject &get_json_object ) const {
	auto appDataJsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( );
	auto jsonKey = appDataJsonKey->getFavoriteWidget( );

	QJsonObject jsonObject;
	jsonObject.insert( jsonKey->getWidth( ), this->width( ) );
	jsonObject.insert( jsonKey->getHeight( ), this->height( ) );
	get_json_object.insert( jsonKey->getObjectName( ), jsonObject );
	return true;
}

bool FavoriteWidget::setJsonData( const QJsonObject &set_json_object ) {
	if( set_json_object.empty( ) )
		return false;
	auto appDataJsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( );
	auto jsonKey = appDataJsonKey->getFavoriteWidget( );
	auto find = set_json_object.find( jsonKey->getObjectName( ) );
	auto end = set_json_object.end( );
	if( find == end )
		return false;

	auto jsonObject = find.value( ).toObject( );
	end = jsonObject.end( );
	qint64 width = this->width( );
	qint64 height = this->height( );
	find = jsonObject.find( jsonKey->getWidth( ) );
	if( find != end )
		width = find.value( ).toInteger( );
	find = jsonObject.find( jsonKey->getHeight( ) );
	if( find != end )
		height = find.value( ).toInteger( );
	resize( width, height );
	adjustSize( );
	return true;
}

bool FavoriteWidget::init( ) {
	return true;
}

bool FavoriteWidget::initBefore( ) {
	deleteResource( );

	return true;
}

bool FavoriteWidget::initAfter( ) {
	auto appMusicManage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( );
	rootItem = appMusicManage->getRootItem( );
	FavoriteItemWidget *itemWidget = rootItem->getFavoriteItemWidget( );
	itemWidget->setParent( this );
	itemWidget->show( );
	// 没有旧记录。则使用默认项
	if( selectFavorite == nullptr )
		setSelectFavorite( rootItem );

	updateLayout( );
	connect( appMusicManage, &AppMusicManage::signal_update_favorite_item, this, &FavoriteWidget::slot_update_favorite_item );
	return true;
}

FavoriteItem * FavoriteWidget::getSelectFavorite( ) const {
	return selectFavorite;
}

const std::vector< FavoriteItem * > & FavoriteWidget::getFavoriteVector( ) const {
	return favoriteVector;
}

void FavoriteWidget::updateLayout( ) {
	int maxWidth = 0;
	int maxHeight = 0;
	int compWidth;
	int offsetX = 10;
	// 顶部
	FavoriteItemWidget *itemWidget = rootItem->getFavoriteItemWidget( );
	itemWidget->adjustSize( );
	itemWidget->move( 0, maxHeight );
	maxHeight += itemWidget->height( );
	compWidth = itemWidget->width( );
	if( compWidth > maxWidth )
		maxWidth = compWidth;
	size_t count = favoriteVector.size( );
	if( count ) {
		auto data = favoriteVector.data( );
		size_t index;
		for( index = 0; index < count; index += 1 ) {
			itemWidget = data[ index ]->getFavoriteItemWidget( );
			itemWidget->adjustSize( );
			itemWidget->move( offsetX, maxHeight );
			maxHeight += itemWidget->height( );
			compWidth = itemWidget->width( ) + offsetX;
			if( compWidth > maxWidth )
				maxWidth = compWidth;
		}
	}
	resize( maxWidth, maxHeight );
	emit signal_update_layout_over( );
}

bool FavoriteWidget::resetFavoriteItem( const std::vector< FavoriteItem * > &favorite_vector ) {
	favoriteVector = favorite_vector;
	return true;
}

FavoriteItem * FavoriteWidget::getSelectItem( const QString &name ) const {
	size_t count = favoriteVector.size( );
	if( count ) {
		auto data = favoriteVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( data[ index ]->getFavoriteName( ) == name )
				return data[ index ];
	}
	return nullptr;
}

FavoriteItem * FavoriteWidget::getSelectItem( const QPoint &pos ) const {
	size_t count = favoriteVector.size( );
	if( count ) {
		auto data = favoriteVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( data[ index ]->getFavoriteItemWidget( )->geometry( ).contains( pos ) )
				return data[ index ];
	}
	return nullptr;
}

FavoriteItem * FavoriteWidget::leftClickPos( const QPoint &pos ) {
	selectFavorite = getSelectItem( pos );
	if( selectFavorite == nullptr )
		return nullptr;
	emit signal_click_favorite_Item( );
	return selectFavorite;
}

FavoriteItem * FavoriteWidget::rightClickPos( const QPoint &pos ) {
	selectFavorite = getSelectItem( pos );
	emit signal_click_favorite_Item( );
	emit signal_favorite_Item_pop_menu( );
	return selectFavorite;
}

void FavoriteWidget::slot_change_name_finished( ) {
}

void FavoriteWidget::slot_change_vector_finished( ) {
	if( selectFavorite ) {
		auto appInstance = AppInstance::getAppInstance( );
		auto musicContreWidget = appInstance->getAppUserInterfaceManage( )->getMainWindow( )->getMainStackedWidget( )->getPlayerWindow( )->getMusicListWindow( )->getMusicContreScrollArea( )->getMusicContreWidget( );
		musicContreWidget->setMusicInfoVector( selectFavorite->getMusicItemvVector( ) );
		updateLayout( );
		return;
	}
	// 没有被正确运行并且返回
	setSelectFavorite( rootItem );
}

void FavoriteWidget::slot_destroyed( QObject *delete_ptr ) {
	if( selectFavorite != delete_ptr )
		return;

	selectFavorite->disconnect( selectFavorite, &FavoriteItem::signal_change_name_finished, this, &FavoriteWidget::slot_change_name_finished );

	selectFavorite->disconnect( selectFavorite, &FavoriteItem::signal_change_vector_finished, this, &FavoriteWidget::slot_change_vector_finished );

	selectFavorite->disconnect( selectFavorite, &QObject::destroyed, this, &FavoriteWidget::slot_destroyed );
	selectFavorite = nullptr;
}

void FavoriteWidget::slot_update_favorite_item( const FavoriteItemWidget *favorite_widget ) {
	if( favorite_widget != this->selectFavorite->getFavoriteItemWidget( ) )
		return;
	auto appInstance = AppInstance::getAppInstance( );
	auto musicContreWidget = appInstance->getAppUserInterfaceManage( )->getMainWindow( )->getMainStackedWidget( )->getPlayerWindow( )->getMusicListWindow( )->getMusicContreScrollArea( )->getMusicContreWidget( );
	musicContreWidget->setMusicInfoVector( selectFavorite->getMusicItemvVector( ) );
}
