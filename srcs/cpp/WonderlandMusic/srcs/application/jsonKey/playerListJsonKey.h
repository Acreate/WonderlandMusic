#ifndef PLAYERLISTJSONKEY_H_H_HEAD__FILE__
#define PLAYERLISTJSONKEY_H_H_HEAD__FILE__
#include "iJsonKey.h"

class PlayerListJsonKey : public IJsonKey {
	QString musicPlayerListInfoFileJsonPath;
	QString musicInfoListCount;
	QString musicInfoListName;
	QString musicInfoListIndex;
	QString songPlayerInfoJsonPath;
	QString fileSelectWorkPath;
	QString dirSelectWorkPath;

public:
	bool init( ) override;

	virtual const QString & getMusicPlayerListInfoFileJsonPath( ) const;

	virtual const QString & getMusicInfoListCount( ) const;

	virtual const QString & getMusicInfoListName( ) const;

	virtual const QString & getMusicInfoListIndex( ) const;

	virtual const QString & getSongPlayerInfoJsonPath( ) const;

	virtual const QString & getFileSelectWorkPath( ) const;

	virtual const QString & getDirSelectWorkPath( ) const;
};

#endif // PLAYERLISTJSONKEY_H_H_HEAD__FILE__
