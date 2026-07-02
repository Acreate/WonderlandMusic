#ifndef MUSICINFOITEMWIDGETJSONKEY_H_H_HEAD__FILE__
#define MUSICINFOITEMWIDGETJSONKEY_H_H_HEAD__FILE__
#include "iJsonKey.h"

class MusicInfoItemWidgetJsonKey : public IJsonKey {
	QString musicInfoFile;
	QString musicInfoName;
	QString musicInfoSinger;
	QString musicInfoDuration;

public:
	bool init( ) override;

public:
	virtual const QString & getMusicInfoFile( ) const;

	virtual const QString & getMusicInfoName( ) const;

	virtual const QString & getMusicInfoSinger( ) const;

	virtual const QString & getMusicInfoDuration( ) const;
};

#endif // MUSICINFOITEMWIDGETJSONKEY_H_H_HEAD__FILE__
