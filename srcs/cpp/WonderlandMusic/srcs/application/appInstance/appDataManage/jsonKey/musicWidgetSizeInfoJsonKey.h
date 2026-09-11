#ifndef MUSICWIDGETSIZEINFOJSONKEY_H_H_HEAD__FILE__
#define MUSICWIDGETSIZEINFOJSONKEY_H_H_HEAD__FILE__

#include <interface/iJsonKey.h>

class MusicWidgetSizeInfoJsonKey : public IJsonKey {
	QString favoriteWidth;
	QString titleHeight;

public:
	bool init( ) override;
	virtual const QString & getFavoriteWidth( ) const;
	virtual const QString & getTitleHeight( ) const;
};

namespace AppJsonKeyTools {
	Declaration_Get_JsonKey( MusicWidgetSizeInfo );
};
#endif // MUSICWIDGETSIZEINFOJSONKEY_H_H_HEAD__FILE__
