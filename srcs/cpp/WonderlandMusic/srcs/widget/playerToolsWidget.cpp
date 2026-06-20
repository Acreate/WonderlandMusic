#include "playerToolsWidget.h"

#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <qevent.h>

#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/jsonFileKey.h"
#include "../application/renderImage.h"

#include "../tools/dateTimeFormat.h"

PlayerToolsWidget::PlayerToolsWidget( QWidget *parent ) : QWidget( parent ) {
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
	auto from = DateTimeFormat::millsecondToHourMinSecFrom( 0 );
	playAllDateTime->setText( from );
	playUseDateTime->setText( from );

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
	return true;
}

bool PlayerToolsWidget::compLayout( ) {
	int width = this->contentsRect( ).width( );

	int offsetX = 0;
	this->thePreviousSong->move( offsetX, 0 );

	offsetX += this->thePreviousSong->width( );
	this->controlPlay->move( offsetX, 0 );

	offsetX += this->controlPlay->width( );
	this->theNextSong->move( offsetX, 0 );

	// 播放进度的起始 x 位置
	offsetX += this->controlPlay->width( );
	this->playProgress->move( offsetX, 0 );

	int offsetY = showCurrentPlayerList->height( );
	playAllDateTime->move( offsetX, offsetY );

	offsetX += playAllDateTime->width( );
	playDateTimeSpace->move( offsetX, offsetY );

	offsetX += playDateTimeSpace->width( );
	playUseDateTime->move( offsetX, offsetY );

	// 播放进度的终止 x 位置
	offsetX = width - showCurrentPlayerList->width( );
	showCurrentPlayerList->move( offsetX, 0 );

	// 剩余空间留给进度条
	if( offsetX < progressBarMinWidth )
		offsetX = progressBarMinWidth;
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

	int minWidth = thePreviousSong->width( ) + this->controlPlay->width( ) + this->theNextSong->width( ) + maxWidth + showCurrentPlayerList->width( );

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
