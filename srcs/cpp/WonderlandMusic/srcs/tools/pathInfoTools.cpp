#include "pathInfoTools.h"

#include <QStringList>

#include "instanceTools.h"

#include "../application/appInstance/appDataManage.h"
#include "../application/appInstance/appDataManage/appMusicManage/appMusicDecoder.h"

bool PathInfoTools::getAppSettintHomePath( QString &result_app_setting_home_path ) {
	auto appDataManage = InstanceTools::getAppDataManage( );
	if( appDataManage == nullptr )
		return false;
	result_app_setting_home_path = appDataManage->getAppSettingPath( );
	return true;
}
bool PathInfoTools::getSupperDecodeFileSuffixFilter( QString &result_supper_decode_music_file_suffix_filter ) {
	std::vector< QString > decodeFileSuffix;
	if( PathInfoTools::getSupperDecodeFileSuffix( decodeFileSuffix ) == false )
		return false;
	auto count = decodeFileSuffix.size( );
	if( count == 0 )
		return false;
	auto data = decodeFileSuffix.data( );
	size_t index = 0;
	QStringList json;
	for( ; index < count; index += 1 )
		json.append( "*." + data[ index ] );
	result_supper_decode_music_file_suffix_filter = "音频(" + json.join( " " ) + ");;所有(*.*)";
	return true;
}
bool PathInfoTools::getSupperDecodeFileSuffix( std::vector< QString > &result_supper_decode_music_file_suffix ) {
	auto appMusicDecoder = InstanceTools::getAppMusicDecoder( );
	if( appMusicDecoder == nullptr )
		return false;
	result_supper_decode_music_file_suffix = appMusicDecoder->getSupperDecodeFileSuffix( );
	return true;
}
