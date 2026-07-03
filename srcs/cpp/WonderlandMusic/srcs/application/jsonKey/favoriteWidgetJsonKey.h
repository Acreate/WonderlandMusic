#ifndef FAVORITEWIDGETJSONKEY_H_H_HEAD__FILE__
#define FAVORITEWIDGETJSONKEY_H_H_HEAD__FILE__

#include <interface/iJsonKey.h>

class FavoriteWidgetJsonKey : public IJsonKey {
	QString jsonFilePath;
	QString favoriteArrayCount;
	QString favoriteArrayData;
	QString favoriteArrayIndex;

public:
	bool init( ) override;

	virtual const QString & getJsonFilePath( ) const;

	virtual const QString & getFavoriteArrayCount( ) const;

	virtual const QString & getFavoriteArrayData( ) const;

	virtual const QString & getFavoriteArrayIndex( ) const;
};

#endif // FAVORITEWIDGETJSONKEY_H_H_HEAD__FILE__
