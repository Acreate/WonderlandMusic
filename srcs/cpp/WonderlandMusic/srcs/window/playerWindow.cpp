#include "playerWindow.h"

#include <QDockWidget>
#include <QScrollArea>
#include <QMenuBar>
#include <QFileDialog>
#include <QJsonObject>

#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/jsonFileKey.h"
#include "../application/musicDecoder.h"

#include "../tools/pathTools.h"
#include "../tools/widgetTools.h"

#include "../widget/playListWidget.h"
#include "../widget/playerListTopWidget.h"

PlayerWindow::PlayerWindow( QWidget *parent ) : QMainWindow( parent ) {
	setWindowFlags( Qt::WindowType::Widget );
	topDocWidget = new QDockWidget( this );
	topDocWidget->setAllowedAreas( Qt::TopDockWidgetArea );
	addDockWidget( Qt::DockWidgetArea::TopDockWidgetArea, topDocWidget );
	topDocWidget->setTitleBarWidget( new QWidget( topDocWidget ) );
	topDocWidget->setContentsMargins( 0, 0, 0, 0 );
	playerListTopWidget = new PlayerListTopWidget( topDocWidget );
	topDocWidget->setWidget( playerListTopWidget );

	playListWidgetScrollArea = new QScrollArea( this );
	playListWidgetScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	playListWidgetScrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	playListWidgetScrollArea->setWidgetResizable( true );
	playListWidgetScrollArea->setWindowFlags( Qt::WindowType::Widget );

	playListWidget = new PlayListWidget( playListWidgetScrollArea );
	playListWidget->adjustSize( );
	playListWidgetScrollArea->setWidget( playListWidget );

	setCentralWidget( playListWidgetScrollArea );

	auto windowMenuBar = menuBar( );
	if( windowMenuBar == nullptr ) {
		windowMenuBar = new QMenuBar( this );
		setMenuBar( windowMenuBar );
	}
	auto appInstance = AppInstance::getAppInstance( );
	auto appTranslate = appInstance->getTranslate( );
	auto fileMenu = windowMenuBar->addMenu( appTranslate->getMenuFileTitle( ) );
	auto addMultiFileMusicToCollectionAction = fileMenu->addAction( appTranslate->getActionAddMultiMusicFileToCollection( ) );
	auto addMultiMusicDirToCollection = fileMenu->addAction( appTranslate->getActionAddMultiMusicDirToCollection( ) );
	auto removeMultiMusicItemAtCollectionAction = fileMenu->addAction( appTranslate->getActionRemoveMultiMusicAtCollection( ) );

	connect( addMultiFileMusicToCollectionAction, &QAction::triggered, [this]( ) {
		QFileDialog dialog( this );
		dialog.setWindowTitle( tr( "多选文件" ) );
		dialog.setDirectory( fileSelectWorkPath );
		dialog.setFileMode( QFileDialog::ExistingFiles );

		auto appInstance = AppInstance::getAppInstance( );
		auto musicDecoder = appInstance->getMusicDecoder( );
		auto decodeFileSuffix = musicDecoder->getSupperDecodeFileSuffix( );
		QStringList filterSuffixList;
		size_t count = decodeFileSuffix.size( );
		auto data = decodeFileSuffix.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			filterSuffixList.append( "*." + data[ index ] );
		auto appTranslate = appInstance->getTranslate( );
		auto musicTypeName = appTranslate->getMusicTypeName( );
		auto filterSuffix = filterSuffixList.join( " " );
		auto filterName = musicTypeName + "(" + filterSuffix + ")";
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
		QFileInfo fileInfo( selectFileData[ 0 ] );
		auto dir = fileInfo.dir( );
		fileSelectWorkPath = dir.absolutePath( );
		for( index = 0; index < count; index += 1 )
			playListWidget->fromFileLoadItemInfo( selectFileData[ index ] );
	} );

	connect( addMultiMusicDirToCollection, &QAction::triggered, [this]( ) {
		QFileDialog dialog( this );
		dialog.setWindowTitle( tr( "选择目录" ) );
		dialog.setDirectory( dirSelectWorkPath );
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
		dirSelectWorkPath = files[ 0 ];
	} );
}

bool PlayerWindow::loadJsonPathInfo( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getJsonFileKey( );
	QJsonObject jsonObject;
	auto path = jsonFileKey->getPlayerWindowSettingJsonPath( );
	if( PathTools::readJsonObject( jsonObject, path ) == true ) {
		auto end = jsonObject.end( );
		QString key = jsonFileKey->getPlayerWindowFileSelectWorkPath( );
		auto find = jsonObject.find( key );
		if( find != end )
			fileSelectWorkPath = find.value( ).toString( );
		else
			fileSelectWorkPath = QDir::currentPath( );
		key = jsonFileKey->getPlayerWindowDirSelectWorkPath( );
		find = jsonObject.find( key );
		if( find != end )
			dirSelectWorkPath = find.value( ).toString( );
		else
			dirSelectWorkPath = QDir::currentPath( );
	}
	playerListTopWidget->autoSetItemSize(  );
	playerListTopWidget->loadJsonPathInfo( );
	playListWidget->setItemWidth( playerListTopWidget );
	playListWidget->loadJsonPathInfo( );
	return true;
}

bool PlayerWindow::writeJsonPathInfo( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getJsonFileKey( );
	QJsonObject jsonObject;
	QString key = jsonFileKey->getPlayerWindowFileSelectWorkPath( );
	jsonObject.insert( key, fileSelectWorkPath );
	key = jsonFileKey->getPlayerWindowDirSelectWorkPath( );
	jsonObject.insert( key, dirSelectWorkPath );
	auto path = jsonFileKey->getPlayerWindowSettingJsonPath( );
	PathTools::writeJsonObject( jsonObject, path );
	return playListWidget->writeJsonPathInfo( );
}

void PlayerWindow::showEvent( QShowEvent *event ) {
	QMainWindow::showEvent( event );

}
