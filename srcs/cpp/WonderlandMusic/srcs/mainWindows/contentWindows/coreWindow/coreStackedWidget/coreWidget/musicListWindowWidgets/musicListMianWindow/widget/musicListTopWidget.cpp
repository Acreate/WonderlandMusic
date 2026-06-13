#include "musicListTopWidget.h"

#include <QLabel>
#include <QPainter>
#include <qevent.h>

#include <applications/applicationEvenTrigger.h>
#include <applications/applicationInstance.h>

#include "../../../../../../../../msgInfo/messageErrorOut.h"

#include "musicListItemWidget/labelItem.h"

MusicListTopWidget::MusicListTopWidget( QWidget *parent ) : BaseWidget( parent ) {
	titleVector.emplace_back( new LabelItem( tr( "歌名" ), this ) );
	titleVector.emplace_back( new LabelItem( tr( "主唱" ), this ) );
	titleVector.emplace_back( new LabelItem( tr( "时长" ), this ) );
	titleVector.emplace_back( new LabelItem( tr( "" ), this ) );
	currentDragItem = nullptr;
	permissonDrag = readyDrag = false;
	// 起始
	int stertX = 20;
	size_t count = titleVector.size( );
	auto data = titleVector.data( );
	size_t index = 0;
	for( ; index < count; ++index ) {
		data[ index ]->move( stertX, 0 );
		stertX += data[ index ]->width( );
	}
	minWidth = data[ 0 ]->x( ) + data[ 0 ]->width( );
	index -= 1;
	maxWidth = data[ index ]->x( ) + data[ index ]->width( );

	ApplicationEvenTrigger::connectApplicationInstanceEvent( [this] ( ApplicationInstance *application_instance, const ApplicationInstanceEventInfo &application_instance_event_info ) {
		auto eventType = application_instance_event_info.getEventType( );

		switch( eventType ) {
			case ApplicationInstanceEventInfo::EventType::Move_Global_Mouse_Pos : {
				// 检测是否在拖拽区间，并且设置准备符号
				// 在激活拖拽功能的情况下发送信号
				auto point = QCursor::pos( );
				point = mapFromGlobal( point );
				int currentX = point.x( );
				// 未进入拖拽状态
				if( permissonDrag == true && currentDragItem ) {
					int desX = currentX - dragOffsetX;
					if( desX <= minWidth )
						break;
					currentDragItem->move( desX, 0 );
					size_t count = titleVector.size( );
					auto data = titleVector.data( );
					size_t index = 1; // 跳过第一个
					for( ; index < count; ++index )
						if( data[ index ] == currentDragItem ) {

							size_t nextIndex = index + 1; // 跳过当前控制
							// 如果是末尾，则跳出
							if( nextIndex == count )
								break;

							// 获取当前组件的原始坐标
							int stertX = data[ index ]->x( ) + data[ index ]->width( );

							for( ; nextIndex < count; ++nextIndex ) {
								data[ nextIndex ]->move( stertX, 0 );
								stertX += data[ nextIndex ]->width( );
							}
							break;
						}
				} else {
					if( currentX > maxWidth || currentX < minWidth )
						break; // 超出检测限制
					int currentY = point.y( );
					if( currentY < 0 )
						break;
					int widgetHeight = height( );
					if( currentY > widgetHeight )
						break;
					currentDragItem = nullptr;
					size_t count = titleVector.size( );
					auto data = titleVector.data( );
					size_t index = 1; // 跳过第一个
					for( ; index < count; ++index ) {
						if( data[ index ]->x( ) + data[ index ]->getDrawDecollatorInterspace( ) > currentX ) {
							if( data[ index ]->x( ) > currentX )
								break; // 没有
							currentDragItem = data[ index ];
							break;
						}
					}
					if( currentDragItem == nullptr )
						break;
					readyDrag = true;
				}
			}

			break;
			case ApplicationInstanceEventInfo::EventType::Press_Global_Mouse_Pos :
				// 在准备符号为确定的情况下激活拖拽功能
				if( readyDrag && currentDragItem ) {
					auto point = QCursor::pos( );
					point = mapFromGlobal( point );
					int currentX = point.x( );
					int itemX = currentDragItem->x( );
					dragOffsetX = currentX - itemX;
					permissonDrag = true;
					MusicListTopWidgetEvent( this, MusicListTopWidgetEventInfo( MusicListTopWidgetEventInfo::EventType::Drag_Start_Item_Width ) );
				}
				break;
			case ApplicationInstanceEventInfo::EventType::Release_Global_Mouse_Pos :
				// 取消拖拽功能
				if( readyDrag && currentDragItem ) {
					// 更新最大宽度
					size_t count = titleVector.size( ) - 1;
					auto data = titleVector.data( );
					maxWidth = data[ count ]->x( ) + data[ count ]->width( );
					int currentWidth = this->width( );
					if( currentWidth != maxWidth )
						setFixedWidth( maxWidth );
					MusicListTopWidgetEvent( this, MusicListTopWidgetEventInfo( MusicListTopWidgetEventInfo::EventType::Drag_End_Item_Width ) );
				}
				currentDragItem = nullptr;
				permissonDrag = readyDrag = false; // 重置状态
				break;
		}
	} );
}
MusicListTopWidget::~MusicListTopWidget( ) {

}
const LabelItem * MusicListTopWidget::getTopItem( const size_t &item_index ) const {
	size_t count = titleVector.size( );
	if( count >= item_index )
		return nullptr;
	auto data = titleVector.data( );
	return data[ item_index ];
}
void MusicListTopWidget::resizeEvent( QResizeEvent *event ) {
	BaseWidget::resizeEvent( event );

}
void MusicListTopWidget::paintEvent( QPaintEvent *event ) {
	BaseWidget::paintEvent( event );
}
