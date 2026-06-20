#include "playerListTopWidget.h"

#include <QJsonObject>
#include <QMouseEvent>
#include <QPainter>

#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/jsonFileKey.h"
#include "../application/renderImage.h"
#include "../application/jsonKey/playerListTopWidgetJsonKey.h"
#include "../application/translate/playerTopWidgetTranslate.h"

#include "../tools/pathTools.h"

void PlayerListTopWidget::updateCurrentWidgetSize( ) {
	int newWidth = widgetBeforeWidth + widgetAfterWidth + splitWidth * 5 + musicNameWidth + musicSingerWidth + musicDurationWidth + indexWidth;
	AppInstance *appInstance = AppInstance::getAppInstance( );
	auto fontMetrics = appInstance->getRenderImage( )->getFontMetrics( );
	int currentHeight = fontMetrics->height( );
	setFixedSize( newWidth, currentHeight );
}

PlayerListTopWidget::PlayerListTopWidget( QWidget *parent ) : QWidget( parent ), isDrag( false ), isReadyDrag( false ) {
	setMouseTracking( true );
}

PlayerListTopWidget::~PlayerListTopWidget( ) {
}

bool PlayerListTopWidget::loadJsonPathInfo( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getJsonFileKey( );
	auto listTopWidgetJsonKey = jsonFileKey->getPlayerListTopWidget( );
	auto fileJsonPath = listTopWidgetJsonKey->getPlayerListWidgetTopJsonPath( );
	QJsonObject fileJsonObject;
	if( PathTools::readJsonObject( fileJsonObject, fileJsonPath ) == false )
		return true;
	auto end = fileJsonObject.end( );
	QJsonObject::iterator find;

	find = fileJsonObject.find( listTopWidgetJsonKey->getPlayerListWidgetItemSplitWidth( ) );
	if( find != end )
		splitWidth = find.value( ).toInt( splitWidth );
	find = fileJsonObject.find( listTopWidgetJsonKey->getPlayerListWidgetItemMusicNameWidth( ) );
	if( find != end )
		musicNameWidth = find.value( ).toInt( musicNameWidth );
	find = fileJsonObject.find( listTopWidgetJsonKey->getPlayerListWidgetItemMusicSingerWidth( ) );
	if( find != end )
		musicSingerWidth = find.value( ).toInt( musicSingerWidth );
	find = fileJsonObject.find( listTopWidgetJsonKey->getPlayerListWidgetItemMusicDurationWidth( ) );
	if( find != end )
		musicDurationWidth = find.value( ).toInt( musicDurationWidth );

	find = fileJsonObject.find( listTopWidgetJsonKey->getPlayerListWidgetItemWidgetBeforeWidth( ) );
	if( find != end )
		widgetBeforeWidth = find.value( ).toInt( musicDurationWidth );

	find = fileJsonObject.find( listTopWidgetJsonKey->getPlayerListWidgetItemWidgetAfterWidth( ) );
	if( find != end )
		widgetAfterWidth = find.value( ).toInt( musicDurationWidth );

	find = fileJsonObject.find( listTopWidgetJsonKey->getPlayerListWidgetItemWidgetIndexWidth( ) );
	if( find != end )
		indexWidth = find.value( ).toInt( musicDurationWidth );
	find = fileJsonObject.find( listTopWidgetJsonKey->getPlayerListWidgetItemWidth( ) );
	if( find != end ) {
		QRect rect = contentsRect( );
		int w = find.value( ).toInt( rect.width( ) );
		setFixedSize( w, rect.height( ) );
	}

	return true;
}

bool PlayerListTopWidget::writeJsonPathInfo( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getJsonFileKey( );

	QJsonObject fileJsonObject;
	int width = contentsRect( ).width( );
	auto listTopWidgetJsonKey = jsonFileKey->getPlayerListTopWidget( );
	fileJsonObject.insert( listTopWidgetJsonKey->getPlayerListWidgetItemWidth( ), width );
	fileJsonObject.insert( listTopWidgetJsonKey->getPlayerListWidgetItemSplitWidth( ), splitWidth );
	fileJsonObject.insert( listTopWidgetJsonKey->getPlayerListWidgetItemMusicNameWidth( ), musicNameWidth );
	fileJsonObject.insert( listTopWidgetJsonKey->getPlayerListWidgetItemMusicSingerWidth( ), musicSingerWidth );
	fileJsonObject.insert( listTopWidgetJsonKey->getPlayerListWidgetItemMusicDurationWidth( ), musicDurationWidth );
	fileJsonObject.insert( listTopWidgetJsonKey->getPlayerListWidgetItemWidgetBeforeWidth( ), widgetBeforeWidth );
	fileJsonObject.insert( listTopWidgetJsonKey->getPlayerListWidgetItemWidgetAfterWidth( ), widgetAfterWidth );
	fileJsonObject.insert( listTopWidgetJsonKey->getPlayerListWidgetItemWidgetIndexWidth( ), indexWidth );
	auto fileJsonPath = listTopWidgetJsonKey->getPlayerListWidgetTopJsonPath( );
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
	if( getMinSize( ) == false )
		return;
	updateCurrentWidgetSize( );
	update( );
	emitChangedWidth( );
}

bool PlayerListTopWidget::getMinSize( QSize &result_min_size ) {
	auto appInstance = AppInstance::getAppInstance( );
	if( appInstance == nullptr )
		return false;
	auto appTranslate = appInstance->getTranslate( );
	if( appTranslate == nullptr )
		return false;
	auto renderImage = appInstance->getRenderImage( );
	if( renderImage == nullptr )
		return false;
	auto fontMetrics = renderImage->getFontMetrics( );
	if( fontMetrics == nullptr )
		return false;

	auto indexWidth = fontMetrics->horizontalAdvance( "0000" );
	if( indexWidth < 0 )
		return false;
	auto playerTopWidgetTranslate = appTranslate->getPlayerTopWidget( );
	auto nameWidth = fontMetrics->horizontalAdvance( playerTopWidgetTranslate->getMusicName( ) );
	if( nameWidth < 0 )
		return false;
	auto singerWidth = fontMetrics->horizontalAdvance( playerTopWidgetTranslate->getMusicSinger( ) );
	if( singerWidth < 0 )
		return false;
	auto durationWidth = fontMetrics->horizontalAdvance( playerTopWidgetTranslate->getMusicDuration( ) );
	if( durationWidth < 0 )
		return false;

	// 获取字符串最小宽度
	double widthPercentage = nameWidth + singerWidth + durationWidth + indexWidth;
	// 获取分割最小宽度
	double spliteWidthUserSpace = splitWidth * 5;
	// 获取两侧最小宽度
	double borderWidth = widgetBeforeWidth + widgetAfterWidth;
	// 整体最小宽度
	double minWidth = widthPercentage + spliteWidthUserSpace + borderWidth;
	if( minWidth < 0 )
		return false;
	int h = fontMetrics->height( );
	if( h < 0 )
		return false;
	result_min_size = QSize( minWidth, h );
	return minWidth;
}

bool PlayerListTopWidget::getMinSize( ) {
	QSize result_min_size;
	return getMinSize( result_min_size );
}

void PlayerListTopWidget::emitChangedWidth( ) {
	emit changedWidth( splitWidth, widgetBeforeWidth, this->indexWidth, this->musicNameWidth, this->musicSingerWidth, this->musicDurationWidth, this->widgetAfterWidth );
}

bool PlayerListTopWidget::init( ) {
	cursorShape = Qt::ArrowCursor;
	indexWidth = widgetBeforeWidth = widgetAfterWidth = splitWidth = musicNameWidth = musicSingerWidth = musicDurationWidth = 4;
	QSize minSize;
	if( getMinSize( minSize ) == false )
		return false;
	setFixedSize( minSize );
	if( averageItem( ) == false )
		return false;
	if( loadJsonPathInfo( ) == false )
		return false;
	repaint( );
	emitChangedWidth( );
	return true;
}

void PlayerListTopWidget::suggestWidth( int suggest_width ) {
}

bool PlayerListTopWidget::averageItem( ) {// 获取字符串最小宽度
	auto appInstance = AppInstance::getAppInstance( );
	auto appTranslate = appInstance->getTranslate( );
	auto renderImage = appInstance->getRenderImage( );
	auto fontMetrics = renderImage->getFontMetrics( );
	auto playerTopWidgetTranslate = appTranslate->getPlayerTopWidget( );
	auto indexWidth = fontMetrics->horizontalAdvance( "0000" );
	auto nameWidth = fontMetrics->horizontalAdvance( playerTopWidgetTranslate->getMusicName( ) );
	auto singerWidth = fontMetrics->horizontalAdvance( playerTopWidgetTranslate->getMusicSinger( ) );
	auto durationWidth = fontMetrics->horizontalAdvance( playerTopWidgetTranslate->getMusicDuration( ) );

	// 获取字符串最小宽度
	double widthPercentage = nameWidth + singerWidth + durationWidth + indexWidth;
	// 获取分割最小宽度
	double spliteWidthUserSpace = splitWidth * 5;
	// 获取两侧最小宽度
	double borderWidth = widgetBeforeWidth + widgetAfterWidth;

	double width = this->width( );
	double residue = width - spliteWidthUserSpace - borderWidth;
	double part = residue / widthPercentage;
	this->indexWidth = part * indexWidth;
	this->musicDurationWidth = part * durationWidth;
	this->musicSingerWidth = part * singerWidth;
	this->musicNameWidth = residue - this->musicDurationWidth - this->musicSingerWidth;
	return true;
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

void PlayerListTopWidget::closeEvent( QCloseEvent *event ) {
	QWidget::closeEvent( event );
}

void PlayerListTopWidget::hideEvent( QHideEvent *event ) {
	writeJsonPathInfo( );
	QWidget::hideEvent( event );
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
	auto playerTopWidget = appTranslate->getPlayerTopWidget( );
	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentHeight );
	drawOffsetX += offsetSplitX;
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( indexWidth, currentHeight ) );
	painter.drawText( drawRect, playerTopWidget->getMusicIndex( ) );
	drawOffsetX += indexWidth + offsetSplitX;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentHeight );
	drawOffsetX += offsetSplitX;
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( musicNameWidth, currentHeight ) );
	painter.drawText( drawRect, playerTopWidget->getMusicName( ) );
	drawOffsetX += musicNameWidth + offsetSplitX;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentHeight );
	drawOffsetX += offsetSplitX;
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( musicSingerWidth, currentHeight ) );
	painter.drawText( drawRect, playerTopWidget->getMusicSinger( ) );
	drawOffsetX += musicSingerWidth + offsetSplitX;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentHeight );
	drawOffsetX += offsetSplitX;
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( musicDurationWidth, currentHeight ) );
	painter.drawText( drawRect, playerTopWidget->getMusicDuration( ) );
	drawOffsetX += musicDurationWidth + offsetSplitX;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentHeight );

	painter.end( );
}

void PlayerListTopWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
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
