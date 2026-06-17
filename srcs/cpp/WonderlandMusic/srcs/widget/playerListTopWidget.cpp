#include "playerListTopWidget.h"

#include <QJsonObject>
#include <QMouseEvent>
#include <QPainter>

#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/jsonFileKey.h"
#include "../application/renderImage.h"

#include "../tools/pathTools.h"

PlayerListTopWidget::PlayerListTopWidget( QWidget *parent ) : QWidget( parent ), isDrag( false ) {
	splitWidth = musicNameWidth = musicSingerWidth = musicDurationWidth = 4;
	AppInstance *appInstance = AppInstance::getAppInstance( );
	auto fontMetrics = appInstance->getRenderImage( )->getFontMetrics( );
	int currentHeight = fontMetrics->height( );
	setFixedHeight( currentHeight );
	setMouseTracking( true );
	cursorShape = Qt::ArrowCursor;
}

bool PlayerListTopWidget::loadJsonPathInfo( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getJsonFileKey( );
	auto fileJsonPath = jsonFileKey->getPlayerListWidgetTopJsonPath( );
	QJsonObject fileJsonObject;
	if( PathTools::readJsonObject( fileJsonObject, fileJsonPath ) == false )
		return true;
	auto end = fileJsonObject.end( );
	QJsonObject::iterator find;

	find = fileJsonObject.find( jsonFileKey->getPlayerListWidgetItemSplitWidth( ) );
	if( find != end )
		splitWidth = find.value( ).toInt( splitWidth );
	find = fileJsonObject.find( jsonFileKey->getPlayerListWidgetItemMusicNameWidth( ) );
	if( find != end )
		musicNameWidth = find.value( ).toInt( musicNameWidth );
	find = fileJsonObject.find( jsonFileKey->getPlayerListWidgetItemMusicSingerWidth( ) );
	if( find != end )
		musicSingerWidth = find.value( ).toInt( musicSingerWidth );
	find = fileJsonObject.find( jsonFileKey->getPlayerListWidgetItemMusicDurationWidth( ) );
	if( find != end )
		musicDurationWidth = find.value( ).toInt( musicDurationWidth );

	return true;
}

bool PlayerListTopWidget::writeJsonPathInfo( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getJsonFileKey( );

	QJsonObject fileJsonObject;
	fileJsonObject.insert( jsonFileKey->getPlayerListWidgetItemSplitWidth( ), splitWidth );
	fileJsonObject.insert( jsonFileKey->getPlayerListWidgetItemMusicNameWidth( ), musicNameWidth );
	fileJsonObject.insert( jsonFileKey->getPlayerListWidgetItemMusicSingerWidth( ), musicSingerWidth );
	fileJsonObject.insert( jsonFileKey->getPlayerListWidgetItemMusicDurationWidth( ), musicDurationWidth );
	auto fileJsonPath = jsonFileKey->getPlayerListWidgetTopJsonPath( );
	PathTools::writeJsonObject( fileJsonObject, fileJsonPath );
	return true;
}

int PlayerListTopWidget::getSplitWidth( ) const {
	return splitWidth;
}

void PlayerListTopWidget::setSplitWidth( const int split_width ) {
	splitWidth = split_width;
}

int PlayerListTopWidget::getMusicNameWidth( ) const {
	return musicNameWidth;
}

void PlayerListTopWidget::setMusicNameWidth( const int music_name_width ) {
	musicNameWidth = music_name_width;
}

int PlayerListTopWidget::getMusicSingerWidth( ) const {
	return musicSingerWidth;
}

void PlayerListTopWidget::setMusicSingerWidth( const int music_singer_width ) {
	musicSingerWidth = music_singer_width;
}

int PlayerListTopWidget::getMusicDurationWidth( ) const {
	return musicDurationWidth;
}

void PlayerListTopWidget::setMusicDurationWidth( const int music_duration_width ) {
	musicDurationWidth = music_duration_width;
}

void PlayerListTopWidget::mouseMoveEvent( QMouseEvent *event ) {
	int x = event->x( );
	Qt::CursorShape buffCursorShape = Qt::ArrowCursor;
	if( x < splitWidth )
		buffCursorShape = Qt::CursorShape::SizeHorCursor;
	else {
		int leftX = splitWidth + musicNameWidth;
		int rightX = splitWidth + leftX;
		if( x > leftX && x < rightX )
			buffCursorShape = Qt::CursorShape::SizeHorCursor;
		else {
			leftX = rightX + musicSingerWidth;
			rightX = splitWidth + leftX;
			if( x > leftX && x < rightX )
				buffCursorShape = Qt::CursorShape::SizeHorCursor;
			else {
				leftX = rightX + musicDurationWidth;
				rightX = splitWidth + leftX;
				if( x > leftX && x < rightX )
					buffCursorShape = Qt::CursorShape::SizeHorCursor;
			}
		}
	}
	if( cursorShape != buffCursorShape ) {
		cursorShape = buffCursorShape;
		setCursor( cursorShape );
		if( cursorShape == Qt::SizeHorCursor )
			isDrag = true;
	}
}

void PlayerListTopWidget::mousePressEvent( QMouseEvent *event ) {
	if( cursorShape != Qt::ArrowCursor ) {
		isDrag = true;
	}
}

void PlayerListTopWidget::mouseReleaseEvent( QMouseEvent *event ) {
	if( isDrag ) {
		cursorShape = Qt::ArrowCursor;
		setCursor( cursorShape );
		isDrag = false;
	}
}

void PlayerListTopWidget::paintEvent( QPaintEvent *event ) {
	AppInstance *appInstance = AppInstance::getAppInstance( );
	auto appTranslate = appInstance->getTranslate( );
	auto font = appInstance->getRenderImage( )->getFont( );

	int offsetSplitX = splitWidth / 2;
	QPainter painter;
	painter.begin( this );
	auto pen = painter.pen( );
	pen.setWidth( splitWidth );
	painter.setPen( pen );
	painter.setFont( *font );

	int drawOffsetX = offsetSplitX;
	QRect drawRect;
	auto currentHeight = height( );
	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentHeight );
	drawOffsetX += offsetSplitX;
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( musicNameWidth, currentHeight ) );
	painter.drawText( drawRect, appTranslate->getMusicName( ) );
	drawOffsetX += musicNameWidth + offsetSplitX;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentHeight );
	drawOffsetX += offsetSplitX;
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( musicSingerWidth, currentHeight ) );
	painter.drawText( drawRect, appTranslate->getMusicSinger( ) );
	drawOffsetX += musicSingerWidth + offsetSplitX;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentHeight );
	drawOffsetX += offsetSplitX;
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( musicDurationWidth, currentHeight ) );
	painter.drawText( drawRect, appTranslate->getMusicDuration( ) );
	drawOffsetX += musicDurationWidth + offsetSplitX;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentHeight );

	painter.end( );
}

void PlayerListTopWidget::leaveEvent( QEvent *event ) {
	if( isDrag ) {
		cursorShape = Qt::ArrowCursor;
		setCursor( cursorShape );
		isDrag = false;
	}
}
