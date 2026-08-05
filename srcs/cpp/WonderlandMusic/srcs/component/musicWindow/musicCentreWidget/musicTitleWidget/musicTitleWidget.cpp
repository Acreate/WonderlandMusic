#include "musicTitleWidget.h"

#include <QPainter>
#include <QMouseEvent>

#include "../musicCentreWidget.h"

#include "../../../../application/appRenderImage.h"
#include "../../../../application/translate/musicTitleWidgetTranslate.h"

#include "../../../../head/release_macro.h"

#include "../../../../mutex/userMutex.h"

#include "../../../../tools/instanceTools.h"
MusicTitleWidget::MusicTitleWidget( MusicCentreWidget *music_centre_widget ) : QWidget( music_centre_widget ), musicCentreWidget( music_centre_widget ) {
}
MusicTitleWidget::~MusicTitleWidget( ) {
	deleteResource( );
}
bool MusicTitleWidget::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	Delete_Resource_App_Core_Ptr( pen );
	Delete_Resource_App_Core_Ptr( painter );
	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}
void MusicTitleWidget::paintEvent( QPaintEvent *event ) {
	painter->begin( this );
	painter->setFont( *font );
	painter->setPen( *pen );

	int offsetX = intervalWidth;
	int offsetY = 0;

	painter->fillRect( QRect( offsetX, offsetY, separatorWidth, suggestHeight ), fillSeparatorColor );

	offsetX += intervalWidth + separatorWidth;
	painter->drawText( QRect( offsetX, offsetY, musicCodeWidth, suggestHeight ), musicCode );

	offsetX += intervalWidth + musicCodeWidth;
	painter->fillRect( QRect( offsetX, offsetY, separatorWidth, suggestHeight ), fillSeparatorColor );

	offsetX += intervalWidth + separatorWidth;
	painter->drawText( QRect( offsetX, offsetY, musicCodeWidth, suggestHeight ), musicName );

	offsetX += intervalWidth + musicNameWidth;
	painter->fillRect( QRect( offsetX, offsetY, separatorWidth, suggestHeight ), fillSeparatorColor );

	offsetX += intervalWidth + separatorWidth;
	painter->drawText( QRect( offsetX, offsetY, musicCodeWidth, suggestHeight ), musicSingeName );

	offsetX += intervalWidth + musicSingerNameWidth;
	painter->fillRect( QRect( offsetX, offsetY, separatorWidth, suggestHeight ), fillSeparatorColor );

	offsetX += intervalWidth + separatorWidth;
	painter->drawText( QRect( offsetX, offsetY, musicCodeWidth, suggestHeight ), musicDurationTime );

	offsetX += intervalWidth + musicDurationTimeWidth;
	painter->fillRect( QRect( offsetX, offsetY, separatorWidth, suggestHeight ), fillSeparatorColor );
	painter->end( );
}
void MusicTitleWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
}
void MusicTitleWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	int pos = event->pos( ).x( );
	isDragSeparator( dragSeparator, pos );
}
void MusicTitleWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	if( dragSeparator == DragItemType::None )
		return;
	setMinimumWidth( getCalculateMinWidth( ) );
	dragSeparator = DragItemType::None;
}
bool MusicTitleWidget::isDragSeparator( DragItemType &index, int x_pos ) const {
	index = DragItemType::None;
	int offsetX;
	int clickWidth = intervalWidth * 2 + separatorWidth;
	// 首个分隔符
	offsetX = clickWidth;
	if( x_pos < offsetX )
		return false;
	// 是否点击编号
	offsetX += musicCodeWidth;
	if( x_pos < offsetX )
		return false;
	// 点击编号分隔符
	offsetX += clickWidth;
	if( x_pos < offsetX ) {
		index = DragItemType::Code;
		return true;
	}

	// 是否点击歌名
	offsetX += musicNameWidth;
	if( x_pos < offsetX )
		return false;
	// 点击歌名分隔符
	offsetX += clickWidth;
	if( x_pos < offsetX ) {
		index = DragItemType::Name;
		return true;
	}

	// 是否点击歌手
	offsetX += musicSingerNameWidth;
	if( x_pos < offsetX )
		return false;
	// 点击歌手分隔符
	offsetX += clickWidth;
	if( x_pos < offsetX ) {
		index = DragItemType::Singer;
		return true;
	}
	// 是否点击时长
	offsetX += musicDurationTimeWidth;
	if( x_pos < offsetX )
		return false;
	// 点击时长分隔符
	offsetX += clickWidth;
	if( x_pos < offsetX ) {
		index = DragItemType::Duration;
		return true;
	}

	return false;
}
bool MusicTitleWidget::initBefore( ) {
	return true;
}
bool MusicTitleWidget::init( ) {
	return true;
}
bool MusicTitleWidget::initAfter( ) {
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	if( appRenderImage == nullptr )
		return false;

	fontMetrics = appRenderImage->getFontMetrics( );
	if( AppTranslateTools::getMusicTitleWidget( [this] ( MusicTitleWidgetTranslate &translate ) {
		musicCode = translate.getMusicCode( );
		musicName = translate.getMusicName( );
		musicSingeName = translate.getMusicSingeName( );
		musicDurationTime = translate.getMusicDurationTime( );

		musicCodeWidth = fontMetrics->horizontalAdvance( musicCode );
		musicNameWidth = fontMetrics->horizontalAdvance( musicName );
		musicSingerNameWidth = fontMetrics->horizontalAdvance( musicSingeName );
		musicDurationTimeWidth = fontMetrics->horizontalAdvance( musicDurationTime );
	} ) == false )
		return false;
	dragSeparator = DragItemType::None;
	suggestHeight = fontMetrics->height( );
	font = appRenderImage->getFont( );
	fillSeparatorColor = Qt::GlobalColor::black;
	separatorWidth = 5;
	intervalWidth = 2;
	pen = new QPen;
	painter = new QPainter( );
	pen->setColor( fillSeparatorColor );
	setMinimumWidth( getCalculateMinWidth( ) );
	return true;
}
int MusicTitleWidget::getSuggestHeight( ) const {
	return suggestHeight;
}
int MusicTitleWidget::getCalculateMinWidth( ) const {
	return ( intervalWidth + separatorWidth ) * 5 + musicCodeWidth + musicNameWidth + musicSingerNameWidth + musicDurationTimeWidth + separatorWidth;
}
