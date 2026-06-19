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
	QString playerListWidgetItemSplitWidth;
	QString playerListWidgetItemWidgetIndexWidth;
	QString playerListWidgetItemMusicNameWidth;
	QString playerListWidgetItemMusicSingerWidth;
	QString playerListWidgetItemMusicDurationWidth;
	QString playerListWidgetItemWidgetBeforeWidth;
	QString playerListWidgetItemWidgetAfterWidth;

public:
	virtual ~JsonFileKey( ) = default;

	JsonFileKey( );

	virtual bool init( );

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
};

#endif // JSONFILEKEY_H_H_HEAD__FILE__
