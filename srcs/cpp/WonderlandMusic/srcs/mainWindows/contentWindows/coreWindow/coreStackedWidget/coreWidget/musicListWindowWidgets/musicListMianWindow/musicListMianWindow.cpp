#include "musicListMianWindow.h"

#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>

#include <applications/applicationEvenTrigger.h>

#include "widget/musicListTopWidget.h"
#include "widget/musicListWidget.h"
MusicListMianWindow::MusicListMianWindow( QWidget *parent ) : BaseWidgetTypeMainWindow( parent ) {
	mainWidget = new QWidget( this );
	setCentralWidget( mainWidget );

	musicScrollArea = new QScrollArea( mainWidget );
	musicScrollArea->setWidgetResizable( true );
	musicScrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	musicScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );

	musicListWidget = new MusicListWidget( musicScrollArea );
	musicScrollArea->setWidget( musicListWidget );

	mainLayout = new QVBoxLayout( mainWidget );
	mainLayout->setContentsMargins( 0, 0, 0, 0 );
	mainLayout->setSpacing( 0 );
	mainLayout->addWidget( musicScrollArea );

	musicListTopWidget = new MusicListTopWidget( musicScrollArea );
	musicListTopWidget->move( 0, 0 );
	musicListTopWidget->show( );

	ApplicationEvenTrigger::connectMusicListTopWidgetEvent( [this] ( MusicListTopWidget *music_list_top_widget, const MusicListTopWidgetEventInfo &music_list_top_widget_event_info ) {
		auto eventType = music_list_top_widget_event_info.getEventType( );
		switch( eventType ) {
			case MusicListTopWidgetEventInfo::EventType::Drag_Start_Item_Width :
				break;
			case MusicListTopWidgetEventInfo::EventType::Drag_End_Item_Width :
			case MusicListTopWidgetEventInfo::EventType::Update_Item_Width : {

				int musicListWidgetWidth = music_list_top_widget->width( ) + musicScrollArea->verticalScrollBar( )->width( );
				musicListWidget->setFixedWidth( musicListWidgetWidth );
			}
			break;
		}
	} );

}
void MusicListMianWindow::resizeEvent( QResizeEvent *event ) {
	BaseMainWindow::resizeEvent( event );
	int musicWidth = musicListWidget->width( );
	int newWidth = musicScrollArea->width( );
	if( musicWidth < newWidth )
		musicWidth = newWidth;
	int musicVBarWidth = musicScrollArea->verticalScrollBar( )->width( );
	newWidth = musicWidth + musicVBarWidth;
	int oldWidth = musicListTopWidget->width( );
	if( oldWidth < newWidth )
		musicListTopWidget->setFixedWidth( newWidth );

}
