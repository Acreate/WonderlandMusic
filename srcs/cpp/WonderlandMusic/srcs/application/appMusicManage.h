#ifndef APPMUSICMANAGE_H_H_HEAD__FILE__
#define APPMUSICMANAGE_H_H_HEAD__FILE__
#include "../interface/iAppCore.h"

class QMediaPlayer;
class AppMusicDecoder;

class AppMusicManage : public QObject, public IAppCore {
	Q_OBJECT;

protected:
	AppMusicDecoder *appMusicDecoder = nullptr;
	std::vector< QMediaPlayer * > loadMediaVector;
	std::vector< QString > loadFileVector;

protected:
	bool deleteResource( ) override;

	virtual void loadFile( const QString &music_file );

public:
	bool init( ) override;

	virtual AppMusicDecoder * getAppMusicDecoder( ) const;

	virtual void loadMusciFromFileVector( const std::vector< QString > &music_file );

	virtual void loadMusciFromDir( const std::vector< QString > &music_dir );

Q_SIGNALS:
	void signal_load_error( const QMediaPlayer &player );

	void signal_load_over( const std::vector< QMediaPlayer * > &player_vector );

	void signal_load_star( );

	void signal_load_unity( const QMediaPlayer &player );
};

#endif // APPMUSICMANAGE_H_H_HEAD__FILE__
