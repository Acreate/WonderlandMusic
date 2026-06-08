#include "applicationInstance.h"
#include <QScreen>
#include <QCursor>
#include <QDir>
#include <QFileInfo>
#include <QFontDatabase>
#include <QJsonObject>
#include <QPainter>
#include <QFileDialog>
#include <QTranslator>

#include "applicationEvenTrigger.h"

#include "../mainWindows/mainWindow.h"
#include "../mainWindows/contentWindows/coreWindow/coreStackedWidget/coreWidget/musicListWindowWidgets/musicListMainWidget.h"
#include "../mainWindows/contentWindows/coreWindow/coreStackedWidget/coreWidget/musicListWindowWidgets/widget/musicCollectionWidget.h"
#include "../mainWindows/contentWindows/coreWindow/coreStackedWidget/coreWidget/musicListWindowWidgets/widget/collectionItemWidget/collectionTopToolWidget.h"
#include "../mainWindows/contentWindows/coreWindow/coreStackedWidget/coreWidget/settingWindowWidgets/optionWidget/pathSettingWidget.h"

#include "../menus/musicCollectionSubMenu.h"
#include "../menus/musicCollectionTopMenu.h"
#include "../menus/musicListSubMenu.h"
#include "../menus/musicListTopMenu.h"

#include "../msgInfo/messageErrorOut.h"

#include "private/appRenderObj.h"

ApplicationInstance *ApplicationInstance::current = nullptr;
ApplicationInstance * ApplicationInstance::getApplicationInstance( ) {
	if( current )
		return current;
	QCoreApplication *instance = QApplication::instance( );
	if( instance == nullptr ) {
		MessageErrorOut( false ) << tr( "无法从 QCoreApplicationInstance::instance( ) 获取实例指针" );
		return nullptr;
	}
	current = qobject_cast< ApplicationInstance * >( instance );
	if( current )
		return current;
	MessageErrorOut( false ) << tr( "无法从 QCoreApplicationInstance::instance( ) 转换到 Application * 类型" );
	return nullptr;
}
void ApplicationInstance::initVar( ) {
	mainWindowPtr = nullptr;
	firstShow = false;
	appSetting = new QJsonObject;
	qDirTool = new QDir;
	fileInfoTool = new QFileInfo;
	translate = new Translate;
	appStartRunTime = new QDateTime( );
	*appStartRunTime = QDateTime::currentDateTime( );
}
void ApplicationInstance::initJson( ) {
	appSettingPath = qDirTool->currentPath( ) + "/program/setting/" + applicationName( ) + ".app.json";
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
void ApplicationInstance::initTranslation( ) {
	QString translationFilePath;
	auto jsonValue = appSetting->find( jsonKey.app_QTranslator_path_key );
	if( jsonValue != appSetting->end( ) )
		translationFilePath = jsonValue->toString( );
	// 加载语言文件
	fileInfoTool->setFile( translationFilePath );
	// 语言文件不存在，则使用自定义路径
	if( fileInfoTool->exists( ) == false ) {
		QLocale locale = QLocale::system( );
		auto localeName = locale.name( );
		QString currentPath = qDirTool->currentPath( );
		translationFilePath = currentPath + "/program/translations/" + applicationName( ) + "_" + localeName + ".qm";
		if( fileInfoTool->exists( translationFilePath ) == false )
			translationFilePath = currentPath + "/program/translations/" + applicationName( ) + ".qm";
	}
	qTranslator = new QTranslator;
	if( qTranslator->load( translationFilePath ) == false ) {
		MessageErrorOut( ) << translate->loadQTranslatorFile << " : " << translationFilePath;
		// 失败则删除语言文件路径
		appSetting->remove( jsonKey.app_QTranslator_path_key );
	} else if( installTranslator( qTranslator ) == false ) {
		MessageErrorOut( ) << translate->loadQTranslatorApp << " : " << translationFilePath;
		// 失败则删除语言文件路径
		appSetting->remove( jsonKey.app_QTranslator_path_key );
	} else {
		// 刷新翻译
		*translate = Translate( );
		// 插入语言文件路径
		appSetting->insert( jsonKey.app_QTranslator_path_key, translationFilePath );
	}
}
void ApplicationInstance::initRender( ) {
	// 配置默认字体
	QFont customFont = QFont( "Microsoft YaHei", 14 );
	// 使用外部字体，加载字体
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
}
void ApplicationInstance::initApplicationEvenTrigger( ) {
	applicationEvenTrigger = new ApplicationEvenTrigger( this );
}
void ApplicationInstance::initMainWindow( ) {
	auto main = new MainWindow;
	setMainWindowPtr( main );
	musicCollectionTopMenu = new MusicCollectionTopMenu;
	musicCollectionSubMenu = new MusicCollectionSubMenu;
	musicListTopMenu = new MusicListTopMenu;
	musicListSubMenu = new MusicListSubMenu;
}
void ApplicationInstance::initTriggerEvent( ) {
	connect( applicationEvenTrigger, &ApplicationEvenTrigger::triggerPathSettingWidgetEvent, [this] ( PathSettingWidget *sender_ptr, const PathSettingWidgetEventInfo &info ) {
		auto eventType = info.getEventType( );
		switch( eventType ) {
			case PathSettingWidgetEventInfo::EventType::None :
				break;
			case PathSettingWidgetEventInfo::EventType::Update_Music_info_File_Path_Info : {
				auto loadFileInfoPath = sender_ptr->getLoadFileInfoPath( );
				appSetting->insert( jsonKey.app_music_info_file_path, loadFileInfoPath );
				saveJsonDataToAppSettingFile( );
				// todo : 然后移动文件
			}
			break;
		}
	} );

	connect( applicationEvenTrigger, &ApplicationEvenTrigger::triggerMusicListMainWidgetEvent, [this] ( auto, const MusicListMainWidgetEventInfo &info ) {
		auto eventType = info.getEventType( );
		switch( eventType ) {
			case MusicListMainWidgetEventInfo::EventType::Over_Draw_Music_Widget_Width :
				appSetting->insert( jsonKey.app_music_collection_main_widget_width, info.getNewMusicWidgetWidth( ) );
				break;
		}
	} );

	connect( applicationEvenTrigger, &ApplicationEvenTrigger::triggerMusicCollectionTopMenuEvent, [this] ( MusicCollectionTopMenu *sender, const MusicCollectionTopMenuEventInfo &info ) {
		auto eventType = info.getEventType( );
		switch( eventType ) {
			case MusicCollectionTopMenuEventInfo::EventType::Append_Collection_Item :
				info.getMusicCollectionWidget( )->appendItemWidget( "新的" );
				break;
			case MusicCollectionTopMenuEventInfo::EventType::Append_Muisc_File_Path : {
				QFileDialog dlg;
				dlg.setWindowTitle( "选择音频文件" );
				dlg.setDirectory( "." );
				dlg.setNameFilter( "音频文件 (*.mp3 *.wma *.m4a *.ogg *.aac *.flac)" );
				dlg.exec( );
				QStringList filePaths = dlg.selectedFiles( );
				MessageErrorOut( ) << tr( "选中文件" ) << ":\n\t" << filePaths.join( "\n\t" );
			}
			break;
			case MusicCollectionTopMenuEventInfo::EventType::Append_Muisc_Dir_Path : {
				QFileDialog dlg;
				dlg.setWindowTitle( "选择音频目录" );
				dlg.setDirectory( "." );
				dlg.setFileMode( QFileDialog::Directory );
				dlg.setOption( QFileDialog::ShowDirsOnly );
				dlg.exec( );
				QStringList filePaths = dlg.selectedFiles( );
				MessageErrorOut( ) << tr( "选中目录" ) << ":\n\t" << filePaths.join( "\n\t" );
			}
			break;
		}

	} );

	connect( applicationEvenTrigger, &ApplicationEvenTrigger::triggerMusicListMainWidgetEvent, [this] ( MusicListMainWidget *sender, const MusicListMainWidgetEventInfo &info ) {
		auto eventType = info.getEventType( );
		switch( eventType ) {

			case MusicListMainWidgetEventInfo::EventType::None :
				break;
			case MusicListMainWidgetEventInfo::EventType::Show_Draw_Mouse_ICO :
				sender->setCursor( Qt::CursorShape::SizeHorCursor );
				break;
			case MusicListMainWidgetEventInfo::EventType::HIDE_Draw_Mouse_ICO :
				sender->setCursor( Qt::CursorShape::ArrowCursor );
				break;
			case MusicListMainWidgetEventInfo::EventType::Start_Draw_Music_Widget_Width :
				break;
			case MusicListMainWidgetEventInfo::EventType::Over_Draw_Music_Widget_Width :
				break;

		}

	} );

	connect( applicationEvenTrigger, &ApplicationEvenTrigger::triggerMusicCollectionWidgetEvent, [this] ( MusicCollectionWidget *sender, const MusicCollectionWidgetEventInfo &info ) {
		auto eventType = info.getEventType( );
		switch( eventType ) {
			case MusicCollectionWidgetEventInfo::EventType::Mouse_Right_Release_Select_Top_Item :
				ApplicationInstanceEvent::triggerApplicationInstanceEvent( applicationEvenTrigger, this, ApplicationInstanceEventInfo( ApplicationInstanceEventInfo::EventType::Pop_Music_Collection_Top_Menu, sender ) );
				break;

			case MusicCollectionWidgetEventInfo::EventType::Mouse_Right_Release_Select_Sub_Item : ApplicationInstanceEvent::triggerApplicationInstanceEvent( applicationEvenTrigger, this, ApplicationInstanceEventInfo( ApplicationInstanceEventInfo::EventType::Pop_Music_Collection_Sub_Menu, sender ) );
				break;
		}

	} );

}
void ApplicationInstance::sendAppEvent( ) {
	auto jsonEnd = this->appSetting->end( );
	auto findResult = this->appSetting->find( jsonKey.app_music_info_file_path );
	// 找到存储的路径
	if( findResult != jsonEnd ) {
		auto string = findResult.value( ).toString( );
		ApplicationInstanceEvent::triggerApplicationInstanceEvent( applicationEvenTrigger, this, ApplicationInstanceEventInfo( ApplicationInstanceEventInfo::EventType::Load_Music_Info_Path_Text, string ) );
	}
	findResult = this->appSetting->find( jsonKey.app_music_collection_main_widget_width );
	// 找到收藏列表的宽度
	if( findResult != jsonEnd ) {
		auto widgetWidth = findResult.value( ).toInt( );
		ApplicationInstanceEvent::triggerApplicationInstanceEvent( applicationEvenTrigger, this, ApplicationInstanceEventInfo( ApplicationInstanceEventInfo::EventType::Init_Music_Widget_Width, widgetWidth ) );
	}
}
ApplicationInstance::ApplicationInstance( int &argc, char **const argv, const int i ) : applicationEvenTrigger( nullptr ), BseeApplication( argc, argv, i ) {
	initVar( );
	initApplicationEvenTrigger( );
	initJson( );
	initTranslation( );
	initRender( );
	initTriggerEvent( );
	initMainWindow( );
	sendAppEvent( );
}
void ApplicationInstance::saveJsonDataToAppSettingFile( ) const {
	fileInfoTool->setFile( appSettingPath );
	if( fileInfoTool->exists( ) == false ) {
		QDir dir = fileInfoTool->dir( );
		if( dir.exists( ) == false ) {
			auto absolutePath = dir.absolutePath( );
			if( dir.mkdir( absolutePath ) == false ) {
				MessageErrorOut( ) << translate->createDirError << " : " << absolutePath;
				return;
			}
		}
	}
	QFile file( appSettingPath );
	if( file.open( QIODeviceBase::ReadWrite | QIODeviceBase::Text | QIODeviceBase::Truncate ) ) {
		QJsonDocument doc( *appSetting );
		QString jsonStr = doc.toJson( QJsonDocument::Indented ); //格式化字符串
		auto byteArray = jsonStr.toUtf8( );
		file.write( byteArray );
		file.close( );
	}
}
ApplicationInstance::~ApplicationInstance( ) {

	saveJsonDataToAppSettingFile( );
	if( mainWindowPtr )
		delete mainWindowPtr;
	delete musicCollectionTopMenu;
	delete musicCollectionSubMenu;
	delete musicListTopMenu;
	delete musicListSubMenu;
	delete render;
	delete applicationEvenTrigger;
	delete appSetting;
	delete qDirTool;
	delete fileInfoTool;
	delete appStartRunTime;
	delete translate;
	delete qTranslator;
	current = nullptr;
}
bool ApplicationInstance::notify( QObject *object, QEvent *event ) {
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
				quit( );
			}
			break;
		case QEvent::Quit :
			break;
		case QEvent::Type::MouseMove :
			ApplicationInstanceEvent::triggerApplicationInstanceEvent( applicationEvenTrigger, this, ApplicationInstanceEventInfo( ApplicationInstanceEventInfo::EventType::Move_Global_Mouse_Pos ) );
			break;
		case QEvent::Type::MouseButtonPress :
			ApplicationInstanceEvent::triggerApplicationInstanceEvent( applicationEvenTrigger, this, ApplicationInstanceEventInfo( ApplicationInstanceEventInfo::EventType::Press_Global_Mouse_Pos ) );
			break;
		case QEvent::Type::MouseButtonRelease :
			ApplicationInstanceEvent::triggerApplicationInstanceEvent( applicationEvenTrigger, this, ApplicationInstanceEventInfo( ApplicationInstanceEventInfo::EventType::Release_Global_Mouse_Pos ) );
			break;
	}
	return QApplication::notify( object, event );
}
bool ApplicationInstance::event( QEvent *event ) {
	return QApplication::event( event );
}
ApplicationInstance::Translate::Translate( ) {
	createDirError = QObject::tr( "创建目录失败" );
	openFileError = QObject::tr( "打开文件失败" );

	loadQTranslatorFile = QObject::tr( "打开语言文件失败" );
	loadQTranslatorApp = QObject::tr( "加载语言到软件失败" );

}
ApplicationInstance::JSonKey::JSonKey( ) {
	/* 配置文件 */
	app_QTranslator_path_key = "app.QTranslator.path";
	main_window_x_key = "app.MainWindow.x";
	main_window_y_key = "app.MainWindow.y";
	main_window_w_key = "app.MainWindow.w";
	main_window_h_key = "app.MainWindow.h";
	app_music_info_file_path = "app.setting.music.info.file.path";
	app_music_collection_main_widget_width = "app.setting.music.widget.collection.width";
}
void ApplicationInstance::setMainWindowPtr( MainWindow *main_window_ptr ) {
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
void ApplicationInstance::firstMainWindowShow( MainWindow *first_show_main_window ) {

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
