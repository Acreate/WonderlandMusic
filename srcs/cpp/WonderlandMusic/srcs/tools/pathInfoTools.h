#ifndef PATHINFOTOOLS_H_H_HEAD__FILE__
#define PATHINFOTOOLS_H_H_HEAD__FILE__
#include <vector>

class QString;

namespace PathInfoTools {
	bool getAppSettintHomePath( QString &result_app_setting_home_path );
	bool getSupperDecodeFileSuffixFilter( QString &result_supper_decode_music_file_suffix_filter );
	bool getSupperDecodeFileSuffix( std::vector< QString > &result_supper_decode_music_file_suffix );
}

#endif // PATHINFOTOOLS_H_H_HEAD__FILE__
