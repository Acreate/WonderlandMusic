#include "musicListStackedWidget.h"

MusicListStackedWidget::MusicListStackedWidget( QWidget *parent ) : QStackedWidget( parent ) {
}

MusicListStackedWidget::~MusicListStackedWidget( ) {
	deleteResource( );
}

bool MusicListStackedWidget::deleteResource( ) {
	disconnect( );
	return true;
}

bool MusicListStackedWidget::init( ) {
	deleteResource( );
	return true;
}
