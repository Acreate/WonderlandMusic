#include "playerWidget.h"

#include <QPushButton>

#include "../playerDockWidget.h"
PlayerWidget::PlayerWidget( PlayerDockWidget *parent ) : QWidget( parent ), playerDockWidget( parent ) {
	controlStatus = ControlStatus::None;
	previousTrackBtn = new QPushButton( tr( "上一曲" ), this );
	nextTrackBtn = new QPushButton( tr( "下一曲" ), this );
	controlCurrentBtn = new QPushButton( tr( "播放" ), this );
	connect( controlCurrentBtn, &QPushButton::clicked, [this]( ) {
		switch( controlStatus ) {
			case ControlStatus::None :
			case ControlStatus::Player :
				controlCurrentBtn->setText( tr( "播放" ) );
				PlayerWidgetEvent::triggerPlayerWidgetEvent( playerDockWidget, this, PlayerWidgetEventInfo( PlayerWidgetEventInfo::EventType::Player ) );
				controlStatus = ControlStatus::Pause;
				break;
			case ControlStatus::Pause :
				controlCurrentBtn->setText( tr( "暂停" ) );
				PlayerWidgetEvent::triggerPlayerWidgetEvent( playerDockWidget, this, PlayerWidgetEventInfo( PlayerWidgetEventInfo::EventType::Pause ) );
				controlStatus = ControlStatus::Player;
				break;
		}
	} );
	connect( nextTrackBtn, &QPushButton::clicked, [this]( ) {
		controlStatus = ControlStatus::Player;
		controlCurrentBtn->setText( tr( "暂停" ) );
		PlayerWidgetEvent::triggerPlayerWidgetEvent( playerDockWidget, this, PlayerWidgetEventInfo( PlayerWidgetEventInfo::EventType::Next_Track ) );
	} );
	connect( previousTrackBtn, &QPushButton::clicked, [this]( ) {
		controlStatus = ControlStatus::Player;
		controlCurrentBtn->setText( tr( "暂停" ) );
		PlayerWidgetEvent::triggerPlayerWidgetEvent( playerDockWidget, this, PlayerWidgetEventInfo( PlayerWidgetEventInfo::EventType::Previous_Track ) );
	} );

	previousTrackBtn->move( 0, 0 );
	auto preWidth = previousTrackBtn->width( );
	controlCurrentBtn->move( preWidth, 0 );
	auto conWidth = controlCurrentBtn->width( );
	nextTrackBtn->move( conWidth + preWidth, 0 );
	auto minWidth = nextTrackBtn->width( ) + nextTrackBtn->x( );
	setMinimumWidth( minWidth );
	auto preHeight = previousTrackBtn->height( );
	auto conHeight = controlCurrentBtn->height( );
	auto nextHeight = nextTrackBtn->height( );
	if( preHeight < conHeight )
		preHeight = conHeight;
	if( preHeight < nextHeight )
		preHeight = nextHeight;
	setFixedHeight( preHeight );
}
