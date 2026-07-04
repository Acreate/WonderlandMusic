#ifndef APPMUSICMANAGE_H_H_HEAD__FILE__
#define APPMUSICMANAGE_H_H_HEAD__FILE__
#include "../interface/iAppCore.h"
#include "../interface/iAppDiskJsonData.h"
#include "../interface/iAppJsonData.h"

class MusicItem;
class UserMutex;
class QMediaPlayer;
class AppMusicDecoder;

class AppMusicManage : public QObject, public IAppCore, public IAppDiskJsonData {
	Q_OBJECT;

protected:

protected:
	UserMutex *loadMutex = nullptr;
	AppMusicDecoder *appMusicDecoder = nullptr;
	std::vector< QMediaPlayer * > loadMediaVector;
	std::vector< QString > loadFileVector;
	size_t loadCount;
	std::vector< MusicItem * > musicItemvVector;

protected:
	bool deleteResource( ) override;

	virtual void loadFile( const QString &music_file );

public:
	bool readJsonData( ) override;

	bool writeJsonData( ) override;

	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;

	bool getJsonData( QJsonObject &get_json_object ) const override;

	bool setJsonData( const QJsonObject &set_json_object ) override;

	~AppMusicManage( ) override;

	virtual AppMusicDecoder * getAppMusicDecoder( ) const;

	virtual void loadMusciFromFileVector( const std::vector< QString > &music_file );

	virtual void loadMusciFromDir( const std::vector< QString > &music_dir );

	virtual std::vector< MusicItem * > & getMusicItem( std::vector< MusicItem * > &result_vector ) const;
};

#endif // APPMUSICMANAGE_H_H_HEAD__FILE__
