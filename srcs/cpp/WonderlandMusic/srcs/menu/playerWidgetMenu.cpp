#include "playerWidgetMenu.h"

#include <QFileDialog>
#include <QJsonObject>

#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/jsonFileKey.h"
#include "../application/musicDecoder.h"
#include "../application/jsonKey/playerListMenuJsonKey.h"
#include "../application/translate/playerListMenuTranslate.h"

#include "../friend/playerListWidgetFriend.h"

#include "../tools/pathTools.h"
#include "../tools/widgetTools.h"

#include "../widget/playerListWidget.h"

PlayerWidgetMenu::PlayerWidgetMenu( PlayerListWidget *player_list_widget ) : QMenu( player_list_widget ), playerListWidget( player_list_widget ) {
}

bool PlayerWidgetMenu::initVar( ) {
	if( playerListWidget == nullptr )
		return false;
	appInstance = AppInstance::getAppInstance( );
	if( appInstance == nullptr )
		return false;
	appTranslate = appInstance->getTranslate( );
	if( appTranslate == nullptr )
		return false;
	playerListMenuTranslate = appTranslate->getPlayerListMenu( );
	if( playerListMenuTranslate == nullptr )
		return false;
	musicDecoder = appInstance->getMusicDecoder( );
	if( musicDecoder == nullptr )
		return false;
	jsonFileKey = appInstance->getJsonFileKey( );
	if( jsonFileKey == nullptr )
		return false;
	playerListMenuJsonKey = jsonFileKey->getPlayerListMenu( );
	if( playerListMenuJsonKey == nullptr )
		return false;
	fileSelectWorkPath = QDir::currentPath( );
	dirSelectWorkPath = QDir::currentPath( );
	playerListWidgetFriend = new PlayerListWidgetFriend( this, playerListWidget );
	loadJsonPathInfo( );
	return true;
}

bool PlayerWidgetMenu::initSubMenu( ) {
	playerMenu = addMenu( playerListMenuTranslate->getPlayerListMenuenuPlayerMenu( ) );

	removeMenu = addMenu( playerListMenuTranslate->getPlayerListMenuMoveMenu( ) );
	controlMenu = addMenu( playerListMenuTranslate->getPlayerListMenuControlMenu( ) );

	loadMenu = addMenu( playerListMenuTranslate->getPlayerListMenuFileLoadMenu( ) );
	return true;
}

bool PlayerWidgetMenu::initSubMenuAcction( ) {
	setplay = playerMenu->QWidget::addAction( playerListMenuTranslate->getPlayerListMenuPlayerMenuSetCurrentPlayAction( ) );
	insterPlay = playerMenu->QWidget::addAction( playerListMenuTranslate->getPlayerListMenuPlayerMenuInsterCurrentPlayAction( ) );

	moveTop = controlMenu->QWidget::addAction( playerListMenuTranslate->getPlayerListMenuControlMenuMoveTopMusicAction( ) );
	moveBottom = controlMenu->QWidget::addAction( playerListMenuTranslate->getPlayerListMenuControlMenuMoveBottomMusicAction( ) );

	removeMusicAtList = removeMenu->QWidget::addAction( playerListMenuTranslate->getPlayerListMenuControlMenuRemoveMusicAction( ) );
	deleteMusicAtDiskFile = removeMenu->QWidget::addAction( playerListMenuTranslate->getPlayerListMenuControlMenuDeleteMusicAction( ) );

	addMultiFileMusicToCollectionAction = loadMenu->addAction( playerListMenuTranslate->getPlayerListAddMultiMusicFileToCollectionAction( ) );
	addMultiMusicDirToCollection = loadMenu->addAction( playerListMenuTranslate->getPlayerListAddMultiMusicDirToCollectionAction( ) );

	return true;
}

bool PlayerWidgetMenu::initConnectAcction( ) {
	connect( addMultiFileMusicToCollectionAction, &QAction::triggered, this, &PlayerWidgetMenu::loadDiskFile );
	connect( addMultiMusicDirToCollection, &QAction::triggered, this, &PlayerWidgetMenu::loadDiskDir );

	connect( moveTop, &QAction::triggered, this, &PlayerWidgetMenu::selectListMoveTop );
	connect( moveBottom, &QAction::triggered, this, &PlayerWidgetMenu::selectListMoveBottom );

	connect( setplay, &QAction::triggered, this, &PlayerWidgetMenu::setCurrentSelectPlay );
	connect( insterPlay, &QAction::triggered, this, &PlayerWidgetMenu::insterCurrentSelectPlay );

	connect( removeMusicAtList, &QAction::triggered, this, &PlayerWidgetMenu::removePlayListSelectInfo );
	connect( deleteMusicAtDiskFile, &QAction::triggered, this, &PlayerWidgetMenu::deletePlayListSelectFile );

	return true;
}

void PlayerWidgetMenu::loadDiskFile( ) {
	QFileDialog dialog( this );

	dialog.setWindowTitle( playerListMenuTranslate->getLoadDiskFileTitle( ) );
	dialog.setDirectory( fileSelectWorkPath );
	dialog.setFileMode( QFileDialog::ExistingFiles );

	auto decodeFileSuffix = musicDecoder->getSupperDecodeFileSuffix( );
	QStringList filterSuffixList;
	size_t count = decodeFileSuffix.size( );
	auto data = decodeFileSuffix.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		filterSuffixList.append( "*." + data[ index ] );
	auto musicTypeName = playerListMenuTranslate->getMusicTypeName( );
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
	fileSelectWorkPath = PathTools::getAutoShortenPathName( dir.absolutePath( ) );
	writeJsonPathInfo( );
	std::vector< QString > loadVector( count );
	auto dataPtr = loadVector.data( );
	for( index = 0; index < count; index += 1 )
		dataPtr[ index ] = selectFileData[ index ];
	playerListWidgetFriend->loadDiskMusicFileList( loadVector );
}

void PlayerWidgetMenu::loadDiskDir( ) {
	QFileDialog dialog( this );
	dialog.setWindowTitle( playerListMenuTranslate->getLoadDiskDirTitle( ) );
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
	qsizetype count = files.size( );
	auto data = files.data( );
	dirSelectWorkPath = PathTools::getAutoShortenPathName( data[ 0 ] );
	writeJsonPathInfo( );
	size_t index;
	std::vector< QString > loadVector( count );
	auto dataPtr = loadVector.data( );
	for( index = 0; index < count; index += 1 )
		dataPtr[ index ] = data[ index ];
	playerListWidgetFriend->loadDiskMusicDirList( loadVector );
}

void PlayerWidgetMenu::deleteResource( ) {
	clear( );
	if( playerListWidgetFriend )
		( delete playerListWidgetFriend, playerListWidgetFriend = nullptr );
}

bool PlayerWidgetMenu::init( ) {
	deleteResource( );
	if( initVar( ) == false )
		return false;
	if( initSubMenu( ) == false )
		return false;
	if( initSubMenuAcction( ) == false )
		return false;
	if( initConnectAcction( ) == false )
		return false;
	return true;
}

bool PlayerWidgetMenu::loadJsonPathInfo( ) {
	auto jsonPath = playerListMenuJsonKey->getSettingJsonPath( );
	QJsonObject readObj;
	if( PathTools::readJsonObject( readObj, jsonPath ) == false )
		return true;
	auto end = readObj.end( );
	auto find = readObj.find( playerListMenuJsonKey->getFileSelectWorkPath( ) );
	if( find != end )
		fileSelectWorkPath = find.value( ).toString( fileSelectWorkPath );
	find = readObj.find( playerListMenuJsonKey->getDirSelectWorkPath( ) );
	if( find != end )
		dirSelectWorkPath = find.value( ).toString( dirSelectWorkPath );
	return true;
}

bool PlayerWidgetMenu::writeJsonPathInfo( ) {
	auto jsonPath = playerListMenuJsonKey->getSettingJsonPath( );
	QJsonObject writeObj;

	writeObj.insert( playerListMenuJsonKey->getFileSelectWorkPath( ), fileSelectWorkPath );
	writeObj.insert( playerListMenuJsonKey->getDirSelectWorkPath( ), dirSelectWorkPath );

	PathTools::writeJsonObject( writeObj, jsonPath );
	return true;
}

void PlayerWidgetMenu::setCurrentSelectPlay( ) {
	std::vector< MusicInfoItemWidget * > selectVector;
	playerListWidget->getSelectItemWidgetVector( selectVector );
	playerListWidgetFriend->setCurrentPlayerMusicList( selectVector );
}

void PlayerWidgetMenu::insterCurrentSelectPlay( ) {
	std::vector< MusicInfoItemWidget * > selectVector;
	playerListWidget->getSelectItemWidgetVector( selectVector );
	playerListWidgetFriend->setInsertPlayerMusicList( selectVector );
}

void PlayerWidgetMenu::removePlayListSelectInfo( ) {
	std::vector< MusicInfoItemWidget * > selectVector;
	playerListWidget->getSelectItemWidgetVector( selectVector );
	playerListWidgetFriend->removeListMusicFileList( selectVector );
}

void PlayerWidgetMenu::deletePlayListSelectFile( ) {
	std::vector< MusicInfoItemWidget * > selectVector;
	playerListWidget->getSelectItemWidgetVector( selectVector );
	playerListWidgetFriend->deleteDiskMusicFileList( selectVector );
}

void PlayerWidgetMenu::selectListMoveTop( ) {
	std::vector< MusicInfoItemWidget * > selectVector;
	playerListWidget->getSelectItemWidgetVector( selectVector );
	playerListWidgetFriend->moveMusicToListTop( selectVector );
}

void PlayerWidgetMenu::selectListMoveBottom( ) {
	std::vector< MusicInfoItemWidget * > selectVector;
	playerListWidget->getSelectItemWidgetVector( selectVector );
	playerListWidgetFriend->moveMusicToListBottom( selectVector );
}
