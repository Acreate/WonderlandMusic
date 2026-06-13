#include "musicListItemWidget.h"

#include <QFileInfo>
#include <QLabel>
#include <QHBoxLayout>

#include <musics/musicInfo.h>

#include "labelItem.h"

#include "../musicListTopWidget.h"

#include <applications/applicationEvenTrigger.h>

MusicListItemWidget::MusicListItemWidget( QWidget *parent, const QString &file_path, const QString &music_name, const QString &singer_name, qint64 duration_ms ) : BaseWidget( parent ),
	filePath( file_path ), musicName( music_name ), singerName( singer_name ), duration_ms( duration_ms ) {

	QDateTime dt = QDateTime::fromMSecsSinceEpoch( duration_ms );
	QString formatTime = dt.toString( "hh:mm:ss" );
	labelItemVector.emplace_back( new LabelItem( music_name, this ) );
	labelItemVector.emplace_back( new LabelItem( singer_name, this ) );
	labelItemVector.emplace_back( new LabelItem( formatTime, this ) );
	labelItemVector.emplace_back( new LabelItem( "", this ) );

	ApplicationEvenTrigger::connectMusicListTopWidgetEvent( [this] ( MusicListTopWidget *music_list_top_widget, const MusicListTopWidgetEventInfo &music_list_top_widget_event_info ) {
		auto eventType = music_list_top_widget_event_info.getEventType( );
		switch( eventType ) {

			case MusicListTopWidgetEventInfo::EventType::Drag_Start_Item_Width :
				break; // 消耗性能
			case MusicListTopWidgetEventInfo::EventType::Drag_End_Item_Width :
			case MusicListTopWidgetEventInfo::EventType::Update_Item_Width : {
				auto titleVector = music_list_top_widget->getTitleVector( );
				size_t currentItemCount = labelItemVector.size( );
				size_t titleCount = titleVector.size( );
				if( currentItemCount != titleCount )
					break; // 数据不匹配
				auto currentItemData = labelItemVector.data( );
				auto titleItemData = titleVector.data( );
				titleCount = 0;
				for( ; titleCount < currentItemCount; ++titleCount ) {
					currentItemData[ titleCount ]->move( titleItemData[ titleCount ]->x( ), 0 );
					currentItemData[ titleCount ]->setFixedWidth( titleItemData[ titleCount ]->width( ) );
				}
				setFixedSize( music_list_top_widget->size( ) );
			}
			break;
		}
	} );
}
