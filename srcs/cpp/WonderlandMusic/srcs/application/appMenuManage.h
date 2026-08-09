#ifndef APPMENUMANAGE_H_H_HEAD__FILE__
#define APPMENUMANAGE_H_H_HEAD__FILE__
#include <QObject>

#include "../interface/iAppCore.h"

class SystemTrayIconMenu;
class QPoint;

class AppMenuManage : public QObject, public IAppCore {
	Q_OBJECT;

protected:
	SystemTrayIconMenu *systemTrayIconMenu = nullptr;

public:
	AppMenuManage( );

	~AppMenuManage( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;

	bool init( ) override;

	bool initAfter( ) override;

	virtual bool popSystemTratIconMenu( const QPoint &pos ) const;

	virtual bool popPlayerListWidgetMenu( const QPoint &pos ) const;

	virtual bool popFavoriteWidgetMenu( const QPoint &pos ) const;

	virtual SystemTrayIconMenu * getSystemTrayIconMenu( ) const;
};

#endif // APPMENUMANAGE_H_H_HEAD__FILE__
