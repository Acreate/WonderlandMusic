#ifndef APPEVENTMANAGE_H_H_HEAD__FILE__
#define APPEVENTMANAGE_H_H_HEAD__FILE__

#include "appCore.h"
#include "appInstance.h"

class AppEventManage : public QObject, public AppCore {
	Q_OBJECT;

protected:
	AppInstance *appInstance;
	int execResultCode;
	AppUserInterfaceManage *appUserInterfaceManage;
	MainWindow *mainWindow;

protected:
	bool deleteResource( ) override;

public:
	bool init( ) override;

	~AppEventManage( ) override;

	void processEvents( QEventLoop::ProcessEventsFlags flags = QEventLoop::AllEvents );

	void processEvents( QEventLoop::ProcessEventsFlags flags, int maxtime );

	void processEvents( QEventLoop::ProcessEventsFlags flags, QDeadlineTimer deadline );

	bool sendEvent( QObject *receiver, QEvent *event );

	void postEvent( QObject *receiver, QEvent *event, int priority = Qt::NormalEventPriority );

	void sendPostedEvents( QObject *receiver = nullptr, int event_type = 0 );

	void removePostedEvents( QObject *receiver, int eventType = 0 );

	QAbstractEventDispatcher * eventDispatcher( );

	void setEventDispatcher( QAbstractEventDispatcher *eventDispatcher );

	int exec( );

	void quit( );

	virtual bool notify( QObject *object, QEvent *event );
};

#endif // APPEVENTMANAGE_H_H_HEAD__FILE__
