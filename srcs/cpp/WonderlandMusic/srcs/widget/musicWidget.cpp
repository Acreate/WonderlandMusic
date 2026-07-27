#include "musicWidget.h"
#include "../application/translate/musicWidgetTranslate.h"
#include "../component/optionWindow/optionWindow.h"
#include "../tools/appTranslateTools.h"
class MusicWidgetTranslate;

MusicWidget::MusicWidget( OptionWindow *parent ) : FavoriteWindow( parent ), OptionPanel( ) {
}

MusicWidget::~MusicWidget( ) {
}

QWidget * MusicWidget::toWidget( ) {
	return this;
}

bool MusicWidget::deleteResource( ) {
	return FavoriteWindow::deleteResource( );
}

bool MusicWidget::initBefore( ) {
	deleteResource( );

	if( AppTranslateTools::getMusicWidget( [this] ( MusicWidgetTranslate &translate ) {
		setName( translate.getTitleName( ) );
	} ) == false )
		setName( tr( "音乐" ) );
	if( FavoriteWindow::initBefore( ) == false )
		return false;
	return true;
}

bool MusicWidget::init( ) {
	return FavoriteWindow::init( );
}

bool MusicWidget::initAfter( ) {
	return FavoriteWindow::initAfter( );
}

bool MusicWidget::getJsonData( QJsonObject &get_json_object ) const {
	return FavoriteWindow::getJsonData( get_json_object );
}

bool MusicWidget::setJsonData( const QJsonObject &set_json_object ) {
	return FavoriteWindow::setJsonData( set_json_object );
}
