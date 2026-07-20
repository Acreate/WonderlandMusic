#include "opetionListWidget.h"

OpetionListWidget::OpetionListWidget( QWidget *parent ): QWidget( parent ) {
}

OpetionListWidget::~OpetionListWidget( ) {
	deleteResource(  );
}

bool OpetionListWidget::deleteResource( ) {
	return false;
}

bool OpetionListWidget::initBefore( ) {
	return false;
}

bool OpetionListWidget::init( ) {
	return false;
}

bool OpetionListWidget::initAfter( ) {
	return false;
}
