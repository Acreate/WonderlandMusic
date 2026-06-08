#include "musicListMainWidget.h"

#include <QMouseEvent>
#include <QMenu>
#include <QScrollBar>

#include "musicCollectionScrollArea.h"
#include "musicListScrollArea.h"

#include "../../../../../../applications/applicationEvenTrigger.h"
#include "../../../../../../applications/applicationInstance.h"
MusicListMainWidget::MusicListMainWidget( QWidget *parent ) : BaseWidget( parent ) {

	minCollectionWidth = 10;
	isragWidgetWidth = readyDragWidgetWidth = false;
	musicCollectionScrollArea = new MusicCollectionScrollArea( this );
	musicListScrollArea = new MusicListScrollArea( this );

	ApplicationInstance *instance = ApplicationInstance::getApplicationInstance( );
	auto applicationEvenTrigger = instance->getApplicationEvenTrigger( );
	connect( applicationEvenTrigger, &ApplicationEvenTrigger::triggerApplicationInstanceEvent, [this] ( auto, const ApplicationInstanceEventInfo &info ) {
		switch( info.getEventType( ) ) {
			case ApplicationInstanceEventInfo::EventType::Init_Music_Widget_Width :
			case ApplicationInstanceEventInfo::EventType::Update_Music_Widget_Width : {
				int newMusicWidgetWidth = info.getNewMusicWidgetWidth( );
				if( musicCollectionScrollArea->width( ) == newMusicWidgetWidth )
					return;
				setMusicCollectionWidth( newMusicWidgetWidth );
			}
			break;
			case ApplicationInstanceEventInfo::EventType::Move_Global_Mouse_Pos : {
				auto pos = mapFromGlobal( QCursor::pos( ) );
				int x = pos.x( );
				int width = musicCollectionScrollArea->width( );
				if( isragWidgetWidth ) {
					if( width == x )
						return;
					setMusicCollectionWidth( x );
				} else {
					int abs = std::abs( x - width );
					if( abs < 5 ) {
						// 拉伸
						readyDragWidgetWidth = true;
						auto applicationEvenTrigger = ApplicationInstance::getApplicationInstance( )->getApplicationEvenTrigger( );
						MusicListMainWidgetEvent::triggerMusicListMainWidgetEvent( applicationEvenTrigger, this, MusicListMainWidgetEventInfo( MusicListMainWidgetEventInfo::EventType::Show_Draw_Mouse_ICO, musicCollectionScrollArea->width( ) ) );
					} else if( readyDragWidgetWidth == true ) {
						readyDragWidgetWidth = false;
						auto applicationEvenTrigger = ApplicationInstance::getApplicationInstance( )->getApplicationEvenTrigger( );
						MusicListMainWidgetEvent::triggerMusicListMainWidgetEvent( applicationEvenTrigger, this, MusicListMainWidgetEventInfo( MusicListMainWidgetEventInfo::EventType::HIDE_Draw_Mouse_ICO, musicCollectionScrollArea->width( ) ) );
					}
				}

			}
			break;
			case ApplicationInstanceEventInfo::EventType::Press_Global_Mouse_Pos :
				if( readyDragWidgetWidth ) {
					isragWidgetWidth = true;
					auto applicationEvenTrigger = ApplicationInstance::getApplicationInstance( )->getApplicationEvenTrigger( );
					MusicListMainWidgetEvent::triggerMusicListMainWidgetEvent( applicationEvenTrigger, this, MusicListMainWidgetEventInfo( MusicListMainWidgetEventInfo::EventType::Start_Draw_Music_Widget_Width, musicCollectionScrollArea->width( ) ) );
				}
				break;
			case ApplicationInstanceEventInfo::EventType::Release_Global_Mouse_Pos : {
				ApplicationInstance *applicationInstance = ApplicationInstance::getApplicationInstance( );
				if( readyDragWidgetWidth ) {
					isragWidgetWidth = readyDragWidgetWidth = false;
					auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
					MusicListMainWidgetEvent::triggerMusicListMainWidgetEvent( applicationEvenTrigger, this, MusicListMainWidgetEventInfo( MusicListMainWidgetEventInfo::EventType::Over_Draw_Music_Widget_Width, musicCollectionScrollArea->width( ) ) );
				} else {
					auto mouseButtons = applicationInstance->mouseButtons( );
					if( mouseButtons.testFlag( Qt::RightButton ) ) {
						// todo : 发送弹出菜单信号
					}
				}
			}
			break;
		}
	} );

}
MusicListMainWidget::~MusicListMainWidget( ) {

}
int MusicListMainWidget::getMusicCollectionWidth( ) const {
	return musicCollectionScrollArea->width( );
}
void MusicListMainWidget::setMusicCollectionWidth( int new_width ) {
	if( minCollectionWidth > new_width || minCollectionWidth > ( currentWidgetWidth - new_width ) )
		return;
	musicCollectionScrollArea->setGeometry( 0, 0, new_width, currentWidgetHeight );
	musicListScrollArea->setGeometry( new_width, 0, currentWidgetWidth - new_width, currentWidgetHeight );
}
void MusicListMainWidget::updateSubWidgetSize( ) {
	setMusicCollectionWidth( musicCollectionScrollArea->width( ) );
}
void MusicListMainWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	auto *view = musicCollectionScrollArea->viewport( );
	minCollectionWidth = 10 + musicCollectionScrollArea->width( ) - view->width( );
	currentContentsRect = this->contentsRect( );
	currentWidgetWidth = currentContentsRect.width( ) - currentContentsRect.x( );
	currentWidgetHeight = currentContentsRect.height( ) - currentContentsRect.y( );
	updateSubWidgetSize( );
}
