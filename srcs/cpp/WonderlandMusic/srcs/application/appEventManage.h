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
declaration_signal_event_info( MusicPlayer );
declaration_signal_event_info( MusicPlayerThread );
declaration_signal_event_info( MusicMediaPlayerThread );
declaration_signal_event_info( MusicAudioSinkPlayerThread );

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
	 * 触发信号函数声明
	 */
Q_SIGNALS:
	declaration_AppEventManage_signal( PlayerListWidget );

	declaration_AppEventManage_signal( PlayerToolsWidget );

	declaration_AppEventManage_signal( PlayerWidgetMenu );

	declaration_AppEventManage_signal( MusicPlayer );

	declaration_AppEventManage_signal( MusicPlayerThread );

	/*
	 * 信号链接声明
	 */
public:
	definition_AppEventManage_connect_Type( PlayerListWidget );

	definition_AppEventManage_connect_Type( PlayerToolsWidget );

	definition_AppEventManage_connect_Type( PlayerWidgetMenu );

	definition_AppEventManage_connect_Type( MusicPlayer );

	definition_AppEventManage_connect_Type( MusicPlayerThread );
};

/*
 * 触发信号，事件函数声明
 */

definition_emit_event( PlayerListWidget );

definition_emit_event( PlayerToolsWidget );

definition_emit_event( PlayerWidgetMenu );

definition_emit_event( MusicPlayer );

definition_emit_event( MusicPlayerThread );

definition_emit_inherit_event( MusicMediaPlayerThread, MusicPlayerThread );

definition_emit_inherit_event( MusicAudioSinkPlayerThread, MusicPlayerThread );
#endif // APPEVENTMANAGE_H_H_HEAD__FILE__
