#include "appTranslate.h"

#include <QObject>
#include <QTextCodec>

const QString & AppTranslate::getControlPausa( ) const {
	return controlPausa;
}

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

	menuFileTitle = QObject::tr( "文件" );

	actionAddMultiMusicFileToCollection = QObject::tr( "添加文件列表到集" );
	actionAddMultiMusicDirToCollection = QObject::tr( "添加目录列表到集" );
	actionRemoveMultiMusicAtCollection = QObject::tr( "把文件列表从集中删除" );

	musicTypeName = QObject::tr( "音频" );

	musicIndex = QObject::tr( "#" );
	musicName = QObject::tr( "歌名" );
	musicSinger = QObject::tr( "歌手" );
	musicDuration = QObject::tr( "时长" );

	playerListMenuenuPlayerMenu = QObject::tr( "播放菜单" );
	playerListMenuPlayerMenuSetCurrentPlayAction = QObject::tr( "从选中开始播放" );
	playerListMenuPlayerMenuInsterCurrentPlayAction = QObject::tr( "插入选中并播放" );

	playerListMenuMoveMenu = QObject::tr( "删除菜单" );
	playerListMenuControlMenuRemoveMusicAction = QObject::tr( "从列表移除" );
	playerListMenuControlMenuDeleteMusicAction = QObject::tr( "从文件移除" );

	playerListMenuControlMenu = QObject::tr( "控制菜单" );
	playerListMenuControlMenuMoveTopMusicAction = QObject::tr( "选中列表移动到顶部" );
	playerListMenuControlMenuMoveBottomMusicAction = QObject::tr( "选中列表移动到底部" );

	thePreviousSong = QObject::tr( "上一曲" );
	controlPlay = QObject::tr( "播放" );
	controlPausa = QObject::tr( "暂停" );
	theNextSong = QObject::tr( "下一曲" );
	currentPlayList = QObject::tr( "当前播放列表" );
	playSongDateTimeSpace = QObject::tr( "/" );
}

bool AppTranslate::init( ) {
	setCodecForLocale( );
	translateString( );
	return true;
}

const QString & AppTranslate::getPlaySongDateTimeSpace( ) const {
	return playSongDateTimeSpace;
}

const QString & AppTranslate::getSourceFile( ) const {
	return sourceFile;
}

const QString & AppTranslate::getSourceFunction( ) const {
	return sourceFunction;
}

const QString & AppTranslate::getSourceLine( ) const {
	return sourceLine;
}

const QString & AppTranslate::getCreateDirError( ) const {
	return createDirError;
}

const QString & AppTranslate::getCreateFileError( ) const {
	return createFileError;
}

const QString & AppTranslate::getOpenFileError( ) const {
	return openFileError;
}

const QString & AppTranslate::getAppWindowTitleName( ) const {
	return appWindowTitleName;
}

const QString & AppTranslate::getPlay( ) const {
	return playMusic;
}

const QString & AppTranslate::getStop( ) const {
	return stopMusic;
}

const QString & AppTranslate::getPause( ) const {
	return pauseMusic;
}

const QString & AppTranslate::getPlayListWidget( ) const {
	return playListWidget;
}

const QString & AppTranslate::getSettingWidget( ) const {
	return settingWidget;
}

const QString & AppTranslate::getAboutWidget( ) const {
	return aboutWidget;
}

const QString & AppTranslate::getYear( ) const {
	return year;
}

const QString & AppTranslate::getMonth( ) const {
	return month;
}

const QString & AppTranslate::getDay( ) const {
	return day;
}

const QString & AppTranslate::getHour( ) const {
	return hour;
}

const QString & AppTranslate::getMinute( ) const {
	return minute;
}

const QString & AppTranslate::getSecond( ) const {
	return second;
}

const QString & AppTranslate::getMillsecond( ) const {
	return millsecond;
}

const QString & AppTranslate::getWriteFileError( ) const {
	return writeFileError;
}

const QString & AppTranslate::getReadFileError( ) const {
	return readFileError;
}

const QString & AppTranslate::getFileConverJsonDocError( ) const {
	return fileConverJsonDocError;
}

const QString & AppTranslate::getNotFindJsonKey( ) const {
	return notFindJsonKey;
}

const QString & AppTranslate::getActionAddMultiMusicFileToCollection( ) const {
	return actionAddMultiMusicFileToCollection;
}

const QString & AppTranslate::getActionAddMultiMusicDirToCollection( ) const {
	return actionAddMultiMusicDirToCollection;
}

const QString & AppTranslate::getActionRemoveMultiMusicAtCollection( ) const {
	return actionRemoveMultiMusicAtCollection;
}

const QString & AppTranslate::getMenuFileTitle( ) const {
	return menuFileTitle;
}

const QString & AppTranslate::getMusicTypeName( ) const {
	return musicTypeName;
}

const QString & AppTranslate::getMusicIndex( ) const {
	return musicIndex;
}

const QString & AppTranslate::getMusicName( ) const {
	return musicName;
}

const QString & AppTranslate::getMusicSinger( ) const {
	return musicSinger;
}

const QString & AppTranslate::getMusicDuration( ) const {
	return musicDuration;
}

const QString & AppTranslate::getPlayerListMenuenuPlayerMenu( ) const {
	return playerListMenuenuPlayerMenu;
}

const QString & AppTranslate::getPlayerListMenuPlayerMenuSetCurrentPlayAction( ) const {
	return playerListMenuPlayerMenuSetCurrentPlayAction;
}

const QString & AppTranslate::getPlayerListMenuPlayerMenuInsterCurrentPlayAction( ) const {
	return playerListMenuPlayerMenuInsterCurrentPlayAction;
}

const QString & AppTranslate::getPlayerListMenuControlMenu( ) const {
	return playerListMenuControlMenu;
}

const QString & AppTranslate::getPlayerListMenuControlMenuRemoveMusicAction( ) const {
	return playerListMenuControlMenuRemoveMusicAction;
}

const QString & AppTranslate::getPlayerListMenuControlMenuMoveTopMusicAction( ) const {
	return playerListMenuControlMenuMoveTopMusicAction;
}

const QString & AppTranslate::getPlayerListMenuControlMenuMoveBottomMusicAction( ) const {
	return playerListMenuControlMenuMoveBottomMusicAction;
}

const QString & AppTranslate::getPlayerListMenuMoveMenu( ) const {
	return playerListMenuMoveMenu;
}

const QString & AppTranslate::getPlayerListMenuControlMenuDeleteMusicAction( ) const {
	return playerListMenuControlMenuDeleteMusicAction;
}

const QString & AppTranslate::getThePreviousSong( ) const {
	return thePreviousSong;
}

const QString & AppTranslate::getControlPlay( ) const {
	return controlPlay;
}

const QString & AppTranslate::getTheNextSong( ) const {
	return theNextSong;
}

const QString & AppTranslate::getCurrentPlayList( ) const {
	return currentPlayList;
}
