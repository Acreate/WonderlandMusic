#include "stringTools.h"

#include <QString>

QString StringTools::getFileSuffix( const QString &file_name ) {
	return file_name.mid( file_name.lastIndexOf( '.' ) + 1 );
}
QString StringTools::ptrToNumber( void *ptr ) {
	auto upper = QString::number( ( uint64_t ) ptr, 16 ).toUpper( );
	return upper;
}
