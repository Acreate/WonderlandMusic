#ifndef APPTRANSLATE_H_H_HEAD__FILE__
#define APPTRANSLATE_H_H_HEAD__FILE__
#include <qstring.h>

class ITranslate {
public:
	ITranslate( ) {
	}

	virtual ~ITranslate( ) {
	}

	virtual bool init( ) = 0;
};

class MessageTranslate : public ITranslate {
	QString sourceFile;
	QString sourceFunction;
	QString sourceLine;

	QString createDirError;
	QString createFileError;

	QString openFileError;
	QString writeFileError;
	QString readFileError;

public:
	bool init( ) override;

	virtual const QString & getSourceFile( ) const;

	virtual const QString & getSourceFunction( ) const;

	virtual const QString & getSourceLine( ) const;

	virtual const QString & getCreateDirError( ) const;

	virtual const QString & getCreateFileError( ) const;

	virtual const QString & getOpenFileError( ) const;

	virtual const QString & getWriteFileError( ) const;

	virtual const QString & getReadFileError( ) const;
};

class MainWindowTranslate : public ITranslate {
	QString appWindowTitleName;

	QString settingWidget;

	QString aboutWidget;
	QString musicTypeName;

public:
	bool init( ) override;

	virtual const QString & getAppWindowTitleName( ) const;

	virtual const QString & getSettingWidget( ) const;

	virtual const QString & getAboutWidget( ) const;

	virtual const QString & getMusicTypeName( ) const;
};

class PlayerWidgetTranslate : public ITranslate {
	QString playMusic;
	QString stopMusic;
	QString pauseMusic;
	QString playListWidget;

public:
	bool init( ) override;

	virtual const QString & getPlayMusic( ) const;

	virtual const QString & getStopMusic( ) const;

	virtual const QString & getPauseMusic( ) const;

	virtual const QString & getPlayListWidget( ) const;
};

class SettingWidgetTranslate : public ITranslate {
public:
	bool init( ) override;
};

class AboutWidgetTranslate : public ITranslate {
public:
	bool init( ) override;
};

class DateTimeFormatTranslate : public ITranslate {
	/// @brief 年
	QString year;
	/// @brief 月
	QString month;
	/// @brief 日
	QString day;
	/// @brief 小时
	QString hour;
	/// @brief 分钟
	QString minute;
	/// @brief 秒
	QString second;
	/// @brief 毫秒
	QString millsecond;

public:
	bool init( ) override;

	virtual const QString & getYear( ) const;

	virtual const QString & getMonth( ) const;

	virtual const QString & getDay( ) const;

	virtual const QString & getHour( ) const;

	virtual const QString & getMinute( ) const;

	virtual const QString & getSecond( ) const;

	virtual const QString & getMillsecond( ) const;
};

class JsonTranslate : public ITranslate {
	QString fileConverJsonDocError;
	QString notFindJsonKey;

public:
	bool init( ) override;

	virtual const QString & getFileConverJsonDocError( ) const;

	virtual const QString & getNotFindJsonKey( ) const;
};

class PlayerWindowTranslate : public ITranslate {
public:
	bool init( ) override;
};

class PlayerTopWidgetTranslate : public ITranslate {
	QString musicIndex;
	QString musicName;
	QString musicSinger;
	QString musicDuration;

public:
	bool init( ) override;

	virtual const QString & getMusicIndex( ) const;

	virtual const QString & getMusicName( ) const;

	virtual const QString & getMusicSinger( ) const;

	virtual const QString & getMusicDuration( ) const;
};

class PlayerListMenuTranslate : public ITranslate {
	QString playerListMenuFileLoadMenu;
	QString playerListAddMultiMusicFileToCollectionAction;
	QString playerListAddMultiMusicDirToCollectionAction;
	QString playerListMenuenuPlayerMenu;
	QString playerListMenuPlayerMenuSetCurrentPlayAction;
	QString playerListMenuPlayerMenuInsterCurrentPlayAction;
	QString playerListMenuControlMenu;
	QString playerListMenuControlMenuRemoveMusicAction;
	QString playerListMenuControlMenuDeleteMusicAction;
	QString playerListMenuMoveMenu;
	QString playerListMenuControlMenuMoveTopMusicAction;
	QString playerListMenuControlMenuMoveBottomMusicAction;

	QString musicTypeName;

public:
	bool init( ) override;

	virtual const QString & getPlayerListMenuFileLoadMenu( ) const;

	virtual const QString & getPlayerListAddMultiMusicFileToCollectionAction( ) const;

	virtual const QString & getPlayerListAddMultiMusicDirToCollectionAction( ) const;

	virtual const QString & getPlayerListMenuenuPlayerMenu( ) const;

	virtual const QString & getPlayerListMenuPlayerMenuSetCurrentPlayAction( ) const;

	virtual const QString & getPlayerListMenuPlayerMenuInsterCurrentPlayAction( ) const;

	virtual const QString & getPlayerListMenuControlMenu( ) const;

	virtual const QString & getPlayerListMenuControlMenuRemoveMusicAction( ) const;

	virtual const QString & getPlayerListMenuControlMenuDeleteMusicAction( ) const;

	virtual const QString & getPlayerListMenuMoveMenu( ) const;

	virtual const QString & getPlayerListMenuControlMenuMoveTopMusicAction( ) const;

	virtual const QString & getPlayerListMenuControlMenuMoveBottomMusicAction( ) const;

	virtual const QString & getMusicTypeName( ) const;
};

class PlayerToolsWidgetTranslate : public ITranslate {
	/// @brief 上一曲
	QString thePreviousSong;
	/// @brief 播放控制
	QString controlPlay;
	/// @brief 暂停播放
	QString controlPausa;
	/// @brief 下一曲
	QString theNextSong;
	/// @brief 当前播放列表
	QString currentPlayList;
	/// @brief 播放时间分隔
	QString playSongDateTimeSpace;

public:
	bool init( ) override;

	virtual const QString & getThePreviousSong( ) const;

	virtual const QString & getControlPlay( ) const;

	virtual const QString & getControlPausa( ) const;

	virtual const QString & getTheNextSong( ) const;

	virtual const QString & getCurrentPlayList( ) const;

	virtual const QString & getPlaySongDateTimeSpace( ) const;
};

class AppTranslate {
protected:
	SettingWidgetTranslate *settingWidget = nullptr;
	PlayerToolsWidgetTranslate *playerToolsWidget = nullptr;
	PlayerListMenuTranslate *playerListMenu = nullptr;
	PlayerTopWidgetTranslate *playerTopWidget = nullptr;
	PlayerWindowTranslate *playerWindow = nullptr;
	JsonTranslate *json = nullptr;
	DateTimeFormatTranslate *dateTimeFormat = nullptr;
	AboutWidgetTranslate *aboutWidget = nullptr;
	PlayerWidgetTranslate *playerWidget = nullptr;
	MainWindowTranslate *mainWindow = nullptr;
	MessageTranslate *message = nullptr;

protected:
	virtual void setCodecForLocale( );

	virtual bool translateString( );

	virtual void deleteResource( );

public:
	virtual ~AppTranslate( );

	AppTranslate( );

	virtual bool init( );

	virtual SettingWidgetTranslate * getSettingWidget( ) const;

	virtual PlayerToolsWidgetTranslate * getPlayerToolsWidget( ) const;

	virtual PlayerListMenuTranslate * getPlayerListMenu( ) const;

	virtual PlayerTopWidgetTranslate * getPlayerTopWidget( ) const;

	virtual PlayerWindowTranslate * getPlayerWindow( ) const;

	virtual JsonTranslate * getJson( ) const;

	virtual DateTimeFormatTranslate * getDateTimeFormat( ) const;

	virtual AboutWidgetTranslate * getAboutWidget( ) const;

	virtual PlayerWidgetTranslate * getPlayerWidget( ) const;

	virtual MainWindowTranslate * getMainWindow( ) const;

	virtual MessageTranslate * getMessage( ) const;
};

#endif // APPTRANSLATE_H_H_HEAD__FILE__
