#ifndef SYSTEMTRAYICONMENU_H_H_HEAD__FILE__
#define SYSTEMTRAYICONMENU_H_H_HEAD__FILE__
#include <QMenu>

#include "../interface/iAppCore.h"
#include "../interface/iAppResourceCore.h"

class SystemTrayIconMenu : public QMenu, public IAppCore, public IAppResourceCore {
	Q_OBJECT;

protected:
	QAction *showMainWindowItem;
	QAction *quitApp;

private:
	void slot_showMainWindow( );
	void slot_quitApp( );

protected:
	bool deleteResource( ) override;

public:
	SystemTrayIconMenu( QWidget *parent = nullptr );

	SystemTrayIconMenu( const QString &title, QWidget *parent );

	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;

	~SystemTrayIconMenu( ) override;
};

#endif // SYSTEMTRAYICONMENU_H_H_HEAD__FILE__
