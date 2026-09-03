#include "cmakeInfo.h"

#include <QDateTime>
#include <QString>

#include <cmake_property_to_c_cpp_header_env.h>

#include <cmake_to_c_cpp_header_env.h>

bool CmakeInfo::getGeneratePorjectDateTime( QDateTime &result_data_time ) {
	QString format = cmake_property_Generate_Date_Time_Format;
	format.replace( "%Y", "yyyy" );
	format.replace( "%m", "MM" );
	format.replace( "%d", "dd" );
	format.replace( "%H", "HH" );
	format.replace( "%M", "mm" );
	format.replace( "%S", "ss" );
	result_data_time = QDateTime::fromString(
		cmake_property_Generate_Date_Time,
		format
		);
	return true;
}
bool CmakeInfo::getGeneratePorjectCmakeSourceDir( QString &result_source_dir ) {
	result_source_dir = QString( Cmake_Source_Dir );
	return result_source_dir.isEmpty( ) == false;
}
