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
declaration_signal_event_info( PlayerToolsWidget );
declaration_signal_event_info( PlayerWidgetMenu );

class AppEventManage : public QObject, public AppCore {
	Q_OBJECT;

protected:
	AppInstance *appInstance;
	int execResultCode;

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

	/*
	 * 信号链接声明
	 */
public:
	definition_AppEventManage_connect_Type( PlayerListWidget );

	definition_AppEventManage_connect_Type( PlayerToolsWidget );

	definition_AppEventManage_connect_Type( PlayerWidgetMenu );

	/*
	 * 触发信号函数声明
	 */
Q_SIGNALS:
	declaration_AppEventManage_signal( PlayerListWidget );

	declaration_AppEventManage_signal( PlayerToolsWidget );

	declaration_AppEventManage_signal( PlayerWidgetMenu );
};

/*
 * 触发信号，事件函数声明
 */

definition_emit_event( PlayerListWidget );

definition_emit_event( PlayerToolsWidget );

definition_emit_event( PlayerWidgetMenu );
#endif // APPEVENTMANAGE_H_H_HEAD__FILE__
