#include "playerListTopWidget.h"

#include <QJsonObject>
#include <QMouseEvent>
#include <QPainter>

#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/jsonFileKey.h"
#include "../application/renderImage.h"

#include "../tools/pathTools.h"

void PlayerListTopWidget::updateCurrentWidgetSize( ) {
	int newWidth = widgetBeforeWidth + widgetAfterWidth + splitWidth * 5 + musicNameWidth + musicSingerWidth + musicDurationWidth + indexWidth;
	AppInstance *appInstance = AppInstance::getAppInstance( );
	auto fontMetrics = appInstance->getRenderImage( )->getFontMetrics( );
	int currentHeight = fontMetrics->height( );
	setFixedSize( newWidth, currentHeight );
}

PlayerListTopWidget::PlayerListTopWidget( QWidget *parent ) : QWidget( parent ), isDrag( false ), isReadyDrag( false ) {
	indexWidth = widgetBeforeWidth = widgetAfterWidth = splitWidth = musicNameWidth = musicSingerWidth = musicDurationWidth = 4;
	updateCurrentWidgetSize( );
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

	find = fileJsonObject.find( jsonFileKey->getPlayerListWidgetItemWidgetBeforeWidth( ) );
	if( find != end )
		widgetBeforeWidth = find.value( ).toInt( musicDurationWidth );

	find = fileJsonObject.find( jsonFileKey->getPlayerListWidgetItemWidgetAfterWidth( ) );
	if( find != end )
		widgetAfterWidth = find.value( ).toInt( musicDurationWidth );

	find = fileJsonObject.find( jsonFileKey->getPlayerListWidgetItemWidgetIndexWidth( ) );
	if( find != end )
		indexWidth = find.value( ).toInt( musicDurationWidth );

	autoSetItemSize( );
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
	fileJsonObject.insert( jsonFileKey->getPlayerListWidgetItemWidgetBeforeWidth( ), widgetBeforeWidth );
	fileJsonObject.insert( jsonFileKey->getPlayerListWidgetItemWidgetAfterWidth( ), widgetAfterWidth );
	fileJsonObject.insert( jsonFileKey->getPlayerListWidgetItemWidgetIndexWidth( ), indexWidth );
	auto fileJsonPath = jsonFileKey->getPlayerListWidgetTopJsonPath( );
	PathTools::writeJsonObject( fileJsonObject, fileJsonPath );
	return true;
}

int PlayerListTopWidget::getSplitWidth( ) const {
	return splitWidth;
}

int PlayerListTopWidget::getIndexWidth( ) const {
	return indexWidth;
}

int PlayerListTopWidget::getMusicNameWidth( ) const {
	return musicNameWidth;
}

int PlayerListTopWidget::getMusicSingerWidth( ) const {
	return musicSingerWidth;
}

int PlayerListTopWidget::getMusicDurationWidth( ) const {
	return musicDurationWidth;
}

int PlayerListTopWidget::getWidgetBeforeWidth( ) const {
	return widgetBeforeWidth;
}

int PlayerListTopWidget::getWidgetAfterWidth( ) const {
	return widgetAfterWidth;
}

void PlayerListTopWidget::autoSetItemSize( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto appTranslate = appInstance->getTranslate( );
	auto renderImage = appInstance->getRenderImage( );
	auto fontMetrics = renderImage->getFontMetrics( );

	auto indexWidth = fontMetrics->horizontalAdvance( "0000" );
	auto nameWidth = fontMetrics->horizontalAdvance( appTranslate->getMusicName( ) );
	auto singerWidth = fontMetrics->horizontalAdvance( appTranslate->getMusicSinger( ) );
	auto durationWidth = fontMetrics->horizontalAdvance( appTranslate->getMusicDuration( ) );

	double widthPercentage = nameWidth + singerWidth + durationWidth + indexWidth;
	auto spliteWidthUserSpace = splitWidth * 5;
	int borderWidth = widgetBeforeWidth + widgetAfterWidth;
	int width = this->width( );
	double residue = width - spliteWidthUserSpace - borderWidth;
	double part = residue / widthPercentage;
	this->indexWidth = part * indexWidth;
	this->musicDurationWidth = part * durationWidth;
	this->musicSingerWidth = part * singerWidth;
	this->musicNameWidth = residue - this->musicDurationWidth - this->musicSingerWidth;
	updateCurrentWidgetSize( );
	update( );
	emit changedWidth( splitWidth, widgetBeforeWidth, this->indexWidth, this->musicNameWidth, this->musicSingerWidth, this->musicDurationWidth, this->widgetAfterWidth );
}

void PlayerListTopWidget::mouseMoveEvent( QMouseEvent *event ) {
	int x = event->x( );
	if( isDrag ) {
		*dragBeforeWidthOrgPtr = dragWidth + x - dragBeforeX;
		repaint( );
		return;
	}

	Qt::CursorShape buffCursorShape = Qt::ArrowCursor;
	int leftX = widgetBeforeWidth;
	int rightX = splitWidth + widgetBeforeWidth;
	dragIndex = 0;
	if( x > leftX && x < rightX ) {
		buffCursorShape = Qt::CursorShape::SizeHorCursor;
		dragWidth = widgetBeforeWidth;
		dragBeforeWidthOrgPtr = &widgetBeforeWidth;
	} else {
		dragIndex += 1;
		leftX = rightX + indexWidth;
		rightX = splitWidth + leftX;
		if( x > leftX && x < rightX ) {
			buffCursorShape = Qt::CursorShape::SizeHorCursor;
			dragWidth = indexWidth;
			dragBeforeWidthOrgPtr = &indexWidth;
		} else {
			dragIndex += 1;
			leftX = rightX + musicNameWidth;
			rightX = splitWidth + leftX;
			if( x > leftX && x < rightX ) {
				buffCursorShape = Qt::CursorShape::SizeHorCursor;
				dragWidth = musicNameWidth;
				dragBeforeWidthOrgPtr = &musicNameWidth;
			} else {
				dragIndex += 1;
				leftX = rightX + musicSingerWidth;
				rightX = splitWidth + leftX;
				if( x > leftX && x < rightX ) {
					buffCursorShape = Qt::CursorShape::SizeHorCursor;
					dragWidth = musicSingerWidth;
					dragBeforeWidthOrgPtr = &musicSingerWidth;
				} else {
					dragIndex += 1;
					leftX = rightX + musicDurationWidth;
					rightX = splitWidth + leftX;
					if( x > leftX && x < rightX ) {
						buffCursorShape = Qt::CursorShape::SizeHorCursor;
						dragWidth = musicDurationWidth;
						dragBeforeWidthOrgPtr = &musicDurationWidth;
					}
				}
			}
		}
	}
	if( cursorShape != buffCursorShape ) {
		dragBeforeX = x;
		cursorShape = buffCursorShape;
		setCursor( cursorShape );
		if( cursorShape == Qt::SizeHorCursor )
			isReadyDrag = true;
	}
}

void PlayerListTopWidget::mousePressEvent( QMouseEvent *event ) {
	if( cursorShape != Qt::ArrowCursor && isReadyDrag ) {
		isDrag = true;
	}
}

void PlayerListTopWidget::mouseReleaseEvent( QMouseEvent *event ) {
	if( isDrag ) {
		cursorShape = Qt::ArrowCursor;
		setCursor( cursorShape );
		isReadyDrag = isDrag = false;
		updateCurrentWidgetSize( );
		emit changedWidth( splitWidth, widgetBeforeWidth, this->indexWidth, this->musicNameWidth, this->musicSingerWidth, this->musicDurationWidth, this->widgetAfterWidth );
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

	int drawOffsetX = offsetSplitX + widgetBeforeWidth;
	QRect drawRect;
	auto currentHeight = height( );

	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentHeight );
	drawOffsetX += offsetSplitX;
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( indexWidth, currentHeight ) );
	painter.drawText( drawRect, appTranslate->getMusicIndex( ) );
	drawOffsetX += indexWidth + offsetSplitX;

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
		isReadyDrag = isDrag = false;
		updateCurrentWidgetSize( );
		emit changedWidth( splitWidth, widgetBeforeWidth, this->indexWidth, this->musicNameWidth, this->musicSingerWidth, this->musicDurationWidth, this->widgetAfterWidth );
	}
}
