#include "messageErrorOut.h"
#include <cmake_include_to_c_cpp_header_env.h>
#include <qdir.h>
MessageErrorOut & MessageErrorOut::operator<<( const QString &msg ) {
	outMsgVector.emplace_back( msg );
	return *this;
}
MessageErrorOut::~MessageErrorOut( ) {
	uint_least32_t msgCodeLine = location.line( );
	auto msgCodeFileName = location.file_name( );
	auto msgCodeFunctionName = location.function_name( );
	QDir cmakeRootPath( Cmake_Source_Dir );
	auto relativeFilePath = cmakeRootPath.relativeFilePath( msgCodeFileName );
	QString outString;
	QString jion;
	size_t count = outMsgVector.size( );
	size_t index;
	if( count > 0 ) {
		auto data = outMsgVector.data( );
		for( index = 0; index < count; ++index )
			jion += data[ index ];
	}
	outString.append( "::->" ).append( relativeFilePath ).append( " : [ " ).append( msgCodeFunctionName ).append( " ] : ( " ).append( QString::number( msgCodeLine ) ).append( " )=>\n" ).append( jion ).append( "\n-----" );

	qDebug( ) << outString.toStdString( ).c_str( );
}
