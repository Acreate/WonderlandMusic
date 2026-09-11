#ifndef MUSICITEMJSONKEY_H_H_HEAD__FILE__
#define MUSICITEMJSONKEY_H_H_HEAD__FILE__
#include "../../../../interface/iJsonKey.h"

class MusicItemJsonKey : public IJsonKey {
	QString idCodeKey;
	QString nameKey;
	QString singerKey;
	QString absoluteFilePathKey;
	QString elapsedTimeKey;

public:
	bool init( ) override;
	virtual const QString & getIdCodeKey( ) const;
	virtual const QString & getNameKey( ) const;
	virtual const QString & getSingerKey( ) const;
	virtual const QString & getAbsoluteFilePathKey( ) const;
	virtual const QString & getElapsedTimeKey( ) const;
};

namespace AppJsonKeyTools {
	Declaration_Get_JsonKey( MusicItem );
}

#endif // MUSICITEMJSONKEY_H_H_HEAD__FILE__
