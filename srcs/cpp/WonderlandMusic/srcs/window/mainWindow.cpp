#include "mainWindow.h"

#include <QDir>
#include <QStackedWidget>
#include <QDockWidget>
#include <QFileInfo>
#include <QPushButton>
#include <QJsonObject>
#include <qboxlayout.h>

#include "playerWindow.h"

#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/jsonFileKey.h"

#include "../msgInfo/messageErrorOut.h"

#include "../tools/pathTools.h"

#include "../widget/aboutWidget.h"
#include "../widget/settingWidget.h"

MainWindow::MainWindow( QWidget *parent ) : MainWindow( parent, Qt::WindowFlags( ) ) {
}

MainWindow::MainWindow( Qt::WindowFlags flags ) : MainWindow( nullptr, flags ) {
}

MainWindow::MainWindow( ) : MainWindow( nullptr, Qt::WindowFlags( ) ) {
}

void MainWindow::writeWidgetSettingToFile( ) {
	saveMainWindowSetting( );
	// 写入播放列表
	playerWindow->writeJsonPathInfo( );
	// 写入配置信息
	settingWidget->writeJsonPathInfo( );
}

MainWindow::~MainWindow( ) {
	releaseResource( );
}

MainWindow::MainWindow( QWidget *parent, Qt::WindowFlags flags ) : QMainWindow( parent, flags ), isLoadJsonFile( false ) {
}

bool MainWindow::loadSettingWidgetInfoAtFile( ) {
	// 加载播放列表
	playerWindow->loadJsonPathInfo( );
	// 记载配置列表
	settingWidget->loadJsonPathInfo( );
	return true;
}

bool MainWindow::init( ) {
	releaseResource( );
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
	return true;
}

void MainWindow::showEvent( QShowEvent *event ) {
	QMainWindow::showEvent( event );
	if( isLoadJsonFile == false ) {
		isLoadJsonFile = true;
		loadSettingWidgetInfoAtFile( );
	}
}

void MainWindow::releaseResource( ) {
	#define RS( ptr ) if( ptr ) {delete ptr; ptr = nullptr;}

	RS( showSettingWidgetBtn );
	RS( showAboutWidgetBtn );
	RS( showPlayListWidgetBtn );

	RS( leftOptionWidget );
	RS( leftOptionDockWidget );

	RS( aboutWidget );
	RS( playerWindow );
	RS( settingWidget );
}

bool MainWindow::initApp( ) {
	appInstance = AppInstance::getAppInstance( );
	appTranslate = appInstance->getTranslate( );
	jsonFileKey = appInstance->getJsonFileKey( );
	// 配置窗口顶部显示
	setWindowTitle( appTranslate->getAppWindowTitleName( ) );
	return true;
}

bool MainWindow::initStackedWidget( ) {
	mainStackedWidget = new QStackedWidget( this );
	setCentralWidget( mainStackedWidget );

	playerWindow = new PlayerWindow( mainStackedWidget );
	mainStackedWidget->addWidget( playerWindow );

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

	showPlayListWidgetBtn = new QPushButton( appTranslate->getPlayListWidget( ), leftOptionWidget );
	optionLayout->addWidget( showPlayListWidgetBtn, 0, Qt::AlignTop );

	showSettingWidgetBtn = new QPushButton( appTranslate->getSettingWidget( ), leftOptionWidget );
	optionLayout->addWidget( showSettingWidgetBtn, 0, Qt::AlignTop );

	showAboutWidgetBtn = new QPushButton( appTranslate->getAboutWidget( ), leftOptionWidget );
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
	// 获取 json 路径
	auto mainWindowJsonFile = jsonFileKey->getMainWindowSettingJsonPath( );
	QJsonObject mainWindowSettingJsonObject;
	if( PathTools::readJsonObject( mainWindowSettingJsonObject, mainWindowJsonFile ) == false )
		return true;
	// 匹配 x
	int x = this->x( );
	// 匹配 y
	int y = this->y( );
	// 匹配 w
	int width = this->width( );
	// 匹配 h
	int height = this->height( );
	// 匹配终结符
	auto end = mainWindowSettingJsonObject.end( );
	// 查找返回
	QJsonObject::iterator find;
	// 查找 x 坐标
	find = mainWindowSettingJsonObject.find( jsonFileKey->getMainWindowPointXPos( ) );
	if( find != end )
		x = find.value( ).toInt( );
	// 查找 y 坐标
	find = mainWindowSettingJsonObject.find( jsonFileKey->getMainWindowPointYPos( ) );
	if( find != end )
		y = find.value( ).toInt( );
	// 查找 w 宽度
	find = mainWindowSettingJsonObject.find( jsonFileKey->getMainWindowSizeWidth( ) );
	if( find != end )
		width = find.value( ).toInt( );
	// 查找 h 高度
	find = mainWindowSettingJsonObject.find( jsonFileKey->getMainWindowSizeHeight( ) );
	if( find != end )
		height = find.value( ).toInt( );
	// 设置坐标与宽高
	setGeometry( x, y, width, height );

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
	wirteJsonObject.insert( jsonFileKey->getMainWindowPointXPos( ), x( ) );
	wirteJsonObject.insert( jsonFileKey->getMainWindowPointYPos( ), y( ) );
	wirteJsonObject.insert( jsonFileKey->getMainWindowSizeWidth( ), width( ) );
	wirteJsonObject.insert( jsonFileKey->getMainWindowSizeHeight( ), height( ) );

	// 获取 json 路径
	auto mainWindowJsonFile = jsonFileKey->getMainWindowSettingJsonPath( );
	PathTools::writeJsonObject( wirteJsonObject, mainWindowJsonFile );
	return true;
}

void MainWindow::hideEvent( QHideEvent *event ) {
	QMainWindow::hideEvent( event );

	writeWidgetSettingToFile( );
}
