#include "musicTitleWidget.h"

#include <QPainter>
#include <qevent.h>

#include <component/musicWindow/musicCentreWidget/musicCentreWidget.h>

#include "../../application/appInstance/appDataManage.h"
#include "../../application/appInstance/appUserInterfaceManage/appDrawManage.h"
#include "../../application/appInstance/appUserInterfaceManage/appDrawManage/appRenderImage.h"

#include "../../head/release_macro.h"

#include "../../info/musicItemWidthInfo.h"

#include "../../tools/instanceTools.h"

MusicTitleWidget::MusicTitleWidget( ) {
	appendTypeInfo( this );
}
MusicTitleWidget::~MusicTitleWidget( ) {
	deleteResource( );
}
bool MusicTitleWidget::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}
bool MusicTitleWidget::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
bool MusicTitleWidget::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return true;
}
bool MusicTitleWidget::deleteResource( ) {
	auto musicCentreWidget = getMusicCentreWidget( );
	if( musicCentreWidget )
		musicCentreWidget->removeMusicTitleWidget( this );
	Delete_Resource_App_Core_Ptr( renderBuff );
	return true;
}
void MusicTitleWidget::paintEvent( QPaintEvent *event ) {
	if( renderBuff == nullptr )
		return;
	QPainter painter( this );
	painter.setClipRect( event->rect( ) );
	painter.drawImage( 0, 0, *renderBuff );
	painter.setClipping( false );
}
bool MusicTitleWidget::initBefore( ) {
	deleteResource( );
	renderBuff = new QImage;
	return true;
}
bool MusicTitleWidget::init( ) {
	return true;
}
bool MusicTitleWidget::initAfter( ) {
	if( autoLayout( ) == false )
		return false;
	return true;
}
QWidget * MusicTitleWidget::toWidget( ) {
	return this;
}
MusicCentreWidget * MusicTitleWidget::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
bool MusicTitleWidget::setIMusicItemWidthInfo( IMusicItemWidthInfo *music_item_width_info ) {
	musicItemWidthInfo = music_item_width_info;
	return true;
}
IMusicItemWidthInfo * MusicTitleWidget::getIMusicItemWidthInfo( ) const {
	return musicItemWidthInfo;
}
bool MusicTitleWidget::autoLayout( ) {
	auto appDrawManage = InstanceTools::getAppDrawManage( );
	if( appDrawManage == nullptr )
		return false;
	if( musicItemWidthInfo == nullptr ) {
		AppDataManage *appDataManage = InstanceTools::getAppDataManage( );
		if( appDataManage == nullptr )
			return false;
		musicItemWidthInfo = appDataManage->getMusicItemWidthInfo( );
	}
	auto calculateMinWidth = musicItemWidthInfo->getCalculateMinWidth( );
	auto suggestHeight = musicItemWidthInfo->getSuggestHeight( );
	*renderBuff = QImage( calculateMinWidth, suggestHeight, QImage::Format_RGBA8888 );
	if( renderBuff->isNull( ) )
		return false;
	renderBuff->fill( 0 );
	QPainter painter( renderBuff );
	auto appRenderImage = appDrawManage->getAppRenderImage( );
	painter.setFont( *appRenderImage->getFont( ) );
	if( appDrawManage->drawTitle( painter, musicItemWidthInfo, 0, 0 ) == false )
		return false;
	repaint( );
	return true;
}
