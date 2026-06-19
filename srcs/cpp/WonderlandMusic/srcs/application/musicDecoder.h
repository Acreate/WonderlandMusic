#ifndef MUSICDECODER_H_H_HEAD__FILE__
#define MUSICDECODER_H_H_HEAD__FILE__

#include <qcontainerfwd.h>
#include <vector>

class PlayerListWidget;
class MusicInfoItemWidget;
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

	virtual void addPlayMusicVector( PlayerListWidget *player_list_widget, const std::vector< MusicInfoItemWidget * > &play_vector );

	virtual void insterMusicVector( PlayerListWidget *player_list_widget, const std::vector< MusicInfoItemWidget * > &play_vector );

	virtual void removeAtPlayerListWidgetMusicVector( PlayerListWidget *player_list_widget, const std::vector< MusicInfoItemWidget * > &play_vector );

	virtual void setCurrentSelectPlay( const std::vector< MusicInfoItemWidget * > &selct_play_vector );

	virtual void insterCurrentSelectPlay( const std::vector< MusicInfoItemWidget * > &selct_play_vector );

	virtual void removePlayListSelectInfo( const std::vector< MusicInfoItemWidget * > &selct_play_vector );

	virtual void deletePlayListSelectFile( const std::vector< MusicInfoItemWidget * > &selct_play_vector );

	virtual void selectListMoveTop( const std::vector< MusicInfoItemWidget * > &selct_play_vector );

	virtual void selectListMoveBottom( const std::vector< MusicInfoItemWidget * > &selct_play_vector );
};

#endif // MUSICDECODER_H_H_HEAD__FILE__
