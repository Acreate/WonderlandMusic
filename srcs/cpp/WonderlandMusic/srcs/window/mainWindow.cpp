#include "mainWindow.h"

#include <QJsonObject>
#include <QSystemTrayIcon>
#include <qboxlayout.h>

#include "playerWindow.h"

#include "../application/appDataJsonKey.h"
#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/applicationManage.h"
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

MainStackedWidget * MainWindow::getMainStackedWidget( ) const {
	return mainStackedWidget;
}

OptionDockWidget * MainWindow::getLeftOptionDockWidget( ) const {
	return leftOptionDockWidget;
}

bool MainWindow::getJsonData( QJsonObject &get_json_object ) const {
	mainStackedWidget->getJsonData( get_json_object );
	leftOptionDockWidget->getJsonData( get_json_object );
	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getAppDataManage( )->getAppDataJsonKey( );
	auto geo = geometry( );
	int windowX = geo.x( );
	auto mainWindowJsonFileKey = jsonFileKey->getMainWindow( );

	QJsonObject json;
	json.insert( mainWindowJsonFileKey->getPointXPos( ), windowX );
	int windowY = geo.y( );
	json.insert( mainWindowJsonFileKey->getPointYPos( ), windowY );
	int windowWidth = geo.width( );
	json.insert( mainWindowJsonFileKey->getSizeWidth( ), windowWidth );
	int windowHeight = geo.height( );
	json.insert( mainWindowJsonFileKey->getSizeHeight( ), windowHeight );
	get_json_object.insert( mainWindowJsonFileKey->getObjectName( ), json );

	return true;
}

bool MainWindow::setJsonData( const QJsonObject &set_json_object ) {
	mainStackedWidget->setJsonData( set_json_object );
	leftOptionDockWidget->setJsonData( set_json_object );
	if( set_json_object.empty( ) )
		return false;
	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getAppDataManage( )->getAppDataJsonKey( );

	auto windowJsonFileKey = jsonFileKey->getMainWindow( );

	// 匹配终结符
	auto end = set_json_object.end( );
	// 查找返回
	QJsonObject::const_iterator find = set_json_object.find( windowJsonFileKey->getObjectName( ) );
	if( find != end ) {
		auto jsonObject = find.value( ).toObject( );
		if( jsonObject.empty( ) == false ) {
			// 匹配 x
			int x = this->x( );
			// 匹配 y
			int y = this->y( );
			// 匹配 w
			int width = this->width( );
			// 匹配 h
			int height = this->height( );

			end = jsonObject.end( );
			// 查找 x 坐标
			find = jsonObject.find( windowJsonFileKey->getPointXPos( ) );
			if( find != end )
				x = find.value( ).toInt( );
			// 查找 y 坐标
			find = jsonObject.find( windowJsonFileKey->getPointYPos( ) );
			if( find != end )
				y = find.value( ).toInt( );
			// 查找 w 宽度
			find = jsonObject.find( windowJsonFileKey->getSizeWidth( ) );
			if( find != end )
				width = find.value( ).toInt( );
			// 查找 h 高度
			find = jsonObject.find( windowJsonFileKey->getSizeHeight( ) );
			if( find != end )
				height = find.value( ).toInt( );
			// 设置坐标与宽高
			setGeometry( x, y, width, height );
		}
	}
	return true;
}

MainWindow::~MainWindow( ) {
	deleteResource( );
}

MainWindow::MainWindow( QWidget *parent, Qt::WindowFlags flags ) : QMainWindow( parent, flags ) {
}

bool MainWindow::init( ) {
	Before_Init_Resource_App_Core_Ptr( mainStackedWidget );
	Before_Init_Resource_App_Core_Ptr( leftOptionDockWidget );

	Init_Resource_App_Core_Ptr( mainStackedWidget );
	Init_Resource_App_Core_Ptr( leftOptionDockWidget );

	After_Init_Resource_App_Core_Ptr( mainStackedWidget );
	After_Init_Resource_App_Core_Ptr( leftOptionDockWidget );

	return true;
}

bool MainWindow::initBefore( ) {
	deleteResource( );
	auto appInstance = AppInstance::getAppInstance( );
	auto appTranslate = appInstance->getAppDataManage( )->getTranslate( );
	// 配置窗口顶部显示
	setWindowTitle( appTranslate->getMainWindow( )->getAppWindowTitleName( ) );

	mainStackedWidget = new MainStackedWidget( this );

	leftOptionDockWidget = new OptionDockWidget( this );
	return true;
}

bool MainWindow::initAfter( ) {
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
	leftOptionDockWidget->show( );
	return true;
}

bool MainWindow::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( leftOptionDockWidget );
	Delete_Resource_App_Core_Ptr( mainStackedWidget );
	disconnect( );
	return true;
}

bool MainWindow::event( QEvent *event ) {
	auto type = event->type( );
	switch( type ) {
		case QEvent::Close :
			//if( QSystemTrayIcon::isSystemTrayAvailable( ) ) {
			//	hide( );
			//	event->ignore( );
			//	return true;
			//}
			auto appInstance = AppInstance::getAppInstance( )->getApplicationManage( );
			appInstance->quit( );
	}
	return QMainWindow::event( event );
}
