#include "playerWindow.h"

#include <QDockWidget>
#include <QScrollBar>
#include <QFileDialog>
#include <QJsonObject>
#include <QScrollArea>
#include <QStackedWidget>
#include <qevent.h>
#include <qjsonarray.h>

#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/jsonFileKey.h"
#include "../application/musicDecoder.h"
#include "../application/musicManage.h"
#include "../application/jsonKey/playerWindowJsonKey.h"
#include "../application/translate/playerWindowTranslate.h"

#include "../itemWidget/musicInfoItemWidget.h"

#include "../menu/playerListWidgetMenu.h"

#include "../mutex/userMutex.h"

#include "../tools/pathTools.h"
#include "../tools/widgetTools.h"

#include "../widget/playerListWidget.h"
#include "../widget/playerListTopWidget.h"
#include "../widget/playerToolsWidget.h"

PlayerWindow::~PlayerWindow( ) {
	deleteResource( );
}

PlayerWindow::PlayerWindow( QWidget *parent ) : QMainWindow( parent ) {
	setWindowFlags( Qt::WindowType::Widget );
}

bool PlayerWindow::deleteResource( ) {
	if( musicInfoMutex ) {
		this->disconnect( );
		writeJsonData( );
		musicInfoMutex->lock( );
		size_t count = musicInfoVector.size( );
		auto data = musicInfoVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			delete data[ index ];
		musicInfoVector.clear( );

		count = playerListWidgetVector.size( );
		index = 0;
		auto playerListWidget = playerListWidgetVector.data( );
		for( ; index < count; index += 1 ) {
			playerListStackedWidget->removeWidget( playerListWidget[ index ] );
			delete playerListWidget[ index ];
		}
		playerListWidgetVector.clear( );
		Delete_Resource_App_Core_Ptr( topDocWidget );
		Delete_Resource_App_Core_Ptr( bottomDocWidget );
		Delete_Resource_App_Core_Ptr( playerListStackedWidget );
		musicInfoMutex->unlock( );
		Delete_Resource_App_Core_Ptr( musicInfoMutex );
	}
	return true;
}

bool PlayerWindow::initWidget( ) {
	topDocWidget = new QDockWidget( this );
	topDocWidget->setAllowedAreas( Qt::TopDockWidgetArea );
	addDockWidget( Qt::DockWidgetArea::TopDockWidgetArea, topDocWidget );
	topDocWidget->setTitleBarWidget( new QWidget( topDocWidget ) );
	topDocWidget->setContentsMargins( 0, 0, 0, 0 );

	playerListTopWidgetScrollArea = new QScrollArea( this );
	playerListTopWidgetScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	playerListTopWidgetScrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	playerListTopWidgetScrollArea->setWidgetResizable( true );
	playerListTopWidgetScrollArea->setWindowFlags( Qt::WindowType::Widget );
	playerListTopWidgetScrollArea->verticalScrollBar( )->setEnabled( false );
	topDocWidget->setWidget( playerListTopWidgetScrollArea );

	playerListTopWidget = new PlayerListTopWidget( playerListTopWidgetScrollArea );
	playerListTopWidgetScrollArea->setWidget( playerListTopWidget );

	bottomDocWidget = new QDockWidget( this );
	playListWidgetScrollArea = new QScrollArea( this );

	playListWidgetScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	playListWidgetScrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	playListWidgetScrollArea->setWidgetResizable( true );
	playListWidgetScrollArea->setWindowFlags( Qt::WindowType::Widget );

	bottomDocWidget->setAllowedAreas( Qt::BottomDockWidgetArea );
	bottomDocWidget->setTitleBarWidget( new QWidget( bottomDocWidget ) );
	bottomDocWidget->setContentsMargins( 0, 0, 0, 0 );
	addDockWidget( Qt::DockWidgetArea::BottomDockWidgetArea, bottomDocWidget );

	playerToolsWidget = new PlayerToolsWidget( this );
	playListWidget = new PlayerListWidget( this );

	bottomDocWidget->setWidget( playerToolsWidget );
	setCentralWidget( playListWidgetScrollArea );
	playListWidgetScrollArea->setWidget( playListWidget );

	return true;
}

bool PlayerWindow::initMenu( ) {
	playerListWidgetMenu = new PlayerListWidgetMenu( playListWidget );

	return true;
}

bool PlayerWindow::initConnect( ) {
	connect( playerListTopWidget, &PlayerListTopWidget::changedWidth, [this]( ) {
		playListWidget->setItemWidth( playerListTopWidget );
	} );
	auto playListHBar = playListWidgetScrollArea->horizontalScrollBar( );
	auto topWidgetHBar = playerListTopWidgetScrollArea->horizontalScrollBar( );
	connect( playListHBar, &QScrollBar::sliderMoved, topWidgetHBar, &QScrollBar::setValue );
	connect( playListWidget, &PlayerListWidget::popMenu, this, [this]( ) {
		popPlayerListWidgetMenu( );
	} );

	connect( playerListWidgetMenu, &PlayerListWidgetMenu::loadDiskFile, this, [this]( ) {
		QFileInfo fileInfo;
		QFileDialog dialog( this );
		auto appInstance = AppInstance::getAppInstance( );
		auto appDataManage = appInstance->getAppDataManage( );
		auto appTranslate = appDataManage->getTranslate( );
		auto playerWindowTranslate = appTranslate->getPlayerWindow( );
		dialog.setWindowTitle( playerWindowTranslate->getLoadDiskDirTitle( ) );
		fileInfo.setFile( fileSelectWorkPath );
		auto openDirPath = fileInfo.absoluteFilePath( );
		dialog.setDirectory( openDirPath );
		dialog.setFileMode( QFileDialog::ExistingFiles );
		auto musicManage = appInstance->getMusicManage( );
		auto musicDecoder = musicManage->getMusicDecoder( );
		auto decodeFileSuffix = musicDecoder->getSupperDecodeFileSuffix( );
		QStringList filterSuffixList;
		size_t count = decodeFileSuffix.size( );
		auto data = decodeFileSuffix.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			filterSuffixList.append( "*." + data[ index ] );
		auto musicTypeName = playerWindowTranslate->getMusicTypeName( );
		auto filterSuffix = filterSuffixList.join( " " );
		auto filterName = musicTypeName + "(" + filterSuffix + ");;" + playerWindowTranslate->getAnyTypeName( ) + "(*.*)";
		dialog.setNameFilter( filterName );
		QRect geometry = this->geometry( );
		auto curentWindowSize = geometry.size( );
		dialog.resize( curentWindowSize );
		auto center = geometry.center( );
		center = mapToGlobal( center );
		WidgetTools::moveWidgetToCenterPos( center, &dialog );
		if( dialog.exec( ) != QDialog::Accepted )
			return;
		QStringList files = dialog.selectedFiles( );
		count = files.size( );
		auto selectFileData = files.data( );
		fileInfo.setFile( selectFileData[ 0 ] );
		auto dir = fileInfo.dir( );
		fileSelectWorkPath = PathTools::getAutoShortenPathName( dir.absolutePath( ) );
		std::vector< QString > loadVector( count );
		auto dataPtr = loadVector.data( );
		for( index = 0; index < count; index += 1 )
			dataPtr[ index ] = selectFileData[ index ];
		//playListWidget->loadDiskMusicFileList( loadVector );
	} );
	connect( playerListWidgetMenu, &PlayerListWidgetMenu::loadDiskDir, this, [this]( ) {
		QFileInfo fileInfo;

		QFileDialog dialog( this );
		auto appInstance = AppInstance::getAppInstance( );
		auto appDataManage = appInstance->getAppDataManage( );
		auto appTranslate = appDataManage->getTranslate( );
		auto playerWindowTranslate = appTranslate->getPlayerWindow( );
		dialog.setWindowTitle( playerWindowTranslate->getLoadDiskDirTitle( ) );
		fileInfo.setFile( dirSelectWorkPath );
		auto openDirPath = fileInfo.absoluteFilePath( );
		dialog.setDirectory( openDirPath );
		dialog.setFileMode( QFileDialog::Directory );

		QRect geometry = this->geometry( );
		auto curentWindowSize = geometry.size( );
		dialog.resize( curentWindowSize );
		auto center = geometry.center( );
		center = mapToGlobal( center );
		WidgetTools::moveWidgetToCenterPos( center, &dialog );
		if( dialog.exec( ) != QDialog::Accepted )
			return;

		QStringList files = dialog.selectedFiles( );
		qsizetype count = files.size( );
		auto data = files.data( );
		dirSelectWorkPath = PathTools::getAutoShortenPathName( data[ 0 ] );
		size_t index;
		std::vector< QString > loadVector( count );
		auto dataPtr = loadVector.data( );
		for( index = 0; index < count; index += 1 )
			dataPtr[ index ] = data[ index ];
		//playListWidget->loadDiskMusicDirList( loadVector );
	} );

	return true;
}

bool PlayerWindow::updateSubCompoment( ) {
	if( playListWidget->init( ) == false )
		return false;
	if( playerToolsWidget->init( ) == false )
		return false;
	if( playerListTopWidget->init( ) == false )
		return false;
	if( playerListWidgetMenu->init( ) == false )
		return false;
	playListWidget->setFixedWidth( playerListTopWidget->width( ) );
	topDocWidget->setFixedHeight( playerListTopWidget->height( ) );
	return true;
}

bool PlayerWindow::init( ) {
	deleteResource( );

	musicInfoMutex = new UserMutex;

	if( initWidget( ) == false )
		return false;
	if( initMenu( ) == false )
		return false;
	if( initConnect( ) == false )
		return false;
	if( updateSubCompoment( ) == false )
		return false;
	return true;
}

PlayerListWidget * PlayerWindow::getPlayListWidget( ) const {
	return playListWidget;
}

PlayerListTopWidget * PlayerWindow::getPlayerListTopWidget( ) const {
	return playerListTopWidget;
}

PlayerToolsWidget * PlayerWindow::getPlayerToolsWidget( ) const {
	return playerToolsWidget;
}

PlayerListWidgetMenu * PlayerWindow::getPlayerListWidgetMenu( ) const {
	return playerListWidgetMenu;
}

void PlayerWindow::showEvent( QShowEvent *event ) {
	QMainWindow::showEvent( event );
}

void PlayerWindow::resizeEvent( QResizeEvent *event ) {
	QMainWindow::resizeEvent( event );
	int width = event->size( ).width( );
	playerListTopWidget->suggestWidth( width );
	playerToolsWidget->suggestWidth( width );
}

void PlayerWindow::mouseReleaseEvent( QMouseEvent *event ) {
	QMainWindow::mouseReleaseEvent( event );
	auto mouseButton = event->button( );

	switch( mouseButton ) {
		case Qt::MouseButton::RightButton :
			popPlayerListWidgetMenu( );
			break;
	}
}

bool PlayerWindow::popPlayerListWidgetMenu( ) {
	auto point = QCursor::pos( );
	auto mapFromGlobal = playListWidgetScrollArea->mapFromGlobal( point );
	auto contentsRect = playListWidgetScrollArea->contentsRect( );
	if( contentsRect.contains( mapFromGlobal ) ) {
		playerListWidgetMenu->exec( point );
		return true;
	}
	return false;
}

bool PlayerWindow::readJsonData( ) {
	AppInstance *appInstance = AppInstance::getAppInstance( );
	AppDataManage *appDataManage = appInstance->getAppDataManage( );
	JsonFileKey *jsonFileKey = appDataManage->getJsonFileKey( );
	auto playerWindowJsonKey = jsonFileKey->getPlayerWindow( );
	QJsonObject readResultJsonObject;
	if( PathTools::readJsonObject( readResultJsonObject, playerWindowJsonKey->getFileSelect( ) ) == false )
		return false;
	return setJsonData( readResultJsonObject );
}

bool PlayerWindow::writeJsonData( ) {
	QJsonObject saveResultJsonObject;
	if( getJsonData( saveResultJsonObject ) == false )
		return false;
	AppInstance *appInstance = AppInstance::getAppInstance( );
	AppDataManage *appDataManage = appInstance->getAppDataManage( );
	JsonFileKey *jsonFileKey = appDataManage->getJsonFileKey( );
	auto playerWindowJsonKey = jsonFileKey->getPlayerWindow( );
	return PathTools::writeJsonObject( saveResultJsonObject, playerWindowJsonKey->getFileSelect( ) );
}

bool PlayerWindow::getJsonData( QJsonObject &get_json_object ) const {
	if( musicInfoMutex->tryLock( ) == false )
		return false;
	AppInstance *appInstance = AppInstance::getAppInstance( );
	AppDataManage *appDataManage = appInstance->getAppDataManage( );
	JsonFileKey *jsonFileKey = appDataManage->getJsonFileKey( );
	auto playerWindowJsonKey = jsonFileKey->getPlayerWindow( );
	// 文件择选路径
	auto &fileSelect = playerWindowJsonKey->getFileSelect( );
	get_json_object.insert( fileSelect, fileSelectWorkPath );
	// 目录选择路径
	auto &dirSelect = playerWindowJsonKey->getDirSelect( );
	get_json_object.insert( dirSelect, dirSelectWorkPath );

	// 音频序列
	auto &musicArrayObjName = playerWindowJsonKey->getMusicArrayObjName( );
	QJsonObject musicArrayJsonObject;
	size_t musicCount = musicInfoVector.size( );
	// 音频序列个数
	auto &arrayCount = playerWindowJsonKey->getMusicArrayCount( );
	musicArrayJsonObject.insert( arrayCount, QString::number( musicCount ) );
	MusicInfoItemWidget *const*musicData = musicInfoVector.data( );
	size_t musicIndex;
	if( musicCount ) {
		musicIndex = 0;
		QJsonObject itemJsonArray;
		for( ; musicIndex < musicCount; musicIndex += 1 ) {
			auto itemWidget = musicData[ musicIndex ];
			QJsonObject itemJson;
			if( itemWidget->toJsonObect( itemJson, *itemWidget ) == false )
				continue;
			itemJsonArray.insert( QString::number( musicIndex ), itemJson );
		}
		// 音频序列数据
		auto &musicArrayData = playerWindowJsonKey->getMusicArrayData( );
		musicArrayJsonObject.insert( musicArrayData, itemJsonArray );
	}

	get_json_object.insert( musicArrayObjName, musicArrayJsonObject );
	// 收藏夹序列
	auto &favoriteArrayObjName = playerWindowJsonKey->getFavoriteArrayObjName( );
	QJsonObject favoriteArrayJsonObject;
	auto favoriteCount = playerListWidgetVector.size( );
	// 收藏夹序列个数
	auto &favoriteArrayCount = playerWindowJsonKey->getFavoriteArrayCount( );
	favoriteArrayJsonObject.insert( favoriteArrayCount, QString::number( favoriteCount ) );
	if( favoriteCount && musicCount ) {
		decltype(favoriteCount) index;
		std::vector< MusicInfoItemWidget * > musicInfoItemWidgets;
		size_t playerListCount;
		size_t playerListIndex;
		MusicInfoItemWidget **playerListData;
		MusicInfoItemWidget *findItem;
		QJsonObject favoriteData;
		// 收藏夹名称
		auto &favoriteName = playerWindowJsonKey->getFavoriteName( );
		// 收藏夹歌曲号序列
		auto &favoriteCodeArray = playerWindowJsonKey->getFavoriteCodeArray( );
		auto listWidgetData = playerListWidgetVector.data( );
		for( index = 0; index < favoriteCount; index += 1 ) {
			auto playerListWidget = listWidgetData[ index ];
			playerListWidget->getWidgetMusicInfoVector( musicInfoItemWidgets );
			// 匹配下标
			playerListCount = musicInfoItemWidgets.size( );
			playerListData = musicInfoItemWidgets.data( );
			QJsonObject favorite;
			QJsonObject playListMusicIndex;
			for( playerListIndex = 0; playerListIndex < playerListCount; playerListIndex += 1 ) {
				findItem = playerListData[ playerListIndex ];
				for( musicIndex = 0; musicIndex < musicCount; musicIndex += 1 )
					if( findItem == musicData[ musicIndex ] )
						break;
				if( musicIndex == musicCount )
					continue; // 不匹配
				playListMusicIndex.insert( QString::number( playerListIndex ), QString::number( musicIndex ) );
			}
			favorite.insert( favoriteName, playerListWidget->windowTitle( ) );
			favorite.insert( favoriteCodeArray, playListMusicIndex );
			favoriteData.insert( QString::number( index ), favorite );
		}
		// 收藏夹数据
		auto &favoriteArrayData = playerWindowJsonKey->getFavoriteArrayData( );
		favoriteArrayJsonObject.insert( favoriteArrayData, favoriteData );
	}
	get_json_object.insert( favoriteArrayObjName, favoriteArrayJsonObject );
	musicInfoMutex->unlock( );
	return true;
}

bool PlayerWindow::setJsonData( const QJsonObject &set_json_object ) {
	// 返回
	bool result = false;
	if( set_json_object.isEmpty( ) )
		return result;

	musicInfoMutex->lock( );
	AppInstance *appInstance = AppInstance::getAppInstance( );
	AppDataManage *appDataManage = appInstance->getAppDataManage( );
	JsonFileKey *jsonFileKey = appDataManage->getJsonFileKey( );
	auto playerWindowJsonKey = jsonFileKey->getPlayerWindow( );

	// 文件择选路径
	auto &fileSelect = playerWindowJsonKey->getFileSelect( );

	// 目录选择路径
	auto &dirSelect = playerWindowJsonKey->getDirSelect( );
	// 音频序列
	auto &musicArrayObjName = playerWindowJsonKey->getMusicArrayObjName( );

	// 收藏夹序列
	auto &favoriteArrayObjName = playerWindowJsonKey->getFavoriteArrayObjName( );
	// 音频数据
	QJsonObject musicArrayDataJsonObject;
	// 音频数据量
	size_t musicInfoCount = 0;
	// 收藏夹数据
	QJsonObject favoriteArrayDataJsonObject;
	// 收藏夹数量
	int favoriteCount = 0;
	// 遍历类型
	using QJsonObjectIteratorType = QKeyValueIterator< QAnyStringView, QJsonValueRef, QJsonObject::iterator, QtPrivate::QJsonObjectKeyValues< QJsonValueRef, QJsonObject::iterator > >;
	// 遍历结束
	QJsonObjectIteratorType foreachEnd;
	// 遍历起始
	QJsonObjectIteratorType foreachIterator;
	// 类型转换
	bool isConver;
	auto &arrayCount = playerWindowJsonKey->getMusicArrayCount( );
	auto iterator = set_json_object.keyValueBegin( );
	auto end = set_json_object.keyValueEnd( );
	for( ; iterator != end; ++iterator ) {
		auto key = iterator->first;
		if( key == fileSelect ) {
			fileSelectWorkPath = iterator->second.toString( fileSelectWorkPath );
		} else if( key == dirSelect ) {
			dirSelectWorkPath = iterator->second.toString( dirSelectWorkPath );
		} else if( key == musicArrayObjName ) {
			auto musicArrayJsonObject = iterator->second.toObject( );
			if( musicArrayJsonObject.isEmpty( ) )
				continue;
			// 音频序列数据
			auto &musicArrayData = playerWindowJsonKey->getMusicArrayData( );
			// 音频序列个数
			foreachIterator = musicArrayJsonObject.keyValueBegin( );
			foreachEnd = musicArrayJsonObject.keyValueEnd( );
			for( ; foreachIterator != foreachEnd; ++foreachEnd )
				if( foreachIterator->first == arrayCount ) {
					musicInfoCount = foreachIterator->second.toString( ).toULongLong( &isConver );
					if( isConver == false || musicInfoCount == 0 )
						break; // 转换失败
					if( musicArrayDataJsonObject.empty( ) == false )
						break; // 已经存在数据
				} else if( foreachIterator->first == musicArrayData ) {
					musicArrayDataJsonObject = foreachIterator->second.toObject( );
					if( musicArrayDataJsonObject.empty( ) )
						break; // 转换失败
					if( isConver == true )
						break; // 已经存在数据
				}
			if( isConver == false || musicArrayDataJsonObject.empty( ) )
				break; // 任意转换失败，则退出顶级循环
		} else if( key == favoriteArrayObjName ) {
			auto musicArrayJsonObject = iterator->second.toObject( );
			if( musicArrayJsonObject.isEmpty( ) )
				continue;

			// 收藏夹序列个数
			auto &favoriteArrayCount = playerWindowJsonKey->getFavoriteArrayCount( );
			// 收藏夹数据
			auto &favoriteArrayData = playerWindowJsonKey->getFavoriteArrayData( );
			foreachIterator = musicArrayJsonObject.keyValueBegin( );
			foreachEnd = musicArrayJsonObject.keyValueEnd( );
			for( ; foreachIterator != foreachEnd; ++foreachIterator )
				if( foreachIterator->first == favoriteArrayCount ) {
					favoriteCount = foreachIterator->second.toString( ).toULongLong( &isConver );
					if( isConver == false )
						continue; // 失败
					if( favoriteArrayDataJsonObject.isEmpty( ) == false )
						break; // 已经存在数据
				} else if( foreachIterator->first == favoriteArrayData ) {
					favoriteArrayDataJsonObject = foreachIterator->second.toObject( );
					if( favoriteArrayDataJsonObject.isEmpty( ) == false )
						break; // 转换失败
					if( isConver == true )
						continue; // 已经知道个数
				}
			if( isConver == false || favoriteArrayDataJsonObject.empty( ) || favoriteCount == 0 )
				break; // 任意转换失败，则退出顶级循环
		}
	}
	// 个数存在，与已经实现的转换，窗口不能为 0 个
	if( musicInfoCount && isConver && favoriteCount != 0 ) {
		// 从 musicArrayDataJsonObject 恢复列表

		size_t index;
		size_t count;

		std::vector< MusicInfoItemWidget * > buff( musicInfoCount, nullptr );
		MusicInfoItemWidget **infoItemWidget = buff.data( );

		foreachIterator = musicArrayDataJsonObject.keyValueBegin( );
		foreachEnd = musicArrayDataJsonObject.keyValueEnd( );
		count = 0;
		for( ; foreachIterator != foreachEnd; ++foreachIterator ) {
			auto setIndex = foreachIterator->first.toString( ).toULongLong( &isConver );
			if( isConver == false )
				break;
			if( setIndex >= musicInfoCount )
				break; // 越界
			auto jsonValueRef = foreachIterator->second.toObject( );
			auto newItem = new MusicInfoItemWidget( );
			infoItemWidget[ setIndex ] = newItem;
			if( newItem->forJsonObject( *newItem, jsonValueRef ) == false )
				break;
			count += 1;
		}
		if( count != musicInfoCount )/* 数据不匹配，清理数据 */ {
			for( index = 0; index < musicInfoCount; index += 1 )
				if( infoItemWidget[ index ] )
					delete infoItemWidget[ index ];
		} else {
			// 从 favoriteArrayDataJsonObject 恢复收藏夹
			std::vector< PlayerListWidget * > buffListWidget( favoriteCount, nullptr );
			PlayerListWidget **playerListWidgetData = buffListWidget.data( );
			for( index = 0; index < favoriteCount; index += 1 )
				playerListWidgetData[ index ] = new PlayerListWidget( this );

			result = true;
			QJsonObject favore;
			auto &favoriteName = playerWindowJsonKey->getFavoriteName( );
			auto &favoriteCodeArray = playerWindowJsonKey->getFavoriteCodeArray( );
			foreachIterator = favoriteArrayDataJsonObject.keyValueBegin( );
			foreachEnd = favoriteArrayDataJsonObject.keyValueEnd( );
			for( ; foreachIterator != foreachEnd; ++foreachIterator )
				if( index = foreachIterator->first.toString( ).toULongLong( &isConver ), isConver == false || index >= favoriteCount ) {
					// 返回 false
					result = false;
					break; // 跳出循环
				} else {
					QString widgetTitleName;
					QJsonObject jsonArray;

					favore = foreachIterator->second.toObject( );
					iterator = favore.constKeyValueBegin( );
					end = favore.constKeyValueEnd( );
					for( ; iterator != end; ++iterator )
						if( iterator->first == favoriteName ) {
							widgetTitleName = iterator->second.toString( );
							if( widgetTitleName.isEmpty( ) )
								break; // 收藏夹名称为空
							if( jsonArray.empty( ) == false )
								break; // 序列不为空
						} else if( iterator->first == favoriteCodeArray ) {
							jsonArray = iterator->second.toObject( );
							if( jsonArray.empty( ) )
								break; // 序列为空
							if( widgetTitleName.isEmpty( ) == false )
								break; // 收藏夹名称不为空
						}
					if( widgetTitleName.isEmpty( ) ) {
						result = false;
						break;
					}
					playerListWidgetData[ index ]->setWindowTitle( widgetTitleName );
					qsizetype jsonArrayCount = jsonArray.size( );
					std::vector< MusicInfoItemWidget * > setVector( jsonArrayCount );
					auto setData = setVector.data( );
					auto arrayKeyValueIt = jsonArray.keyValueBegin( );
					auto arrayKeyValueEn = jsonArray.keyValueEnd( );
					for( ; arrayKeyValueIt != arrayKeyValueEn; ++arrayKeyValueIt ) {
						auto setIndex = arrayKeyValueIt->first.toString( ).toULongLong( &isConver );
						if( isConver == false )
							break;
						auto var = arrayKeyValueIt->second.toString( ).toULongLong( &isConver );
						if( isConver == false )
							break;
						setData[ setIndex ] = infoItemWidget[ var ];
					}
					if( arrayKeyValueIt != arrayKeyValueEn ) {
						result = false;
						break;
					}
					playerListWidgetData[ index ]->setWidgetMusicInfoVector( setVector );
				}
			// 数据处理返回 true，则覆盖旧数据
			if( result == false ) {
				/* 转码失败，或者窗口越界，清理数据 */
				for( index = 0; index < favoriteCount; index += 1 )
					if( playerListWidgetData[ index ] )
						delete playerListWidgetData[ index ];
				for( index = 0; index < musicInfoCount; index += 1 )
					if( infoItemWidget[ index ] )
						delete infoItemWidget[ index ];
			} else {
				count = playerListWidgetVector.size( );
				playerListWidgetData = playerListWidgetVector.data( );
				for( index = 0; index < count; index += 1 ) {
					playerListStackedWidget->removeWidget( playerListWidgetData[ index ] );
					delete playerListWidgetData[ index ];
				}
				playerListWidgetVector = buffListWidget;
				count = playerListWidgetVector.size( );
				playerListWidgetData = playerListWidgetVector.data( );
				for( index = 0; index < count; index += 1 )
					playerListStackedWidget->addWidget( playerListWidgetData[ index ] );
				count = musicInfoVector.size( );
				if( count )/* 删除旧有数据 */ {
					infoItemWidget = musicInfoVector.data( );
					for( index = 0; index < count; index += 1 )
						delete infoItemWidget[ index ];
				}
				musicInfoVector = buff;
				result = true;
			}
		}
	}
	musicInfoMutex->unlock( );
	return result;
}
