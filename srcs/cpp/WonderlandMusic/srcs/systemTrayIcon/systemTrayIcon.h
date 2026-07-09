#ifndef SYSTEMTRAYICON_H_H_HEAD__FILE__
#define SYSTEMTRAYICON_H_H_HEAD__FILE__
#include <QSystemTrayIcon>
#include "../interface/iAppCore.h"
class SystemTrayIconMenu;

class SystemTrayIcon : public QSystemTrayIcon, public IAppCore {
	Q_OBJECT;

protected:
	bool deleteResource( ) override;

protected Q_SLOTS:
	virtual void activated_slot( QSystemTrayIcon::ActivationReason reason );

public:
	SystemTrayIcon( QObject *parent = nullptr );
	SystemTrayIcon( const QIcon &icon, QObject *parent );
	bool initBefore( ) override;
	bool initAfter( ) override;
	bool init( ) override;
	~SystemTrayIcon( ) override;
Q_SIGNALS:
	void sigal_pop_menu( );
};
#endif // SYSTEMTRAYICON_H_H_HEAD__FILE__
