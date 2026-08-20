#ifndef MUSICFAVORITEMENUJSONKEY_H_H_HEAD__FILE__
#define MUSICFAVORITEMENUJSONKEY_H_H_HEAD__FILE__
#include <interface/iJsonKey.h>

class MusicFavoriteMenuJsonKey : public IJsonKey {
	QString loadMultDir;
	QString loadMultFile;

public:
	bool init( ) override;
	virtual const QString & getLoadMultDir( ) const;
	virtual const QString & getLoadMultFile( ) const;
};

namespace AppJsonKeyTools {
	Declaration_Get_JsonKey( MusicFavoriteMenu );
};
#endif // MUSICFAVORITEMENUJSONKEY_H_H_HEAD__FILE__
