#ifndef SYSTEMTRAYICON_H_H_HEAD__FILE__
#define SYSTEMTRAYICON_H_H_HEAD__FILE__

#include <QSystemTrayIcon>

class SystemTrayIconMenu;

class SystemTrayIcon : public QSystemTrayIcon {
	Q_OBJECT;

protected:
	SystemTrayIconMenu *systemTrayIconMenu = nullptr;

	virtual bool deleteResource( );

protected Q_SLOTS:
	virtual void activated_slot( QSystemTrayIcon::ActivationReason reason );

public:
	SystemTrayIcon( QObject *parent = nullptr );

	SystemTrayIcon( const QIcon &icon, QObject *parent );

	virtual bool init( );

	~SystemTrayIcon( ) override;
};

#endif // SYSTEMTRAYICON_H_H_HEAD__FILE__
