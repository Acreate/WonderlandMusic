#include "playerToolsWidget.h"

#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <qevent.h>

#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/jsonFileKey.h"
#include "../application/renderImage.h"

#include "../msgInfo/messageErrorOut.h"

#include "../tools/dateTimeFormat.h"

PlayerToolsWidget::PlayerToolsWidget( QWidget *parent ) : QWidget( parent ) {
	progressBarMinWidth = 100;
	widgetSpace = 10;
	this->thePreviousSong = new QPushButton( this );
	this->theNextSong = new QPushButton( this );
	this->controlPlay = new QPushButton( this );

	this->playProgress = new QProgressBar( this );
	this->playAllDateTime = new QLabel( this );
	this->playUseDateTime = new QLabel( this );
	this->playDateTimeSpace = new QLabel( this );
	this->showCurrentPlayerList = new QPushButton( this );

	this->playIcon = new QIcon;
	this->pauseIcon = new QIcon;
}

PlayerToolsWidget::~PlayerToolsWidget( ) {
	delete playIcon;
	delete pauseIcon;
}

bool PlayerToolsWidget::init( ) {
	progressBarMinWidth = 100;
	widgetSpace = 10;
	setMouseTracking( true );
	auto from = DateTimeFormat::millsecondToHourMinSecFrom( 0 );
	playAllDateTime->setText( from );
	playUseDateTime->setText( from );

	thePreviousSong->disconnect( );
	theNextSong->disconnect( );
	controlPlay->disconnect( );
	showCurrentPlayerList->disconnect( );

	auto appInstance = AppInstance::getAppInstance( );
	auto appTranslate = appInstance->getTranslate( );
	thePreviousSong->setText( appTranslate->getThePreviousSong( ) );
	theNextSong->setText( appTranslate->getTheNextSong( ) );
	controlPlay->setText( appTranslate->getControlPlay( ) );
	showCurrentPlayerList->setText( appTranslate->getCurrentPlayList( ) );

	auto jsonFileKey = appInstance->getJsonFileKey( );
	playIcon->addFile( jsonFileKey->getControlPlayIconPath( ) );
	pauseIcon->addFile( jsonFileKey->getControlPauseIconPath( ) );

	thePreviousSong->setIcon( QIcon( jsonFileKey->getThePreviousSongIconPath( ) ) );
	theNextSong->setIcon( QIcon( jsonFileKey->getTheNextSongIconPath( ) ) );
	controlPlay->setIcon( *playIcon );
	showCurrentPlayerList->setIcon( QIcon( jsonFileKey->getCurrentSongPlayListIconPath( ) ) );

	playDateTimeSpace->setText( appTranslate->getPlaySongDateTimeSpace( ) );

	playProgress->setRange( 0, 100 );
	playProgress->setValue( 100 );
	playProgress->setTextVisible( false );
	playProgress->setAttribute( Qt::WA_TransparentForMouseEvents, true );

	thePreviousSong->adjustSize( );
	theNextSong->adjustSize( );
	controlPlay->adjustSize( );
	showCurrentPlayerList->adjustSize( );
	playDateTimeSpace->adjustSize( );
	playAllDateTime->adjustSize( );
	playUseDateTime->adjustSize( );
	playProgress->adjustSize( );

	QSize minSize;
	compMinSize( minSize, progressBarMinWidth );
	setMinimumSize( minSize );
	compLayout( );

	// 链接信号

	return true;
}

bool PlayerToolsWidget::compLayout( ) {
	auto contentsRect = this->contentsRect( );
	int width = contentsRect.width( );
	int height = contentsRect.height( );
	int half = height / 2;
	int offsetX;
	int offsetY;
	int buttonHeightHalf;

	offsetX = widgetSpace;
	buttonHeightHalf = thePreviousSong->height( ) / 2;
	offsetY = half - buttonHeightHalf;
	this->thePreviousSong->move( offsetX, offsetY );

	offsetX += this->thePreviousSong->width( ) + widgetSpace;
	buttonHeightHalf = controlPlay->height( ) / 2;
	offsetY = half - buttonHeightHalf;
	this->controlPlay->move( offsetX, offsetY );

	offsetX += this->controlPlay->width( ) + widgetSpace;
	buttonHeightHalf = theNextSong->height( ) / 2;
	offsetY = half - buttonHeightHalf;
	this->theNextSong->move( offsetX, offsetY );
	auto theNextSongX = offsetX;

	// 播放进度的起始 x 位置
	height = this->theNextSong->width( );
	offsetX = theNextSongX + height + widgetSpace;
	this->playProgress->move( offsetX, 0 );

	offsetY = playProgress->height( );
	playAllDateTime->move( offsetX, offsetY );

	offsetX += playAllDateTime->width( ) + widgetSpace;
	playDateTimeSpace->move( offsetX, offsetY );

	offsetX += playDateTimeSpace->width( ) + widgetSpace;
	playUseDateTime->move( offsetX, offsetY );

	offsetX = width - showCurrentPlayerList->width( ) - widgetSpace;
	buttonHeightHalf = showCurrentPlayerList->height( ) / 2;
	offsetY = half - buttonHeightHalf;
	showCurrentPlayerList->move( offsetX, offsetY );

	offsetX = offsetX - theNextSongX - height - widgetSpace - widgetSpace;
	if( offsetX < 0 )
		offsetX = 1;
	this->playProgress->setFixedWidth( offsetX );
	return true;
}

int PlayerToolsWidget::getMinHeight( ) {
	int maxHeight = playProgress->height( ) + playAllDateTime->height( );
	int cmpHeight = playProgress->height( ) + playUseDateTime->height( );
	if( maxHeight < cmpHeight )
		maxHeight = cmpHeight;
	cmpHeight = playProgress->height( ) + playDateTimeSpace->height( );
	if( maxHeight < cmpHeight )
		maxHeight = cmpHeight;
	cmpHeight = thePreviousSong->height( );
	if( maxHeight < cmpHeight )
		maxHeight = cmpHeight;
	cmpHeight = controlPlay->height( );
	if( maxHeight < cmpHeight )
		maxHeight = cmpHeight;

	cmpHeight = theNextSong->height( );
	if( maxHeight < cmpHeight )
		maxHeight = cmpHeight;

	cmpHeight = showCurrentPlayerList->height( );
	if( maxHeight < cmpHeight )
		maxHeight = cmpHeight;
	return maxHeight;
}

int PlayerToolsWidget::getMinWidth( int progress_bar_width ) {
	int playerDateWidth = playAllDateTime->width( );

	int maxWidth = progress_bar_width > playerDateWidth ? progress_bar_width : playerDateWidth;
	playerDateWidth = playUseDateTime->width( ) + playDateTimeSpace->width( );
	maxWidth = maxWidth > playerDateWidth ? maxWidth : playerDateWidth;

	int minWidth = thePreviousSong->width( ) + this->controlPlay->width( ) + this->theNextSong->width( ) + maxWidth + showCurrentPlayerList->width( ) + widgetSpace * 6;

	return minWidth;
}

bool PlayerToolsWidget::setCurrentPlayerTime( qint64 current ) {
	return false;
}

bool PlayerToolsWidget::setDuratctionPlayerTime( qint64 duratction ) {
	return false;
}

bool PlayerToolsWidget::compMinSize( QSize &result_min_size, int progress_bar_width ) {
	int minWidth = getMinWidth( progress_bar_width );
	int minHeight = getMinHeight( );
	result_min_size = QSize( minWidth, minHeight );
	return true;
}

void PlayerToolsWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	compLayout( );
}

void PlayerToolsWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
}

void PlayerToolsWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	auto point = event->pos( );
	if( playProgress->geometry( ).contains( point ) ) {
		auto mapFromParent = playProgress->mapFromParent( point );
		double x = mapFromParent.x( );
		double playProgressWidth = playProgress->width( );
		int newVar = x * 100 / playProgressWidth + 0.99;
		playProgress->setValue( newVar );
	}
}
