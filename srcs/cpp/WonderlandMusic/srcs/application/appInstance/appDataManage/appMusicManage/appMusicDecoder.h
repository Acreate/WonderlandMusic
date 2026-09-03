#ifndef APPMUSICDECODER_H_H_HEAD__FILE__
#define APPMUSICDECODER_H_H_HEAD__FILE__

#include <vector>

#include <interface/iAppCore.h>

#include <interface/iAppResourceCore.h>

class MusicInfo;
class MusicInfoList;
class IMusicFavoriteItem;
class QMediaPlayer;

class AppMusicDecoder : public IAppCore, public IAppResourceCore {
	friend class LoadMusicDecoderTools;

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

	class LoadMusic {
		friend class LoadMusicDecoderTools;
		IMusicFavoriteItem *musicFavoriteItem;
		MusicInfoList *musicInfoList;
		AppMusicDecoder *appMusicDecoder;

	private:
		void connectLoadOverFinish( );
		void releaseAppMusicDecoder( );

	public:
		explicit LoadMusic( AppMusicDecoder *app_music_decoder, IMusicFavoriteItem *music_favorite_item );
		explicit LoadMusic( AppMusicDecoder *app_music_decoder, IMusicFavoriteItem *music_favorite_item, const std::vector< QString > &file_list );
		virtual ~LoadMusic( );
		virtual bool start( );
		virtual bool append( const std::vector< QString > &file_list );
		virtual bool isRunning( );
		virtual bool isFinished( );
		virtual MusicInfoList * getMusicInfoList( ) const;
		virtual bool moveToMusicInfoVector( std::vector< MusicInfo * > &result_detach_vector );
		virtual IMusicFavoriteItem * getMusicFavoriteItem( ) const;
	};

protected:
	UserMutex *userMutex = nullptr;
	std::vector< QString * > supperDecodeFileSuffix;
	std::vector< LoadMusic * > loadMusicVector;

protected:
	virtual bool overLoad( LoadMusic *load_music );
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
	virtual bool loadMusicFile( IMusicFavoriteItem *music_favorite_item, const QString &music_file );
	virtual size_t loadMusicFile( IMusicFavoriteItem *music_favorite_item, const std::vector< QString > &music_file_path_vector );
	virtual size_t loadMusicDir( IMusicFavoriteItem *music_favorite_item, const QString &music_dir_path );

	virtual bool startLoad( );

protected:
	bool deleteResource( ) override;

public:
	virtual std::vector< QString > getSupperDecodeFileSuffix( ) const;
Q_SIGNALS:
	void signal_load_music_file_over( QMediaPlayer *media_player );
};

class LoadMusicDecoderTools {
	friend class AppMusicDecoder;
	friend class AppMusicDecoder::LoadMusic;

	static bool overLoad( AppMusicDecoder *app_music_decoder, AppMusicDecoder::LoadMusic *load_music );
	static void releaseAppMusicDecoder( AppMusicDecoder::LoadMusic *load_music );
};
#endif // APPMUSICDECODER_H_H_HEAD__FILE__
