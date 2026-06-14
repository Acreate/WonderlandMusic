#include "musicListWidget.h"

#include <QDir>
#include <QFileInfo>
#include <QJsonObject>
#include <QMediaMetaData>
#include <QPainter>
#include <qjsondocument.h>
#include <qjsonparseerror.h>

#include "../../musicListMainWidget.h"

#include <applications/applicationEvenTrigger.h>

#include <musics/musicInfo.h>

#include "musicListTopWidget.h"

#include "../../../../../../../../msgInfo/messageErrorOut.h"

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
		MusicListWidgetEvent( this, MusicListWidgetEventInfo( MusicListWidgetEventInfo::EventType::Load_Over ) );
	} );
	ApplicationEvenTrigger::connectMusicListTopWidgetEvent( [this] ( MusicListTopWidget *music_list_top_widget, const MusicListTopWidgetEventInfo &music_list_top_widget_event_info ) {
		auto eventType = music_list_top_widget_event_info.getEventType( );
		switch( eventType ) {
			case MusicListTopWidgetEventInfo::EventType::Drag_Start_Item_Width :
				break;
			case MusicListTopWidgetEventInfo::EventType::Drag_End_Item_Width :
			case MusicListTopWidgetEventInfo::EventType::Update_Item_Width : {
				// 获取顶部高度
				int height = music_list_top_widget->height( );
				size_t count = musicListItemWidgets.size( );
				auto data = musicListItemWidgets.data( );
				size_t index = 0;
				for( ; index < count; ++index ) {
					data[ index ]->move( 0, height );
					height += data[ index ]->height( );
				}

			}
			break;
		}
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
size_t MusicListWidget::getMusicListItemWidgets( std::vector< const MusicListItemWidget * > &result_vector ) const {
	size_t count = musicListItemWidgets.size( );
	if( count == 0 )
		return 0;
	auto data = musicListItemWidgets.data( );
	result_vector.resize( count );
	auto des = result_vector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		des[ index ] = data[ index ];
	return count;
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
