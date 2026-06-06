#include "playerDockWidget.h"

#include <QPainter>
#include <QPushButton>

#include "../contentWindow.h"

#include "playerDockWidget/playerBarWidget.h"
#include "playerDockWidget/playerWidget.h"
PlayerDockWidget::PlayerDockWidget( ContentWindow *parent ) : QDockWidget( parent ), contentWindow( parent ) {
	playerWidget = new PlayerWidget( this );
	setWidget( playerWidget );
	setContextMenuPolicy( Qt::NoContextMenu );
	setTitleBarWidget( new PlayerBarWidget( this ) );
}
size_t PlayerDockWidget::triggerPlayerWidgetEvent( PlayerWidget *sender, const PlayerWidgetEventInfo &info ) {
	return 0;
}
