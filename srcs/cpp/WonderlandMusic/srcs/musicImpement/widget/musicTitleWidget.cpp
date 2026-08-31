#include "musicTitleWidget.h"

#include <QPainter>
#include <qevent.h>

#include <component/musicWindow/musicCentreWidget/musicCentreWidget.h>

#include "../../application/appInstance/appDataManage.h"
#include "../../application/appInstance/appUserInterfaceManage/appDrawManage.h"
#include "../../application/appInstance/appUserInterfaceManage/appDrawManage/appRenderImage.h"

#include "../../head/release_macro.h"

#include "../../info/musicItemWidthInfo.h"

#include "../../mutex/userMutex.h"

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
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	resuntIndexVarPtr = nullptr;
	resultIndex = 0;
	auto musicCentreWidget = getMusicCentreWidget( );
	if( musicCentreWidget )
		musicCentreWidget->removeMusicTitleWidget( this );
	Delete_Resource_App_Core_Ptr( renderBuff );
	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}
void MusicTitleWidget::paintEvent( QPaintEvent *event ) {
	if( userMutex == nullptr )
		return;
	if( renderBuff == nullptr )
		return;
	userMutex->lock( );
	QPainter painter( this );
	painter.setClipRect( event->rect( ) );
	painter.drawImage( 0, 0, *renderBuff );
	painter.setClipping( false );
	userMutex->unlock( );
}
void MusicTitleWidget::mouseMoveEvent( QMouseEvent *event ) {
	if( userMutex == nullptr )
		return;
	if( musicItemWidthInfo == nullptr )
		return;
	userMutex->lock( );
	if( musicItemWidthInfo->getPosItemWidthPtr( resuntIndexVarPtr, resultIndex, event->pos( ) ) == false )
		resuntIndexVarPtr = nullptr;
	userMutex->unlock( );
}
void MusicTitleWidget::mousePressEvent( QMouseEvent *event ) {
	if( userMutex == nullptr )
		return;
	if( musicItemWidthInfo == nullptr )
		return;
	userMutex->lock( );
	if( resuntIndexVarPtr ) {
		setCursor( Qt::SizeHorCursor );
	}
	userMutex->unlock( );
}
void MusicTitleWidget::mouseReleaseEvent( QMouseEvent *event ) {
	if( userMutex == nullptr )
		return;
	if( musicItemWidthInfo == nullptr )
		return;
	userMutex->lock( );
	if( resuntIndexVarPtr ) {
		setCursor( Qt::ArrowCursor );
	}
	resuntIndexVarPtr = nullptr;
	userMutex->unlock( );
}
bool MusicTitleWidget::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
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
	if( userMutex == nullptr )
		return false;
	auto appDrawManage = InstanceTools::getAppDrawManage( );
	if( appDrawManage == nullptr )
		return false;
	userMutex->lock( );
	if( musicItemWidthInfo == nullptr ) {
		AppDataManage *appDataManage = InstanceTools::getAppDataManage( );
		if( appDataManage == nullptr )
			return userMutex->result_unlock( false );
		musicItemWidthInfo = appDataManage->getMusicItemWidthInfo( );
	}
	auto calculateMinWidth = musicItemWidthInfo->getCalculateMinWidth( );
	auto suggestHeight = musicItemWidthInfo->getSuggestHeight( );
	*renderBuff = QImage( calculateMinWidth, suggestHeight, QImage::Format_RGBA8888 );
	if( renderBuff->isNull( ) )
		return userMutex->result_unlock( false );
	renderBuff->fill( 0 );
	QPainter painter( renderBuff );
	auto appRenderImage = appDrawManage->getAppRenderImage( );
	QFont font = *appRenderImage->getFont( );
	painter.setFont( font );
	painter.setBrush( QColor( 112, 128, 144 ) );
	if( appDrawManage->drawTitle( painter, musicItemWidthInfo, 0, 0 ) == false )
		return userMutex->result_unlock( false );
	userMutex->unlock( );
	repaint( );
	return true;
}
