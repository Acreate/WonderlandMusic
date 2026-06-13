#include "musicListMianWindow.h"

#include <QScrollArea>
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
	ApplicationEvenTrigger::connectMusicListTopWidgetEvent( [this] ( MusicListTopWidget *music_list_top_widget, const MusicListTopWidgetEventInfo &music_list_top_widget_event_info ) {
		auto eventType = music_list_top_widget_event_info.getEventType( );
		switch( eventType ) {
			case MusicListTopWidgetEventInfo::EventType::Drag_Start_Item_Width :
				break;
			case MusicListTopWidgetEventInfo::EventType::Drag_End_Item_Width :
			case MusicListTopWidgetEventInfo::EventType::Update_Item_Width : {
				int scrollWidth = musicScrollArea->width( );
				int musicListWidgetWidth = musicListWidget->width( );
				int modWidth = scrollWidth - musicListWidgetWidth;
				musicListWidgetWidth = music_list_top_widget->width( ) + modWidth;
				musicListWidget->setFixedWidth( musicListWidgetWidth );
			}
			break;
		}
	} );

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
