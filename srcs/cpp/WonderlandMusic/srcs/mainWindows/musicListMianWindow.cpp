#include "musicListMianWindow.h"

#include <QPainter>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <qcoreevent.h>

#include <applications/applicationEvenTrigger.h>

#include "../widgets/musicListTopWidget.h"
#include "../widgets/musicListWidget.h"

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
	auto scrollBar = musicScrollArea->horizontalScrollBar( );
	connect( scrollBar, &QScrollBar::valueChanged, [this] ( int new_var ) {
		musicListTopWidget->move( -new_var, 0 );
	} );
}
void MusicListMianWindow::resizeEvent( QResizeEvent *event ) {
	BaseMainWindow::resizeEvent( event );
	int topWidth = musicListTopWidget->width( );
	int thisWidth = height( );
	if( thisWidth > topWidth )
		musicListTopWidget->setFixedWidth( thisWidth );
}
void MusicListMianWindow::showEvent( QShowEvent *event ) {
	BaseWidgetTypeMainWindow::showEvent( event );
}
void MusicListMianWindow::paintEvent( QPaintEvent *event ) {
	BaseWidgetTypeMainWindow::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::white );
}
bool MusicListMianWindow::eventFilter( QObject *watched, QEvent *event ) {

	bool eventFilter;
	if( watched == musicListWidget ) {
		auto type = event->type( );
		switch( type ) {
			case QEvent::Resize : {
				eventFilter = BaseWidgetTypeMainWindow::eventFilter( watched, event );
				int musicListWidth = musicListWidget->width( );
				QScrollBar *scrollBar = musicScrollArea->verticalScrollBar( );
				int scrollBarWidth = scrollBar->width( );
				int newWidth = musicListWidth + scrollBarWidth;
				int oldWidth = musicListTopWidget->width( );
				if( oldWidth < newWidth )
					musicListTopWidget->setFixedWidth( newWidth );
			}
			break;
			case QEvent::Paint : {

				QPainter painter( musicListWidget );
				painter.fillRect( contentsRect( ), Qt::GlobalColor::white );
				event->accept( );
				return true;
			}
			break;
		}
	} else if( watched == musicListWidget ) {
		auto type = event->type( );
		switch( type ) {
			case QEvent::Paint : {
				QPainter painter( musicListTopWidget );
				painter.fillRect( contentsRect( ), Qt::GlobalColor::white );
				event->accept( );
				return true;
			}
			break;
		}
	}
	return eventFilter;
}
