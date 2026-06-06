#include "playerDockWidget.h"

#include <QPainter>
#include <QPushButton>

#include "../contentWindow.h"
PlayerDockWidget::PlayerDockWidget( ContentWindow *parent ) : QDockWidget( parent ), contentWindow( parent ) {
	controlStatus = ControlStatus::None;
	previousTrackBtn = new QPushButton( tr( "上一曲" ), this );
	nextTrackBtn = new QPushButton( tr( "下一曲" ), this );
	controlCurrentBtn = new QPushButton( tr( "播放" ), this );
	connect( controlCurrentBtn, &QPushButton::clicked, [this]( ) {
		switch( controlStatus ) {
			case ControlStatus::None :
			case ControlStatus::Player :
				controlCurrentBtn->setText( tr( "播放" ) );
				PlayerDockWidgetEvent::triggerPlayerDockWidgetEvent( contentWindow, this, PlayerDockWidgetEventInfo( PlayerDockWidgetEventInfo::EventType::Player ) );
				controlStatus = ControlStatus::Pause;
				break;
			case ControlStatus::Pause :
				controlCurrentBtn->setText( tr( "暂停" ) );
				PlayerDockWidgetEvent::triggerPlayerDockWidgetEvent( contentWindow, this, PlayerDockWidgetEventInfo( PlayerDockWidgetEventInfo::EventType::Pause ) );
				controlStatus = ControlStatus::Player;
				break;
		}
	} );
	connect( nextTrackBtn, &QPushButton::clicked, [this]( ) {

		controlStatus = ControlStatus::Player;
		controlCurrentBtn->setText( tr( "暂停" ) );
		PlayerDockWidgetEvent::triggerPlayerDockWidgetEvent( contentWindow, this, PlayerDockWidgetEventInfo( PlayerDockWidgetEventInfo::EventType::Next_Track ) );
	} );
	connect( previousTrackBtn, &QPushButton::clicked, [this]( ) {
		controlStatus = ControlStatus::Player;
		controlCurrentBtn->setText( tr( "暂停" ) );
		PlayerDockWidgetEvent::triggerPlayerDockWidgetEvent( contentWindow, this, PlayerDockWidgetEventInfo( PlayerDockWidgetEventInfo::EventType::Previous_Track ) );
	} );

	previousTrackBtn->move( 0, 0 );
	controlCurrentBtn->move( previousTrackBtn->width( ), 0 );
	nextTrackBtn->move( controlCurrentBtn->width( ) + previousTrackBtn->width( ), 0 );
}
