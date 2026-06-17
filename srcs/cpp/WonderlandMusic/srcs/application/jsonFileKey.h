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
};

#endif // JSONFILEKEY_H_H_HEAD__FILE__
