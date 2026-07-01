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
		Delete_Resource_App_Core_Ptr( topDocWidget );
		Delete_Resource_App_Core_Ptr( bottomDocWidget );
		Delete_Resource_App_Core_Ptr( playerListStackedWidget );
		size_t count = musicInfoVector.size( );
		auto data = musicInfoVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			delete data[ index ];
		musicInfoVector.clear( );
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
		playListWidget->loadDiskMusicFileList( loadVector );
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
		playListWidget->loadDiskMusicDirList( loadVector );
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
		auto &musicArrayData = playerWindowJsonKey->getMusicArrayData( );
		musicArrayJsonObject.insert( musicArrayData, itemJsonArray );
	}

	get_json_object.insert( musicArrayObjName, musicArrayJsonObject );

	auto &favoriteArrayObjName = playerWindowJsonKey->getFavoriteArrayObjName( );
	QJsonObject favoriteArrayJsonObject;
	auto favoriteCount = playerListStackedWidget->count( );
	auto &favoriteArrayCount = playerWindowJsonKey->getFavoriteArrayCount( );
	favoriteArrayJsonObject.insert( favoriteArrayCount, favoriteCount );
	if( favoriteCount && musicCount ) {
		decltype(favoriteCount) index = 0;
		std::vector< MusicInfoItemWidget * > musicInfoItemWidgets;
		size_t playerListCount;
		size_t playerListIndex;
		MusicInfoItemWidget **playerListData;
		MusicInfoItemWidget *findItem;
		for( ; index < favoriteCount; index += 1 ) {
			auto widget = playerListStackedWidget->widget( index );
			if( widget == nullptr )
				continue;
			auto playerListWidget = qobject_cast< PlayerListWidget * >( widget );
			if( playerListWidget == nullptr )
				continue;
			playerListWidget->getMusicInfoVector( musicInfoItemWidgets );
			// 匹配下标
			playerListCount = musicInfoItemWidgets.size( );
			playerListData = musicInfoItemWidgets.data( );
			QJsonArray playListMusicIndex;
			for( playerListIndex = 0; playerListIndex < playerListCount; playerListIndex += 1 ) {
				findItem = playerListData[ playerListIndex ];
				for( ; musicIndex < musicCount; musicIndex += 1 )
					if( findItem == musicData[ musicIndex ] )
						break;
				if( musicIndex == musicCount )
					continue; // 不匹配
				playListMusicIndex.append( QString::number( musicIndex ) );
			}
			favoriteArrayJsonObject.insert( QString::number( index ), playListMusicIndex );
		}
	}
	get_json_object.insert( favoriteArrayObjName, favoriteArrayJsonObject );
	musicInfoMutex->unlock( );
	return true;
}

bool PlayerWindow::setJsonData( const QJsonObject &set_json_object ) {
	return false;
}
