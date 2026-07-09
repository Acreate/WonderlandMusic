#include "musicContreScrollArea.h"
#include <QMouseEvent>
#include <QScrollBar>
#include "../application/appInstance.h"
#include "../widget/musicContreWidget.h"

MusicContreScrollArea::MusicContreScrollArea( QWidget *parent ) : QScrollArea( parent ) {
}

bool MusicContreScrollArea::showFavorteMusicContreList( const QString &music_favorte_widget ) {
	return musicContreWidget->showFavorteMusicContreList( music_favorte_widget );
}

void MusicContreScrollArea::setItemWidth( const PlayerListTopWidget *player_list_top_widget ) {
	musicContreWidget->setItemPlayerListTopWidgetWidth( player_list_top_widget );
}

void MusicContreScrollArea::setItemVector( const std::vector< MusicItem * > &load_music_items ) {
	musicContreWidget->setMusicInfoVector( load_music_items );
}

void MusicContreScrollArea::setItemWidth( int widget_before_width, int splite_width, int index_width, int music_name_width, int music_singer_width, int music_duration_width, int widget_after_width ) {
	musicContreWidget->setItemWidth( widget_before_width, splite_width, index_width, music_name_width, music_singer_width, music_duration_width, widget_after_width );
}

MusicContreWidget * MusicContreScrollArea::getMusicContreWidget( ) const {
	return musicContreWidget;
}

bool MusicContreScrollArea::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( musicContreWidget );
	return true;
}

bool MusicContreScrollArea::getJsonData( QJsonObject &get_json_object ) const {
	return false;
}

bool MusicContreScrollArea::setJsonData( const QJsonObject &set_json_object ) {
	return false;
}

bool MusicContreScrollArea::init( ) {
	Init_Resource_App_Core_Ptr( musicContreWidget );

	return true;
}

bool MusicContreScrollArea::initBefore( ) {
	deleteResource( );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setWidgetResizable( true );
	musicContreWidget = new MusicContreWidget( this );
	Before_Init_Resource_App_Core_Ptr( musicContreWidget );
	return true;
}

bool MusicContreScrollArea::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( musicContreWidget );
	setWidget( musicContreWidget );
	auto scrollBar = horizontalScrollBar( );
	connect( scrollBar, &QScrollBar::valueChanged, this, &MusicContreScrollArea::signal_horizontal_scroll_set_value );
	viewport( )->setAttribute( Qt::WA_TransparentForMouseEvents, false );
	setMouseTracking( true );
	return true;
}

void MusicContreScrollArea::mouseDoubleClickEvent( QMouseEvent *mouse_event ) {
	QScrollArea::mouseDoubleClickEvent( mouse_event );
}

void MusicContreScrollArea::mouseMoveEvent( QMouseEvent *mouse_event ) {
	QScrollArea::mouseMoveEvent( mouse_event );
	if( musicContreWidget == nullptr )
		return;
	musicContreWidget->highlghtItem( musicContreWidget->mapFromParent( mouse_event->pos( ) ) );
}

void MusicContreScrollArea::mousePressEvent( QMouseEvent *mouse_event ) {
	QScrollArea::mousePressEvent( mouse_event );
}

void MusicContreScrollArea::mouseReleaseEvent( QMouseEvent *mouse_event ) {
	QScrollArea::mouseReleaseEvent( mouse_event );
	if( musicContreWidget == nullptr )
		return;
	Qt::MouseButton mouseButton = mouse_event->button( );
	switch( mouseButton ) {
		case Qt::MouseButton::LeftButton :
			musicContreWidget->selectorItem( musicContreWidget->mapFromParent( mouse_event->pos( ) ) );
			break;
		case Qt::MouseButton::RightButton :
			musicContreWidget->showItemMenu( musicContreWidget->mapFromParent( mouse_event->pos( ) ) );
			break;
	}
}
