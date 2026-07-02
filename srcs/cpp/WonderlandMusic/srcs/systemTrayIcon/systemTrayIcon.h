#ifndef SYSTEMTRAYICON_H_H_HEAD__FILE__
#define SYSTEMTRAYICON_H_H_HEAD__FILE__

#include <QSystemTrayIcon>

#include "../application/appCore.h"

class SystemTrayIconMenu;

class SystemTrayIcon : public QSystemTrayIcon, public AppCore {
	Q_OBJECT;

protected:
	SystemTrayIconMenu *systemTrayIconMenu = nullptr;

	bool deleteResource( ) override;

protected Q_SLOTS:
	virtual void activated_slot( QSystemTrayIcon::ActivationReason reason );

public:
	SystemTrayIcon( QObject *parent = nullptr );

	SystemTrayIcon( const QIcon &icon, QObject *parent );

	bool init( ) override;

	~SystemTrayIcon( ) override;
};

#endif // SYSTEMTRAYICON_H_H_HEAD__FILE__
