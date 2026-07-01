#ifndef PLAYERWINDOWJSONKEY_H_H_HEAD__FILE__
#define PLAYERWINDOWJSONKEY_H_H_HEAD__FILE__

#include "iJsonKey.h"

class PlayerWindowJsonKey : public IJsonKey {
	QString jsonFilePath;
	QString fileSelect;
	QString dirSelect;
	QString favoriteArrayObjName;
	QString favoriteArrayCount;
	QString favoriteArrayData;
	
	QString musicArrayObjName;
	QString musicArrayCount;
	QString musicArrayData;

public:
	bool init( ) override;

	virtual const QString & getJsonFilePath( ) const;

	virtual const QString & getFavoriteArrayObjName( ) const;

	virtual const QString & getFavoriteArrayCount( ) const;

	virtual const QString & getFavoriteArrayData( ) const;

	virtual const QString & getFileSelect( ) const;

	virtual const QString & getDirSelect( ) const;

	virtual const QString & getMusicArrayObjName( ) const;

	virtual const QString & getMusicArrayCount( ) const;

	virtual const QString & getMusicArrayData( ) const;
};
#endif // PLAYERWINDOWJSONKEY_H_H_HEAD__FILE__
