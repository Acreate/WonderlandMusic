#include "application.h"
#include <QScreen>
#include <QCursor>
#include <QDir>
#include <QFileInfo>
#include <QJsonObject>

#include "../mainWindows/mainWindow.h"

#include "../msgInfo/messageErrorOut.h"
Application::Application( int &argc, char **const argv, const int i ) : QApplication( argc, argv, i ) {
	mainWindowPtr = nullptr;
	firstShow = false;
	appSetting = new QJsonObject;
	qDirTool = new QDir;
	fileInfoTool = new QFileInfo;
	appSettingPath = qDirTool->currentPath( ) + "/program/setting/app.json";
	fileInfoTool->setFile( appSettingPath );
	if( fileInfoTool->exists( ) ) {

		QFile file( appSettingPath );
		if( file.open( QIODeviceBase::Text | QIODeviceBase::ReadOnly ) ) {
			auto byteArray = file.readAll( );
			QJsonParseError err;
			QJsonDocument doc = QJsonDocument::fromJson( byteArray, &err );
			if( err.error != QJsonParseError::NoError ) {
				MessageErrorOut( ) << tr( "文件读取失败:%1:%2" ).arg( appSettingPath ).arg( err.errorString( ) );
			} else {
				*appSetting = doc.object( );
			}
		} else
			MessageErrorOut( ) << tr( "文件打开失败:%1" ).arg( appSettingPath );

	} else {
		QDir dir = fileInfoTool->dir( );
		auto absolutePath = dir.absolutePath( );
		if( dir.mkdir( absolutePath ) == false )
			MessageErrorOut( ) << tr( "构建路径异常:%1" ).arg( absolutePath );
	}
}
Application::~Application( ) {
	fileInfoTool->setFile( appSettingPath );
	if( fileInfoTool->exists( ) == false ) {
		QDir dir = fileInfoTool->dir( );
		auto absolutePath = dir.absolutePath( );
		if( dir.mkdir( absolutePath ) == false )
			MessageErrorOut( ) << tr( "构建路径异常:%1" ).arg( absolutePath );
	}
	QFile file( appSettingPath );
	if( file.open( QIODeviceBase::WriteOnly | QIODeviceBase::Text | QIODeviceBase::Truncate ) ) {
		QJsonDocument doc( *appSetting );
		QString jsonStr = doc.toJson( QJsonDocument::Indented ); //格式化字符串
		auto byteArray = jsonStr.toUtf8( );
		file.write( byteArray );
		file.close( );
	}
	delete appSetting;
	delete qDirTool;
	delete fileInfoTool;
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
			// 找到匹配的屏幕
			screenX = screenX + screenWidth / 2;
			screenY = screenY + screenHeight / 2;
			first_show_main_window->suggestGeometry( screenX, screenY, 0, 0 );
			break; // 移动完成，则跳出屏幕检索
		}

	}

}
