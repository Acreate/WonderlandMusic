#ifndef MUSICINFOLIST_H_H_HEAD__FILE__
#define MUSICINFOLIST_H_H_HEAD__FILE__
#include <QThread>

class UserMutex;
class MusicFileInfo;

class MusicFileInfoList : public QThread {
	Q_OBJECT;

private:
	std::vector< MusicFileInfo * > overLoadMusicVector;
	std::vector< MusicFileInfo * > musicVector;
	UserMutex *userMutex;
	size_t count;
	size_t index;
	MusicFileInfo * *musicVectorDataPtr;

protected:
	virtual void loadFinished( MusicFileInfo *music_info );

public:
	MusicFileInfoList( const std::vector< QString > &file_list );
	MusicFileInfoList( );
	~MusicFileInfoList( ) override;
	virtual bool appendLoadMusicFileList( const std::vector< QString > &file_list );
	virtual bool getOverLoadMusicVector( std::vector< MusicFileInfo * > &result_over_load_music_info_vector ) const;
	virtual QStringList toQStringList( ) const;
	virtual operator QString( ) const;
	virtual size_t getCount( ) const;
	virtual bool moveToMusicInfoVector( std::vector< MusicFileInfo * > &result_detach_vector );

protected:
	void run( ) override;
};

#endif // MUSICINFOLIST_H_H_HEAD__FILE__
