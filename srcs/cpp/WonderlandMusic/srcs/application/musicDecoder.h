#ifndef MUSICDECODER_H_H_HEAD__FILE__
#define MUSICDECODER_H_H_HEAD__FILE__

#include <iostream>
#include <qcontainerfwd.h>
#include <vector>

class PlayerListWidget;
class MusicInfoItemWidget;
class QMediaPlayer;
class QString;

class MusicDecoder {
protected:
	class StringOperator {
		QStringList *stringList;

	public:
		StringOperator( );

		virtual ~StringOperator( );

		virtual StringOperator & operator<<( const QString &append );

		virtual const QStringList & getStringList( ) const {
			return *stringList;
		}
	};

protected:
	std::vector< QString * > supperDecodeFileSuffix;

protected:
	virtual void appendDecodeFileSuffix( const QString &decode_file_suffix );

	virtual void appendDecodeFileSuffix( const QStringList &decode_file_suffix );

	template< typename ...QString >
	void appendAnyDecodeFileSuffix( QString && ...file_path_vector ) {
		StringOperator stringBuff;
		(stringBuff << ... << file_path_vector);
		appendDecodeFileSuffix( stringBuff.getStringList( ) );
	}

public:
	virtual ~MusicDecoder( );

	MusicDecoder( );

	virtual bool musicFileNmaeSupperDecoder( const QString &music_file_path ) const;

	virtual bool init( );

	virtual std::vector< QString > getSupperDecodeFileSuffix( ) const;
};

#endif // MUSICDECODER_H_H_HEAD__FILE__
