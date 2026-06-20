#include "appTranslate.h"

#include <QObject>
#include <QTextCodec>

AppTranslate::AppTranslate( ) {
}

bool MessageTranslate::init( ) {
	sourceFile = QObject::tr( "源文件" );
	sourceFunction = QObject::tr( "源函数" );
	sourceLine = QObject::tr( "源行号" );
	createDirError = QObject::tr( "创建目录失败" );
	createFileError = QObject::tr( "创建文件失败" );

	openFileError = QObject::tr( "打开文件失败" );
	readFileError = QObject::tr( "读取文件失败" );
	writeFileError = QObject::tr( "写入文件失败" );
	return true;
}

const QString & MessageTranslate::getSourceFile( ) const {
	return sourceFile;
}

const QString & MessageTranslate::getSourceFunction( ) const {
	return sourceFunction;
}

const QString & MessageTranslate::getSourceLine( ) const {
	return sourceLine;
}

const QString & MessageTranslate::getCreateDirError( ) const {
	return createDirError;
}

const QString & MessageTranslate::getCreateFileError( ) const {
	return createFileError;
}

const QString & MessageTranslate::getOpenFileError( ) const {
	return openFileError;
}

const QString & MessageTranslate::getWriteFileError( ) const {
	return writeFileError;
}

const QString & MessageTranslate::getReadFileError( ) const {
	return readFileError;
}

bool MainWindowTranslate::init( ) {
	appWindowTitleName = QObject::tr( "仙缘村落" );
	musicTypeName = QObject::tr( "音频" );
	settingWidget = QObject::tr( "软件设置" );
	aboutWidget = QObject::tr( "关于" );
	return true;
}

const QString & MainWindowTranslate::getAppWindowTitleName( ) const {
	return appWindowTitleName;
}

const QString & MainWindowTranslate::getSettingWidget( ) const {
	return settingWidget;
}

const QString & MainWindowTranslate::getAboutWidget( ) const {
	return aboutWidget;
}

const QString & MainWindowTranslate::getMusicTypeName( ) const {
	return musicTypeName;
}

bool PlayerWidgetTranslate::init( ) {
	playMusic = QObject::tr( "开始" );
	stopMusic = QObject::tr( "停止" );
	pauseMusic = QObject::tr( "暂停" );
	playListWidget = QObject::tr( "播放列表" );

	return true;
}

const QString & PlayerWidgetTranslate::getPlayMusic( ) const {
	return playMusic;
}

const QString & PlayerWidgetTranslate::getStopMusic( ) const {
	return stopMusic;
}

const QString & PlayerWidgetTranslate::getPauseMusic( ) const {
	return pauseMusic;
}

const QString & PlayerWidgetTranslate::getPlayListWidget( ) const {
	return playListWidget;
}

bool SettingWidgetTranslate::init( ) {
	return true;
}

bool AboutWidgetTranslate::init( ) {
	return true;
}

bool DateTimeFormatTranslate::init( ) {
	year = QObject::tr( "年" );
	month = QObject::tr( "月" );
	day = QObject::tr( "日" );
	hour = QObject::tr( "时" );
	minute = QObject::tr( "分" );
	second = QObject::tr( "秒" );
	millsecond = QObject::tr( "毫秒" );

	return true;
}

const QString & DateTimeFormatTranslate::getYear( ) const {
	return year;
}

const QString & DateTimeFormatTranslate::getMonth( ) const {
	return month;
}

const QString & DateTimeFormatTranslate::getDay( ) const {
	return day;
}

const QString & DateTimeFormatTranslate::getHour( ) const {
	return hour;
}

const QString & DateTimeFormatTranslate::getMinute( ) const {
	return minute;
}

const QString & DateTimeFormatTranslate::getSecond( ) const {
	return second;
}

const QString & DateTimeFormatTranslate::getMillsecond( ) const {
	return millsecond;
}

bool JsonTranslate::init( ) {
	fileConverJsonDocError = QObject::tr( "文件转 QJsonDocument 对象错误" );
	notFindJsonKey = QObject::tr( "找不到匹配的关键字" );

	return true;
}

const QString & JsonTranslate::getFileConverJsonDocError( ) const {
	return fileConverJsonDocError;
}

const QString & JsonTranslate::getNotFindJsonKey( ) const {
	return notFindJsonKey;
}

bool PlayerWindowTranslate::init( ) {
	return true;
}

bool PlayerTopWidgetTranslate::init( ) {
	musicIndex = QObject::tr( "#" );
	musicName = QObject::tr( "歌名" );
	musicSinger = QObject::tr( "歌手" );
	musicDuration = QObject::tr( "时长" );
	return true;
}

const QString & PlayerTopWidgetTranslate::getMusicIndex( ) const {
	return musicIndex;
}

const QString & PlayerTopWidgetTranslate::getMusicName( ) const {
	return musicName;
}

const QString & PlayerTopWidgetTranslate::getMusicSinger( ) const {
	return musicSinger;
}

const QString & PlayerTopWidgetTranslate::getMusicDuration( ) const {
	return musicDuration;
}

bool PlayerListMenuTranslate::init( ) {
	playerListMenuFileLoadMenu = QObject::tr( "加载菜单" );
	playerListAddMultiMusicFileToCollectionAction = QObject::tr( "添加文件到列表" );
	playerListAddMultiMusicDirToCollectionAction = QObject::tr( "添加目录到列表" );

	playerListMenuenuPlayerMenu = QObject::tr( "播放菜单" );
	playerListMenuPlayerMenuSetCurrentPlayAction = QObject::tr( "从选中开始播放" );
	playerListMenuPlayerMenuInsterCurrentPlayAction = QObject::tr( "插入选中并播放" );

	playerListMenuMoveMenu = QObject::tr( "删除菜单" );
	playerListMenuControlMenuRemoveMusicAction = QObject::tr( "从列表移除" );
	playerListMenuControlMenuDeleteMusicAction = QObject::tr( "从文件移除" );

	playerListMenuControlMenu = QObject::tr( "控制菜单" );
	playerListMenuControlMenuMoveTopMusicAction = QObject::tr( "选中列表移动到顶部" );
	playerListMenuControlMenuMoveBottomMusicAction = QObject::tr( "选中列表移动到底部" );
	musicTypeName = QObject::tr( "音频" );
	return true;
}

const QString & PlayerListMenuTranslate::getPlayerListMenuFileLoadMenu( ) const {
	return playerListMenuFileLoadMenu;
}

const QString & PlayerListMenuTranslate::getPlayerListAddMultiMusicFileToCollectionAction( ) const {
	return playerListAddMultiMusicFileToCollectionAction;
}

const QString & PlayerListMenuTranslate::getPlayerListAddMultiMusicDirToCollectionAction( ) const {
	return playerListAddMultiMusicDirToCollectionAction;
}

const QString & PlayerListMenuTranslate::getPlayerListMenuenuPlayerMenu( ) const {
	return playerListMenuenuPlayerMenu;
}

const QString & PlayerListMenuTranslate::getPlayerListMenuPlayerMenuSetCurrentPlayAction( ) const {
	return playerListMenuPlayerMenuSetCurrentPlayAction;
}

const QString & PlayerListMenuTranslate::getPlayerListMenuPlayerMenuInsterCurrentPlayAction( ) const {
	return playerListMenuPlayerMenuInsterCurrentPlayAction;
}

const QString & PlayerListMenuTranslate::getPlayerListMenuControlMenu( ) const {
	return playerListMenuControlMenu;
}

const QString & PlayerListMenuTranslate::getPlayerListMenuControlMenuRemoveMusicAction( ) const {
	return playerListMenuControlMenuRemoveMusicAction;
}

const QString & PlayerListMenuTranslate::getPlayerListMenuControlMenuDeleteMusicAction( ) const {
	return playerListMenuControlMenuDeleteMusicAction;
}

const QString & PlayerListMenuTranslate::getPlayerListMenuMoveMenu( ) const {
	return playerListMenuMoveMenu;
}

const QString & PlayerListMenuTranslate::getPlayerListMenuControlMenuMoveTopMusicAction( ) const {
	return playerListMenuControlMenuMoveTopMusicAction;
}

const QString & PlayerListMenuTranslate::getPlayerListMenuControlMenuMoveBottomMusicAction( ) const {
	return playerListMenuControlMenuMoveBottomMusicAction;
}

const QString & PlayerListMenuTranslate::getMusicTypeName( ) const {
	return musicTypeName;
}

bool PlayerToolsWidgetTranslate::init( ) {
	thePreviousSong = QObject::tr( "上一曲" );
	controlPlay = QObject::tr( "播放" );
	controlPausa = QObject::tr( "暂停" );
	theNextSong = QObject::tr( "下一曲" );
	currentPlayList = QObject::tr( "当前播放列表" );
	playSongDateTimeSpace = QObject::tr( "/" );
	return true;
}

const QString & PlayerToolsWidgetTranslate::getThePreviousSong( ) const {
	return thePreviousSong;
}

const QString & PlayerToolsWidgetTranslate::getControlPlay( ) const {
	return controlPlay;
}

const QString & PlayerToolsWidgetTranslate::getControlPausa( ) const {
	return controlPausa;
}

const QString & PlayerToolsWidgetTranslate::getTheNextSong( ) const {
	return theNextSong;
}

const QString & PlayerToolsWidgetTranslate::getCurrentPlayList( ) const {
	return currentPlayList;
}

const QString & PlayerToolsWidgetTranslate::getPlaySongDateTimeSpace( ) const {
	return playSongDateTimeSpace;
}

void AppTranslate::setCodecForLocale( ) {
	QTextCodec *utf8 = QTextCodec::codecForName( "UTF-8" );
	QTextCodec::setCodecForLocale( utf8 );
}

bool AppTranslate::translateString( ) {
	#define if_init_result( obj ) if(obj->init() == false) return false;
	if_init_result( settingWidget );
	if_init_result( playerToolsWidget );
	if_init_result( playerListMenu );
	if_init_result( playerTopWidget );
	if_init_result( playerWindow );
	if_init_result( json );
	if_init_result( dateTimeFormat );
	if_init_result( aboutWidget );
	if_init_result( playerWidget );
	if_init_result( mainWindow );
	if_init_result( message );

	return true;
}

void AppTranslate::deleteResource( ) {
	#define d_r( ptr ) if(ptr) {delete ptr; ptr = nullptr;}
	d_r( settingWidget );
	d_r( playerToolsWidget );
	d_r( playerListMenu );
	d_r( playerTopWidget );
	d_r( playerWindow );
	d_r( json );
	d_r( dateTimeFormat );
	d_r( aboutWidget );
	d_r( playerWidget );
	d_r( mainWindow );
	d_r( message );
}

AppTranslate::~AppTranslate( ) {
	deleteResource( );
}

bool AppTranslate::init( ) {
	deleteResource( );

	settingWidget = new SettingWidgetTranslate;
	playerToolsWidget = new PlayerToolsWidgetTranslate;
	playerListMenu = new PlayerListMenuTranslate;
	playerTopWidget = new PlayerTopWidgetTranslate;
	playerWindow = new PlayerWindowTranslate;
	json = new JsonTranslate;
	dateTimeFormat = new DateTimeFormatTranslate;
	aboutWidget = new AboutWidgetTranslate;
	playerWidget = new PlayerWidgetTranslate;
	mainWindow = new MainWindowTranslate;
	message = new MessageTranslate;

	setCodecForLocale( );
	if( translateString( ) == false )
		return false;
	return true;
}

SettingWidgetTranslate * AppTranslate::getSettingWidget( ) const {
	return settingWidget;
}

PlayerToolsWidgetTranslate * AppTranslate::getPlayerToolsWidget( ) const {
	return playerToolsWidget;
}

PlayerListMenuTranslate * AppTranslate::getPlayerListMenu( ) const {
	return playerListMenu;
}

PlayerTopWidgetTranslate * AppTranslate::getPlayerTopWidget( ) const {
	return playerTopWidget;
}

PlayerWindowTranslate * AppTranslate::getPlayerWindow( ) const {
	return playerWindow;
}

JsonTranslate * AppTranslate::getJson( ) const {
	return json;
}

DateTimeFormatTranslate * AppTranslate::getDateTimeFormat( ) const {
	return dateTimeFormat;
}

AboutWidgetTranslate * AppTranslate::getAboutWidget( ) const {
	return aboutWidget;
}

PlayerWidgetTranslate * AppTranslate::getPlayerWidget( ) const {
	return playerWidget;
}

MainWindowTranslate * AppTranslate::getMainWindow( ) const {
	return mainWindow;
}

MessageTranslate * AppTranslate::getMessage( ) const {
	return message;
}
