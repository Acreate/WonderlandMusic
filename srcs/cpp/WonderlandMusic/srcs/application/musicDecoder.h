#ifndef MUSICDECODER_H_H_HEAD__FILE__
#define MUSICDECODER_H_H_HEAD__FILE__

#include <vector>

class QString;
class MusicDecoder {
	std::vector< QString * > supperDecodeFileSuffix;
public:
	virtual ~MusicDecoder( );
	MusicDecoder( );
	virtual bool musicFileNmaeSupperDecoder( const QString &music_file_path ) const;
	virtual bool init( );
};

#endif // MUSICDECODER_H_H_HEAD__FILE__
