#ifndef MUSICINFO_H_H_HEAD__FILE__
#define MUSICINFO_H_H_HEAD__FILE__
#include <QThread>

class QFileInfo;
class UserMutex;
struct AVFormatContext;

class MusicInfo : public QThread {
	Q_OBJECT;

protected:
	enum class RunStatus {
		Ready,
		Run,
		Over
	};

private:
	QString filePath;
	UserMutex *userMutex;
	QFileInfo *fileInfo;
	RunStatus status;
	AVFormatContext *fmtCtx;
	QString title;
	QString artist;
	QString album;
	QString albumArtist;
	QString genre;
	QString date;
	QString track;
	QString comment;
	QString avcodecGetName;
	int sampleRate;
	int nbChannels;
	QString avGetSampleFmtName;

	int64_t bitRate;
	int64_t durationMillsecond;
	QString channelLayoutDescribe;

public:
	explicit MusicInfo( const QString &file_path );
	~MusicInfo( ) override;

protected:
	void run( ) override;

public:
	virtual bool isRead( ) const;
	virtual const QString & getFilePath( ) const;
	virtual RunStatus getStatus( ) const;
	virtual const QString & getTitle( ) const;
	virtual const QString & getArtist( ) const;
	virtual const QString & getAlbum( ) const;
	virtual const QString & getAlbumArtist( ) const;
	virtual const QString & getGenre( ) const;
	virtual const QString & getDate( ) const;
	virtual const QString & getTrack( ) const;
	virtual const QString & getComment( ) const;
	virtual const QString & getAvcodecGetName( ) const;
	virtual int getSampleRate( ) const;
	virtual int getNbChannels( ) const;
	virtual const QString & getAvGetSampleFmtName( ) const;
	virtual int64_t getBitRate( ) const;
	virtual int64_t getDurationMillsecond( ) const;
	virtual const QString & getChannelLayoutDescribe( ) const;
};

#endif // MUSICINFO_H_H_HEAD__FILE__
