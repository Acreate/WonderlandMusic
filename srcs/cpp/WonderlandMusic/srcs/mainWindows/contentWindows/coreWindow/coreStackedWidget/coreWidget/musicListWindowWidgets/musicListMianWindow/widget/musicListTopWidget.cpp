#include "musicListTopWidget.h"

#include <QLabel>
#include <QPainter>
#include <qevent.h>

#include <applications/applicationEvenTrigger.h>
#include <applications/applicationInstance.h>

#include "../../../../../../../../msgInfo/messageErrorOut.h"

#include "musicListItemWidget/labelItem.h"

MusicListTopWidget::MusicListTopWidget( QWidget *parent ) : BaseWidget( parent ) {
	musicNameItem = new LabelItem( tr( "歌名" ), this );
	musicSingerItem = new LabelItem( tr( "主唱" ), this );
	musicPlayerTimeItem = new LabelItem( tr( "时长" ), this );
	musicNameItem->move( 0, 0 );
	int width = musicNameItem->width( );
	musicSingerItem->move( width, 0 );
	width += musicSingerItem->width( );
	musicPlayerTimeItem->move( width, 0 );

	ApplicationEvenTrigger::connectApplicationInstanceEvent( [this] ( ApplicationInstance *application_instance, const ApplicationInstanceEventInfo &application_instance_event_info ) {
		auto eventType = application_instance_event_info.getEventType( );

		switch( eventType ) {
			case ApplicationInstanceEventInfo::EventType::Move_Global_Mouse_Pos : {
				// 检测是否在拖拽区间，并且设置准备符号
				// 在激活拖拽功能的情况下发送信号
				auto point = QCursor::pos( );
				point = mapFromGlobal( point );
				if( geometry( ).contains( point ) == false )
					break;
				if( musicNameItem->isContainsDecollator( point ) ) {
					break;
				} else if( musicSingerItem->isContainsDecollator( point ) ) {
					break;
				} else if( musicPlayerTimeItem->isContainsDecollator( point ) ) {
					break;
				}
			}

			break;
			case ApplicationInstanceEventInfo::EventType::Press_Global_Mouse_Pos :
				// 在准备符号为确定的情况下激活拖拽功能

				break;
			case ApplicationInstanceEventInfo::EventType::Release_Global_Mouse_Pos :
				// 取消拖拽功能

				break;
		}
	} );
}
MusicListTopWidget::~MusicListTopWidget( ) {

}
void MusicListTopWidget::resizeEvent( QResizeEvent *event ) {
	BaseWidget::resizeEvent( event );

}
void MusicListTopWidget::paintEvent( QPaintEvent *event ) {
	BaseWidget::paintEvent( event );
}
