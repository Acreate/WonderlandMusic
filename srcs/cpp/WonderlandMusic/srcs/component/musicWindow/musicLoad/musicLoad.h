#ifndef MUSICLOADTOOLS_H_H_HEAD__FILE__
#define MUSICLOADTOOLS_H_H_HEAD__FILE__

#include <interface/iAppCore.h>

class MusicListWidget;
class QString;

class MusicLoad : public IAppCore {
	friend class MusicLoadTools;

protected:
	MusicListWidget *musicListWidget;
	MusicLoad( MusicListWidget *music_list_widget );
	~MusicLoad( ) override;

public:

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	virtual bool loadMusicFile( const QString &music_file_path );
	virtual bool loadMusicDir( const QString &music_dir_path );
};

class MusicLoadTools {
	friend class MusicLoad;
	friend class MusicListWidget;
	static bool createMusicLoad( MusicLoad **music_load, MusicListWidget *music_list_widget );
	static bool releaseMusicLoad( MusicLoad **music_load );
	static bool setMusicListWidget( MusicLoad *music_load, MusicListWidget *music_list_widget );
};
#endif // MUSICLOADTOOLS_H_H_HEAD__FILE__
