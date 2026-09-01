#include "musicTitleWidget.h"

#include <QPainter>
#include <qevent.h>

#include <component/musicWindow/musicCentreWidget/musicCentreWidget.h>

#include <application/appInstance/appDataManage.h>
#include <application/appInstance/appUserInterfaceManage/appDrawManage.h>
#include <application/appInstance/appUserInterfaceManage/appDrawManage/appRenderImage.h>

#include <component/musicWindow/interface/info/iMusicItemWidthInfo.h>

#include <head/release_macro.h>
#include <head/result_message_out.h>

#include <mutex/userMutex.h>

#include <tools/instanceTools.h>

#include <musicImpement/info/musicItemWidthInfo.h>

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
	isDrag = false;
	currentCursor = Qt::ArrowCursor;
	setCursor( currentCursor );
	resuntIndexVarPtr = nullptr;
	orgX = resultIndex = 0;
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
	event->ignore( );
	if( userMutex == nullptr )
		return;
	if( musicItemWidthInfo == nullptr )
		return;
	userMutex->lock( );
	if( isDrag == false ) {
		auto point = event->pos( );
		orgX = point.x( );
		if( musicItemWidthInfo->getPosItemWidthPtr( resuntIndexVarPtr, resultIndex, orgX ) == true ) {
			if( currentCursor != Qt::SizeHorCursor ) {
				currentCursor = Qt::SizeHorCursor;
				setCursor( currentCursor );
			}
			userMutex->unlock( );
			return;
		}

		resuntIndexVarPtr = nullptr;
		if( currentCursor != Qt::ArrowCursor ) {
			currentCursor = Qt::ArrowCursor;
			setCursor( Qt::ArrowCursor );
		}
		userMutex->unlock( );
		event->accept( );
		return;
	} else if( resuntIndexVarPtr != nullptr ) {
		auto point = event->pos( );
		int newWidth = point.x( ) - orgX + orgWidth;
		bool posItemWidthPtrVar = setPosItemWidthPtrVar( resuntIndexVarPtr, resultIndex, newWidth );
		if( posItemWidthPtrVar == false )
			Result_Void_Messag_Ptr_Out_Args( this, tr( "设置 %1 下标宽度异常" ).arg( resultIndex ) );
		userMutex->unlock( );
		event->accept( );
		if( posItemWidthPtrVar )
			autoLayout( );
		return;
	}
	userMutex->unlock( );
	event->accept( );
}
void MusicTitleWidget::mousePressEvent( QMouseEvent *event ) {
	event->ignore( );
	if( userMutex == nullptr )
		return;
	if( musicItemWidthInfo == nullptr )
		return;
	userMutex->lock( );
	if( resuntIndexVarPtr ) {
		orgWidth = *resuntIndexVarPtr;
		orgX = event->pos( ).x( );
		isDrag = true;
	}
	userMutex->unlock( );
	event->accept( );
}
void MusicTitleWidget::mouseReleaseEvent( QMouseEvent *event ) {
	event->ignore( );
	if( userMutex == nullptr )
		return;
	if( musicItemWidthInfo == nullptr )
		return;
	userMutex->lock( );
	if( resuntIndexVarPtr ) {
		setCursor( Qt::ArrowCursor );
	}
	resuntIndexVarPtr = nullptr;
	isDrag = false;
	orgWidth = 0;
	userMutex->unlock( );
	event->accept( );
}
bool MusicTitleWidget::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
	renderBuff = new QImage;
	setMouseTracking( true );
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
