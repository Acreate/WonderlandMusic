#include "mainWindow.h"

#include <QDir>
#include <QStackedWidget>
#include <QDockWidget>
#include <QFileInfo>
#include <QPushButton>
#include <QJsonObject>
#include <QScrollArea>
#include <qboxlayout.h>

#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/jsonFileKey.h"

#include "../msgInfo/messageErrorOut.h"

#include "../widget/aboutWidget.h"
#include "../widget/playListWidget.h"
#include "../widget/settingWidget.h"
MainWindow::MainWindow( QWidget *parent ) : MainWindow( parent, Qt::WindowFlags( ) ) { }
MainWindow::MainWindow( Qt::WindowFlags flags ) : MainWindow( nullptr, flags ) { }
MainWindow::MainWindow( ) : MainWindow( nullptr, Qt::WindowFlags( ) ) { }

void MainWindow::writeWidgetSettingToFile( ) {
	saveMainWindowSetting( );
	// 写入播放列表
	playListWidget->writeJsonPathInfo( );
	// 写入配置信息
	settingWidget->writeJsonPathInfo( );
}
MainWindow::~MainWindow( ) {
	writeWidgetSettingToFile( );
}
MainWindow::MainWindow( QWidget *parent, Qt::WindowFlags flags ) : QMainWindow( parent, flags ) {

}
bool MainWindow::loadSettingWidgetInfoAtFile( ) {
	// 加载播放列表
	playListWidget->loadJsonPathInfo( );
	// 记载配置列表
	settingWidget->loadJsonPathInfo( );
	return true;
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

	if( loadSettingWidgetInfoAtFile( ) == false )
		return false;
	if( initConnect( ) == false )
		return false;
	return true;
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

	playListWidgetScrollArea = new QScrollArea( mainStackedWidget );
	playListWidgetScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	playListWidgetScrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	playListWidgetScrollArea->setWidgetResizable( true );
	playListWidgetScrollArea->setWindowFlags( Qt::WindowType::Widget );

	mainStackedWidget->addWidget( playListWidgetScrollArea );

	playListWidget = new PlayListWidget( playListWidgetScrollArea );
	playListWidget->adjustSize( );
	playListWidgetScrollArea->setWidget( playListWidget );

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
	// 在左容器窗口配置按钮组件
	QWidget *leftOptionWidget = new QWidget( leftOptionDockWidget );
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
	// 查看是否存在
	QFileInfo info( mainWindowJsonFile );
	if( info.exists( ) == false )
		return true;
	// 读取文件
	QFile readJson( mainWindowJsonFile );
	if( readJson.open( QIODeviceBase::ReadOnly ) == false )
		return true;
	auto jsonFileAllData = readJson.readAll( );

	QJsonParseError jsonParseError;
	QJsonObject mainWindowSettingJsonObject;
	// 转化文件
	auto fromFileDataToDoc = QJsonDocument::fromJson( jsonFileAllData, &jsonParseError );
	if( jsonParseError.error != QJsonParseError::ParseError::NoError )
		return true;
	// 转换对象
	mainWindowSettingJsonObject = fromFileDataToDoc.object( );
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
		mainStackedWidget->setCurrentWidget( playListWidgetScrollArea );
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

	// 获取 json 路径
	auto mainWindowJsonFile = jsonFileKey->getMainWindowSettingJsonPath( );
	// 查看是否存在
	QFileInfo info( mainWindowJsonFile );
	if( info.exists( ) == false ) {
		// 创建
		auto dir = info.dir( );
		auto absolutePath = dir.absolutePath( );
		bool mkdir = dir.mkdir( absolutePath );
		if( mkdir == false ) {
			Message_Error_Out << appTranslate->getCreateDirError( ) + " : " << absolutePath;
			return false;
		}
	}
	QFile openFile( mainWindowJsonFile );
	bool open = openFile.open( QIODeviceBase::ReadWrite | QIODeviceBase::Truncate );
	if( open == false ) {
		Message_Error_Out << appTranslate->getOpenFileError( ) + " : " << mainWindowJsonFile;
		return false;
	}

	QJsonObject wirteJsonObject;
	wirteJsonObject.insert( jsonFileKey->getMainWindowPointXPos( ), x( ) );
	wirteJsonObject.insert( jsonFileKey->getMainWindowPointYPos( ), y( ) );
	wirteJsonObject.insert( jsonFileKey->getMainWindowSizeWidth( ), width( ) );
	wirteJsonObject.insert( jsonFileKey->getMainWindowSizeHeight( ), height( ) );

	QJsonDocument writeJsonDoc( wirteJsonObject );
	auto jsonData = writeJsonDoc.toJson( );
	openFile.write( jsonData );
	return true;
}
