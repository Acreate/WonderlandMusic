#include "musicListItemWidget.h"

#include <QFileInfo>
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>

#include <musics/musicInfo.h>

#include "labelItem.h"

#include "../musicListTopWidget.h"

#include <applications/applicationEvenTrigger.h>

#include <widgetEffects/widgetEffect.h>
#include <widgetEffects/highlight/highlightBackground.h>
#include <widgetEffects/highlight/highlightBorder.h>

QString MusicListItemWidget::msToHMS( qint64 totalMs ) {
	qint64 totalSec = totalMs / 1000;
	qint64 h = totalSec / 3600;
	qint64 m = ( totalSec % 3600 ) / 60;
	qint64 s = totalSec % 60;
	return QString( "%1:%2:%3" )
			.arg( h, 2, 10, QChar( '0' ) )
			.arg( m, 2, 10, QChar( '0' ) )
			.arg( s, 2, 10, QChar( '0' ) );
}
MusicListItemWidget::MusicListItemWidget( QWidget *parent, const QString &file_path, const QString &music_name, const QString &singer_name, qint64 duration_ms ) : BaseWidget( parent ),
	filePath( file_path ), musicName( music_name ), singerName( singer_name ), duration_ms( duration_ms ) {
	select = false;
	activity = false;
	selectEffect = new HighlightBackground( this );
	activityEffect = new HighlightBorder( this );

	QString formatTime = msToHMS( duration_ms );
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
					int width = titleItemData[ titleCount ]->width( );
					currentItemData[ titleCount ]->setFixedWidth( width );
				}
				setFixedSize( music_list_top_widget->size( ) );
			}
			break;
		}
	} );
}
MusicListItemWidget::~MusicListItemWidget( ) {
	delete activityEffect;
	activityEffect = nullptr;
	delete selectEffect;
	selectEffect = nullptr;
}

void MusicListItemWidget::setActivity( const bool activity ) {
	this->activity = activity;
	update( );
}
void MusicListItemWidget::setSelect( const bool select ) {
	this->select = select;
	update( );
}
void MusicListItemWidget::paintEvent( QPaintEvent *event ) {
	BaseWidget::paintEvent( event );
	if( select && selectEffect )
		selectEffect->renderEffect( );
	if( activity && activityEffect )
		activityEffect->renderEffect( );
}
void MusicListItemWidget::resizeEvent( QResizeEvent *event ) {
	BaseWidget::resizeEvent( event );

}
