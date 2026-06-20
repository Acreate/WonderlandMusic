#ifndef JSONFILEKEY_H_H_HEAD__FILE__
#define JSONFILEKEY_H_H_HEAD__FILE__
#include <QString>

class JsonFileKey {
protected:
	QString mainWindowSettingJsonPath;
	QString mainWindowPointXPos;
	QString mainWindowPointYPos;
	QString mainWindowSizeWidth;
	QString mainWindowSizeHeight;

	QString musicPlayerListInfoFileJsonPath;
	QString musicInfoListCount;
	QString musicInfoListName;
	QString musicInfoListIndex;
	QString musicInfoFile;
	QString musicInfoName;
	QString musicInfoSinger;
	QString musicInfoDuration;

	QString playerWindowSettingJsonPath;
	QString playerWindowFileSelectWorkPath;
	QString playerWindowDirSelectWorkPath;

	QString playerListWidgetTopJsonPath;
	QString playerListWidgetItemWidth;
	QString playerListWidgetItemSplitWidth;
	QString playerListWidgetItemWidgetIndexWidth;
	QString playerListWidgetItemMusicNameWidth;
	QString playerListWidgetItemMusicSingerWidth;
	QString playerListWidgetItemMusicDurationWidth;
	QString playerListWidgetItemWidgetBeforeWidth;
	QString playerListWidgetItemWidgetAfterWidth;
	/// @brief 上一曲图标
	QString thePreviousSongIconPath;
	/// @brief 播放图标
	QString controlPlayIconPath;
	/// @brief 暂停图标
	QString controlPauseIconPath;
	/// @brief 下一曲图标
	QString theNextSongIconPath;
	/// @brief 当前播放列表
	QString currentSongPlayListIconPath;
	/// @brief 播放列表位置
	QString songPlayerInfoJsonPath;
	/// @brief qt 标识
	QString qtLogoIconPath;

public:
	virtual ~JsonFileKey( ) = default;

	JsonFileKey( );

	virtual bool init( );

	virtual const QString & getCurrentSongPlayListIconPath( ) const;

	virtual const QString & getSongPlayerInfoJsonPath( ) const;

	virtual const QString & getQtLogoIconPath( ) const;

	virtual const QString & getPlayerListWidgetItemWidth( ) const;

	virtual const QString & getMainWindowSettingJsonPath( ) const;

	virtual const QString & getMainWindowPointXPos( ) const;

	virtual const QString & getMainWindowPointYPos( ) const;

	virtual const QString & getMainWindowSizeWidth( ) const;

	virtual const QString & getMainWindowSizeHeight( ) const;

	virtual const QString & getMusicPlayerListInfoFileJsonPath( ) const;

	virtual const QString & getMusicInfoFile( ) const;

	virtual const QString & getMusicInfoName( ) const;

	virtual const QString & getMusicInfoSinger( ) const;

	virtual const QString & getMusicInfoDuration( ) const;

	virtual const QString & getMusicInfoListCount( ) const;

	virtual const QString & getMusicInfoListName( ) const;

	virtual const QString & getMusicInfoListIndex( ) const;

	virtual const QString & getPlayerWindowSettingJsonPath( ) const;

	virtual const QString & getPlayerWindowFileSelectWorkPath( ) const;

	virtual const QString & getPlayerWindowDirSelectWorkPath( ) const;

	virtual const QString & getPlayerListWidgetItemSplitWidth( ) const;

	virtual const QString & getPlayerListWidgetItemWidgetIndexWidth( ) const;

	virtual const QString & getPlayerListWidgetItemMusicNameWidth( ) const;

	virtual const QString & getPlayerListWidgetItemMusicSingerWidth( ) const;

	virtual const QString & getPlayerListWidgetItemMusicDurationWidth( ) const;

	virtual const QString & getPlayerListWidgetTopJsonPath( ) const;

	virtual const QString & getPlayerListWidgetItemWidgetBeforeWidth( ) const;

	virtual const QString & getPlayerListWidgetItemWidgetAfterWidth( ) const;

	virtual const QString & getThePreviousSongIconPath( ) const;

	virtual const QString & getControlPlayIconPath( ) const;

	virtual const QString & getControlPauseIconPath( ) const;

	virtual const QString & getTheNextSongIconPath( ) const;
};

#endif // JSONFILEKEY_H_H_HEAD__FILE__
