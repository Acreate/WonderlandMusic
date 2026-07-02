#include "musicContreWidget.h"

#include "../window/playerWindow.h"

MusicContreWidget::MusicContreWidget( PlayerWindow *player_window ) : QWidget( player_window ), playerWindow( player_window ) {
}

bool MusicContreWidget::deleteResource( ) {
	return false;
}

bool MusicContreWidget::init( ) {
	playListWidgetScrollArea->setWidget( playListWidget );

	favoriteWidget = new FavoriteWidget( this );
	playListWidgetScrollArea = new QScrollArea( this );

	playListWidget = new PlayerListWidget( this );
	playListWidgetScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	playListWidgetScrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	playListWidgetScrollArea->setWidgetResizable( true );
	playListWidgetScrollArea->setWindowFlags( Qt::WindowType::Widget );

	return false;
}
