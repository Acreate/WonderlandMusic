#include "aboutWidgetTranslate.h"

bool AboutWidgetTranslate::init( ) {
	titleName = QObject::tr( "关于" );
	return true;
}

const QString & AboutWidgetTranslate::getTitleName( ) const {
	return titleName;
}
