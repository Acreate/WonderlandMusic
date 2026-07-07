#ifndef MUSICITEMJSONKEY_H_H_HEAD__FILE__
#define MUSICITEMJSONKEY_H_H_HEAD__FILE__
#include "../../interface/iJsonKey.h"

class MusicItemJsonKey : public IJsonKey {
	QString musicVector;
	QString musicData;
	QString musicCount;

public:
	bool init( ) override;

	virtual const QString & getMusicVector( ) const;

	virtual const QString & getMusicData( ) const;

	virtual const QString & getMusicCount( ) const;
};

#endif // MUSICITEMJSONKEY_H_H_HEAD__FILE__
