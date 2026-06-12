#include "musicListMianWindow.h"

#include <QScrollArea>
#include <QVBoxLayout>

#include "widget/musicListTopWidget.h"
#include "widget/musicListWidget.h"
MusicListMianWindow::MusicListMianWindow( QWidget *parent ) : BaseWidgetTypeMainWindow( parent ) {
	mainWidget = new QWidget( this );
	setCentralWidget( mainWidget );

	musicScrollArea = new QScrollArea( mainWidget );
	musicScrollArea->setWidgetResizable( true );
	musicScrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	musicScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

	musicListWidget = new MusicListWidget( musicScrollArea );
	musicScrollArea->setWidget( musicListWidget );

	mainLayout = new QVBoxLayout( mainWidget );
	mainLayout->setContentsMargins( 0, 0, 0, 0 );
	mainLayout->setSpacing( 0 );

	musicListTopWidget = new MusicListTopWidget( musicScrollArea );
	musicListTopWidget->move( 0, 0 );
	musicListTopWidget->show( );
	mainLayout->addWidget( musicScrollArea );
}
void MusicListMianWindow::resizeEvent( QResizeEvent *event ) {
	BaseMainWindow::resizeEvent( event );
}
