#include "appMusicManage.h"
#include <QJsonObject>
#include <QMediaPlayer>
#include "appDataJsonKey.h"
#include "appDataManage.h"
#include "appInstance.h"
#include "appMenuManage.h"
#include "appMusicDecoder.h"
#include "appUserInterfaceManage.h"
#include "applicationManage.h"
#include "../dockWidget/favoritemDockWidget.h"
#include "../dockWidget/musicItemSizeInfoDockWidget.h"
#include "../item/favoriteItem.h"
#include "../item/musicItem.h"
#include "../itemWidget/favoriteItemWidget.h"
#include "../itemWidget/musicInfoItemWidget.h"
#include "../menu/favoriteWidgetMenu.h"
#include "../menu/playerListWidgetMenu.h"
#include "../mutex/userMutex.h"
#include "../scrollArea/favoriteSrollArea.h"
#include "../scrollArea/musicContreScrollArea.h"
#include "../stackedWidget/mainStackedWidget.h"
#include "../tools/appJsonKeyTools.h"
#include "../tools/appTranslateTools.h"
#include "../tools/pathTools.h"
#include "../tools/widgetTools.h"
#include "../widget/favoriteWidget.h"
#include "../widget/musicContreWidget.h"
#include "../window/mainWindow.h"
#include "../window/musicListWindow.h"
#include "../window/playerWindow.h"
#include "jsonKey/appMusicManageJsonKey.h"
#include "translate/appMusicManageTranslate.h"

void AppMusicManage::removeVectorFavoriteItem( FavoriteItem *delete_ptr ) {
	size_t count = favoriteItemVector.size( );
	auto data = favoriteItemVector.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		if( data[ index ] == delete_ptr ) {
			releaseFavoriteItemFreeConnect( delete_ptr );
			favoriteItemVector.erase( favoriteItemVector.begin( ) + index );
			break;
		}
}

void AppMusicManage::removeVectorMusicItem( MusicItem *delete_ptr ) {
	releaseMusicItemFreeConnect( delete_ptr );
	rootItem->removeMusicItem( delete_ptr );
}

bool AppMusicManage::deleteResource( ) {
	releaseFavoriteItemFreeConnect( );
	releaseMusicItemFreeConnect( );
	size_t index;
	size_t count;
	count = loadMediaVector.size( );
	if( count ) {
		auto data = loadMediaVector.data( );
		for( index = 0; index < count; index += 1 )
			delete data[ index ];
		loadMediaVector.clear( );
	}
	if( rootItem ) {
		auto musicItems = rootItem->getMusicItemvVector( );
		count = musicItems.size( );
		if( count ) {
			rootItem->clearAllMusicItem( );
			auto data = musicItems.data( );
			for( index = 0; index < count; index += 1 )
				delete data[ index ];
		}
		rootItem->disconnect( rootItem, nullptr, this, nullptr );
		delete rootItem;
		rootItem = nullptr;
	}
	count = favoriteItemVector.size( );
	if( count ) {
		auto data = favoriteItemVector.data( );
		for( index = 0; index < count; index += 1 )
			delete data[ index ];
		favoriteItemVector.clear( );
	}
	Delete_Resource_App_Core_Ptr( appMusicDecoder );
	loadFileVector.clear( );
	loadCount = 0;
	loadFileToItem = nullptr;
	return true;
}

bool AppMusicManage::connectPlayerListWidgetMenuSignal( ) {// 链接信号
	auto instance = AppInstance::getAppInstance( );
	auto appMenuManage = instance->getAppUserInterfaceManage( )->getAppMenuManage( );
	auto playerListWidgetMenu = appMenuManage->getPlayerListWidgetMenu( );

	connect( playerListWidgetMenu, &PlayerListWidgetMenu::signal_open_file_dialog, this, [this]( ) {
		if( loadFileToItem == nullptr )
			return; // 上次未加载完成
		auto instance = AppInstance::getAppInstance( );
		auto appTranslate = instance->getAppDataManage( )->getTranslate( );
		auto translate = appTranslate->getAppMusicManage( );

		auto decodeFileSuffix = appMusicDecoder->getSupperDecodeFileSuffix( );
		QStringList filterSuffixList;
		size_t count = decodeFileSuffix.size( );
		auto data = decodeFileSuffix.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			filterSuffixList.append( "*." + data[ index ] );
		auto musicTypeName = translate->getMusicFileTypeName( );
		auto filterSuffix = filterSuffixList.join( " " );
		auto filterName = musicTypeName + "(" + filterSuffix + ");;" + translate->getAnyFileTypeName( ) + "(*.*)";

		auto mainWindow = instance->getAppUserInterfaceManage( )->getMainWindow( );
		QStringList resultSelectFile;
		std::vector< QString > fileVector;
		if( WidgetTools::showMultipleSelectFileDialog( fileVector, openMultipleFilePath, mainWindow, translate->getSelectMultipleFileTitle( ), filterName ) == false )
			return;
		loadFileToItem = favoriteWidget->getSelectFavorite( );

		std::vector< QString > loadJob;
		size_t loadFileCount = filterMusciFromFileVector( loadJob, fileVector );
		if( loadFileCount == 0 )
			return;
		loadFileVector.append_range( loadJob );
		auto loadBuffData = loadJob.data( );
		for( index = 0; index < loadFileCount; index += 1 )
			loadFile( loadBuffData[ index ] );
	} );
	connect( playerListWidgetMenu, &PlayerListWidgetMenu::signal_open_dir_dialog, this, []( ) {
		// todo : 打开多选目录对话框
	} );
	connect( playerListWidgetMenu, &PlayerListWidgetMenu::signal_select_move_top, this, []( ) {
		// todo : 选择移动到顶部
	} );
	connect( playerListWidgetMenu, &PlayerListWidgetMenu::signal_select_move_bottom, this, []( ) {
		// todo : 选择移动到底部
	} );
	connect( playerListWidgetMenu, &PlayerListWidgetMenu::signal_select_aggregate_select_first, this, []( ) {
		// todo : 在首选项聚合选择
	} );
	connect( playerListWidgetMenu, &PlayerListWidgetMenu::signal_select_aggregate_select_last, this, []( ) {
		// todo : 在末选项聚合选择
	} );

	connect( playerListWidgetMenu, &PlayerListWidgetMenu::signal_select_aggregate_play_before, this, []( ) {
		// todo : 在播放项前聚合选择
	} );

	connect( playerListWidgetMenu, &PlayerListWidgetMenu::signal_select_aggregate_play_after, this, []( ) {
		// todo : 在播放项后聚合选择
	} );

	connect( playerListWidgetMenu, &PlayerListWidgetMenu::signal_select_music_remove_list, this, []( ) {
		// todo : 在列表当中删除选择
	} );
	connect( playerListWidgetMenu, &PlayerListWidgetMenu::signal_select_music_delete_file_list, this, []( ) {
		// todo : 在磁盘中删除选择
	} );
	return true;
}

bool AppMusicManage::connectFavoriteWidgetMenuSignal( ) {
	auto instance = AppInstance::getAppInstance( );
	auto appMenuManage = instance->getAppUserInterfaceManage( )->getAppMenuManage( );
	auto favoriteWidgetMenu = appMenuManage->getFavoriteWidgetMenu( );
	connect( favoriteWidgetMenu, &FavoriteWidgetMenu::signal_add, this, []( ) {
		// todo : 添加收藏夹
	} );
	connect( favoriteWidgetMenu, &FavoriteWidgetMenu::signal_del, this, []( ) {
		// todo : 删除收藏夹
	} );
	connect( favoriteWidgetMenu, &FavoriteWidgetMenu::signal_change, this, []( ) {
		// todo : 更改收藏夹
	} );
	return true;
}

bool AppMusicManage::connectMusicInfoItemWidgetSignal( MusicItem *music_item ) {
	if( music_item == nullptr )
		return false;
	auto musicItemFreeConnect = connect( music_item, &MusicItem::signal_free, this, [this] ( MusicItem *delete_ptr ) {
		emit signal_music_item_free( delete_ptr );
		removeVectorMusicItem( delete_ptr );
	} );
	musicItemFreeConnectVector.emplace_back( music_item, musicItemFreeConnect );
	auto infoItemWidget = music_item->getMusicInfoItemWidget( );
	connect( infoItemWidget, &MusicInfoItemWidget::signal_enter_item, this, [this] ( MusicInfoItemWidget *item ) {
		emit signal_music_item_enter( item->getMusicItem( ) );
	} );
	connect( infoItemWidget, &MusicInfoItemWidget::signal_leave_item, this, [this] ( MusicInfoItemWidget *item ) {
		emit signal_music_item_leave( item->getMusicItem( ) );
	} );
	connect( infoItemWidget, &MusicInfoItemWidget::signal_single_click_item, this, [this] ( MusicInfoItemWidget *item ) {
		emit signal_music_item_single_click( item->getMusicItem( ) );
	} );
	connect( infoItemWidget, &MusicInfoItemWidget::signal_double_click_item, this, [this] ( MusicInfoItemWidget *item ) {
		emit signal_music_item_double_click( item->getMusicItem( ) );
	} );
	return true;
}

bool AppMusicManage::connectFavoriteItemWidgetSignal( FavoriteItem *favorite_item ) {
	if( favorite_item == nullptr )
		return false;
	QMetaObject::Connection favoriteItemFreeConnect = connect( favorite_item, &FavoriteItem::signal_free, this, [this] ( FavoriteItem *delete_ptr ) {
		emit signal_favorite_item_free( delete_ptr );
		removeVectorFavoriteItem( delete_ptr );
	} );
	favoriteItemFreeConnectVector.emplace_back( favorite_item, favoriteItemFreeConnect );
	connect( favorite_item, &FavoriteItem::signal_change_vector_finished, this, &AppMusicManage::signal_favorite_item_change_vector_finished );
	auto favoriteItemWidget = favorite_item->getFavoriteItemWidget( );
	connect( favoriteItemWidget, &FavoriteItemWidget::signal_change_name_finished, this, [this] ( FavoriteItemWidget *item ) {
		emit signal_favorite_item_change_name( item->getFavorItem( ) );
	} );
	connect( favoriteItemWidget, &FavoriteItemWidget::signal_click_item, this, [this] ( FavoriteItemWidget *item ) {
		emit signal_favorite_item_click( item->getFavorItem( ) );
	} );
	connect( favoriteItemWidget, &FavoriteItemWidget::signal_enter_item, this, [this] ( FavoriteItemWidget *item ) {
		emit signal_favorite_item_enter( item->getFavorItem( ) );
	} );
	connect( favoriteItemWidget, &FavoriteItemWidget::signal_leave_item, this, [this] ( FavoriteItemWidget *item ) {
		emit signal_favorite_item_leave( item->getFavorItem( ) );
	} );

	return false;
}

void AppMusicManage::releaseMusicItemFreeConnect( ) {
	auto &connectVector = musicItemFreeConnectVector;
	size_t count = connectVector.size( );
	if( count == 0 )
		return;
	size_t index;
	auto data = connectVector.data( );
	for( index = 0; index < count; index += 1 )
		disconnect( data[ index ].second );
	connectVector.clear( );
}

void AppMusicManage::releaseFavoriteItemFreeConnect( ) {
	auto &connectVector = favoriteItemFreeConnectVector;
	size_t count = connectVector.size( );
	if( count == 0 )
		return;
	size_t index;
	auto data = connectVector.data( );
	for( index = 0; index < count; index += 1 )
		disconnect( data[ index ].second );
	connectVector.clear( );
}

void AppMusicManage::releaseMusicItemFreeConnect( const MusicItem *music_item ) {
	auto &connectVector = musicItemFreeConnectVector;
	size_t count = connectVector.size( );
	if( count == 0 )
		return;
	size_t index;
	auto data = connectVector.data( );
	for( index = 0; index < count; index += 1 )
		if( music_item == data[ index ].first ) {
			disconnect( data[ index ].second );
			connectVector.erase( index + connectVector.begin( ) );
			return;
		}
}

void AppMusicManage::releaseFavoriteItemFreeConnect( const FavoriteItem *favorite_item ) {
	auto &connectVector = favoriteItemFreeConnectVector;
	size_t count = connectVector.size( );
	if( count == 0 )
		return;
	size_t index;
	auto data = connectVector.data( );
	for( index = 0; index < count; index += 1 )
		if( favorite_item == data[ index ].first ) {
			disconnect( data[ index ].second );
			connectVector.erase( index + connectVector.begin( ) );
			return;
		}
}

void AppMusicManage::loadFile( const QString &music_file ) {
	// 构建对象
	auto loadMusicFile = new QMediaPlayer;
	// 链接信号
	loadMusicFile->connect( loadMusicFile, &QMediaPlayer::mediaStatusChanged, this, [this, loadMusicFile] ( QMediaPlayer::MediaStatus status ) {
		MusicItem *musicItem = new MusicItem( *loadMusicFile );
		switch( status ) {
			case QMediaPlayer::EndOfMedia :
			case QMediaPlayer::InvalidMedia :
			case QMediaPlayer::NoMedia :
				emit signal_load_error( musicItem->getAbsFilePath( ) );
			case QMediaPlayer::LoadingMedia :
			case QMediaPlayer::StalledMedia :
			case QMediaPlayer::BufferingMedia :
			case QMediaPlayer::BufferedMedia :
				return; // 不是加载完成，则无法运行该功能
			case QMediaPlayer::LoadedMedia :
				break;
		}
		loadMusicFile->disconnect( loadMusicFile, nullptr, this, nullptr );
		loadCount += 1;
		size_t loadOverCount = loadMediaVector.size( );
		rootItem->appendMusicItem( musicItem );
		if( rootItem != loadFileToItem )
			loadFileToItem->appendMusicItem( musicItem );

		connectMusicInfoItemWidgetSignal( musicItem );

		emit signal_load_unity( *musicItem );
		if( loadOverCount == loadCount ) {
			auto mediaPlayer = loadMediaVector.data( );
			for( loadOverCount = 0; loadOverCount < loadCount; loadOverCount += 1 )
				delete mediaPlayer[ loadOverCount ];
			loadMediaVector.clear( );
			// 拷贝序列
			auto musicItems = rootItem->getMusicItemvVector( );
			// 触发信号
			emit signal_load_over( loadFileToItem, musicItems );
			loadFileToItem = nullptr;
		}
	} );

	// 存储
	loadMediaVector.emplace_back( loadMusicFile );
	// 开始配置
	loadMusicFile->setSource( QUrl::fromLocalFile( music_file ) );
}

bool AppMusicManage::readJsonData( ) {
	auto jsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getAppMusicManage( );
	QJsonObject readJson;
	if( PathTools::readJsonObject( readJson, jsonKey->getFilePath( ) ) == false )
		return false;
	if( setJsonData( readJson ) == false )
		return false;

	return true;
}

bool AppMusicManage::writeJsonData( ) {
	QJsonObject getJson;
	if( getJsonData( getJson ) == false )
		return false;
	auto jsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getAppMusicManage( );
	if( PathTools::writeJsonObject( getJson, jsonKey->getFilePath( ) ) == false )
		return false;
	return true;
}

void AppMusicManage::loadMusciFromFileVector( const std::vector< QString > &music_file ) {
	size_t count = loadFileVector.size( );

	size_t compCount = music_file.size( );
	auto loadArray = music_file.data( );
	size_t loadIndex;
	std::vector< QString > loadBuff( compCount );
	std::vector< QString > dirVector;
	auto loadBuffData = loadBuff.data( );
	size_t loadBuffCount = 0;
	size_t index;
	QFileInfo fileInfo;
	QString compItem;
	if( count ) {
		auto data = loadFileVector.data( );
		for( loadIndex = 0; loadIndex < compCount; loadIndex += 1 ) {
			fileInfo.setFile( loadArray[ loadIndex ] );
			if( fileInfo.exists( ) == false )
				continue;
			compItem = fileInfo.absoluteFilePath( );
			if( fileInfo.isDir( ) ) {
				dirVector.emplace_back( compItem );
				continue;
			}
			for( index = 0; index < loadBuffCount; index += 1 )
				if( compItem == loadBuffData[ index ] )
					break;
			if( index != loadBuffCount )
				continue;
			for( index = 0; index < count; index += 1 )
				if( compItem == data[ index ] )
					break;
			if( index != count )
				continue;
			loadBuffData[ loadBuffCount ] = compItem;
			loadBuffCount += 1;
		}
		if( loadBuffCount != compCount )
			loadBuff.resize( loadBuffCount );
		loadFileVector.append_range( loadBuff );
	} else {
		for( loadIndex = 0; loadIndex < compCount; loadIndex += 1 ) {
			fileInfo.setFile( loadArray[ loadIndex ] );
			if( fileInfo.exists( ) == false )
				continue;
			compItem = fileInfo.absoluteFilePath( );
			if( fileInfo.isDir( ) ) {
				dirVector.emplace_back( compItem );
				continue;
			}
			compItem = fileInfo.absoluteFilePath( );
			for( index = 0; index < loadBuffCount; index += 1 )
				if( compItem == loadBuffData[ index ] )
					break;
			if( index != loadBuffCount )
				continue;
			loadBuffData[ loadBuffCount ] = compItem;
			loadBuffCount += 1;
		}
		if( loadBuffCount != compCount )
			loadBuff.resize( loadBuffCount );
		loadFileVector.append_range( loadBuff );
	}
	for( index = 0; index < loadBuffCount; index += 1 )
		loadFile( loadBuffData[ index ] );
}

size_t AppMusicManage::filterMusciFromFileVector( std::vector< QString > &result_filter_over, const std::vector< QString > &music_file ) {
	size_t fileCount = music_file.size( );
	auto fileData = music_file.data( );
	size_t fileIndex;
	result_filter_over.resize( fileCount );
	auto resultData = result_filter_over.data( );
	size_t resultCount = 0;
	size_t loadIndex;
	size_t musicIndex;
	QFileInfo info;

	size_t loadFileCount = loadFileVector.size( );
	auto loadFileData = loadFileVector.data( );

	auto &musicItems = rootItem->getMusicItemvVector( );
	size_t musicCount = musicItems.size( );
	auto musicData = musicItems.data( );
	for( fileIndex = 0; fileIndex < fileCount; fileIndex += 1 ) {
		auto file = fileData[ fileIndex ];
		info.setFile( file );
		file = info.absoluteFilePath( );
		for( loadIndex = 0; loadIndex < loadFileCount; loadIndex += 1 )
			if( file == loadFileData[ loadIndex ] )
				break;
		if( loadIndex < loadFileCount )
			continue;
		for( musicIndex = 0; musicIndex < musicCount; musicIndex += 1 )
			if( musicData[ musicIndex ]->isMusicFile( file ) )
				break;
		if( musicIndex < musicCount )
			continue;
		resultData[ resultCount ] = file;
		resultCount += 1;
	}
	if( resultCount != fileCount )
		result_filter_over.resize( resultCount );
	return resultCount;
}

void AppMusicManage::loadMusciFromDir( const std::vector< QString > &music_dir ) {
	std::vector< QString > fileVector;
	QFileInfo fileInfo;
	QString compItem;
	size_t compCount = music_dir.size( );
	auto compData = music_dir.data( );
	size_t countIndex;
	std::vector< QString > loadDirVector( compCount );
	auto loadDirData = loadDirVector.data( );
	size_t loadDirCount = 0;
	size_t loadDirIndex;
	for( countIndex = 0; countIndex < compCount; countIndex += 1 ) {
		fileInfo.setFile( compData[ countIndex ] );
		if( fileInfo.exists( ) == false )
			continue;
		compItem = fileInfo.absoluteFilePath( );
		if( fileInfo.isFile( ) ) {
			fileVector.emplace_back( compItem );
			continue;
		}

		for( loadDirIndex = 0; loadDirIndex < loadDirCount; loadDirIndex += 1 )
			if( compItem == loadDirData[ loadDirIndex ] )
				break;
		if( loadDirIndex < loadDirCount )
			continue;
		loadDirData[ loadDirCount ] = compItem;
		loadDirCount += 1;
	}
	if( loadDirCount != compCount ) {
		loadDirVector.resize( loadDirCount );
		loadDirData = loadDirVector.data( );
	}
	QStringList resultFile;

	for( loadDirIndex = 0; loadDirIndex < loadDirCount; loadDirIndex += 1 )
		if( PathTools::entryFilePath( resultFile, loadDirData[ loadDirIndex ] ) ) {
			compCount = fileVector.size( ); // 旧的偏移
			size_t extendCount = resultFile.size( ); // 扩张数量
			auto sourceData = resultFile.data( ); // 拷贝指针
			size_t newsize = extendCount + compCount; // 新的大小
			fileVector.resize( newsize );
			auto setData = fileVector.data( ); // 原始地址
			auto offsetPtr = setData + compCount; // 目标起始地址
			for( countIndex = 0; countIndex < extendCount; countIndex += 1 )
				offsetPtr[ countIndex ] = sourceData[ countIndex ]; // 拷贝
			resultFile.clear( ); // 清空拷贝完成的目标
		}
	loadMusciFromFileVector( fileVector );
}

bool AppMusicManage::appendFavorite( const QString &name ) {
	auto itemWidget = new FavoriteItem( name );
	connectFavoriteItemWidgetSignal( itemWidget );
	favoriteItemVector.emplace_back( itemWidget );
	favoriteWidget->updateAppMusicManageInof( favoriteItemVector );
	return true;
}

bool AppMusicManage::removeSelectMusicItem( ) {
	return false;
}

bool AppMusicManage::deleteSelectMusicItem( ) {
	return false;
}

bool AppMusicManage::openSelectMusicFileDialog( ) {
	return false;
}

bool AppMusicManage::openSelectMusicDirDialog( ) {
	return false;
}

bool AppMusicManage::selectMusicItemMoveToTop( ) {
	return false;
}

bool AppMusicManage::selectMusicItemMoveToBottom( ) {
	return false;
}

bool AppMusicManage::selectMusicItemAggregateToSelectFirst( ) {
	return false;
}

bool AppMusicManage::selectMusicItemAggregateToSelectLast( ) {
	return false;
}

bool AppMusicManage::selectMusicItemAggregateToPlayItemBefore( ) {
	return false;
}

bool AppMusicManage::selectMusicItemAggregateToPlayItemAfter( ) {
	return false;
}

bool AppMusicManage::selectFavorite( ) {
	return false;
}

bool AppMusicManage::init( ) {
	Init_Resource_App_Core_Ptr( appMusicDecoder );
	return true;
}

bool AppMusicManage::initBefore( ) {
	deleteResource( );
	loadCount = 0;
	appMusicDecoder = new AppMusicDecoder;
	rootItem = new FavoriteItem( "" );
	Before_Init_Resource_App_Core_Ptr( appMusicDecoder );
	return true;
}

bool AppMusicManage::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( appMusicDecoder );
	if( connectPlayerListWidgetMenuSignal( ) == false )
		return false;
	if( connectFavoriteWidgetMenuSignal( ) == false )
		return false;
	if( AppTranslateTools::getAppMusicManage( [this] ( AppMusicManageTranslate &translate ) {
		rootItem->setFavoriteName( translate.getRootFavoriteName( ) );
	} ) == false )
		rootItem->setFavoriteName( QObject::tr( "默认" ) );

	auto appInstance = AppInstance::getAppInstance( );
	PlayerWindow *playerWindow = appInstance->getAppUserInterfaceManage( )->getMainWindow( )->getMainStackedWidget( )->getPlayerWindow( );
	musicContreWidget = playerWindow->getMusicListWindow( )->getMusicContreScrollArea( )->getMusicContreWidget( );
	favoriteWidget = playerWindow->getFavoritemDockWidget( )->getFavoriteSrollArea( )->getFavoriteWidget( );
	openMultipleDirPath = openMultipleFilePath = appInstance->getAppDataManage( )->getAppSettingPath( );
	// 在退出之前释放所有 item，包括 ui 组件，其中 ui item 被其他组件释放会弹出异常
	auto applicationManage = appInstance->getApplicationManage( );
	connect( applicationManage, &ApplicationManage::signal_app_quit, this, [this]( ) {
		deleteResource( );
	} );
	return true;
}

FavoriteItem * AppMusicManage::getRootItem( ) const {
	return rootItem;
}

size_t AppMusicManage::findMusicItem( MusicItem *&result_item, const QString &find_music ) const {
	auto item = rootItem->findFirstMusicItem( find_music );
	return item == nullptr ? 0 : 1;
}

size_t AppMusicManage::findMusicItem( std::vector< MusicItem * > &result_item, const std::vector< QString > &find_music ) const {
	auto &musicItemvVector = rootItem->getMusicItemvVector( );
	size_t count = musicItemvVector.size( );
	size_t resultCount = 0;
	if( count ) {
		size_t index;
		auto data = musicItemvVector.data( );
		size_t findeIndex;
		size_t findCount = find_music.size( );
		auto findData = find_music.data( );
		result_item.resize( findCount );
		auto setData = result_item.data( );
		size_t filterIndex;

		for( findeIndex = 0; findeIndex < findCount; findeIndex += 1 ) {
			auto findFile = findData[ findeIndex ];
			for( index = 0; index < count; index += 1 ) {
				if( data[ index ]->isMusicFile( findFile ) ) {
					if( resultCount ) {
						for( filterIndex = 0; filterIndex < resultCount; filterIndex += 1 )
							if( setData[ filterIndex ] == data[ index ] )
								break;
						if( filterIndex < resultCount )
							break;
					}
					setData[ resultCount ] = data[ index ];
					resultCount += 1;
					break;
				}
			}
		}
		if( resultCount != findCount )
			result_item.resize( resultCount );
	}
	return resultCount;
}

bool AppMusicManage::getJsonData( QJsonObject &get_json_object ) const {
	QString jsonObejctJsonKey;
	QString selectDirPathJsonKey;
	QString selectFilePathJsonKey;

	if( AppJsonKeyTools::getAppMusicManage( [&] ( const AppMusicManageJsonKey &json_key ) {
		jsonObejctJsonKey = json_key.getJsonObejct( );
		selectDirPathJsonKey = json_key.getSelectDirPath( );
		selectFilePathJsonKey = json_key.getSelectFilePath( );
	} ) == false )
		return false;
	QJsonObject object;
	if( FavoriteItem::getJsonDataVector( object, favoriteItemVector ) == false )
		return false;
	if( MusicItem::getJsonDataVector( object, rootItem->getMusicItemvVector( ) ) == false )
		return false;
	object.insert( selectFilePathJsonKey, this->openMultipleFilePath );
	object.insert( selectDirPathJsonKey, this->openMultipleDirPath );
	get_json_object.insert( jsonObejctJsonKey, object );
	return true;
}

bool AppMusicManage::setJsonData( const QJsonObject &set_json_object ) {
	if( set_json_object.empty( ) )
		return false;

	QString jsonObejctJsonKey;
	QString selectDirPathJsonKey;
	QString selectFilePathJsonKey;

	if( AppJsonKeyTools::getAppMusicManage( [&] ( const AppMusicManageJsonKey &json_key ) {
		jsonObejctJsonKey = json_key.getJsonObejct( );
		selectDirPathJsonKey = json_key.getSelectDirPath( );
		selectFilePathJsonKey = json_key.getSelectFilePath( );
	} ) == false )
		return false;
	auto find = set_json_object.find( jsonObejctJsonKey );
	auto end = set_json_object.end( );
	if( find == end )
		return false;
	auto jsonObject = find.value( ).toObject( );

	end = jsonObject.end( );
	// 获取文件选择路径
	find = jsonObject.find( selectFilePathJsonKey );
	if( find != end )
		openMultipleFilePath = find.value( ).toString( openMultipleFilePath );
	// 获取目录选择路径
	find = jsonObject.find( selectDirPathJsonKey );
	if( find != end )
		openMultipleDirPath = find.value( ).toString( openMultipleDirPath );
	// 获取音频对象
	std::vector< MusicItem * > resultMusicItemVector;
	if( MusicItem::setJsonDataVector( resultMusicItemVector, jsonObject ) ) {
		releaseMusicItemFreeConnect( );
		rootItem->deleteAllMusicItem( );
		rootItem->appendMusicItem( resultMusicItemVector );
		size_t index;
		auto count = resultMusicItemVector.size( );
		auto copydata = resultMusicItemVector.data( );
		for( index = 0; index < count; index += 1 )
			connectMusicInfoItemWidgetSignal( copydata[ index ] );
	}
	std::vector< FavoriteItem * > resultFavoriteItemVector;
	if( FavoriteItem::setJsonDataVector( resultFavoriteItemVector, jsonObject ) ) {
		releaseFavoriteItemFreeConnect( );
		size_t count = favoriteItemVector.size( );
		FavoriteItem **data;
		size_t index;
		if( count ) {
			data = favoriteItemVector.data( );
			for( index = 0; index < count; index += 1 )
				delete data[ index ];
		}
		count = resultFavoriteItemVector.size( );
		favoriteItemVector.resize( count );
		data = favoriteItemVector.data( );
		auto copydata = resultFavoriteItemVector.data( );
		for( index = 0; index < count; index += 1 ) {
			data[ index ] = copydata[ index ];
			connectFavoriteItemWidgetSignal( data[ index ] );
		}
	}

	auto appUserInterfaceManage = AppInstance::getAppInstance( )->getAppUserInterfaceManage( );
	auto playerWindow = appUserInterfaceManage->getMainWindow( )->getMainStackedWidget( )->getPlayerWindow( );
	auto musicListWindow = playerWindow->getMusicListWindow( );
	auto musicContreWidget = musicListWindow->getMusicContreScrollArea( )->getMusicContreWidget( );
	auto playerListTopWidget = musicListWindow->getMusicItemSizeInfoDockWidget( )->getPlayerListTopWidget( );
	musicContreWidget->setItemPlayerListTopWidgetWidth( playerListTopWidget );

	favoriteWidget->updateAppMusicManageInof( favoriteItemVector );
	return true;
}

void AppMusicManage::toMusicIndex( std::vector< size_t > &result_index, const std::vector< MusicItem * > &find_index_music_item ) {
	rootItem->toMusicIndex( result_index, find_index_music_item );
}

void AppMusicManage::fromMusicIndex( std::vector< MusicItem * > &result_music_item, const std::vector< size_t > &find_index ) {
	rootItem->fromMusicIndex( result_music_item, find_index );
}

bool AppMusicManage::deleteFavoriteItemAllMusicItem( FavoriteItem *favorite_item ) {
	auto &musicItems = favorite_item->getMusicItemvVector( );
	size_t count = musicItems.size( );
	if( count == 0 )
		return false;

	using ConnectVectorType = decltype(musicItemFreeConnectVector);
	ConnectVectorType &connectVector = musicItemFreeConnectVector;
	size_t connectCount = connectVector.size( );
	auto connectData = connectVector.data( );
	size_t conectIndex;
	ConnectVectorType buff( connectCount );
	auto buffData = buff.data( );
	size_t buffCount = 0;

	auto copy = musicItems;
	favorite_item->clearAllMusicItem( );
	auto musicItem = musicItems.data( );
	size_t index;
	for( conectIndex = 0; conectIndex < connectCount; conectIndex += 1 ) {
		auto &pair = connectData[ conectIndex ];
		for( index = 0; index < count; index += 1 )
			if( pair.first == musicItem[ index ] ) {
				pair.first = nullptr;
				disconnect( pair.second );
				delete musicItem[ index ];
				break;
			}
		if( index < count )
			continue;
		buffData[ conectIndex ] = pair;
	}
	if( buffCount != connectCount ) {
		connectVector.resize( buffCount );
		connectData = connectVector.data( );
		for( conectIndex = 0; conectIndex < connectCount; conectIndex += 1 )
			connectData[ conectIndex ] = buffData[ conectIndex ];
		return true;
	}
	return false;
}

AppMusicManage::~AppMusicManage( ) {
	deleteResource( );
}

FavoriteItem * AppMusicManage::getLoadFileToItem( ) const {
	return loadFileToItem;
}

bool AppMusicManage::removeItem( const MusicItem *target ) {
	return rootItem->removeMusicItem( target );
}

bool AppMusicManage::deleteItem( const MusicItem *target ) {
	auto item = rootItem->findFirstMusicItem( target );
	if( item == nullptr )
		return false;
	releaseMusicItemFreeConnect( target );
	rootItem->removeMusicItem( target );
	delete item;
	return true;
}

AppMusicDecoder * AppMusicManage::getAppMusicDecoder( ) const {
	return appMusicDecoder;
}
