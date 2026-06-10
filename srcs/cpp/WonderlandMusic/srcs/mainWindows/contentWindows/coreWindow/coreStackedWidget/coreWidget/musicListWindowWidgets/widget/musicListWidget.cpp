#include "musicListWidget.h"

#include <QDir>
#include <QFileInfo>
#include <QMediaMetaData>
#include <QPainter>

#include "../musicListMainWidget.h"

#include "../../../../../../../applications/applicationEvenTrigger.h"

#include "../../../../../../../msgInfo/messageErrorOut.h"

#include "../../../../../../../musics/musicInfo.h"

#include "musicListItemWidget/musicListItemWidget.h"
MusicListWidget::MusicListWidget( QWidget *parent ) : BaseWidget( parent ) {
	ApplicationEvenTrigger::connectMusicListMainWidgetEvent( [] ( MusicListMainWidget *music_list_main_widget, const MusicListMainWidgetEventInfo &music_list_main_widget_event_info ) {
		auto eventType = music_list_main_widget_event_info.getEventType( );
		if( eventType != MusicListMainWidgetEventInfo::EventType::Music_Load_Over )
			return;
		auto musicInfos = music_list_main_widget->getMusicInfos( );
		size_t count = musicInfos.size( );
		auto data = musicInfos.data( );
		size_t index = 0;

		QStringList outInfo;
		QSet< QString > setName;

		for( ; index < count; ++index ) {
			auto generateStringInfo = data[ index ]->getFilePath( ) + ", " + data[ index ]->getMusicName( ) + ", " + data[ index ]->getSinger( ) + ", " + QString::number( data[ index ]->getDurationMs( ) );
			outInfo << "[ " + QString::number( ++index ) + " ] = " + generateStringInfo;
		}
		Message_Error_Out << outInfo;
	} );
}
bool MusicListWidget::appendItem( const MusicInfo &media_meta_data ) {
	return false;
}
bool MusicListWidget::sort( ) {
	return false;
}
void MusicListWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::black );
}
