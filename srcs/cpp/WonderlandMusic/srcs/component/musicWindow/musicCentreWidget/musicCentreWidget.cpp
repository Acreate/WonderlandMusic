#include "musicCentreWidget.h"

#include <QJsonObject>
#include <QScrollArea>

#include <head/after_init_macro.h>
#include <head/before_init_macro.h>
#include <head/init_macro.h>
#include <head/release_macro.h>

#include <mutex/userMutex.h>

#include "../musicWindow.h"

#include "../transparencyScrollBar/transparencyScrollBar.h"

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
	//Delete_Resource_App_Core_Ptr( transparencyScrollBar );
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
void MusicCentreWidget::updateTitleWidthInfo( MusicTitleWidget *music_title_widget, int interval_width, int separator_width, int music_code_width, int music_name_width, int music_singer_name_width, int music_duration_time_width ) {
	// todo : ...
}
bool MusicCentreWidget::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
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

	musicTitleWidgetScrollArea->setVerticalScrollBar( new TransparencyScrollBar( this ) );
	musicTitleWidgetScrollArea->setMouseTracking( true );
	musicTitleWidgetScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	auto verticalScrollBar = musicTitleWidgetScrollArea->verticalScrollBar( );
	if( verticalScrollBar )
		verticalScrollBar->setEnabled( false );
	auto horizontalScrollBar = musicTitleWidgetScrollArea->horizontalScrollBar( );
	auto scrollBar = musicListWidgetScrollArea->horizontalScrollBar( );

	connect( scrollBar, &QScrollBar::valueChanged, horizontalScrollBar, &QScrollBar::setValue );
	connect( scrollBar, &QScrollBar::rangeChanged, horizontalScrollBar, &QScrollBar::setRange );

	calculateSize( );

	musicfavoriteWidgetScrollArea->show( );
	musicTitleWidgetScrollArea->show( );
	musicToolWidget->show( );
	musicListWidgetScrollArea->show( );

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
bool MusicCentreWidget::getJsonData( QJsonObject &get_json_object ) const {
	QJsonObject musicTitleJson;
	if( musicTitleWidget->getJsonData( musicTitleJson ) == false )
		return false;
	QJsonObject musicListJson;
	if( musicListWidget->getJsonData( musicListJson ) == false )
		return false;
	QJsonObject musicFavoriteJson;
	if( musicfavoriteWidget->getJsonData( musicFavoriteJson ) == false )
		return false;
	get_json_object.insert( musicTitleWidget->metaObject( )->className( ), musicTitleJson );
	get_json_object.insert( musicListWidget->metaObject( )->className( ), musicListJson );
	get_json_object.insert( musicfavoriteWidget->metaObject( )->className( ), musicFavoriteJson );
	return true;
}
bool MusicCentreWidget::setJsonData( const QJsonObject &set_json_object ) {
	auto end = set_json_object.end( );
	auto iterator = set_json_object.find( musicTitleWidget->metaObject( )->className( ) );
	if( iterator == end )
		return false;
	QJsonObject musicTitleJson = iterator->toObject( );
	iterator = set_json_object.find( musicListWidget->metaObject( )->className( ) );
	if( iterator == end )
		return false;
	QJsonObject musicListJson = iterator->toObject( );
	iterator = set_json_object.find( musicfavoriteWidget->metaObject( )->className( ) );
	if( iterator == end )
		return false;
	QJsonObject musicFavoriteJson = iterator->toObject( );
	if( musicTitleWidget->setJsonData( musicTitleJson ) == false )
		return false;
	if( musicListWidget->setJsonData( musicListJson ) == false )
		return false;
	if( musicfavoriteWidget->setJsonData( musicFavoriteJson ) == false )
		return false;
	return true;
}
void MusicTitleWidgetTools::updateMusicCentreWidgetTitleWidthInfo( MusicCentreWidget *music_centre_widget, MusicTitleWidget *music_title_widget ) {
	if( music_centre_widget == nullptr || music_title_widget == nullptr )
		return;
	music_centre_widget->updateTitleWidthInfo( music_title_widget, music_title_widget->intervalWidth, music_title_widget->separatorWidth, music_title_widget->musicCodeWidth, music_title_widget->musicNameWidth, music_title_widget->musicSingerNameWidth, music_title_widget->musicDurationTimeWidth );
}
void MusicTitleWidgetTools::updateMusicTitleWidgetTitleWidthInfo( MusicTitleWidget *music_title_widget, int interval_width, int separator_width, int music_code_width, int music_name_width, int music_singer_name_width, int music_duration_time_width ) {
	if( music_title_widget == nullptr )
		return;
	music_title_widget->setTitleWidthInfo( interval_width, separator_width, music_code_width, music_name_width, music_singer_name_width, music_duration_time_width );
}
