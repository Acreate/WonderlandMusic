#include "deleteException.h"

#include "../tools/sourceLocationTools.h"

DeleteException::DeleteException( const QString &error, const std::source_location &source_location ) : DeleteException( error.toStdString( ), source_location ) {
}

DeleteException::DeleteException( const std::string &error, const std::source_location &source_location ) : error( error ), sourceLocation( source_location ) {
}

const char * DeleteException::what( ) const {
	return error.c_str( );
}

DeleteException::~DeleteException( ) noexcept {
}

DeleteException::operator MessageString( ) const {
	QString msg;
	SourceLocationTools::formatString( msg, sourceLocation, QString::fromStdString( this->error ) );
	return MessageString( msg );
}
