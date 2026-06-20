#ifndef APPTRANSLATE_H_H_HEAD__FILE__
#define APPTRANSLATE_H_H_HEAD__FILE__
#include <qstring.h>

class AppTranslate {
protected:
	QString sourceFile;
	QString sourceFunction;
	QString sourceLine;

	QString createDirError;
	QString createFileError;

	QString openFileError;
	QString writeFileError;
	QString readFileError;

	QString appWindowTitleName;
	QString playMusic;
	QString stopMusic;
	QString pauseMusic;
	QString playListWidget;
	QString settingWidget;
	QString aboutWidget;
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

	QString fileConverJsonDocError;
	QString notFindJsonKey;

	QString menuFileTitle;

	QString actionAddMultiMusicFileToCollection;
	QString actionAddMultiMusicDirToCollection;
	QString actionRemoveMultiMusicAtCollection;

	QString musicTypeName;

	QString musicIndex;
	QString musicName;
	QString musicSinger;
	QString musicDuration;

	QString playerListMenuenuPlayerMenu;
	QString playerListMenuPlayerMenuSetCurrentPlayAction;
	QString playerListMenuPlayerMenuInsterCurrentPlayAction;
	QString playerListMenuControlMenu;
	QString playerListMenuControlMenuRemoveMusicAction;
	QString playerListMenuControlMenuDeleteMusicAction;
	QString playerListMenuMoveMenu;
	QString playerListMenuControlMenuMoveTopMusicAction;
	QString playerListMenuControlMenuMoveBottomMusicAction;
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
	
protected:
	void setCodecForLocale( );

	void translateString( );

public:
	virtual ~AppTranslate( ) = default;

	virtual const QString & getControlPausa( ) const;

	AppTranslate( );

	virtual bool init( );

	virtual const QString & getPlaySongDateTimeSpace( ) const;

	virtual const QString & getSourceFile( ) const;

	virtual const QString & getSourceFunction( ) const;

	virtual const QString & getSourceLine( ) const;

	virtual const QString & getCreateDirError( ) const;

	virtual const QString & getCreateFileError( ) const;

	virtual const QString & getOpenFileError( ) const;

	virtual const QString & getAppWindowTitleName( ) const;

	virtual const QString & getPlay( ) const;

	virtual const QString & getStop( ) const;

	virtual const QString & getPause( ) const;

	virtual const QString & getPlayListWidget( ) const;

	virtual const QString & getSettingWidget( ) const;

	virtual const QString & getAboutWidget( ) const;

	virtual const QString & getYear( ) const;

	virtual const QString & getMonth( ) const;

	virtual const QString & getDay( ) const;

	virtual const QString & getHour( ) const;

	virtual const QString & getMinute( ) const;

	virtual const QString & getSecond( ) const;

	virtual const QString & getMillsecond( ) const;

	virtual const QString & getWriteFileError( ) const;

	virtual const QString & getReadFileError( ) const;

	virtual const QString & getFileConverJsonDocError( ) const;

	virtual const QString & getNotFindJsonKey( ) const;

	virtual const QString & getActionAddMultiMusicFileToCollection( ) const;

	virtual const QString & getActionAddMultiMusicDirToCollection( ) const;

	virtual const QString & getActionRemoveMultiMusicAtCollection( ) const;

	virtual const QString & getMenuFileTitle( ) const;

	virtual const QString & getMusicTypeName( ) const;

	virtual const QString & getMusicIndex( ) const;

	virtual const QString & getMusicName( ) const;

	virtual const QString & getMusicSinger( ) const;

	virtual const QString & getMusicDuration( ) const;

	virtual const QString & getPlayerListMenuenuPlayerMenu( ) const;

	virtual const QString & getPlayerListMenuPlayerMenuSetCurrentPlayAction( ) const;

	virtual const QString & getPlayerListMenuPlayerMenuInsterCurrentPlayAction( ) const;

	virtual const QString & getPlayerListMenuControlMenu( ) const;

	virtual const QString & getPlayerListMenuControlMenuRemoveMusicAction( ) const;

	virtual const QString & getPlayerListMenuControlMenuMoveTopMusicAction( ) const;

	virtual const QString & getPlayerListMenuControlMenuMoveBottomMusicAction( ) const;

	virtual const QString & getPlayerListMenuMoveMenu( ) const;

	virtual const QString & getPlayerListMenuControlMenuDeleteMusicAction( ) const;

	virtual const QString & getThePreviousSong( ) const;

	virtual const QString & getControlPlay( ) const;

	virtual const QString & getTheNextSong( ) const;

	virtual const QString & getCurrentPlayList( ) const;
};

#endif // APPTRANSLATE_H_H_HEAD__FILE__
