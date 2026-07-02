#include "mainWindow.h"

#include <QJsonObject>
#include <QSystemTrayIcon>
#include <qboxlayout.h>

#include "playerWindow.h"

#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/jsonFileKey.h"
#include "../application/jsonKey/mainWindowJsonKey.h"
#include "../application/translate/mainWindowTranslate.h"

#include "../dockWidget/optionDockWidget.h"

#include "../msgInfo/messageErrorOut.h"

#include "../stackedWidget/mainStackedWidget.h"

#include "../tools/pathTools.h"

MainWindow::MainWindow( QWidget *parent ) : MainWindow( parent, Qt::WindowFlags( ) ) {
}

MainWindow::MainWindow( Qt::WindowFlags flags ) : MainWindow( nullptr, flags ) {
}

MainWindow::MainWindow( ) : MainWindow( nullptr, Qt::WindowFlags( ) ) {
}

bool MainWindow::readJsonData( ) {
	// 获取 json 路径
	auto windowJsonFileKey = jsonFileKey->getMainWindow( );
	auto mainWindowJsonFile = windowJsonFileKey->getSettingJsonPath( );
	QJsonObject mainWindowSettingJsonObject;
	if( PathTools::readJsonObject( mainWindowSettingJsonObject, mainWindowJsonFile ) == false )
		return true;
	return setJsonData( mainWindowSettingJsonObject );
}

bool MainWindow::writeJsonData( ) {
	QJsonObject jsonObject;
	if( getJsonData( jsonObject ) == false )
		return false;
	// 获取 json 路径
	auto mainWindowJsonFileKey = jsonFileKey->getMainWindow( );
	auto mainWindowJsonFile = mainWindowJsonFileKey->getSettingJsonPath( );
	PathTools::writeJsonObject( jsonObject, mainWindowJsonFile );
	return true;
}

bool MainWindow::getJsonData( QJsonObject &get_json_object ) const {
	auto geo = geometry( );
	int windowX = geo.x( );
	auto mainWindowJsonFileKey = jsonFileKey->getMainWindow( );
	get_json_object.insert( mainWindowJsonFileKey->getPointXPos( ), windowX );
	int windowY = geo.y( );
	get_json_object.insert( mainWindowJsonFileKey->getPointYPos( ), windowY );
	int windowWidth = geo.width( );
	get_json_object.insert( mainWindowJsonFileKey->getSizeWidth( ), windowWidth );
	int windowHeight = geo.height( );
	get_json_object.insert( mainWindowJsonFileKey->getSizeHeight( ), windowHeight );

	return true;
}

bool MainWindow::setJsonData( const QJsonObject &set_json_object ) {
	auto windowJsonFileKey = jsonFileKey->getMainWindow( );
	auto mainWindowJsonFile = windowJsonFileKey->getSettingJsonPath( );
	// 匹配 x
	int x = this->x( );
	// 匹配 y
	int y = this->y( );
	// 匹配 w
	int width = this->width( );
	// 匹配 h
	int height = this->height( );
	// 匹配终结符
	auto end = set_json_object.end( );
	// 查找返回
	QJsonObject::const_iterator find;
	// 查找 x 坐标
	find = set_json_object.find( windowJsonFileKey->getPointXPos( ) );
	if( find != end )
		x = find.value( ).toInt( );
	// 查找 y 坐标
	find = set_json_object.find( windowJsonFileKey->getPointYPos( ) );
	if( find != end )
		y = find.value( ).toInt( );
	// 查找 w 宽度
	find = set_json_object.find( windowJsonFileKey->getSizeWidth( ) );
	if( find != end )
		width = find.value( ).toInt( );
	// 查找 h 高度
	find = set_json_object.find( windowJsonFileKey->getSizeHeight( ) );
	if( find != end )
		height = find.value( ).toInt( );
	// 设置坐标与宽高
	setGeometry( x, y, width, height );
	return true;
}

MainWindow::~MainWindow( ) {
	deleteResource( );
}

MainWindow::MainWindow( QWidget *parent, Qt::WindowFlags flags ) : QMainWindow( parent, flags ), isLoadJsonFile( false ) {
}

bool MainWindow::init( ) {
	appInstance = AppInstance::getAppInstance( );
	appTranslate = appInstance->getAppDataManage( )->getTranslate( );
	jsonFileKey = appInstance->getAppDataManage( )->getJsonFileKey( );
	// 配置窗口顶部显示
	setWindowTitle( appTranslate->getMainWindow( )->getAppWindowTitleName( ) );

	mainStackedWidget = new MainStackedWidget( this );

	leftOptionDockWidget = new OptionDockWidget( this );

	if( readJsonData( ) == false )
		return false;

	if( leftOptionDockWidget->init( ) == false )
		return false;
	if( mainStackedWidget->init( ) == false )
		return false;

	setCentralWidget( mainStackedWidget );

	connect( leftOptionDockWidget, &OptionDockWidget::signal_click_player_button, [this]( ) {
		mainStackedWidget->slot_showPlayerWidget( );
	} );
	connect( leftOptionDockWidget, &OptionDockWidget::signal_click_setting_button, [this]( ) {
		mainStackedWidget->slot_showSettingWidget( );
	} );
	connect( leftOptionDockWidget, &OptionDockWidget::signal_click_about_button, [this]( ) {
		mainStackedWidget->slot_showAboutWidget( );
	} );

	return true;
}

bool MainWindow::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( leftOptionDockWidget );
	Delete_Resource_App_Core_Ptr( mainStackedWidget );
	return true;
}

bool MainWindow::event( QEvent *event ) {
	auto type = event->type( );
	switch( type ) {
		case QEvent::Close :
			writeJsonData( );
			//if( QSystemTrayIcon::isSystemTrayAvailable( ) ) {
			//	hide( );
			//	event->ignore( );
			//	return true;
			//}
			appInstance->quit( );
	}
	return QMainWindow::event( event );
}
