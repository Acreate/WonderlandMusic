#include "musicContreScrollArea.h"

#include <QScrollBar>

#include "../application/appInstance.h"
#include "../application/appUserInterfaceManage.h"

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
	disconnect( );
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
	Before_Init_Resource_App_Core_Ptr( musicContreWidget );
	Init_Resource_App_Core_Ptr( musicContreWidget );
	After_Init_Resource_App_Core_Ptr( musicContreWidget );

	return true;
}

bool MusicContreScrollArea::initBefore( ) {
	deleteResource( );
	musicContreWidget = new MusicContreWidget( this );
	setWidgetResizable( true );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	return true;
}

bool MusicContreScrollArea::initAfter( ) {
	setWidget( musicContreWidget );

	auto scrollBar = horizontalScrollBar( );
	auto uiManage = AppInstance::getAppInstance( )->getAppUserInterfaceManage( );
	connect( scrollBar, &QScrollBar::valueChanged, this, &MusicContreScrollArea::signal_horizontal_scroll_set_value );

	return true;
}
