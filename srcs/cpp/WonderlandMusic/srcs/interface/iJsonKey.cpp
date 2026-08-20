#include "iJsonKey.h"

#include "../tools/pathInfoTools.h"

bool IJsonKey::deleteResource( ) {
	return true;
}
QString IJsonKey::getNormalJsonKeyFile( const QString &json_file_last_file_path ) const {
	if( json_file_last_file_path.isEmpty( ) )
		return json_file_last_file_path;
	QString applicationDirPath;
	if( PathInfoTools::getAppSettintHomePath( applicationDirPath ) )
		return applicationDirPath + json_file_last_file_path;
	return "./" + json_file_last_file_path;
}

bool IJsonKey::initBefore( ) {
	return true;
}

bool IJsonKey::initAfter( ) {
	return true;
}
QString IJsonKey::getFilePath( ) const {
	return getNormalJsonKeyFile( filePath );
}
