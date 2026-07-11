#include "addFavoriteWindow.h"
#include "../widget/addFavoriteItemWidget.h"

bool AddFavoriteWindow::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( addFavoriteItemWidget );
	return true;
}

AddFavoriteWindow::AddFavoriteWindow( ) : AddFavoriteWindow( nullptr ) {
}

AddFavoriteWindow::AddFavoriteWindow( QWidget *parent ) : QMainWindow( parent ) {
}

AddFavoriteWindow::~AddFavoriteWindow( ) {
	deleteResource( );
}

AddFavoriteItemWidget * AddFavoriteWindow::getAddFavoriteItemWidget( ) const {
	return addFavoriteItemWidget;
}

bool AddFavoriteWindow::initBefore( ) {
	deleteResource( );
	addFavoriteItemWidget = new AddFavoriteItemWidget( this );

	Before_Init_Resource_App_Core_Ptr( addFavoriteItemWidget );

	return true;
}

bool AddFavoriteWindow::init( ) {
	Init_Resource_App_Core_Ptr( addFavoriteItemWidget );
	return true;
}

bool AddFavoriteWindow::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( addFavoriteItemWidget );
	setCentralWidget( addFavoriteItemWidget );
	return true;
}
