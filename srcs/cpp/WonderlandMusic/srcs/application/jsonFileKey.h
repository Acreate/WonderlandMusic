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
public:
	virtual ~JsonFileKey( ) = default;
	JsonFileKey( );
	virtual bool init( );
	virtual const QString & getMainWindowSettingJsonPath( ) const { return mainWindowSettingJsonPath; }
	virtual const QString & getMainWindowPointXPos( ) const { return mainWindowPointXPos; }
	virtual const QString & getMainWindowPointYPos( ) const { return mainWindowPointYPos; }
	virtual const QString & getMainWindowSizeWidth( ) const { return mainWindowSizeWidth; }
	virtual const QString & getMainWindowSizeHeight( ) const { return mainWindowSizeHeight; }
	virtual const QString & getMusicPlayerListInfoFileJsonPath( ) const { return musicPlayerListInfoFileJsonPath; }
	virtual const QString & getMusicInfoFile( ) const { return musicInfoFile; }
	virtual const QString & getMusicInfoName( ) const { return musicInfoName; }
	virtual const QString & getMusicInfoSinger( ) const { return musicInfoSinger; }
	virtual const QString & getMusicInfoDuration( ) const { return musicInfoDuration; }
	virtual const QString & getMusicInfoListCount( ) const { return musicInfoListCount; }
	virtual const QString & getMusicInfoListName( ) const { return musicInfoListName; }
	virtual const QString & getMusicInfoListIndex( ) const { return musicInfoListIndex; }
};

#endif // JSONFILEKEY_H_H_HEAD__FILE__
