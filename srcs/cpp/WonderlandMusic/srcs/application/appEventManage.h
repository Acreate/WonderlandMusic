#ifndef APPEVENTMANAGE_H_H_HEAD__FILE__
#define APPEVENTMANAGE_H_H_HEAD__FILE__

#include <QObject>

#include "appCore.h"

#include "eventMacro/eventMacroDefault.h"

class QAbstractEventDispatcher;
class MainWindow;
class AppUserInterfaceManage;
class AppInstance;
declaration_signal_event_info( PlayerListWidget );

class AppEventManage : public QObject, public AppCore {
	Q_OBJECT;

protected:
	AppInstance *appInstance;
	int execResultCode;
	AppUserInterfaceManage *appUserInterfaceManage;
	MainWindow *mainWindow;

private:
	static AppEventManage * getInstance( );

protected:
	bool deleteResource( ) override;

public:
	bool init( ) override;

	~AppEventManage( ) override;

	void processEvents( );

	bool sendEvent( QObject *receiver, QEvent *event );

	void postEvent( QObject *receiver, QEvent *event, int priority = Qt::NormalEventPriority );

	void sendPostedEvents( QObject *receiver = nullptr, int event_type = 0 );

	void removePostedEvents( QObject *receiver, int eventType = 0 );

	QAbstractEventDispatcher * eventDispatcher( );

	void setEventDispatcher( QAbstractEventDispatcher *eventDispatcher );

	int exec( );

	void quit( );

	virtual bool notify( QObject *object, QEvent *event );

public:
	definition_AppEventManage_connect_Type( PlayerListWidget );

	// 触发信号函数
Q_SIGNALS:
	declaration_AppEventManage_signal( PlayerListWidget );
};

// 触发信号
definition_emit_event( PlayerListWidget );
#endif // APPEVENTMANAGE_H_H_HEAD__FILE__
