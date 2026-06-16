#include "appTranslate.h"

#include <QObject>
#include <QTextCodec>
AppTranslate::AppTranslate( ) {
}
void AppTranslate::setCodecForLocale( ) {
	QTextCodec *utf8 = QTextCodec::codecForName( "UTF-8" );
	QTextCodec::setCodecForLocale( utf8 );
}
void AppTranslate::translateString( ) {
	sourceFile = QObject::tr( "源文件" );
	sourceFunction = QObject::tr( "源函数" );
	sourceLine = QObject::tr( "源行号" );
	createDirError = QObject::tr( "创建目录失败" );
	createFileError = QObject::tr( "创建文件失败" );
	openFileError = QObject::tr( "打开文件失败" );
	appWindowTitleName = QObject::tr( "仙缘村落" );
	playMusic = QObject::tr( "开始" );
	stopMusic = QObject::tr( "停止" );
	pauseMusic = QObject::tr( "暂停" );

	playListWidget = QObject::tr( "播放列表" );
	settingWidget = QObject::tr( "软件设置" );
	aboutWidget = QObject::tr( "关于" );
}
bool AppTranslate::init( ) {
	setCodecForLocale( );
	translateString( );
	return true;
}
