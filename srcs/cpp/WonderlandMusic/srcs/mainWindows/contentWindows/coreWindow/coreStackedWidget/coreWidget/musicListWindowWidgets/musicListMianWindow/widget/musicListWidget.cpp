#include "musicListWidget.h"

#include <QDir>
#include <QFileInfo>
#include <QMediaMetaData>
#include <QPainter>

#include "../../musicListMainWidget.h"

#include <applications/applicationEvenTrigger.h>

#include <musics/musicInfo.h>

#include "musicListItemWidget/musicListItemWidget.h"
MusicListWidget::MusicListWidget( QWidget *parent ) : BaseWidget( parent ) {
	ApplicationEvenTrigger::connectMusicListMainWidgetEvent( [this] ( MusicListMainWidget *music_list_main_widget, const MusicListMainWidgetEventInfo &music_list_main_widget_event_info ) {
		auto eventType = music_list_main_widget_event_info.getEventType( );
		if( eventType != MusicListMainWidgetEventInfo::EventType::Load_Music_File_Over )
			return;
		auto musicInfos = music_list_main_widget->getMusicInfos( );
		size_t count = musicInfos.size( );
		if( count == 0 )
			return;
		auto data = musicInfos.data( );
		if( count == 1 )
			appendItem( *data[ 0 ] );
		else
			for( size_t index = 0; index < count; ++index )
				appendItem( *data[ index ] );
		sort( );
	} );
}
bool MusicListWidget::existMusicFilePath( const QString &file_path ) const {
	size_t count = musicListItemWidgets.size( );
	if( count == 0 )
		return false;
	auto data = musicListItemWidgets.data( );
	size_t index;
	QFileInfo *info = new QFileInfo( file_path );
	auto absoluteFilePath = info->absoluteFilePath( );
	delete info;
	for( index = 0; index < count; ++index )
		if( data[ index ]->getFilePath( ) == absoluteFilePath )
			return true;
	return false;
}
bool MusicListWidget::appendItem( const MusicInfo &media_meta_data ) {
	QString filePath = media_meta_data.getFilePath( );
	size_t count = musicListItemWidgets.size( );
	if( count != 0 ) {
		size_t index = 0;
		auto data = musicListItemWidgets.data( );
		for( ; index < count; ++index )
			if( filePath == data[ index ]->getFilePath( ) )
				return false; // 已经存在
	}
	auto newItem = new MusicListItemWidget( this, filePath, media_meta_data.getMusicName( ), media_meta_data.getSinger( ), media_meta_data.getDurationMs( ) );
	musicListItemWidgets.emplace_back( newItem );
	return true;
}
bool MusicListWidget::sort( ) {
	size_t count = musicListItemWidgets.size( );
	if( count == 0 )
		return false;
	auto data = musicListItemWidgets.data( );
	size_t index;

	int oldWidth = width( );
	int oldHeight = height( );

	int maxWidth = oldWidth;
	int compWidth;
	int maxHeight = 0;
	int compHeight = oldHeight;
	for( index = 0; index < count; ++index ) {
		data[ index ]->adjustSize( );
		compWidth = data[ index ]->width( );
		if( compWidth < maxWidth )
			maxWidth = compWidth;
		data[ index ]->move( 0, maxHeight );
		maxHeight += data[ index ]->height( );
		data[ index ]->show( );
	}
	if( maxHeight > compHeight )
		setFixedHeight( maxHeight );
	if( maxWidth > oldWidth )
		setFixedWidth( maxWidth );
	return true;
}
