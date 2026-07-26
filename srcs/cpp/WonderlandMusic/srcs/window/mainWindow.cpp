#include "mainWindow.h"
#include <QJsonObject>
#include <qboxlayout.h>
#include "../application/appDataJsonKey.h"
#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/applicationManage.h"
#include "../application/jsonKey/mainWindowJsonKey.h"
#include "../application/translate/mainWindowTranslate.h"
#include "../component/optionWindow/optionWindow.h"

#include "../head/after_init_macro.h"
#include "../head/before_init_macro.h"
#include "../head/component_assert_macro.h"
#include "../head/init_macro.h"
#include "../head/release_macro.h"

#include "../msgInfo/messageErrorOut.h"
#include "../tools/pathTools.h"
#include "../widget/aboutWidget.h"
#include "../widget/musicWidget.h"
#include "../widget/settingWidget.h"

MainWindow::MainWindow( QWidget *parent ) : MainWindow( parent, Qt::WindowFlags( ) ) {
}

MainWindow::MainWindow( Qt::WindowFlags flags ) : MainWindow( nullptr, flags ) {
}

MainWindow::MainWindow( ) : MainWindow( nullptr, Qt::WindowFlags( ) ) {
}

OptionWindow * MainWindow::getOptionWindow( ) const {
	return optionWindow;
}

bool MainWindow::getJsonData( QJsonObject &get_json_object ) const {
	optionWindow->getJsonData( get_json_object );
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
	optionWindow->setJsonData( set_json_object );
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
	Init_Resource_App_Core_Ptr( optionWindow );
	return true;
}

bool MainWindow::initBefore( ) {
	deleteResource( );
	auto appInstance = AppInstance::getAppInstance( );
	auto appTranslate = appInstance->getAppDataManage( )->getTranslate( );
	// 配置窗口顶部显示
	setWindowTitle( appTranslate->getMainWindow( )->getAppWindowTitleName( ) );

	optionWindow = new OptionWindow( this );
	Before_Init_Resource_App_Core_Ptr( optionWindow );
	return true;
}

bool MainWindow::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( optionWindow );

	setCentralWidget( optionWindow );
	optionWindow->show( );
	auto musicWidget = new MusicWidget( optionWindow );
	if( optionWindow->addOptionPanel( musicWidget ) == false )
		return false;
	auto settingWidget = new SettingWidget( optionWindow );
	if( optionWindow->addOptionPanel( settingWidget ) == false )
		return false;
	auto aboutWidget = new AboutWidget( optionWindow );
	if( optionWindow->addOptionPanel( aboutWidget ) == false )
		return false;
	return true;
}

bool MainWindow::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( optionWindow );
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
