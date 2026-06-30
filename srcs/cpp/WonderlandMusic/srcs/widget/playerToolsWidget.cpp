#include "playerToolsWidget.h"

#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <qevent.h>

#include "playerListWidget.h"

#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/jsonFileKey.h"
#include "../application/jsonKey/playerListToolWidgetJsonKey.h"
#include "../application/translate/playerToolsWidgetTranslate.h"

#include "../dateTimeFormat/dateTimeFormat.h"

#include "../msgInfo/messageErrorOut.h"

#include "../window/playerWindow.h"

bool PlayerToolsWidget::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( thePreviousSong );
	Delete_Resource_App_Core_Ptr( theNextSong );
	Delete_Resource_App_Core_Ptr( controlPlay );
	Delete_Resource_App_Core_Ptr( playProgress );
	Delete_Resource_App_Core_Ptr( playAllDateTime );
	Delete_Resource_App_Core_Ptr( playUseDateTime );
	Delete_Resource_App_Core_Ptr( playDateTimeSpace );
	Delete_Resource_App_Core_Ptr( playIcon );
	Delete_Resource_App_Core_Ptr( pauseIcon );
	return true;
}

PlayerToolsWidget::PlayerToolsWidget( PlayerWindow *parent ) : QWidget( parent ), playerWindow( parent ) {
}

PlayerToolsWidget::~PlayerToolsWidget( ) {
	deleteResource( );
}

bool PlayerToolsWidget::init( ) {
	deleteResource( );
	isControlPlayProgress = false;
	progressBarMinWidth = 100;
	widgetSpace = 10;
	thePreviousSong = new QPushButton( this );
	theNextSong = new QPushButton( this );
	controlPlay = new QPushButton( this );

	playProgress = new QProgressBar( this );
	playAllDateTime = new QLabel( this );
	playUseDateTime = new QLabel( this );
	playDateTimeSpace = new QLabel( this );

	playIcon = new QIcon;
	pauseIcon = new QIcon;
	setMouseTracking( true );
	auto from = DateTimeFormat::millsecondToHourMinSecFrom( 0 );
	playAllDateTime->setText( from );
	playUseDateTime->setText( from );

	auto appInstance = AppInstance::getAppInstance( );
	auto appDataManage = appInstance->getAppDataManage( );
	auto appTranslate = appDataManage->getTranslate( );
	auto playerToolsWidgetTranslate = appTranslate->getPlayerToolsWidget( );
	thePreviousSong->setText( playerToolsWidgetTranslate->getThePreviousSong( ) );
	theNextSong->setText( playerToolsWidgetTranslate->getTheNextSong( ) );
	controlPlay->setText( playerToolsWidgetTranslate->getControlPlay( ) );

	auto jsonFileKey = appDataManage->getJsonFileKey( );
	auto musicPlayerListToolWidgetJsonFileKey = jsonFileKey->getPlayerListToolWidget( );
	playIcon->addFile( musicPlayerListToolWidgetJsonFileKey->getControlPlayIconPath( ) );
	pauseIcon->addFile( musicPlayerListToolWidgetJsonFileKey->getControlPauseIconPath( ) );

	thePreviousSong->setIcon( QIcon( musicPlayerListToolWidgetJsonFileKey->getThePreviousSongIconPath( ) ) );
	theNextSong->setIcon( QIcon( musicPlayerListToolWidgetJsonFileKey->getTheNextSongIconPath( ) ) );
	controlPlay->setIcon( *playIcon );

	playDateTimeSpace->setText( playerToolsWidgetTranslate->getPlaySongDateTimeSpace( ) );

	playProgress->setRange( 0, 100 );
	playProgress->setValue( 100 );
	playProgress->setTextVisible( false );
	playProgress->setAttribute( Qt::WA_TransparentForMouseEvents, true );

	thePreviousSong->adjustSize( );
	theNextSong->adjustSize( );
	controlPlay->adjustSize( );

	playDateTimeSpace->adjustSize( );
	playAllDateTime->adjustSize( );
	playUseDateTime->adjustSize( );
	playProgress->adjustSize( );

	QSize minSize;
	compMinSize( minSize, progressBarMinWidth );
	setMinimumWidth( minSize.width( ) );
	setFixedHeight( minSize.height( ) );
	compLayout( );

	// 链接信号
	connect( playProgress, &QProgressBar::valueChanged, this, [this] ( int value ) {
		if( musicDuratction > 0 )
			return;
		emit setUseduratctionChange( value * musicDuratction / 100 );
	} );
	connect( thePreviousSong, &QPushButton::clicked, this, []( ) {
	} );
	connect( controlPlay, &QPushButton::clicked, this, []( ) {
	} );
	connect( theNextSong, &QPushButton::clicked, this, []( ) {
	} );
	auto playerListWidget = playerWindow->getPlayListWidget( );
	connect( playerListWidget, &PlayerListWidget::playerMusic, this, [this]( ) {
		auto appInstance = AppInstance::getAppInstance( );
		auto appDataManage = appInstance->getAppDataManage( );
		auto appTranslate = appDataManage->getTranslate( );
		auto playerToolsWidgetTranslate = appTranslate->getPlayerToolsWidget( );
		controlPlay->setText( playerToolsWidgetTranslate->getControlPlay( ) );
		controlPlay->setIcon( *pauseIcon );
	} );

	// 子组件

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

	offsetX = width - offsetX - widgetSpace;
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

	return maxHeight;
}

int PlayerToolsWidget::getMinWidth( int progress_bar_width ) {
	int playerDateWidth = playAllDateTime->width( );

	int maxWidth = progress_bar_width > playerDateWidth ? progress_bar_width : playerDateWidth;
	playerDateWidth = playUseDateTime->width( ) + playDateTimeSpace->width( );
	maxWidth = maxWidth > playerDateWidth ? maxWidth : playerDateWidth;

	int minWidth = thePreviousSong->width( ) + this->controlPlay->width( ) + this->theNextSong->width( ) + maxWidth + widgetSpace * 6;

	return minWidth;
}

bool PlayerToolsWidget::setDuratctionPlayerTime( qint64 duratction ) {
	auto from = DateTimeFormat::millsecondToHourMinSecFrom( duratction );
	playAllDateTime->setText( from );
	this->useDuratction = duratction;
	return true;
}

bool PlayerToolsWidget::compMinSize( QSize &result_min_size, int progress_bar_width ) {
	int minWidth = getMinWidth( progress_bar_width );
	int minHeight = getMinHeight( );
	result_min_size = QSize( minWidth, minHeight );
	return true;
}

void PlayerToolsWidget::suggestWidth( int suggest_width ) {
}

qint64 PlayerToolsWidget::getUseDuratction( ) const {
	return useDuratction;
}

qint64 PlayerToolsWidget::getMusicDuratction( ) const {
	return musicDuratction;
}

void PlayerToolsWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	compLayout( );
}

void PlayerToolsWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	if( isControlPlayProgress == true ) {
		auto mouseeleasePos = event->pos( );
		if( playProgress->geometry( ).contains( mouseeleasePos ) ) {
			auto mapFromPos = playProgress->mapFromParent( mouseeleasePos );
			double x = mapFromPos.x( );
			double playProgressWidth = playProgress->width( );
			int newVar = x * 100 / playProgressWidth + 0.99;
			playProgress->setValue( newVar );
		}
	}
}

void PlayerToolsWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	auto mousePressPos = event->pos( );
	if( playProgress->geometry( ).contains( mousePressPos ) ) {
		isControlPlayProgress = true;
		auto mapFromPos = playProgress->mapFromParent( mousePressPos );
		double x = mapFromPos.x( );
		double playProgressWidth = playProgress->width( );
		int newVar = x * 100 / playProgressWidth + 0.99;
		playProgress->setValue( newVar );
	}
}

void PlayerToolsWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	isControlPlayProgress = false;
}
