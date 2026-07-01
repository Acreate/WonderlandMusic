#include "mainWindow.h"

#include <QStackedWidget>
#include <QDockWidget>
#include <QPushButton>
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

#include "../msgInfo/messageErrorOut.h"

#include "../tools/pathTools.h"
#include "../tools/templateArgs.h"

#include "../widget/aboutWidget.h"
#include "../widget/settingWidget.h"

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

bool MainWindow::subCompomentInit( ) {
	if( playerWindow->init( ) == false )
		return false;
	if( settingWidget->init( ) == false )
		return false;
	if( aboutWidget->init( ) == false )
		return false;
	return true;
}

MainWindow::~MainWindow( ) {
	deleteResource( );
}

MainWindow::MainWindow( QWidget *parent, Qt::WindowFlags flags ) : QMainWindow( parent, flags ), isLoadJsonFile( false ) {
}

bool MainWindow::init( ) {
	if( initApp( ) == false )
		return false;
	if( initStackedWidget( ) == false )
		return false;
	if( initDockWidget( ) == false )
		return false;
	if( initMainWindowSetting( ) == false )
		return false;

	if( initConnect( ) == false )
		return false;

	if( subCompomentInit( ) == false )
		return false;

	return true;
}

bool MainWindow::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( showSettingWidgetBtn );
	Delete_Resource_App_Core_Ptr( showAboutWidgetBtn );
	Delete_Resource_App_Core_Ptr( showPlayListWidgetBtn );
	Delete_Resource_App_Core_Ptr( leftOptionWidget );
	Delete_Resource_App_Core_Ptr( leftOptionDockWidget );
	Delete_Resource_App_Core_Ptr( aboutWidget );
	Delete_Resource_App_Core_Ptr( playerWindow );
	Delete_Resource_App_Core_Ptr( settingWidget );
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

bool MainWindow::initApp( ) {
	appInstance = AppInstance::getAppInstance( );
	appTranslate = appInstance->getAppDataManage( )->getTranslate( );
	jsonFileKey = appInstance->getAppDataManage( )->getJsonFileKey( );
	// 配置窗口顶部显示
	setWindowTitle( appTranslate->getMainWindow( )->getAppWindowTitleName( ) );
	return true;
}

bool MainWindow::initStackedWidget( ) {
	mainStackedWidget = new QStackedWidget( this );
	setCentralWidget( mainStackedWidget );

	playerWindow = new PlayerWindow( mainStackedWidget );
	mainStackedWidget->addWidget( playerWindow );
	playerWindow->adjustSize( );

	settingWidget = new SettingWidget( mainStackedWidget );
	mainStackedWidget->addWidget( settingWidget );
	settingWidget->adjustSize( );

	aboutWidget = new AboutWidget( mainStackedWidget );
	mainStackedWidget->addWidget( aboutWidget );
	aboutWidget->adjustSize( );

	return true;
}

bool MainWindow::initDockWidget( ) {
	leftOptionDockWidget = new QDockWidget( this );
	leftOptionDockWidget->setAllowedAreas( Qt::LeftDockWidgetArea );
	addDockWidget( Qt::DockWidgetArea::LeftDockWidgetArea, leftOptionDockWidget );
	leftOptionDockWidget->setTitleBarWidget( new QWidget( leftOptionDockWidget ) );
	leftOptionDockWidget->setContentsMargins( 0, 0, 0, 0 );

	leftOptionWidget = new QWidget( leftOptionDockWidget );
	leftOptionDockWidget->setWidget( leftOptionWidget );
	// 创建左侧容器组件布局
	auto *optionLayout = new QVBoxLayout( leftOptionWidget );
	optionLayout->setContentsMargins( 0, 0, 0, 0 );
	optionLayout->setSpacing( 0 );
	auto mainWindowTranslate = appTranslate->getMainWindow( );
	showPlayListWidgetBtn = new QPushButton( mainWindowTranslate->getMusicTypeName( ), leftOptionWidget );
	optionLayout->addWidget( showPlayListWidgetBtn, 0, Qt::AlignTop );

	showSettingWidgetBtn = new QPushButton( mainWindowTranslate->getSettingWidget( ), leftOptionWidget );
	optionLayout->addWidget( showSettingWidgetBtn, 0, Qt::AlignTop );

	showAboutWidgetBtn = new QPushButton( mainWindowTranslate->getAboutWidget( ), leftOptionWidget );
	optionLayout->addWidget( showAboutWidgetBtn, 0, Qt::AlignTop );

	// 底部弹顶
	QSpacerItem *spacerItem = new QSpacerItem( 1, 1, QSizePolicy::Ignored, QSizePolicy::Expanding );
	optionLayout->addSpacerItem( spacerItem );
	// 强制宽度
	leftOptionWidget->adjustSize( );
	leftOptionWidget->setFixedWidth( leftOptionWidget->width( ) );

	return true;
}

bool MainWindow::initMainWindowSetting( ) {
	readJsonData( );

	return true;
}

bool MainWindow::initConnect( ) {
	connect( showPlayListWidgetBtn, &QPushButton::clicked, [this]( ) {
		mainStackedWidget->setCurrentWidget( playerWindow );
	} );
	connect( showSettingWidgetBtn, &QPushButton::clicked, [this]( ) {
		mainStackedWidget->setCurrentWidget( settingWidget );
	} );
	connect( showAboutWidgetBtn, &QPushButton::clicked, [this]( ) {
		mainStackedWidget->setCurrentWidget( aboutWidget );
	} );
	return true;
}

bool MainWindow::saveMainWindowSetting( ) {
	QJsonObject wirteJsonObject;
	auto geo = geometry( );
	int windowX = geo.x( );
	auto mainWindowJsonFileKey = jsonFileKey->getMainWindow( );
	wirteJsonObject.insert( mainWindowJsonFileKey->getPointXPos( ), windowX );
	int windowY = geo.y( );
	wirteJsonObject.insert( mainWindowJsonFileKey->getPointYPos( ), windowY );
	int windowWidth = geo.width( );
	wirteJsonObject.insert( mainWindowJsonFileKey->getSizeWidth( ), windowWidth );
	int windowHeight = geo.height( );
	wirteJsonObject.insert( mainWindowJsonFileKey->getSizeHeight( ), windowHeight );

	// 获取 json 路径
	auto mainWindowJsonFile = mainWindowJsonFileKey->getSettingJsonPath( );
	PathTools::writeJsonObject( wirteJsonObject, mainWindowJsonFile );
	return true;
}
