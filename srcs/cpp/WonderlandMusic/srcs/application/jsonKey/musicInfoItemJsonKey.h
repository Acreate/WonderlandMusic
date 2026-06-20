#ifndef MUSICINFOITEMJSONKEY_H_H_HEAD__FILE__
#define MUSICINFOITEMJSONKEY_H_H_HEAD__FILE__
#include "iJsonKey.h"

class MusicInfoItemJsonKey : public IJsonKey {
	QString musicInfoFile;
	QString musicInfoName;
	QString musicInfoSinger;
	QString musicInfoDuration;

public:
	bool init( ) override;

	virtual const QString & getMusicInfoFile( ) const;

	virtual const QString & getMusicInfoName( ) const;

	virtual const QString & getMusicInfoSinger( ) const;

	virtual const QString & getMusicInfoDuration( ) const;
};

#endif // MUSICINFOITEMJSONKEY_H_H_HEAD__FILE__
