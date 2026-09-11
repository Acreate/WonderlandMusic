#include "ffmpegTools.h"

#include <QStringList>

#include "../head/extern_c.h"
INCLUDE_EXTERN_C {
#include <libavformat/avformat.h>
}

std::vector< QString > ffmpegTools::getFFmpegSuperMusicType( ) {
	std::vector< QString > resultType;
	void *opaque = nullptr;
	const AVOutputFormat *ofmt;
	QString buff;
	QStringList spliteStringList;
	qsizetype count;
	qsizetype index;
	QString *data;
	while( ( ofmt = av_muxer_iterate( &opaque ) ) != nullptr ) {
		if( ofmt->audio_codec == AV_CODEC_ID_NONE )
			continue;
		if( ofmt->extensions == nullptr || ofmt->extensions[ 0 ] == '\0' )
			continue;
		buff = QString::fromUtf8( ofmt->extensions );
		spliteStringList = buff.split( "," );
		count = spliteStringList.size( );
		data = spliteStringList.data( );
		for( index = 0; index < count; index += 1 )
			resultType.emplace_back( data[ index ].toUpper( ) );
	}
	return resultType;
}
