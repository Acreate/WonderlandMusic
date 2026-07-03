#ifndef APPMUSICMANAGE_H_H_HEAD__FILE__
#define APPMUSICMANAGE_H_H_HEAD__FILE__
#include "../interface/iAppCore.h"

class MusicItem;
class UserMutex;
class QMediaPlayer;
class AppMusicDecoder;

class AppMusicManage : public QObject, public IAppCore {
	Q_OBJECT;

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
	bool init( ) override;

	~AppMusicManage( ) override;

	virtual AppMusicDecoder * getAppMusicDecoder( ) const;

	virtual void loadMusciFromFileVector( const std::vector< QString > &music_file );

	virtual void loadMusciFromDir( const std::vector< QString > &music_dir );

	virtual std::vector< MusicItem * > & getMusicItem( std::vector< MusicItem * > &result_vector ) const;

Q_SIGNALS:
	void signal_load_error( const QString &music_file_path );

	void signal_load_over( const std::vector< MusicItem * > &music_item_vector );

	void signal_load_star( const QString &music_file_path );

	void signal_load_unity( const MusicItem &music_item );
};

#endif // APPMUSICMANAGE_H_H_HEAD__FILE__
