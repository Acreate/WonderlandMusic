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
	readFileError = QObject::tr( "读取文件失败" );
	writeFileError = QObject::tr( "写入文件失败" );

	appWindowTitleName = QObject::tr( "仙缘村落" );

	playMusic = QObject::tr( "开始" );
	stopMusic = QObject::tr( "停止" );
	pauseMusic = QObject::tr( "暂停" );

	playListWidget = QObject::tr( "播放列表" );
	settingWidget = QObject::tr( "软件设置" );
	aboutWidget = QObject::tr( "关于" );

	year = QObject::tr( "年" );
	month = QObject::tr( "月" );
	day = QObject::tr( "日" );
	hour = QObject::tr( "时" );
	minute = QObject::tr( "分" );
	second = QObject::tr( "秒" );
	millsecond = QObject::tr( "毫秒" );

	fileConverJsonDocError = QObject::tr( "文件转 QJsonDocument 对象错误" );
	notFindJsonKey = QObject::tr( "找不到匹配的关键字" );
}
bool AppTranslate::init( ) {
	setCodecForLocale( );
	translateString( );
	return true;
}
