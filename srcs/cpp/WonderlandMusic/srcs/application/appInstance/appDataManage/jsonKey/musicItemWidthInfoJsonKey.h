#ifndef MUSICITEMWIDTHINFOJSONKEY_H_H_HEAD__FILE__
#define MUSICITEMWIDTHINFOJSONKEY_H_H_HEAD__FILE__

#include <interface/iJsonKey.h>

class MusicItemWidthInfoJsonKey : public IJsonKey {
	QString suggestHeight;
	QString musicCodeWidth;
	QString musicNameWidth;
	QString musicSingerNameWidth;
	QString musicDurationTimeWidth;

public:
	bool init( ) override;
	virtual const QString & getSuggestHeight( ) const;
	virtual const QString & getMusicCodeWidth( ) const;
	virtual const QString & getMusicNameWidth( ) const;
	virtual const QString & getMusicSingerNameWidth( ) const;
	virtual const QString & getMusicDurationTimeWidth( ) const;
};

namespace AppJsonKeyTools {
	Declaration_Get_JsonKey( MusicItemWidthInfo );
};
#endif // MUSICITEMWIDTHINFOJSONKEY_H_H_HEAD__FILE__
