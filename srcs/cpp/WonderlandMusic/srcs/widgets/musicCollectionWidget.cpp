#include "musicCollectionWidget.h"

#include <QMouseEvent>
#include <QPainter>

#include "collectionItemWidget.h"
#include "collectionTopToolWidget.h"

#include "../applications/applicationEvenTrigger.h"
#include "../applications/applicationInstance.h"

MusicCollectionWidget::MusicCollectionWidget( QWidget *parent ) : BaseWidget( parent ) {
	subItemOffsetX = 10;
	this->collectionTopToolWidget = new CollectionTopToolWidget( this );
	this->collectionTopToolWidget->move( 0, 0 );
}
MusicCollectionWidget::~MusicCollectionWidget( ) {
	delete collectionTopToolWidget;
	size_t count = collectionItemWidgets.size( );
	if( count ) {
		auto data = collectionItemWidgets.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			delete data[ index ];
		collectionItemWidgets.clear( );
	}
}

bool MusicCollectionWidget::removeTargetItemWidget( CollectionItemWidget *target_item_widget ) {
	if( target_item_widget == nullptr )
		return false;
	size_t count = collectionItemWidgets.size( );
	if( count == 0 )
		return false;
	auto data = collectionItemWidgets.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == target_item_widget ) {
			auto y = data[ index ]->y( ); // 记录坐标
			delete data[ index ];
			count -= 1;
			for( ; index < count; ++index ) {
				data[ index ] = data[ index + 1 ];
				data[ index ]->move( subItemOffsetX, y );
				y += data[ index ]->height( );
			}
			collectionItemWidgets.resize( count );
			setFixedHeight( y );
			return true; // 匹配成功
		}
	return false; // 找不到
}

bool MusicCollectionWidget::appendItemWidget( const QString &item_name ) {
	auto newItem = new CollectionItemWidget( this );
	newItem->setTitleName( item_name );
	size_t count = collectionItemWidgets.size( );
	CollectionItemWidget **data;
	int targetY;
	CollectionItemWidget *collectionItemWidget;
	size_t index = 0;
	if( count ) {
		data = collectionItemWidgets.data( );
		// 查找是否重复名称
		for( ; index < count; ++index )
			if( data[ index ]->getTitleName( ) == item_name )
				return false; // 重复名称

		count -= 1;
		collectionItemWidget = data[ count ];

		targetY = collectionItemWidget->y( ) + collectionItemWidget->height( );
		newItem->move( subItemOffsetX, targetY );
	} else {
		targetY = collectionTopToolWidget->y( ) + collectionTopToolWidget->height( );
		newItem->move( subItemOffsetX, targetY );
	}
	collectionItemWidgets.emplace_back( newItem );
	data = collectionItemWidgets.data( );
	collectionItemWidget = data[ count ];
	int currentWidth = width( );
	int lastWidth = collectionItemWidget->width( ) + collectionItemWidget->x( );
	if( currentWidth < lastWidth )
		currentWidth = lastWidth;
	lastWidth = collectionItemWidget->height( ) + collectionItemWidget->y( );
	targetY = height( );
	if( targetY < lastWidth )
		targetY = lastWidth;
	setFixedSize( currentWidth, targetY );
	newItem->show( );
	return true;
}
bool MusicCollectionWidget::appendItemMusicInfoList( const CollectionItemWidget *append_target, const std::vector<MusicInfo *> &music_infos ) {
	return false;
}
void MusicCollectionWidget::resizeEvent( QResizeEvent *event ) {
	BaseWidget::resizeEvent( event );
}
void MusicCollectionWidget::mousePressEvent( QMouseEvent *event ) {
	BaseWidget::mousePressEvent( event );
	auto point = event->pos( );
	if( collectionTopToolWidget->geometry( ).contains( point ) ) {
		auto applicationInstance = ApplicationInstance::getApplicationInstance( );
		auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
		Qt::MouseButton mouseButton = event->button( );
		if( mouseButton == Qt::MouseButton::LeftButton )
			MusicCollectionWidgetEvent::triggerMusicCollectionWidgetEvent( applicationEvenTrigger, this, MusicCollectionWidgetEventInfo( MusicCollectionWidgetEventInfo::EventType::Mouse_Left_Press_Select_Top_Item ) );
		else if( mouseButton == Qt::MouseButton::RightButton )
			MusicCollectionWidgetEvent::triggerMusicCollectionWidgetEvent( applicationEvenTrigger, this, MusicCollectionWidgetEventInfo( MusicCollectionWidgetEventInfo::EventType::Mouse_Right_Press_Select_Top_Item ) );
	} else {
		size_t count = collectionItemWidgets.size( );
		if( count ) {
			auto data = collectionItemWidgets.data( );
			size_t index = 0;
			for( ; index < count; ++index )
				if( data[ index ]->geometry( ).contains( point ) ) {
					selectCurrentCollectionItemWidget = data[ index ];
					auto applicationInstance = ApplicationInstance::getApplicationInstance( );
					auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
					Qt::MouseButton mouseButton = event->button( );
					if( mouseButton == Qt::MouseButton::LeftButton )
						MusicCollectionWidgetEvent::triggerMusicCollectionWidgetEvent( applicationEvenTrigger, this, MusicCollectionWidgetEventInfo( MusicCollectionWidgetEventInfo::EventType::Mouse_Left_Press_Select_Sub_Item ) );
					else if( mouseButton == Qt::MouseButton::RightButton )
						MusicCollectionWidgetEvent::triggerMusicCollectionWidgetEvent( applicationEvenTrigger, this, MusicCollectionWidgetEventInfo( MusicCollectionWidgetEventInfo::EventType::Mouse_Right_Press_Select_Sub_Item ) );
					break;
				}
		}
	}
}
void MusicCollectionWidget::mouseReleaseEvent( QMouseEvent *event ) {
	BaseWidget::mouseReleaseEvent( event );
	auto point = event->pos( );
	if( collectionTopToolWidget->geometry( ).contains( point ) ) {
		auto applicationInstance = ApplicationInstance::getApplicationInstance( );
		auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
		Qt::MouseButton mouseButton = event->button( );
		if( mouseButton == Qt::MouseButton::LeftButton )
			MusicCollectionWidgetEvent::triggerMusicCollectionWidgetEvent( applicationEvenTrigger, this, MusicCollectionWidgetEventInfo( MusicCollectionWidgetEventInfo::EventType::Mouse_Left_Release_Select_Top_Item ) );
		else if( mouseButton == Qt::MouseButton::RightButton )
			MusicCollectionWidgetEvent::triggerMusicCollectionWidgetEvent( applicationEvenTrigger, this, MusicCollectionWidgetEventInfo( MusicCollectionWidgetEventInfo::EventType::Mouse_Right_Release_Select_Top_Item ) );
	} else {
		size_t count = collectionItemWidgets.size( );
		if( count ) {
			auto data = collectionItemWidgets.data( );
			size_t index = 0;
			for( ; index < count; ++index )
				if( data[ index ]->geometry( ).contains( point ) ) {
					auto applicationInstance = ApplicationInstance::getApplicationInstance( );
					auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
					Qt::MouseButton mouseButton = event->button( );
					if( mouseButton == Qt::MouseButton::LeftButton )
						MusicCollectionWidgetEvent::triggerMusicCollectionWidgetEvent( applicationEvenTrigger, this, MusicCollectionWidgetEventInfo( MusicCollectionWidgetEventInfo::EventType::Mouse_Left_Release_Select_Sub_Item ) );
					else if( mouseButton == Qt::MouseButton::RightButton )
						MusicCollectionWidgetEvent::triggerMusicCollectionWidgetEvent( applicationEvenTrigger, this, MusicCollectionWidgetEventInfo( MusicCollectionWidgetEventInfo::EventType::Mouse_Right_Release_Select_Sub_Item ) );
					break;
				}
		}
	}
	selectCurrentCollectionItemWidget = nullptr;
}
