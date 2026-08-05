#include "musicCentreWidget.h"

#include <QScrollArea>
#include <QScrollBar>

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
	userMutex = new UserMutex;
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

	musicTitleWidgetScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	auto verticalScrollBar = musicTitleWidgetScrollArea->verticalScrollBar( );
	if( verticalScrollBar )
		verticalScrollBar->setEnabled( false );
	auto horizontalScrollBar = musicTitleWidgetScrollArea->horizontalScrollBar( );
	auto scrollBar = musicListWidgetScrollArea->horizontalScrollBar( );

	connect( scrollBar, &QScrollBar::valueChanged, horizontalScrollBar, &QScrollBar::setValue );
	connect( scrollBar, &QScrollBar::rangeChanged, horizontalScrollBar, &QScrollBar::setRange );

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
	if( userMutex == nullptr )
		return false;
	// 当前组件高度
	int thisCentreHeight = this->height( );
	if( thisCentreHeight <= 0 )
		return false;
	// 当前组件宽度
	int thisCentreWidthWidth = this->width( );
	if( thisCentreWidthWidth <= 0 )
		return false;
	// 组件建议宽度
	int suggestWidth = musicfavoriteWidget->getSuggestWidth( );
	// 收藏组件的高度
	musicfavoriteWidgetScrollArea->setGeometry( 0, 0, suggestWidth, thisCentreHeight );
	musicfavoriteWidgetScrollArea->move( 0, 0 );

	// 剩余宽度
	int modWidth = thisCentreWidthWidth - suggestWidth;
	// 建议高度
	int suggestHeight = musicTitleWidget->getSuggestHeight( );
	// 标题宽度
	musicTitleWidgetScrollArea->setGeometry( suggestWidth, 0, modWidth, suggestHeight );

	// 工具面板高度
	int musicToolHeight = musicToolWidget->getSuggestHeight( );
	// 中心面板
	int modHeight = thisCentreHeight - ( musicToolHeight + suggestHeight );
	musicListWidgetScrollArea->setGeometry( suggestWidth, suggestHeight, modWidth, modHeight );

	modHeight = musicListWidgetScrollArea->y( ) + musicListWidgetScrollArea->height( );
	// 工具宽度
	musicToolWidget->setGeometry( suggestWidth, modHeight, modWidth, musicToolHeight );
	return true;
}
