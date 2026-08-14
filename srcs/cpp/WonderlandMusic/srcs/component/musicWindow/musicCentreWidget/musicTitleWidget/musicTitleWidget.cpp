#include "musicTitleWidget.h"

#include <QJsonObject>
#include <QPainter>
#include <QMouseEvent>

#include "../musicCentreWidget.h"

#include <application/appRenderImage.h>
#include <application/translate/musicTitleWidgetTranslate.h>

#include <head/release_macro.h>

#include <mutex/userMutex.h>

#include <tools/instanceTools.h>

#include "../../tools/musicCenereWidgetTools.h"
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
	//QWidget::mouseMoveEvent( event );

	// 不在拖拽组件上，则开始检测
	if( startDrag == false ) {
		// 获取坐标位置
		dragPosX = event->pos( ).x( );
		// 获取鼠标
		auto newCursor = cursor( );
		// 检测位置
		if( isDragSeparator( dragSeparator, dragPosX ) == false ) {
			// 失败时，鼠标必须为 ArrowCursor 状态
			if( newCursor.shape( ) == Qt::ArrowCursor )
				return; // 如果是 ArrowCursor 状态，则直接返回
			// 如果不是 ArrowCursor 状态，则配置 ArrowCursor 状态
			newCursor.setShape( Qt::ArrowCursor );
			setCursor( newCursor );
		}
		// 鼠标在拖拽组件上
		switch( dragSeparator ) {
			case DragItemType::Code :
				dragTargetPtr = &musicCodeWidth;
				dragTargetValue = *dragTargetPtr;
				newCursor.setShape( Qt::SizeHorCursor );
				setCursor( newCursor );
				break;
			case DragItemType::Name :
				dragTargetPtr = &musicNameWidth;
				dragTargetValue = *dragTargetPtr;
				newCursor.setShape( Qt::SizeHorCursor );
				setCursor( newCursor );
				break;
			case DragItemType::Singer :
				dragTargetPtr = &musicSingerNameWidth;
				dragTargetValue = *dragTargetPtr;
				newCursor.setShape( Qt::SizeHorCursor );
				setCursor( newCursor );
				break;
			case DragItemType::Duration :
				dragTargetPtr = &musicDurationTimeWidth;
				dragTargetValue = *dragTargetPtr;
				newCursor.setShape( Qt::SizeHorCursor );
				setCursor( newCursor );
				break;
			case DragItemType::None :
			default :
				dragTargetPtr = nullptr;
				newCursor.setShape( Qt::ArrowCursor );
				setCursor( newCursor );
				break;
		}

		return;
	}

	*dragTargetPtr = dragTargetValue + event->pos( ).x( ) - dragPosX;
	update( );
}
void MusicTitleWidget::mousePressEvent( QMouseEvent *event ) {
	//QWidget::mousePressEvent( event );
	startDrag = true;
}
void MusicTitleWidget::mouseReleaseEvent( QMouseEvent *event ) {
	//QWidget::mouseReleaseEvent( event );
	if( dragSeparator == DragItemType::None )
		return;

	startDrag = false;
	setMinimumWidth( getCalculateMinWidth( ) );
	dragSeparator = DragItemType::None;
	dragTargetPtr = nullptr;

	auto newCursor = cursor( );
	newCursor.setShape( Qt::ArrowCursor );
	setCursor( newCursor );
	update( );
	updateTitleWidthInfo( );
}
void MusicTitleWidget::showEvent( QShowEvent *event ) {
	QWidget::showEvent( event );
	updateTitleWidthInfo( );
}
bool MusicTitleWidget::isDragSeparator( DragItemType &index, int x_pos ) const {
	index = DragItemType::None;
	int offsetX;

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
void MusicTitleWidget::updateTitleWidthInfo( ) {
	userMutex->lock( );
	ItemWidthInfo itemWidthInfo = getItemWidthInfo( );
	userMutex->unlock( );
	MusicCentreWidgetTools::updateMusicCentreWidgetTitleWidthInfo( musicCentreWidget, itemWidthInfo );
}
bool MusicTitleWidget::initBefore( ) {
	deleteResource( );
	pen = new QPen;
	painter = new QPainter( );

	separatorWidth = 5;
	intervalWidth = 2;
	minItemWidth = intervalWidth * 2 + separatorWidth;
	clickWidth = intervalWidth * 2 + separatorWidth;
	dragSeparator = DragItemType::None;
	dragPosX = 0;
	startDrag = false;
	fillSeparatorColor = Qt::GlobalColor::black;
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
	font = appRenderImage->getFont( );
	if( AppTranslateTools::getMusicTitleWidget( [this] ( MusicTitleWidgetTranslate &translate ) {
		musicCode = translate.getMusicCode( );
		musicName = translate.getMusicName( );
		musicSingeName = translate.getMusicSingeName( );
		musicDurationTime = translate.getMusicDurationTime( );

		musicCodeWidth = fontMetrics->horizontalAdvance( musicCode );
		musicNameWidth = fontMetrics->horizontalAdvance( musicName );
		musicSingerNameWidth = fontMetrics->horizontalAdvance( musicSingeName );
		musicDurationTimeWidth = fontMetrics->horizontalAdvance( musicDurationTime );
		return true;
	} ) == false )
		return false;
	suggestHeight = fontMetrics->height( );
	pen->setColor( fillSeparatorColor );
	setMouseTracking( true );
	setFixedWidth( getCalculateMinWidth( ) );
	return true;
}
bool MusicTitleWidget::getJsonData( QJsonObject &get_json_object ) const {
	bool result = ItemWidthInfo::getJsonData( get_json_object );
	return result;
}
bool MusicTitleWidget::setJsonData( const QJsonObject &set_json_object ) {
	bool result = ItemWidthInfo::setJsonData( set_json_object );
	if( result ) {
		int calculateMinWidth = getCalculateMinWidth( );

		setFixedWidth( calculateMinWidth );
		updateTitleWidthInfo( );
		//repaint( );
	}
	return result;
}
MusicCentreWidget * MusicTitleWidget::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
void MusicTitleWidget::getTitleWidthInfo( int &result_interval_width, int &result_separator_width, int &result_music_code_width, int &result_music_name_width, int &result_music_singer_name_width, int &result_music_duration_time_width ) const {
	getItemWidthInfo( result_interval_width, result_separator_width, result_music_code_width, result_music_name_width, result_music_singer_name_width, result_music_duration_time_width );
}
void MusicTitleWidget::setTitleWidthInfo( int interval_width, int separator_width, int music_code_width, int music_name_width, int music_singer_name_width, int music_duration_time_width ) {
	setItemWidthInfo( interval_width, separator_width, music_code_width, music_name_width, music_singer_name_width, music_duration_time_width );
	repaint( );
}
