#ifndef MUSICDECODER_H_H_HEAD__FILE__
#define MUSICDECODER_H_H_HEAD__FILE__

#include <vector>

class QMediaPlayer;
class QString;

class MusicDecoder {
	std::vector< QString * > supperDecodeFileSuffix;
	QMediaPlayer *mediaPlayer;

public:
	virtual ~MusicDecoder( );

	MusicDecoder( );

	virtual bool musicFileNmaeSupperDecoder( const QString &music_file_path ) const;

	virtual bool init( );

	virtual std::vector< QString > getSupperDecodeFileSuffix( ) const;

	virtual bool setMusicPlayerSourceFile( const QString &file_path );

	virtual bool playerMusic( );

	virtual bool stopMusic( );

	virtual bool pauseMusic( );

	virtual QString getMusicPlayerSourceFile( ) const;
};

#endif // MUSICDECODER_H_H_HEAD__FILE__
