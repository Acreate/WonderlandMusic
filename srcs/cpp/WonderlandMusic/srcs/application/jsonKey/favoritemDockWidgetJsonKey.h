#ifndef FAVORITEMDOCKWIDGETJSONKEY_H_H_HEAD__FILE__
#define FAVORITEMDOCKWIDGETJSONKEY_H_H_HEAD__FILE__
#include "../../interface/iJsonKey.h"

class FavoritemDockWidgetJsonKey : public IJsonKey{
	QString width;

public:
	bool init( ) override;

	virtual const QString & getWidth( ) const;
};

#endif // FAVORITEMDOCKWIDGETJSONKEY_H_H_HEAD__FILE__
