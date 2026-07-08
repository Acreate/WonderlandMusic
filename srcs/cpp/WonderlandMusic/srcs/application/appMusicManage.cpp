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
#include "../item/favoriteItem.h"
#include "../item/musicItem.h"
#include "../itemWidget/favoriteItemWidget.h"
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
#include "../window/mainWindow.h"
#include "../window/musicListWindow.h"
#include "../window/playerWindow.h"
#include "jsonKey/appMusicManageJsonKey.h"
#include "translate/appMusicManageTranslate.h"

void AppMusicManage::deleteFavoriteItem( QObject *delete_ptr ) {
	loadMutex->lock( );
	size_t count = favoriteItemVector.size( );
	auto data = favoriteItemVector.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		if( data[ index ] == delete_ptr ) {
			favoriteItemVector.erase( favoriteItemVector.begin( ) + index );
			break;
		}
	loadMutex->unlock( );
}

void AppMusicManage::deleteMusicItem( QObject *delete_ptr ) {
	loadMutex->lock( );
	size_t count = musicItemVector.size( );
	auto data = musicItemVector.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		if( data[ index ] == delete_ptr ) {
			musicItemVector.erase( musicItemVector.begin( ) + index );
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
		count = musicItemVector.size( );
		if( count ) {
			auto data = musicItemVector.data( );
			for( index = 0; index < count; index += 1 ) {
				data[ index ]->disconnect( data[ index ], nullptr, this, nullptr );
				delete data[ index ];
			}
			musicItemVector.clear( );
		}
		count = favoriteItemVector.size( );
		if( count ) {
			auto data = favoriteItemVector.data( );
			for( index = 0; index < count; index += 1 ) {
				data[ index ]->disconnect( data[ index ], nullptr, this, nullptr );
				delete data[ index ];
			}
			favoriteItemVector.clear( );
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
		auto favoriteItem = favoriteWidget->getSelectFavorite( );
		QObject *job = new QObject( this );

		AppDataManage *dataManage = AppInstance::getAppInstance( )->getAppDataManage( );
		connect( dataManage, &AppDataManage::signal_load_error, job, [=]( ) {
			job->disconnect( );
			job->deleteLater( );
		} );
		connect( dataManage, &AppDataManage::signal_load_over, job, [=] ( const std::vector< MusicItem * > &music_item_vector ) {
			if( favoriteItem )
				favoriteItem->appendMusicItem( fileVector );
			else {
				decltype(favoriteItem) item = nullptr;
				if( getRootFavoriteItem( item ) )
					item->appendMusicItem( fileVector );
			}
			job->disconnect( );
			job->deleteLater( );
		} );

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
		connect( musicItem, &QObject::destroyed, this, &AppMusicManage::deleteMusicItem );
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
		loadMusicFile->disconnect( loadMusicFile, nullptr, this, nullptr );
		loadCount += 1;
		size_t loadOverCount = loadMediaVector.size( );
		musicItemVector.emplace_back( musicItem );
		loadMutex->unlock( );
		emit dataManage->signal_load_unity( *musicItem );
		if( loadOverCount == loadCount ) {
			loadMutex->lock( );
			auto mediaPlayer = loadMediaVector.data( );
			for( loadOverCount = 0; loadOverCount < loadCount; loadOverCount += 1 )
				delete mediaPlayer[ loadOverCount ];
			loadMediaVector.clear( );
			// 拷贝序列
			loadCount = musicItemVector.size( );
			std::vector< const MusicItem * > buff( loadCount );
			auto buffData = buff.data( );
			auto sourceData = musicItemVector.data( );
			for( loadOverCount = 0; loadOverCount < loadCount; loadOverCount += 1 )
				buffData[ loadOverCount ] = sourceData[ loadOverCount ];
			loadMutex->unlock( );
			// 触发信号
			emit dataManage->signal_load_over( musicItemVector );
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
	auto itemWidget = new FavoriteItem( name );
	connect( itemWidget, &QObject::destroyed, this, &AppMusicManage::deleteFavoriteItem );
	loadMutex->lock( );
	favoriteItemVector.emplace_back( itemWidget );
	loadMutex->unlock( );
	favoriteWidget->updateAppMusicManageInof( favoriteItemVector );
	return true;
}

bool AppMusicManage::appendFirstFavorite( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto translate = appInstance->getAppDataManage( )->getTranslate( )->getAppMusicManage( );
	auto name = translate->getRootFavoriteName( );
	auto itemWidget = new FavoriteItem( name );
	itemWidget->setEnabled( false );
	connect( itemWidget, &QObject::destroyed, this, &AppMusicManage::deleteFavoriteItem );
	itemWidget->setFavoriteName( name );
	loadMutex->lock( );
	favoriteItemVector.emplace_back( itemWidget );
	loadMutex->unlock( );
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
	// 在退出之前释放所有 item，包括 ui 组件，其中 ui item 被其他组件释放会弹出异常
	auto applicationManage = appInstance->getApplicationManage( );
	connect( applicationManage, &ApplicationManage::signal_app_quit, this, [this]( ) {
		deleteResource( );
	} );
	return true;
}

bool AppMusicManage::getRootFavoriteItem( FavoriteItem *&result_root_item ) const {
	loadMutex->lock( );
	size_t count = favoriteItemVector.size( );
	if( count ) {
		QString rootName;
		if( AppTranslateTools::getAppMusicManage( [&rootName] ( AppMusicManageTranslate &translate ) {
			rootName = translate.getRootFavoriteName( );
		} ) == false ) {
			loadMutex->unlock( );
			return false;
		}
		size_t index;
		auto data = favoriteItemVector.data( );
		for( index = 0; index < count; index += 1 )
			if( data[ index ]->getFavoriteName( ) == rootName ) {
				result_root_item = data[ index ];
				loadMutex->unlock( );
				return true;
			}
	}

	loadMutex->unlock( );

	return false;
}

size_t AppMusicManage::findMusicItem( MusicItem *&result_item, const QString &find_music ) const {
	loadMutex->lock( );
	size_t count = musicItemVector.size( );
	size_t resultCount = 0;
	if( count ) {
		size_t index = 0;
		auto data = musicItemVector.data( );
		for( ; index < count; index += 1 )
			if( data[ index ]->isMusicFile( find_music ) ) {
				result_item = data[ index ];
				resultCount += 1;
				break;
			}
	}
	loadMutex->unlock( );
	return resultCount;
}

size_t AppMusicManage::findMusicItem( std::vector< MusicItem * > &result_item, const std::vector< QString > &find_music ) const {
	loadMutex->lock( );
	size_t count = musicItemVector.size( );
	size_t resultCount = 0;
	if( count ) {
		size_t index = 0;
		auto data = musicItemVector.data( );
		size_t findeIndex;
		size_t findCount = find_music.size( );
		auto findData = find_music.data( );
		result_item.resize( findCount );
		auto setData = result_item.data( );
		size_t filterIndex;

		for( findeIndex = 0; findeIndex < findCount; findeIndex += 1 ) {
			auto findFile = findData[ findeIndex ];
			for( ; index < count; index += 1 ) {
				if( data[ index ]->isMusicFile( findFile ) ) {
					for( filterIndex = 0; filterIndex < resultCount; filterIndex += 1 )
						if( setData[ filterIndex ] == data[ index ] )
							break;
					if( filterIndex < resultCount )
						break;
					setData[ resultCount ] = data[ index ];
					resultCount += 1;
					break;
				}
			}
		}
		if( resultCount != findCount )
			result_item.resize( resultCount );
	}
	loadMutex->unlock( );
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
	if( FavoriteItem::getJsonDataVector( object, favoriteItemVector ) == false ) {
		return false;
	}
	if( MusicItem::getJsonDataVector( object, musicItemVector ) == false ) {
		return false;
	}
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
		auto count = musicItemVector.size( );
		size_t index;
		MusicItem **data;
		if( count ) {
			data = musicItemVector.data( );
			for( index = 0; index < count; index += 1 ) {
				data[ index ]->disconnect( data[ index ], &QObject::destroyed, this, &AppMusicManage::deleteMusicItem );
				delete data[ index ];
			}
		}
		count = resultMusicItemVector.size( );
		musicItemVector.resize( count );
		data = musicItemVector.data( );
		auto copydata = resultMusicItemVector.data( );
		for( index = 0; index < count; index += 1 ) {
			data[ index ] = copydata[ index ];
			connect( data[ index ], &QObject::destroyed, this, &AppMusicManage::deleteMusicItem );
		}
	}
	std::vector< FavoriteItem * > resultFavoriteItemVector;
	if( FavoriteItem::setJsonDataVector( resultFavoriteItemVector, jsonObject ) ) {
		size_t count = favoriteItemVector.size( );
		FavoriteItem **data;
		size_t index;
		if( count ) {
			data = favoriteItemVector.data( );
			for( index = 0; index < count; index += 1 ) {
				data[ index ]->disconnect( data[ index ], &QObject::destroyed, this, &AppMusicManage::deleteFavoriteItem );
				delete data[ index ];
			}
		}
		count = resultFavoriteItemVector.size( );
		favoriteItemVector.resize( count );
		data = favoriteItemVector.data( );
		auto copydata = resultFavoriteItemVector.data( );
		for( index = 0; index < count; index += 1 ) {
			data[ index ] = copydata[ index ];
			connect( data[ index ], &QObject::destroyed, this, &AppMusicManage::deleteFavoriteItem );
		}
	}
	favoriteWidget->updateAppMusicManageInof( favoriteItemVector );
	return true;
}

void AppMusicManage::toMusicIndex( std::vector< size_t > &result_index, const std::vector< MusicItem * > &find_index_music_item ) {
	loadMutex->lock( );
	size_t findCount = find_index_music_item.size( );
	size_t findIndex;
	result_index.resize( findCount );
	auto findData = find_index_music_item.data( );
	size_t sourceCount = musicItemVector.size( );
	auto sourceData = musicItemVector.data( );
	size_t sourceIndex;
	auto findResultIndexData = result_index.data( );
	size_t findResultCount = 0;
	for( findIndex = 0; findIndex < findCount; findIndex += 1 ) {
		auto findItem = findData[ findIndex ];
		for( sourceIndex = 0; sourceIndex < sourceCount; sourceIndex += 1 )
			if( sourceData[ sourceIndex ] == findItem )
				break;
		if( sourceIndex == sourceCount )
			continue;
		findResultIndexData[ findResultCount ] = sourceIndex;
		findResultCount += 1;
	}
	result_index.resize( findResultCount );
	loadMutex->unlock( );
}

void AppMusicManage::fromMusicIndex( std::vector< MusicItem * > &result_music_item, const std::vector< size_t > &find_index ) {
	loadMutex->lock( );
	size_t findCount = find_index.size( );
	size_t findIndex;
	auto findData = find_index.data( );
	result_music_item.resize( findCount );
	auto resultData = result_music_item.data( );
	size_t resultCount = 0;
	size_t sourceCount = musicItemVector.size( );
	auto sourceData = musicItemVector.data( );
	for( findIndex = 0; findIndex < findCount; findIndex += 1 ) {
		auto findItem = findData[ findIndex ];
		if( findIndex >= sourceCount )
			continue;
		resultData[ resultCount ] = sourceData[ findItem ];
		resultCount += 1;
	}
	result_music_item.resize( resultCount );
	loadMutex->unlock( );
}

AppMusicManage::~AppMusicManage( ) {
	deleteResource( );
}

AppMusicDecoder * AppMusicManage::getAppMusicDecoder( ) const {
	return appMusicDecoder;
}
