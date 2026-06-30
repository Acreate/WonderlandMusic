#include "playerWindow.h"

#include <QDockWidget>
#include <QScrollBar>
#include <QFileDialog>
#include <QJsonObject>
#include <QScrollArea>
#include <qevent.h>

#include "../application/appEventManage.h"
#include "../application/appInstance.h"

#include "../menu/playerWidgetMenu.h"

#include "../tools/pathTools.h"

#include "../widget/playerListWidget.h"
#include "../widget/playerListTopWidget.h"
#include "../widget/playerToolsWidget.h"

PlayerWindow::~PlayerWindow( ) {
	deleteResource( );
}

PlayerWindow::PlayerWindow( QWidget *parent ) : QMainWindow( parent ) {
	setWindowFlags( Qt::WindowType::Widget );
}

bool PlayerWindow::deleteResource( ) {
	delete_ptr( topDocWidget, bottomDocWidget, playerWidgetMenu );
	return true;
}

bool PlayerWindow::initWidget( ) {
	topDocWidget = new QDockWidget( this );
	topDocWidget->setAllowedAreas( Qt::TopDockWidgetArea );
	addDockWidget( Qt::DockWidgetArea::TopDockWidgetArea, topDocWidget );
	topDocWidget->setTitleBarWidget( new QWidget( topDocWidget ) );
	topDocWidget->setContentsMargins( 0, 0, 0, 0 );

	playerListTopWidgetScrollArea = new QScrollArea( this );
	playerListTopWidgetScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	playerListTopWidgetScrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	playerListTopWidgetScrollArea->setWidgetResizable( true );
	playerListTopWidgetScrollArea->setWindowFlags( Qt::WindowType::Widget );
	playerListTopWidgetScrollArea->verticalScrollBar( )->setEnabled( false );
	topDocWidget->setWidget( playerListTopWidgetScrollArea );

	playerListTopWidget = new PlayerListTopWidget( playerListTopWidgetScrollArea );
	playerListTopWidgetScrollArea->setWidget( playerListTopWidget );

	bottomDocWidget = new QDockWidget( this );
	playListWidgetScrollArea = new QScrollArea( this );

	playListWidgetScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	playListWidgetScrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	playListWidgetScrollArea->setWidgetResizable( true );
	playListWidgetScrollArea->setWindowFlags( Qt::WindowType::Widget );

	bottomDocWidget->setAllowedAreas( Qt::BottomDockWidgetArea );
	bottomDocWidget->setTitleBarWidget( new QWidget( bottomDocWidget ) );
	bottomDocWidget->setContentsMargins( 0, 0, 0, 0 );
	addDockWidget( Qt::DockWidgetArea::BottomDockWidgetArea, bottomDocWidget );

	playerToolsWidget = new PlayerToolsWidget( this );
	playListWidget = new PlayerListWidget( this );

	bottomDocWidget->setWidget( playerToolsWidget );
	setCentralWidget( playListWidgetScrollArea );
	playListWidgetScrollArea->setWidget( playListWidget );

	return true;
}

bool PlayerWindow::initMenu( ) {
	playerWidgetMenu = new PlayerWidgetMenu( playListWidget );

	return true;
}

bool PlayerWindow::initConnect( ) {
	connect( playerListTopWidget, &PlayerListTopWidget::changedWidth, [this]( ) {
		playListWidget->setItemWidth( playerListTopWidget );
	} );
	auto playListHBar = playListWidgetScrollArea->horizontalScrollBar( );
	auto topWidgetHBar = playerListTopWidgetScrollArea->horizontalScrollBar( );
	connect( playListHBar, &QScrollBar::sliderMoved, topWidgetHBar, &QScrollBar::setValue );
	connect( playListWidget, &PlayerListWidget::popMenu, this, [this]( ) {
		popPlayerWidgetMenu( );
	} );
	return true;
}

bool PlayerWindow::updateSubCompoment( ) {
	if( playListWidget->init( ) == false )
		return false;
	if( playerToolsWidget->init( ) == false )
		return false;
	if( playerListTopWidget->init( ) == false )
		return false;
	if( playerWidgetMenu->init( ) == false )
		return false;
	playListWidget->setFixedWidth( playerListTopWidget->width( ) );
	topDocWidget->setFixedHeight( playerListTopWidget->height( ) );
	return true;
}

bool PlayerWindow::init( ) {
	deleteResource( );
	if( initWidget( ) == false )
		return false;
	if( initMenu( ) == false )
		return false;
	if( initConnect( ) == false )
		return false;
	if( updateSubCompoment( ) == false )
		return false;
	return true;
}

PlayerListWidget * PlayerWindow::getPlayListWidget( ) const {
	return playListWidget;
}

PlayerListTopWidget * PlayerWindow::getPlayerListTopWidget( ) const {
	return playerListTopWidget;
}

PlayerToolsWidget * PlayerWindow::getPlayerToolsWidget( ) const {
	return playerToolsWidget;
}

PlayerWidgetMenu * PlayerWindow::getPlayerWidgetMenu( ) const {
	return playerWidgetMenu;
}

void PlayerWindow::showEvent( QShowEvent *event ) {
	QMainWindow::showEvent( event );
}

void PlayerWindow::resizeEvent( QResizeEvent *event ) {
	QMainWindow::resizeEvent( event );
	int width = event->size( ).width( );
	playerListTopWidget->suggestWidth( width );
	playerToolsWidget->suggestWidth( width );
}

void PlayerWindow::mouseReleaseEvent( QMouseEvent *event ) {
	QMainWindow::mouseReleaseEvent( event );
	auto mouseButton = event->button( );

	switch( mouseButton ) {
		case Qt::MouseButton::RightButton :
			popPlayerWidgetMenu( );
			break;
	}
}

bool PlayerWindow::popPlayerWidgetMenu( ) {
	auto point = QCursor::pos( );
	auto mapFromGlobal = playListWidgetScrollArea->mapFromGlobal( point );
	auto contentsRect = playListWidgetScrollArea->contentsRect( );
	if( contentsRect.contains( mapFromGlobal ) ) {
		playerWidgetMenu->exec( point );
		return true;
	}
	return false;
}
