#include "application.h"
#include <QScreen>
#include <QCursor>
#include <QDir>
#include <QFileInfo>
#include <QFontDatabase>
#include <QJsonObject>
#include <QPainter>
#include <QTranslator>

#include "applicationEvenTrigger.h"

#include "../mainWindows/mainWindow.h"
#include "../msgInfo/messageErrorOut.h"

#include "../render/render.h"

class AppRenderObj : public Render {
	friend class Application;
private:
	QFont font;
	QColor color;
private:
	AppRenderObj( const QFont &font, const QColor &color )
		: font( font ),
		color( color ) { }
protected:
	~AppRenderObj( ) override { }
public:
	bool renderTextImage( QImage &result_image, const QString &text ) override;
	bool renderTextImage( QImage &result_image, const QString &text, const QColor &draw_color ) override;
	bool renderTextImage( QImage &result_image, const QString &text, const QFont &draw_font ) override;
	bool renderTextImage( QImage &result_image, const QString &text, const QFont &draw_font, const QColor &draw_color ) override;
	bool renderOverlapImage( QImage &result_image, const QImage &top_image ) override;
	bool renderExpandImage( QImage &result_image, const QImage &expand_image, const QPoint &pos ) override;
	bool renderColorImage( QImage &result_image, const QColor &color ) override;
	bool renderColorReplaceColorImage( QImage &result_image, const QColor &old_color, const QColor &new_color ) override;
};

bool AppRenderObj::renderTextImage( QImage &result_image, const QString &text ) {
	return renderTextImage( result_image, text, font, color );
}
bool AppRenderObj::renderTextImage( QImage &result_image, const QString &text, const QColor &draw_color ) {
	return renderTextImage( result_image, text, font, draw_color );
}
bool AppRenderObj::renderTextImage( QImage &result_image, const QString &text, const QFont &draw_font ) {
	return renderTextImage( result_image, text, draw_font, color );
}
bool AppRenderObj::renderTextImage( QImage &result_image, const QString &text, const QFont &draw_font, const QColor &draw_color ) {
	qsizetype length = text.length( );
	if( length == 0 )
		return true;

	QFontMetrics fontMetrics( draw_font );
	int ascent = fontMetrics.ascent( );
	int height = fontMetrics.height( );
	int horizontalAdvance = fontMetrics.horizontalAdvance( text );
	QImage image( horizontalAdvance, height, QImage::Format_RGBA8888 );
	if( image.isNull( ) )
		return false;
	image.fill( 0 );
	QPainter painter;
	painter.begin( &image );
	painter.drawImage( 0, 0, result_image );
	painter.setFont( draw_font );
	QPen pen = painter.pen( );
	pen.setColor( draw_color );
	painter.setPen( pen );
	painter.drawText( 0, ascent, text );
	painter.end( );

	// 刷新
	result_image = image;
	return true;
}
bool AppRenderObj::renderOverlapImage( QImage &result_image, const QImage &top_image ) {
	int resultWidth = result_image.width( );
	int resultHeight = result_image.height( );
	int topWidth = top_image.width( );
	int topHeight = top_image.height( );

	int maxWidth = resultWidth > topWidth ? resultWidth : topWidth;
	int maxHeight = resultHeight > topHeight ? resultHeight : topHeight;

	QImage buff = QImage( maxWidth, maxHeight, QImage::Format_RGBA8888 );
	if( buff.isNull( ) )
		return false;
	buff.fill( 0 );
	QPainter painter;
	painter.begin( &buff );
	painter.drawImage( 0, 0, result_image );
	painter.drawImage( 0, 0, top_image );
	painter.end( );

	// 刷新
	result_image = buff;
	return true;
}
bool AppRenderObj::renderExpandImage( QImage &result_image, const QImage &expand_image, const QPoint &pos ) {
	int resultWidth = result_image.width( );
	int resultHeight = result_image.height( );
	int topWidth = expand_image.width( ) + pos.x( );
	int topHeight = expand_image.height( ) + pos.y( );

	int maxWidth = resultWidth > topWidth ? resultWidth : topWidth;
	int maxHeight = resultHeight > topHeight ? resultHeight : topHeight;

	QImage buff = QImage( maxWidth, maxHeight, QImage::Format_RGBA8888 );
	if( buff.isNull( ) )
		return false;
	buff.fill( 0 );
	QPainter painter;
	painter.begin( &buff );
	painter.drawImage( 0, 0, result_image );
	painter.drawImage( pos, expand_image );
	painter.end( );

	// 刷新
	result_image = buff;
	return true;
}
bool AppRenderObj::renderColorImage( QImage &result_image, const QColor &color ) {
	if( result_image.isNull( ) )
		return false;
	int resultWidth = result_image.width( );
	int resultHeight = result_image.height( );
	QImage buff = QImage( resultWidth, resultHeight, QImage::Format_RGBA8888 );
	if( buff.isNull( ) )
		return false;
	result_image.fill( color );
	result_image = buff;
	return true;
}
bool AppRenderObj::renderColorReplaceColorImage( QImage &result_image, const QColor &old_color, const QColor &new_color ) {
	if( result_image.isNull( ) )
		return false;
	int resultWidth = result_image.width( );
	int resultHeight = result_image.height( );
	QImage buff = QImage( resultWidth, resultHeight, QImage::Format_RGBA8888 );
	if( buff.isNull( ) )
		return false;
	buff.fill( 0 );
	QPainter painter;
	painter.begin( &buff );
	painter.drawImage( 0, 0, result_image );
	painter.end( );

	// 旧的透明
	int oldAlpha = old_color.alpha( );
	// 旧的红
	int oldRed = old_color.red( );
	// 旧的绿
	int oldGreen = old_color.green( );
	// 旧的蓝
	int oldBlue = old_color.blue( );

	// 新的透明
	int newAlpha = new_color.alpha( );
	// 新的红
	int newRed = new_color.red( );
	// 新的绿
	int newGreen = new_color.green( );
	// 新的蓝
	int newBlue = new_color.blue( );

	// 首地址
	uchar *pData = buff.bits( );
	int bytesPerLine = buff.bytesPerLine( );
	int imageWidth = buff.width( );
	int imageHeight = buff.height( );
	int bitY;
	int bitX;
	// pLine[0]=B
	int blueOffset;
	// pLine[1]=G
	int greenOffset;
	// pLine[2]=R
	int redOffset;
	// pLine[3]=A
	int alphaOffset;
	int offset;
	uchar *pLine;
	for( bitY = 0; bitY < imageHeight; bitY++ )
		for( bitX = 0, pLine = pData + bitY * bytesPerLine; bitX < imageWidth; bitX++ ) {
			offset = bitX * 4;
			blueOffset = offset + 0;
			greenOffset = offset + 1;
			redOffset = offset + 2;
			alphaOffset = offset + 3;
			if( pLine[ blueOffset ] == oldBlue && pLine[ greenOffset ] == oldGreen && pLine[ redOffset ] == oldRed && pLine[ alphaOffset ] == oldAlpha ) {
				pLine[ blueOffset ] = newBlue;
				pLine[ greenOffset ] = newGreen;
				pLine[ redOffset ] = newRed;
				pLine[ alphaOffset ] = newAlpha;
			}
		}
	result_image = buff;
	return true;
}
Application * Application::getApplicationInstance( ) {
	QCoreApplication *instance = QCoreApplication::instance( );
	if( instance == nullptr ) {
		MessageErrorOut( ) << tr( "无法从 QCoreApplication::instance( ) 获取实例指针" );
		return nullptr;
	}
	Application *application = qobject_cast< Application * >( instance );
	if( application )
		return application;
	MessageErrorOut( ) << tr( "无法从 QCoreApplication::instance( ) 转换到 Application * 类型" );
	return nullptr;
}
Application::Application( int &argc, char **const argv, const int i ) : QApplication( argc, argv, i ) {

	mainWindowPtr = nullptr;
	firstShow = false;
	appSetting = new QJsonObject;
	qDirTool = new QDir;
	fileInfoTool = new QFileInfo;
	translate = new Translate;
	QString currentPath = qDirTool->currentPath( );

	appStartRunTime = new QDateTime( );
	*appStartRunTime = QDateTime::currentDateTime( );

	QString prefix;

	appSettingPath = currentPath + "/program/setting/app.json";
	fileInfoTool->setFile( appSettingPath );
	if( fileInfoTool->exists( ) ) {
		QFile file( appSettingPath );
		if( file.open( QIODeviceBase::Text | QIODeviceBase::ReadOnly ) ) {
			auto byteArray = file.readAll( );
			QJsonParseError err;
			QJsonDocument doc = QJsonDocument::fromJson( byteArray, &err );
			if( err.error != QJsonParseError::NoError ) {
				MessageErrorOut( ) << translate->openFileError << " : " << appSettingPath << " : " << err.errorString( );
			} else {
				*appSetting = doc.object( );
				auto jsonValue = appSetting->find( jsonKey.app_QTranslator_path_key );
				if( jsonValue != appSetting->end( ) )
					prefix = jsonValue->toString( );
			}
		} else
			MessageErrorOut( ) << translate->openFileError << " : " << appSettingPath;

	} else {
		QDir dir = fileInfoTool->dir( );
		auto absolutePath = dir.absolutePath( );
		if( fileInfoTool->exists( absolutePath ) == false )
			if( dir.mkdir( absolutePath ) == false )
				MessageErrorOut( ) << translate->createDirError << " : " << absolutePath;
	}
	// 加载语言文件
	fileInfoTool->setFile( prefix );
	// 语言文件不存在，则使用自定义路径
	if( fileInfoTool->exists( ) == false ) {
		QLocale locale = QLocale::system( );
		auto localeName = locale.name( );
		prefix = currentPath + "/program/translations/" + applicationName( ) + "_" + localeName + ".qm";
		if( fileInfoTool->exists( prefix ) == false )
			prefix = currentPath + "/program/translations/" + applicationName( ) + ".qm";
	}
	qTranslator = new QTranslator;
	if( qTranslator->load( prefix ) == false ) {
		MessageErrorOut( ) << translate->loadQTranslatorFile << " : " << prefix;
		// 失败则删除语言文件路径
		appSetting->remove( jsonKey.app_QTranslator_path_key );
	} else if( installTranslator( qTranslator ) == false ) {
		MessageErrorOut( ) << translate->loadQTranslatorApp << " : " << prefix;
		// 失败则删除语言文件路径
		appSetting->remove( jsonKey.app_QTranslator_path_key );
	} else {
		// 刷新翻译
		*translate = Translate( );
		// 插入语言文件路径
		appSetting->insert( jsonKey.app_QTranslator_path_key, prefix );
	}

	QFont customFont = QFont( "Microsoft YaHei", 14 ); // 使用外部字体
	// 加载字体
	int fontId = QFontDatabase::addApplicationFont( "./program/font/Alibaba/Alibaba-PuHuiTi-Medium.ttf" );

	QStringList familyList;
	if( fontId != -1 ) {
		familyList = QFontDatabase::applicationFontFamilies( fontId );
		if( !familyList.isEmpty( ) ) {
			QString familyName = familyList.first( );
			customFont = QFont( familyName, 14 );
		}
	}
	render = new AppRenderObj( customFont, Qt::GlobalColor::black );
	applicationEvenTrigger = new ApplicationEvenTrigger( this );

	setMainWindowPtr( new MainWindow );
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
	delete render;
	delete applicationEvenTrigger;
	delete appSetting;
	delete qDirTool;
	delete fileInfoTool;
	delete appStartRunTime;
	delete translate;
	delete qTranslator;
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
				int valueX = mainWindowPtr->x( );
				int valueY = mainWindowPtr->y( );
				int valueW = mainWindowPtr->width( );
				int valueH = mainWindowPtr->height( );
				appSetting->insert( jsonKey.main_window_x_key, valueX );
				appSetting->insert( jsonKey.main_window_y_key, valueY );
				appSetting->insert( jsonKey.main_window_w_key, valueW );
				appSetting->insert( jsonKey.main_window_h_key, valueH );
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

	loadQTranslatorFile = QObject::tr( "打开语言文件失败" );
	loadQTranslatorApp = QObject::tr( "加载语言到软件失败" );

}
Application::JSonKey::JSonKey( ) {
	/* 配置文件 */
	app_QTranslator_path_key = "app.QTranslator.path";
	main_window_x_key = "app.MainWindow.x";
	main_window_y_key = "app.MainWindow.y";
	main_window_w_key = "app.MainWindow.w";
	main_window_h_key = "app.MainWindow.h";
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

	int containsKeyCount = 0;
	auto iterator = appSetting->begin( );
	auto end = appSetting->end( );
	for( ; iterator != end; ++iterator ) {
		objectName = iterator.key( );
		if( objectName == jsonKey.main_window_x_key ) {
			screenX = iterator.value( ).toInt( 0 );
			++containsKeyCount;
		} else if( objectName == jsonKey.main_window_y_key ) {
			screenY = iterator.value( ).toInt( 0 );
			++containsKeyCount;
		} else if( objectName == jsonKey.main_window_w_key ) {
			screenWidth = iterator.value( ).toInt( 200 );
			++containsKeyCount;
		} else if( objectName == jsonKey.main_window_h_key ) {
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
}
