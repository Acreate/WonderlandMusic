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
bool MusicInfo::open( const QString &file_path, const std::function< void( MusicInfo *, const QMediaMetaData & ) > &load_over_call_function ) {
	auto application = ApplicationInstance::getApplicationInstance( );
	if( application->musicFileNmaeSupperDecoder( file_path ) == false )
		return false;
	QFileInfo info( file_path );
	if( info.exists( ) == false )
		return false;
	musicUrl = QUrl::fromLocalFile( file_path );
	loadOverCallFunction = load_over_call_function;
	//if( mediaPlayer == nullptr )
	//	mediaPlayer = new QMediaPlayer;
	connect( mediaPlayer, &QMediaPlayer::mediaStatusChanged, [this] ( QMediaPlayer::MediaStatus media_status ) {
		if( media_status != QMediaPlayer::LoadedMedia )
			return; // 必须标识为加载完成
		if( mediaPlayer->source( ) != musicUrl )
			return; // 不等于源
		auto mediaMetaData = mediaPlayer->metaData( );
		if( mediaMetaData.isEmpty( ) ) {
			MessageErrorOut( ) << QObject::tr( "没有匹配音频文件信息" ) << " : " << musicUrl.toLocalFile( );
			return; // 加载失败
		}
		this->isReadMusicFileOver = true;
		loadOverCallFunction( this, mediaMetaData );
		//delete mediaPlayer;
		//mediaPlayer = nullptr;
	} );
	this->isReadMusicFileOver = false;
	mediaPlayer->setSource( musicUrl );

	return true;
}
