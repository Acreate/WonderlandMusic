#ifndef SYSTEMTRAYICONMENU_H_H_HEAD__FILE__
#define SYSTEMTRAYICONMENU_H_H_HEAD__FILE__
#include <QMenu>

#include "../interface/iAppCore.h"

class SystemTrayIconMenu : public QMenu, public IAppCore {
	Q_OBJECT;

protected:
	QAction *showMainWindowItem;
	QAction *quitApp;

protected:
	bool deleteResource( ) override;

public:
	SystemTrayIconMenu( QWidget *parent = nullptr );

	SystemTrayIconMenu( const QString &title, QWidget *parent );

	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;

	~SystemTrayIconMenu( ) override;
Q_SIGNALS:
	void signal_show_main_window( );
	void signal_quit_app( );
};

#endif // SYSTEMTRAYICONMENU_H_H_HEAD__FILE__
