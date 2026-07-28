#ifndef APPMUSICDECODER_H_H_HEAD__FILE__
#define APPMUSICDECODER_H_H_HEAD__FILE__

#include <qcontainerfwd.h>
#include <vector>

#include "../interface/iAppCore.h"

class QMediaPlayer;

class AppMusicDecoder : public IAppCore {
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
	~AppMusicDecoder( ) override;

	AppMusicDecoder( );

	virtual bool musicFileNmaeSupperDecoder( const QString &music_file_path ) const;

	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;

protected:
	bool deleteResource( ) override;

public:
	virtual std::vector< QString > getSupperDecodeFileSuffix( ) const;
	virtual bool loadMusicFile( const QString &music_file_path );
Q_SIGNALS:
	void signal_load_music_file_over( QMediaPlayer *media_player );
};

#endif // APPMUSICDECODER_H_H_HEAD__FILE__
