#include "musicCentreWidget.h"

#include <QScrollArea>

#include <head/after_init_macro.h>
#include <head/before_init_macro.h>
#include <head/init_macro.h>
#include <head/release_macro.h>

#include <mutex/userMutex.h>

#include "../musicWindow.h"

#include "../musicCentreWidgetInfo/musicCentreWidgetInfo.h"

#include "musicListWidget/musicListWidget.h"

#include "musicTitleWidget/musicTitleWidget.h"

#include "musicToolWidget/musicToolWidget.h"

#include "musicfavoriteWidget/musicfavoriteWidget.h"

MusicCentreWidget::MusicCentreWidget( MusicWindow *parent ) : QWidget( parent ), musicWindow( parent ) {
}
MusicCentreWidget::~MusicCentreWidget( ) {
	deleteResource( );
}
bool MusicCentreWidget::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	unSafetyClearShow( );
	musicfavoriteWidgetScrollArea->takeWidget( );
	Delete_Resource_App_Core_Ptr( musicfavoriteWidgetScrollArea );
	musicListWidgetScrollArea->takeWidget( );
	Delete_Resource_App_Core_Ptr( musicListWidgetScrollArea );
	musicTitleWidgetScrollArea->takeWidget( );
	Delete_Resource_App_Core_Ptr( musicTitleWidgetScrollArea );

	Delete_Resource_App_Core_Ptr( musicfavoriteWidget );
	Delete_Resource_App_Core_Ptr( musicTitleWidget );
	Delete_Resource_App_Core_Ptr( musicListWidget );
	Delete_Resource_App_Core_Ptr( musicToolWidget );
	Delete_Resource_App_Core_Ptr( musicCentreWidgetInfo );

	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}
bool MusicCentreWidget::unSafetyClearShow( ) {
	return true;
}
void MusicCentreWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );

	calculateSize( );
}
QScrollArea * MusicCentreWidget::createControlScrollArea( QWidget *widget ) {
	auto scrollArea = new QScrollArea( this );
	scrollArea->setWidgetResizable( true );
	scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	scrollArea->setWidget( widget );
	return scrollArea;
}
bool MusicCentreWidget::getMusicCentreWidgetInfo( MusicCentreWidgetInfo &music_centre_widget_info ) const {
	if( this->musicCentreWidgetInfo == nullptr )
		return false;
	music_centre_widget_info = *this->musicCentreWidgetInfo;
	return true;
}
bool MusicCentreWidget::setMusicCentreWidgetInfo( MusicCentreWidgetInfo &music_centre_widget_info ) {
	if( this->musicCentreWidgetInfo == nullptr )
		return false;
	*this->musicCentreWidgetInfo = music_centre_widget_info;
	return calculateSize( );
}
bool MusicCentreWidget::initBefore( ) {
	deleteResource( );
	musicCentreWidgetInfo = new MusicCentreWidgetInfo;
	musicfavoriteWidget = new MusicfavoriteWidget( this );
	musicTitleWidget = new MusicTitleWidget( this );
	musicListWidget = new MusicListWidget( this );
	musicToolWidget = new MusicToolWidget( this );
	Before_Init_Resource_App_Core_Ptr( musicfavoriteWidget );
	Before_Init_Resource_App_Core_Ptr( musicTitleWidget );
	Before_Init_Resource_App_Core_Ptr( musicListWidget );
	Before_Init_Resource_App_Core_Ptr( musicToolWidget );
	return true;
}
bool MusicCentreWidget::init( ) {
	Init_Resource_App_Core_Ptr( musicfavoriteWidget );
	Init_Resource_App_Core_Ptr( musicTitleWidget );
	Init_Resource_App_Core_Ptr( musicListWidget );
	Init_Resource_App_Core_Ptr( musicToolWidget );
	return true;
}
bool MusicCentreWidget::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( musicfavoriteWidget );
	After_Init_Resource_App_Core_Ptr( musicTitleWidget );
	After_Init_Resource_App_Core_Ptr( musicListWidget );
	After_Init_Resource_App_Core_Ptr( musicToolWidget );

	musicfavoriteWidgetScrollArea = createControlScrollArea( musicfavoriteWidget );
	musicTitleWidgetScrollArea = createControlScrollArea( musicTitleWidget );
	musicListWidgetScrollArea = createControlScrollArea( musicListWidget );

	musicfavoriteWidgetScrollArea->show( );
	musicTitleWidgetScrollArea->show( );
	musicListWidgetScrollArea->show( );
	musicToolWidget->show( );
	calculateSize( );

	return true;
}
void MusicCentreWidget::clearShowMusic( ) {
}
bool MusicCentreWidget::calculateSize( ) {
	return true;
}
