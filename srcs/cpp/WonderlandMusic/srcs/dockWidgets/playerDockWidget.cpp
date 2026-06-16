#include "playerDockWidget.h"

#include <QPainter>
#include <QPushButton>

#include "../widgets/playerBarWidget.h"
#include "../widgets/playerWidget.h"

#include "../mainWindows/contentWindow.h"
PlayerDockWidget::PlayerDockWidget( ContentWindow *parent ) : BaseDockWidget( parent ), contentWindow( parent ) {
	playerWidget = new PlayerWidget( this );
	setWidget( playerWidget );
	setTitleBarWidget( new PlayerBarWidget( this ) );
}
