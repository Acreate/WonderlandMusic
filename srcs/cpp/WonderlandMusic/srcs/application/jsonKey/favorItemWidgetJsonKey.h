#ifndef FAVORITEMWIDGETJSONKEY_H_H_HEAD__FILE__
#define FAVORITEMWIDGETJSONKEY_H_H_HEAD__FILE__

#include "../../interface/iJsonKey.h"

class FavorItemWidgetJsonKey : public IJsonKey {
	QString favoriteVector;
	QString favoriteData;
	QString favoriteCount;
	QString favorItemWidget;
	QString name;
public:
	bool init( ) override;

	virtual const QString & getFavoriteVector( ) const;

	virtual const QString & getFavoriteData( ) const;

	virtual const QString & getFavoriteCount( ) const;

	virtual const QString & getFavorItemWidget( ) const;

	virtual const QString & getName( ) const;
};

#endif // FAVORITEMWIDGETJSONKEY_H_H_HEAD__FILE__
