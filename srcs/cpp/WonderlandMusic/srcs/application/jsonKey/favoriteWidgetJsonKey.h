#ifndef FAVORITEWIDGETJSONKEY_H_H_HEAD__FILE__
#define FAVORITEWIDGETJSONKEY_H_H_HEAD__FILE__

#include <interface/iJsonKey.h>

class FavoriteWidgetJsonKey : public IJsonKey {
	QString currentName;
	QString width;
	QString height;

public:
	bool init( ) override;

	virtual const QString & getCurrentName( ) const;

	virtual const QString & getWidth( ) const;

	virtual const QString & getHeight( ) const;
};

#endif // FAVORITEWIDGETJSONKEY_H_H_HEAD__FILE__
