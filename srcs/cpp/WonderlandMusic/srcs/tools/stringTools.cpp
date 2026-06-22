#include "stringTools.h"

#include <QString>

QString StringTools::getFileSuffix( const QString &file_name ) {
	return file_name.mid( file_name.lastIndexOf( '.' ) + 1 );
}
