#include "aboutWidgetTranslate.h"

#include <application/appTranslate.h>
#include <tools/instanceTools.h>

#include <head/defininition_get_translate.h>

Defininition_Get_Translate( AboutWidget );

bool AboutWidgetTranslate::init( ) {
	titleName = QObject::tr( "关于" );
	return true;
}

const QString & AboutWidgetTranslate::getTitleName( ) const {
	return titleName;
}
