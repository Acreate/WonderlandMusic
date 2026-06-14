#include "musicListTopWidget.h"

#include <QLabel>
#include <QPainter>
#include <QScrollArea>
#include <qevent.h>

#include <applications/applicationEvenTrigger.h>
#include <applications/applicationInstance.h>

#include "musicListWidget.h"

#include "../../../../../../../../msgInfo/messageErrorOut.h"

#include "musicListItemWidget/labelItem.h"

MusicListTopWidget::MusicListTopWidget( QWidget *parent ) : BaseWidget( parent ) {
	titleVector.emplace_back( new LabelItem( tr( "歌名" ), this ) );
	titleVector.emplace_back( new LabelItem( tr( "主唱" ), this ) );
	titleVector.emplace_back( new LabelItem( tr( "时长" ), this ) );
	titleVector.emplace_back( new LabelItem( tr( "" ), this ) );
	currentDragItem = nullptr;
	permissonDrag = readyDrag = false;
	minHeight = 0;
	int compHieght;
	// 起始
	int stertX = 20;
	size_t count = titleVector.size( );
	auto data = titleVector.data( );
	size_t index = 0;
	for( ; index < count; ++index ) {
		data[ index ]->move( stertX, 0 );
		stertX += data[ index ]->width( );
		compHieght = data[ index ]->height( );
		if( minHeight < compHieght )
			minHeight = compHieght;
	}
	minWidth = data[ 0 ]->x( ) + data[ 0 ]->width( );
	index -= 1;
	maxWidth = data[ index ]->x( ) + data[ index ]->width( );
	setFixedHeight( minHeight );

	for( index = 0; index < count; ++index )
		data[ index ]->setFixedHeight( minHeight );
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
					if( desX <= dragMinWidth )
						break;
					if( desX >= dragMaxWidth )
						break;
					currentDragItem->move( desX, 0 );
					size_t count = titleVector.size( );
					auto data = titleVector.data( );
					size_t index = 1; // 跳过第一个
					for( ; index < count; ++index )
						if( data[ index ] == currentDragItem ) {

							size_t restIndex;
							// 调整上一个组件的宽度
							restIndex = index - 1;
							int newWidth = desX - data[ restIndex ]->x( );
							data[ restIndex ]->setFixedWidth( newWidth );

							// 跳过当前控制
							restIndex = index + 1;
							// 如果是末尾，则跳出
							if( restIndex == count )
								break;

							// 获取当前组件的原始坐标
							newWidth = desX + data[ index ]->width( );

							for( ; restIndex < count; ++restIndex ) {
								data[ restIndex ]->move( newWidth, 0 );
								newWidth += data[ restIndex ]->width( );
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
							currentDragPrevItem = data[ index - 1 ];
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
					dragMinWidth = currentDragPrevItem->x( ) + currentDragPrevItem->getDrawDecollatorInterspace( );
					dragMaxWidth = this->width( );

					permissonDrag = true;
					MusicListTopWidgetEvent( this, MusicListTopWidgetEventInfo( MusicListTopWidgetEventInfo::EventType::Drag_Start_Item_Width ) );
				}
				break;
			case ApplicationInstanceEventInfo::EventType::Mouse_Leave_Pos :
			case ApplicationInstanceEventInfo::EventType::Release_Global_Mouse_Pos :
				// 取消拖拽功能
				if( readyDrag && currentDragItem ) {
					// 更新最大宽度
					size_t count = titleVector.size( ) - 1;
					auto data = titleVector.data( );
					maxWidth = data[ count ]->x( ) + data[ count ]->width( );
					int currentWidth = this->width( );
					auto parentObj = this->parent( );
					if( parentObj ) {
						auto scrollCast = qobject_cast< QScrollArea * >( parentObj );
						if( scrollCast ) {
							int currentX = scrollCast->viewport( )->width( );
							if( currentX > maxWidth )
								maxWidth = currentX;
						} else {
							auto qobjectCast = qobject_cast< QWidget * >( parentObj );
							if( qobjectCast ) {
								int currentX = qobjectCast->width( );
								if( currentX > maxWidth )
									maxWidth = currentX;
							}
						}
					}

					if( currentWidth != maxWidth )
						setFixedWidth( maxWidth );
					MusicListTopWidgetEvent( this, MusicListTopWidgetEventInfo( MusicListTopWidgetEventInfo::EventType::Drag_End_Item_Width ) );
				}
				currentDragItem = nullptr;
				permissonDrag = readyDrag = false; // 重置状态
				break;
		}
	} );

	// 每当加载完毕列表，都触发一次信号
	ApplicationEvenTrigger::connectMusicListWidgetEvent( [this] ( MusicListWidget *music_list_widget, const MusicListWidgetEventInfo &music_list_widget_event_info ) {
		auto eventType = music_list_widget_event_info.getEventType( );
		switch( eventType ) {
			case MusicListWidgetEventInfo::EventType::Load_Over :
				MusicListTopWidgetEvent( this, MusicListTopWidgetEventInfo( MusicListTopWidgetEventInfo::EventType::Update_Item_Width ) );
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
std::vector< const LabelItem * > MusicListTopWidget::getTitleVector( ) const {
	return std::vector< const LabelItem * >( titleVector.begin( ), titleVector.end( ) );
}

void MusicListTopWidget::resizeEvent( QResizeEvent *event ) {
	BaseWidget::resizeEvent( event );

}
void MusicListTopWidget::paintEvent( QPaintEvent *event ) {
	BaseWidget::paintEvent( event );
	/*QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::darkYellow );*/
}
