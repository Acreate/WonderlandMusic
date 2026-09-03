#ifndef MUSICINFOLIST_H_H_HEAD__FILE__
#define MUSICINFOLIST_H_H_HEAD__FILE__
#include <QThread>

class UserMutex;
class MusicInfo;

class MusicInfoList : public QThread {
	Q_OBJECT;

private:
	std::vector< MusicInfo * > overLoadMusicVector;
	std::vector< MusicInfo * > musicVector;
	UserMutex *userMutex;
	size_t count;
	size_t index;
	MusicInfo * *musicVectorDataPtr;

protected:
	virtual void loadFinished( MusicInfo *music_info );

public:
	MusicInfoList( const std::vector< QString > &file_list );
	MusicInfoList( );
	~MusicInfoList( ) override;
	virtual bool appendLoadMusicFileList( const std::vector< QString > &file_list );
	virtual bool getOverLoadMusicVector( std::vector< MusicInfo * > &result_over_load_music_info_vector ) const;
	virtual QStringList toQStringList( ) const;
	virtual operator QString( ) const;
	virtual size_t getCount( ) const;
	virtual bool moveToMusicInfoVector( std::vector< MusicInfo * > &result_detach_vector );

protected:
	void run( ) override;
};

#endif // MUSICINFOLIST_H_H_HEAD__FILE__
