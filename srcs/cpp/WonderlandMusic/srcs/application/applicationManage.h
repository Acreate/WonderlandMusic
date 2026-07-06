#ifndef APPLICATIONMANAGE_H_H_HEAD__FILE__
#define APPLICATIONMANAGE_H_H_HEAD__FILE__
#include <QApplication>

#include "../interface/iAppCore.h"

class AppDataManage;
class AppUserInterfaceManage;
class MainWindow;

class ApplicationManage : public QApplication, public IAppCore {
	Q_OBJECT;

protected:
	AppUserInterfaceManage *appUserInterfaceManage = nullptr;
	AppDataManage *appDataManage = nullptr;
	MainWindow *mainWindow = nullptr;
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	ApplicationManage( int &argc, char **argv, int app_flag_s = QCoreApplication::ApplicationFlags );

	~ApplicationManage( ) override;

	bool notify( QObject *, QEvent * ) override;
Q_SIGNALS:
	void signal_app_quit( );
};

#endif // APPLICATIONMANAGE_H_H_HEAD__FILE__
