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

#include "../item/musicItem.h"

#include "../itemWidget/favoriteItemWidget.h"

#include "../menu/favoriteWidgetMenu.h"
#include "../menu/playerListWidgetMenu.h"

#include "../mutex/userMutex.h"

#include "../scrollArea/favoriteSrollArea.h"
#include "../scrollArea/musicContreScrollArea.h"

#include "../stackedWidget/mainStackedWidget.h"

#include "../tools/arrayTools.h"
#include "../tools/pathTools.h"
#include "../tools/widgetTools.h"

#include "../widget/favoriteWidget.h"

#include "../window/mainWindow.h"
#include "../window/musicListWindow.h"
#include "../window/playerWindow.h"

#include "jsonKey/appMusicManageJsonKey.h"

#include "translate/appMusicManageTranslate.h"

void AppMusicManage::deleteFavoriteItemWidget( QObject *delete_ptr ) {
	loadMutex->lock( );
	size_t count = musicFavoriteMapVector.size( );
	auto data = musicFavoriteMapVector.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		if( data[ index ].first == delete_ptr ) {
			musicFavoriteMapVector.erase( musicFavoriteMapVector.begin( ) + index );
			break;
		}
	loadMutex->unlock( );
}

bool AppMusicManage::deleteResource( ) {
	disconnect( );
	if( loadMutex ) {
		loadMutex->lock( );
		size_t index;
		size_t count;
		count = loadMediaVector.size( );
		if( count ) {
			auto data = loadMediaVector.data( );
			for( index = 0; index < count; index += 1 )
				delete data[ index ];
		}
		count = musicItemvVector.size( );
		if( count ) {
			auto data = musicItemvVector.data( );
			for( index = 0; index < count; index += 1 ) {
				data[ index ]->disconnect( this );
				delete data[ index ];
			}
			musicItemvVector.clear( );
		}
		count = musicFavoriteMapVector.size( );
		if( count ) {
			auto data = musicFavoriteMapVector.data( );
			for( index = 0; index < count; index += 1 ) {
				data[ index ].first->disconnect( this );
				delete data[ index ].first;
			}
			musicFavoriteMapVector.clear( );
		}
		Delete_Resource_App_Core_Ptr( appMusicDecoder );
		loadMediaVector.clear( );
		loadFileVector.clear( );
		loadCount = 0;
		loadMutex->unlock( );
		Delete_Resource_App_Core_Ptr( loadMutex );
	}
	return true;
}

bool AppMusicManage::connectPlayerListWidgetMenuSignal( ) {// 链接信号
	auto instance = AppInstance::getAppInstance( );
	auto appMenuManage = instance->getAppUserInterfaceManage( )->getAppMenuManage( );
	auto playerListWidgetMenu = appMenuManage->getPlayerListWidgetMenu( );

	connect( playerListWidgetMenu, &PlayerListWidgetMenu::signal_open_file_dialog, this, [this]( ) {
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
		loadMusciFromFileVector( fileVector );
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

void AppMusicManage::loadFile( const QString &music_file ) {
	// 构建对象
	auto loadMusicFile = new QMediaPlayer;
	// 链接信号
	loadMusicFile->connect( loadMusicFile, &QMediaPlayer::mediaStatusChanged, this, [this, loadMusicFile] ( QMediaPlayer::MediaStatus status ) {
		AppDataManage *dataManage = AppInstance::getAppInstance( )->getAppDataManage( );
		MusicItem *musicItem = new MusicItem( *loadMusicFile );
		switch( status ) {
			case QMediaPlayer::EndOfMedia :
			case QMediaPlayer::InvalidMedia :
			case QMediaPlayer::NoMedia :
				emit dataManage->signal_load_error( musicItem->getAbsFilePath( ) );
			case QMediaPlayer::LoadingMedia :
			case QMediaPlayer::StalledMedia :
			case QMediaPlayer::BufferingMedia :
			case QMediaPlayer::BufferedMedia :
				return; // 不是加载完成，则无法运行该功能
			case QMediaPlayer::LoadedMedia :
				break;
		}
		loadMutex->lock( );
		loadMusicFile->disconnect( );
		loadCount += 1;
		size_t loadOverCount = loadMediaVector.size( );
		musicItemvVector.emplace_back( musicItem );
		loadMutex->unlock( );
		emit dataManage->signal_load_unity( *musicItem );
		if( loadOverCount == loadCount ) {
			loadMutex->lock( );
			auto mediaPlayer = loadMediaVector.data( );
			for( loadOverCount = 0; loadOverCount < loadCount; loadOverCount += 1 )
				delete mediaPlayer[ loadOverCount ];
			loadMediaVector.clear( );
			// 拷贝序列
			loadCount = musicItemvVector.size( );
			std::vector< const MusicItem * > buff( loadCount );
			auto buffData = buff.data( );
			auto sourceData = musicItemvVector.data( );
			for( loadOverCount = 0; loadOverCount < loadCount; loadOverCount += 1 )
				buffData[ loadOverCount ] = sourceData[ loadOverCount ];
			loadMutex->unlock( );
			// 触发信号
			emit dataManage->signal_load_over( musicItemvVector );
		}
	} );

	// 存储
	loadMutex->lock( );
	loadMediaVector.emplace_back( loadMusicFile );
	loadMutex->unlock( );
	// 开始配置
	loadMusicFile->setSource( QUrl::fromLocalFile( music_file ) );
}

bool AppMusicManage::readJsonData( ) {
	auto jsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getAppMusicManage( );
	QJsonObject readJson;
	if( PathTools::readJsonObject( readJson, jsonKey->getFilePath( ) ) == false )
		return false;
	setJsonData( readJson );

	return true;
}

bool AppMusicManage::writeJsonData( ) {
	return true;
}

void AppMusicManage::loadMusciFromFileVector( const std::vector< QString > &music_file ) {
	loadMutex->lock( );
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
	loadMutex->unlock( );
	for( index = 0; index < loadBuffCount; index += 1 )
		loadFile( loadBuffData[ index ] );
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
	auto itemWidget = new FavoriteItemWidget( );
	connect( itemWidget, &QObject::destroyed, this, &AppMusicManage::deleteFavoriteItemWidget );
	itemWidget->setFavoriteName( name );
	loadMutex->lock( );
	musicFavoriteMapVector.emplace_back( itemWidget, std::vector< MusicItem * >( ) );
	loadMutex->unlock( );
	favoriteWidget->updateAppMusicManageInof( musicFavoriteMapVector );
	return true;
}

bool AppMusicManage::appendFirstFavorite( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto translate = appInstance->getAppDataManage( )->getTranslate( )->getAppMusicManage( );
	auto name = translate->getRootFavoriteName( );
	auto itemWidget = new FavoriteItemWidget( );
	itemWidget->setEnabled( false );
	connect( itemWidget, &QObject::destroyed, this, &AppMusicManage::deleteFavoriteItemWidget );
	itemWidget->setFavoriteName( name );
	loadMutex->lock( );
	musicFavoriteMapVector.emplace_back( itemWidget, std::vector< MusicItem * >( ) );
	loadMutex->unlock( );
	favoriteWidget->updateAppMusicManageInof( musicFavoriteMapVector );
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
	loadMutex = new UserMutex;
	appMusicDecoder = new AppMusicDecoder;
	Before_Init_Resource_App_Core_Ptr( appMusicDecoder );
	return true;
}

bool AppMusicManage::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( appMusicDecoder );
	if( connectPlayerListWidgetMenuSignal( ) == false )
		return false;
	if( connectFavoriteWidgetMenuSignal( ) == false )
		return false;

	auto appInstance = AppInstance::getAppInstance( );
	PlayerWindow *playerWindow = appInstance->getAppUserInterfaceManage( )->getMainWindow( )->getMainStackedWidget( )->getPlayerWindow( );
	musicContreWidget = playerWindow->getMusicListWindow( )->getMusicContreScrollArea( )->getMusicContreWidget( );
	favoriteWidget = playerWindow->getFavoritemDockWidget( )->getFavoriteSrollArea( )->getFavoriteWidget( );
	openMultipleDirPath = openMultipleFilePath = appInstance->getAppDataManage( )->getAppSettingPath( );
	if( appendFirstFavorite( ) == false )
		return false;
	auto applicationManage = appInstance->getApplicationManage( );
	connect( applicationManage, &ApplicationManage::signal_app_quit, this, [this]( ) {
		deleteResource( );
	} );
	return true;
}

bool AppMusicManage::getJsonData( QJsonObject &get_json_object ) const {
	return false;
}

bool AppMusicManage::setJsonData( const QJsonObject &set_json_object ) {
	if( set_json_object.empty( ) )
		return false;
	auto jsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getAppMusicManage( );
	auto end = set_json_object.end( );
	QJsonObject::const_iterator find;
	// 获取文件选择路径
	find = set_json_object.find( jsonKey->getSelectFilePath( ) );
	if( find != end )
		openMultipleFilePath = find.value( ).toString( openMultipleFilePath );
	// 获取目录选择路径
	find = set_json_object.find( jsonKey->getSelectDirPath( ) );
	if( find != end )
		openMultipleDirPath = find.value( ).toString( openMultipleDirPath );
	// 获取音频对象
	std::vector< MusicItem * > resultMusicItemVector;
	if( MusicItem::setJsonDataVector( resultMusicItemVector, set_json_object ) ) {
		auto count = musicItemvVector.size( );
		size_t index;
		MusicItem **data;
		if( count ) {
			data = musicItemvVector.data( );
			for( index = 0; index < count; index += 1 ) {
				data[ index ]->disconnect( this );
				delete data[ index ];
			}
		}
		count = resultMusicItemVector.size( );
		musicItemvVector.reserve( count );
		data = musicItemvVector.data( );
		auto copydata = resultMusicItemVector.data( );
		for( index = 0; index < count; index += 1 )
			data[ index ] = copydata[ index ];
	}
	// 获取音频对象
	std::vector< std::pair< FavoriteItemWidget *, std::vector< MusicItem * > > > resultFavoriteItemWidget;
	if( FavoriteItemWidget::setJsonDataVector( resultFavoriteItemWidget, set_json_object ) ) {
		auto count = musicFavoriteMapVector.size( );
		size_t index;
		std::pair< FavoriteItemWidget *, std::vector< MusicItem * > > *data;
		if( count ) {
			data = musicFavoriteMapVector.data( );
			for( index = 0; index < count; index += 1 ) {
				data[ index ].first->disconnect( this );
				delete data[ index ].first;
			}
		}
		count = resultFavoriteItemWidget.size( );
		musicFavoriteMapVector.reserve( count );
		data = musicFavoriteMapVector.data( );
		auto copydata = resultFavoriteItemWidget.data( );
		for( index = 0; index < count; index += 1 )
			data[ index ] = copydata[ index ];
	}

	return true;
}

bool AppMusicManage::getFavoriteItemMusicVector( std::vector< MusicItem * > &result_vector, const FavoriteItemWidget *favorite_widget ) const {
	loadMutex->lock( );
	size_t count = musicFavoriteMapVector.size( );
	if( count == 0 ) {
		loadMutex->unlock( );
		return false;
	}

	auto data = musicFavoriteMapVector.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		if( data[ index ].first == favorite_widget ) {
			result_vector = data[ index ].second;
			loadMutex->unlock( );
			return true;
		}
	loadMutex->unlock( );
	return false;
}

AppMusicManage::~AppMusicManage( ) {
	deleteResource( );
}

AppMusicDecoder * AppMusicManage::getAppMusicDecoder( ) const {
	return appMusicDecoder;
}
