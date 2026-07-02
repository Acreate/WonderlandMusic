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

#include "../dockWidget/musicControlDocWidget.h"
#include "../dockWidget/musicItemSizeInfoDockWidget.h"

#include "../itemWidget/musicInfoItemWidget.h"

#include "../menu/playerListWidgetMenu.h"

#include "../mutex/userMutex.h"

#include "../tools/pathTools.h"
#include "../tools/widgetTools.h"

#include "../widget/favoriteWidget.h"
#include "../widget/musicContreWidget.h"

PlayerWindow::~PlayerWindow( ) {
	deleteResource( );
}

PlayerWindow::PlayerWindow( QWidget *parent ) : QMainWindow( parent ) {
	setWindowFlags( Qt::WindowType::Widget );
}

bool PlayerWindow::deleteResource( ) {
	this->disconnect( );
	writeJsonData( );
	Delete_Resource_App_Core_Ptr( musicItemSizeInfoDockWidget );
	Delete_Resource_App_Core_Ptr( musicControlDocWidget );
	Delete_Resource_App_Core_Ptr( favoriteWidget );
	Delete_Resource_App_Core_Ptr( musicContreWidget );
	return true;
}

bool PlayerWindow::initWidget( ) {
	musicItemSizeInfoDockWidget = new MusicItemSizeInfoDockWidget( this );

	musicControlDocWidget = new MusicControlDocWidget( this );
	musicContreWidget = new MusicContreWidget( this );
	return true;
}

bool PlayerWindow::initMenu( ) {
	return true;
}

bool PlayerWindow::initConnect( ) {
	return true;
}

bool PlayerWindow::updateSubCompoment( ) {
	if( musicItemSizeInfoDockWidget->init( ) == false )
		return false;
	if( musicControlDocWidget->init( ) == false )
		return false;
	if( favoriteWidget->init( ) == false )
		return false;
	if( musicContreWidget->init( ) == false )
		return false;
	return true;
}

bool PlayerWindow::init( ) {
	deleteResource( );

	if( initWidget( ) == false )
		return false;
	if( initMenu( ) == false )
		return false;
	if( initConnect( ) == false )
		return false;
	if( updateSubCompoment( ) == false )
		return false;

	setCentralWidget( musicContreWidget );
	return true;
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
	return false;
}

bool PlayerWindow::setJsonData( const QJsonObject &set_json_object ) {
	return false;
}
