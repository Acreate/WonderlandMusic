#include "musicItemWidget.h"

#include <QLabel>
#include <QPainter>
#include <qevent.h>

#include <component/musicWindow/interface/info/iMusicItemWidthInfo.h>
#include <component/musicWindow/interface/widget/iMusicListWidget.h>
#include <component/musicWindow/interface/widget/iMusicTitleWidget.h>

#include "../../application/appInstance/appUserInterfaceManage/appDrawManage.h"
#include "../../application/appInstance/appUserInterfaceManage/appDrawManage/appRenderImage.h"

#include "../../component/musicWindow/interface/widget/iMusicCentreWidget.h"

#include "../../tools/instanceTools.h"
MusicItemWidget::MusicItemWidget( ) {
	appendTypeInfo( this );
	hide( );
	setMouseTracking( true );
}
MusicItemWidget::~MusicItemWidget( ) {
}
bool MusicItemWidget::renderToBuff( ) {
	return updateLayout( );
}
bool MusicItemWidget::setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return true;
}
IMusicCentreWidget * MusicItemWidget::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
bool MusicItemWidget::updateLayout( ) {
	if( musicCentreWidget == nullptr )
		return false;
	auto musicTitleWidget = musicCentreWidget->getMusicTitleWidget( );
	if( musicTitleWidget == nullptr )
		return false;
	auto iMusicItemWidthInfo = musicTitleWidget->getIMusicItemWidthInfo( );
	if( iMusicItemWidthInfo == nullptr )
		return false;
	AppDrawManage *appDrawManage = InstanceTools::getAppDrawManage( );
	if( appDrawManage == nullptr )
		return false;
	auto appRenderImage = appDrawManage->getAppRenderImage( );
	if( appRenderImage == nullptr )
		return false;
	auto font = appRenderImage->getFont( );
	if( font == nullptr )
		return false;
	auto renderBuff = getRenderBuff( );
	int calculateMinWidth = iMusicItemWidthInfo->getCalculateMinWidth( );
	int suggestHeight = iMusicItemWidthInfo->getSuggestHeight( );
	*renderBuff = QImage( calculateMinWidth, suggestHeight, QImage::Format_RGBA8888 );
	renderBuff->fill( 0 );
	QPainter painter;
	painter.begin( renderBuff );
	painter.setPen( Qt::GlobalColor::black );
	painter.setBrush( Qt::GlobalColor::red );
	painter.setFont( *font );
	appDrawManage->drawItem( painter, musicItem, iMusicItemWidthInfo );
	painter.end( );
	return true;
}
bool MusicItemWidget::setMusicListWidget( IMusicListWidget *music_list_widget ) {
	musicListWidget = music_list_widget;
	do {
		if( music_list_widget == nullptr )
			break;
		auto parent = music_list_widget->toWidget( );
		if( parent == nullptr )
			break;
		setParent( parent );
		show( );
		return true;
	} while( false );
	hide( );
	setParent( nullptr );
	return true;
}
bool MusicItemWidget::bindMusicItem( IMusicItem *music_item ) {
	musicItem = music_item;
	return true;
}
void MusicItemWidget::paintEvent( QPaintEvent *event ) {
	QPainter painter( this );
	painter.setClipRect( event->rect( ) );
	auto renderBuff = getRenderBuff( );
	painter.drawImage( 0, 0, *renderBuff );
}
void MusicItemWidget::mouseMoveEvent( QMouseEvent *event ) {
	event->ignore( );
}
void MusicItemWidget::mousePressEvent( QMouseEvent *event ) {
	event->ignore( );
}
void MusicItemWidget::mouseReleaseEvent( QMouseEvent *event ) {
	event->ignore( );
}
IMusicItem * MusicItemWidget::getBindMusicItem( ) const {
	return musicItem;
}
QWidget * MusicItemWidget::toWidget( ) {
	return this;
}
