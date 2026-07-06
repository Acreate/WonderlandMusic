#include "favoriteItemWidget.h"

#include <QLineEdit>

FavoriteItemWidget::~FavoriteItemWidget( ) {
}

FavoriteItemWidget::FavoriteItemWidget( ) : FavoriteItemWidget( nullptr ) {
}

FavoriteItemWidget::FavoriteItemWidget( QWidget *parent ) : QWidget( parent ) {
	lineEdit = new QLineEdit( this );
	connect( lineEdit, &QLineEdit::editingFinished, this, [this]( ) {
		lineEdit->setEnabled( false );
		emit signal_change_name_finished( );
	} );
	lineEdit->move( 0, 0 );
	lineEdit->show( );
}

QString FavoriteItemWidget::getFavoriteName( ) const {
	return lineEdit->text( );
}

void FavoriteItemWidget::setFavoriteName( const QString &name ) {
	lineEdit->setText( name );
}

void FavoriteItemWidget::mouseDoubleClickEvent( QMouseEvent *event ) {
	QWidget::mouseDoubleClickEvent( event );
	lineEdit->setEnabled( true );
	lineEdit->setFocus( );
}
