#ifndef MUSICWIDGETSIZEINFOJSONKEY_H_H_HEAD__FILE__
#define MUSICWIDGETSIZEINFOJSONKEY_H_H_HEAD__FILE__

#include <interface/iJsonKey.h>

class MusicWidgetSizeInfoJsonKey : public IJsonKey {
public:
	bool init( ) override;
};

namespace AppJsonKeyTools {
	Declaration_Get_JsonKey( MusicWidgetSizeInfo );
};
#endif // MUSICWIDGETSIZEINFOJSONKEY_H_H_HEAD__FILE__
