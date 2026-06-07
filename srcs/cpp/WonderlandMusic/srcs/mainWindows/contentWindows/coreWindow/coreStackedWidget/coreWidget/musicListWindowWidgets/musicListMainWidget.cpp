#include "musicListMainWidget.h"

#include <QMouseEvent>
#include <QMenu>

#include "musicCollectionScrollArea.h"
#include "musicListScrollArea.h"

#include "../../../../../../applications/applicationEvenTrigger.h"
#include "../../../../../../applications/applicationInstance.h"
MusicListMainWidget::MusicListMainWidget( QWidget *parent ) : QWidget( parent ) {
	dragWidgetWidth = false;
	readyDragWidgetWidth = false;
	musicCollectionScrollArea = new MusicCollectionScrollArea( this );
	musicListScrollArea = new MusicListScrollArea( this );
	setMouseTracking( true );
	ApplicationInstance *instance = ApplicationInstance::getApplicationInstance( );
	auto applicationEvenTrigger = instance->getApplicationEvenTrigger( );
	connect( applicationEvenTrigger, &ApplicationEvenTrigger::triggerApplicationInstanceEvent, [this] ( auto, const ApplicationInstanceEventInfo &info ) {
		switch( info.getEventType( ) ) {
			case ApplicationInstanceEventInfo::EventType::Resize_Music_Widget_Width : {
				int newMusicWidgetWidth = info.getNewMusicWidgetWidth( );
				if( musicCollectionScrollArea->width( ) == newMusicWidgetWidth )
					return;
				musicCollectionScrollArea->setFixedWidth( newMusicWidgetWidth );
				updateSubWidgetSize( );
				auto applicationEvenTrigger = ApplicationInstance::getApplicationInstance( )->getApplicationEvenTrigger( );
				MusicListMainWidgetEvent::triggerMusicListMainWidgetEvent( applicationEvenTrigger, this, MusicListMainWidgetEventInfo( musicCollectionScrollArea->width( ) ) );
			}
			break;
		}
	} );

}
MusicListMainWidget::~MusicListMainWidget( ) {

}
void MusicListMainWidget::updateSubWidgetSize( ) {
	auto contentsRect = this->contentsRect( );
	int contentWidth = contentsRect.width( ) - contentsRect.x( );
	int contentHeight = contentsRect.height( ) - contentsRect.y( );

	int collWidth = musicCollectionScrollArea->width( );
	musicCollectionScrollArea->setGeometry( 0, 0, collWidth, contentHeight );
	musicListScrollArea->setGeometry( collWidth, 0, contentWidth - collWidth, contentHeight );
}
void MusicListMainWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	updateSubWidgetSize( );
}
void MusicListMainWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	auto pos = event->pos( );
	int x = pos.x( );
	if( dragWidgetWidth ) {
		if( x > 10 && x < contentsRect( ).width( ) - 10 ) {
			musicCollectionScrollArea->setFixedWidth( x );
			updateSubWidgetSize( );
		}
	} else {
		int width = musicCollectionScrollArea->width( );
		int abs = std::abs( x - width );
		if( abs < 5 ) {
			// 拉伸
			readyDragWidgetWidth = true;
			setCursor( Qt::SizeHorCursor );
		} else if( readyDragWidgetWidth == true ) {
			readyDragWidgetWidth = false;
			setCursor( Qt::ArrowCursor );
		}
	}
}
void MusicListMainWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	if( readyDragWidgetWidth )
		dragWidgetWidth = true;
}
void MusicListMainWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	if( readyDragWidgetWidth || dragWidgetWidth ) {
		setCursor( Qt::ArrowCursor );
		auto applicationEvenTrigger = ApplicationInstance::getApplicationInstance( )->getApplicationEvenTrigger( );
		MusicListMainWidgetEvent::triggerMusicListMainWidgetEvent( applicationEvenTrigger, this, MusicListMainWidgetEventInfo( musicCollectionScrollArea->width( ) ) );
		readyDragWidgetWidth = dragWidgetWidth = false;
	} else if( event->button( ) == Qt::MouseButton::RightButton ) {
		// todo : 发送弹出菜单信号
	}
}
