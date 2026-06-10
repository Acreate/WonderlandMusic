#include "musicInfo.h"

#include <QAudioDecoder>
#include <QFileInfo>
#include <QMediaMetaData>
#include <QMediaPlayer>

#include "../applications/applicationInstance.h"

#include "../msgInfo/messageErrorOut.h"

MusicInfo::~MusicInfo( ) {
	if( mediaPlayer )
		delete mediaPlayer;
}
MusicInfo::MusicInfo( ) {
	this->isReadMusicFileOver = false;
	mediaPlayer = new QMediaPlayer;
}
bool MusicInfo::open( const QString &file_path, const std::function< void( MusicInfo * ) > &load_over_call_function ) {
	auto application = ApplicationInstance::getApplicationInstance( );
	if( application->musicFileNmaeSupperDecoder( file_path ) == false ) {
		MessageErrorOut( ) << QObject::tr( "音频文件后缀不匹配" ) << " : " << file_path;
		return false;
	}
	QFileInfo info( file_path );
	QString absoluteFilePath = info.absoluteFilePath( );
	if( info.exists( ) == false ) {
		MessageErrorOut( ) << QObject::tr( "路径不存在音频文件" ) << " : " << absoluteFilePath;
		return false;
	}
	musicUrl = QUrl::fromLocalFile( absoluteFilePath );
	loadOverCallFunction = load_over_call_function;
	if( mediaPlayer == nullptr )
		mediaPlayer = new QMediaPlayer;
	connect( mediaPlayer, &QMediaPlayer::mediaStatusChanged, [this] ( QMediaPlayer::MediaStatus media_status ) {
		if( mediaPlayer->source( ) != musicUrl )
			return; // 不等于源

		auto mediaMetaData = mediaPlayer->metaData( );
		if( mediaMetaData.isEmpty( ) ) {
			MessageErrorOut( ) << QObject::tr( "没有匹配音频文件信息" ) << " : " << musicUrl.toLocalFile( );
			return; // 加载失败
		}
		musicName = mediaMetaData.value( QMediaMetaData::Title ).toString( );
		singer = mediaMetaData.value( QMediaMetaData::ContributingArtist ).toString( );
		duration_ms = mediaMetaData.value( QMediaMetaData::Duration ).toLongLong( );
		delete mediaPlayer;
		mediaPlayer = nullptr;
		this->isReadMusicFileOver = true;
		loadOverCallFunction( this );
	} );
	this->isReadMusicFileOver = false;
	mediaPlayer->setSource( musicUrl );

	return true;
}
