#include "playerDockWidget.h"

#include <QPainter>
#include <QPushButton>

#include "../contentWindow.h"

#include "playerDockWidget/playerBarWidget.h"
#include "playerDockWidget/playerWidget.h"
PlayerDockWidget::PlayerDockWidget( ContentWindow *parent ) : BaseDockWidget( parent ), contentWindow( parent ) {
	playerWidget = new PlayerWidget( this );
	setWidget( playerWidget );
	setTitleBarWidget( new PlayerBarWidget( this ) );
}
