#include "application.h"
#include <QScreen>
#include <QCursor>
#include <QDir>
#include <QFileInfo>
#include <QJsonObject>

#include "applicationInstance.h"

#include "../mainWindows/mainWindow.h"

#include "../msgInfo/messageErrorOut.h"
Application::Application( int &argc, char **const argv, const int i ) : QApplication( argc, argv, i ) {
	mainWindowPtr = nullptr;
	firstShow = false;
	appSetting = new QJsonObject;
	qDirTool = new QDir;
	fileInfoTool = new QFileInfo;
	translate = new Translate;
	appStartRunTime = new QDateTime( );
	*appStartRunTime = QDateTime::currentDateTime( );
	applicationInstance = new ApplicationInstance( this );
	ApplicationInstance::instance = applicationInstance;
	appSettingPath = qDirTool->currentPath( ) + "/program/setting/app.json";
	fileInfoTool->setFile( appSettingPath );
	if( fileInfoTool->exists( ) ) {

		QFile file( appSettingPath );
		if( file.open( QIODeviceBase::Text | QIODeviceBase::ReadOnly ) ) {
			auto byteArray = file.readAll( );
			QJsonParseError err;
			QJsonDocument doc = QJsonDocument::fromJson( byteArray, &err );
			if( err.error != QJsonParseError::NoError ) {
				MessageErrorOut( ) << translate->openFileError << " : " << appSettingPath << " : " << err.errorString( );
			} else
				*appSetting = doc.object( );
		} else
			MessageErrorOut( ) << translate->openFileError << " : " << appSettingPath;

	} else {
		QDir dir = fileInfoTool->dir( );
		auto absolutePath = dir.absolutePath( );
		if( fileInfoTool->exists( absolutePath ) == false )
			if( dir.mkdir( absolutePath ) == false )
				MessageErrorOut( ) << translate->createDirError << " : " << absolutePath;
	}
}
Application::~Application( ) {
	fileInfoTool->setFile( appSettingPath );
	if( fileInfoTool->exists( ) == false ) {
		QDir dir = fileInfoTool->dir( );
		auto absolutePath = dir.absolutePath( );
		if( dir.mkdir( absolutePath ) == false )
			MessageErrorOut( ) << translate->createDirError << " : " << absolutePath;
	}
	QFile file( appSettingPath );
	if( file.open( QIODeviceBase::ReadWrite | QIODeviceBase::Text | QIODeviceBase::Truncate ) ) {
		QJsonDocument doc( *appSetting );
		QString jsonStr = doc.toJson( QJsonDocument::Indented ); //格式化字符串
		auto byteArray = jsonStr.toUtf8( );
		file.write( byteArray );
		file.close( );
	}
	delete applicationInstance;
	delete appSetting;
	delete qDirTool;
	delete fileInfoTool;
	delete appStartRunTime;
	delete translate;
}
bool Application::notify( QObject *object, QEvent *event ) {
	bool notify = QApplication::notify( object, event );
	switch( event->type( ) ) {
		case QEvent::Show :
			if( mainWindowPtr == object && firstShow == false ) {
				firstMainWindowShow( mainWindowPtr );
				firstShow = true;
			}
			break;
		case QEvent::Close :
			// 主窗口关闭，则退出软件
			if( mainWindowPtr == object ) {
				QString objectName = mainWindowPtr->objectName( );
				auto mainWindowXKey = objectName + ".x";
				auto mainWindowYKey = objectName + ".y";
				auto mainWindowWKey = objectName + ".w";
				auto mainWindowHKey = objectName + ".h";
				int valueX = mainWindowPtr->x( );
				int valueY = mainWindowPtr->y( );
				int valueW = mainWindowPtr->width( );
				int valueH = mainWindowPtr->height( );
				appSetting->insert( mainWindowXKey, valueX );
				appSetting->insert( mainWindowYKey, valueY );
				appSetting->insert( mainWindowWKey, valueW );
				appSetting->insert( mainWindowHKey, valueH );
				ApplicationInstance::instance = nullptr;
				// 删除所有窗口
				QWidgetList levelWidgets = topLevelWidgets( );
				qsizetype count = levelWidgets.size( );
				auto data = levelWidgets.data( );
				qsizetype index = 0;
				for( ; index < count; ++index )
					if( data[ index ] != mainWindowPtr )
						delete data[ index ];
				quit( );
			}
			break;
		case QEvent::Quit :
			delete mainWindowPtr;
			mainWindowPtr = nullptr;
			break;
	}
	return notify;
}
bool Application::event( QEvent *event ) {
	return QApplication::event( event );
}
Application::Translate::Translate( ) {
	createDirError = QObject::tr( "创建目录失败" );
	openFileError = QObject::tr( "打开文件失败" );
}
void Application::setMainWindowPtr( MainWindow *main_window_ptr ) {
	if( main_window_ptr == nullptr )
		return;
	MainWindow *oldMainWindow = mainWindowPtr;
	mainWindowPtr = main_window_ptr;
	if( oldMainWindow ) {
		oldMainWindow->hide( );
		oldMainWindow->deleteLater( );
	}
	firstShow = false;
	mainWindowPtr->show( );
}
void Application::firstMainWindowShow( MainWindow *first_show_main_window ) {

	int screenX, screenY, screenRightX, screenBottmY, screenWidth, screenHeight;
	QString objectName = first_show_main_window->objectName( );
	auto mainWindowXKey = objectName + ".x";
	auto mainWindowYKey = objectName + ".y";
	auto mainWindowWKey = objectName + ".w";
	auto mainWindowHKey = objectName + ".h";
	int containsKeyCount = 0;
	auto iterator = appSetting->begin( );
	auto end = appSetting->end( );
	for( ; iterator != end; ++iterator ) {
		objectName = iterator.key( );
		if( objectName == mainWindowXKey ) {
			screenX = iterator.value( ).toInt( 0 );
			++containsKeyCount;
		} else if( objectName == mainWindowYKey ) {
			screenY = iterator.value( ).toInt( 0 );
			++containsKeyCount;
		} else if( objectName == mainWindowWKey ) {
			screenWidth = iterator.value( ).toInt( 200 );
			++containsKeyCount;
		} else if( objectName == mainWindowHKey ) {
			screenHeight = iterator.value( ).toInt( 100 );
			++containsKeyCount;
		}
		if( containsKeyCount == 4 ) {
			first_show_main_window->move( screenX, screenY );
			if( screenWidth > 0 && screenHeight > 0 )
				first_show_main_window->resize( screenWidth, screenHeight );
			break;
		}
	}
	if( containsKeyCount != 4 ) {
		// 获取全部屏幕列表
		QList< QScreen * > screenList = screens( );
		qsizetype count = screenList.size( );
		auto data = screenList.data( );
		qsizetype index = 0;
		auto cursorPos = QCursor::pos( );
		int cursorX;
		int cursorY;

		cursorX = cursorPos.x( );
		cursorY = cursorPos.y( );
		QScreen *screen;
		for( ; index < count; ++index ) {
			screen = data[ index ];
			auto geometry = screen->geometry( );
			screenX = geometry.x( );
			if( screenX > cursorX )
				continue; // 左侧坐标大于鼠标
			screenY = geometry.y( );
			if( screenY > cursorY )
				continue; // 下侧大于鼠标
			screenWidth = geometry.width( );
			screenRightX = screenX + screenWidth;
			if( screenRightX < cursorX )
				continue; // 右侧坐标小于鼠标
			screenHeight = geometry.height( );
			screenBottmY = screenY + screenHeight;
			if( screenBottmY < cursorY )
				continue; // 下侧小于鼠标
			// 找到匹配的屏幕，并且移动到中间
			screenX = screenX + ( screenWidth - first_show_main_window->width( ) ) / 2;
			screenY = screenY + ( screenHeight - first_show_main_window->height( ) ) / 2;
			first_show_main_window->move( screenX, screenY );
			break; // 移动完成，则跳出屏幕检索
		}

	}
	MessageErrorOut( ) << tr( "第一次" );
}
