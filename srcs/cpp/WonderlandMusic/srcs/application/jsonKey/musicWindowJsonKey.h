#ifndef MUSICWINDOWJSONKEY_H_H_HEAD__FILE__
#define MUSICWINDOWJSONKEY_H_H_HEAD__FILE__
#include "../../interface/iJsonKey.h"

class MusicWindowJsonKey : public IJsonKey {
	QString jsonFilePath;

public:
	bool init( ) override;
	virtual QString getJsonFilePath( ) const;
};

namespace AppJsonKeyTools {
	Declaration_Get_JsonKey( MusicWindow );
};
#endif // MUSICWINDOWJSONKEY_H_H_HEAD__FILE__
