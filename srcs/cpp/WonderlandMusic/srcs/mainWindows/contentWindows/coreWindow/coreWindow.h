#ifndef COREWINDOW_H_H_HEAD__FILE__
#define COREWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>
class CoreStackedWidget;
class CoreStackedWidgeEventInfo;
class ContentWindow;
class CoreWindow : public QMainWindow {
	friend class CoreStackedWidgetEvent;
	Q_OBJECT;
protected:
	/// @brief 父窗口
	ContentWindow *contentWindow;
	/// @brief 堆叠的窗口
	CoreStackedWidget *coreStackedWidget;
public:
	CoreWindow( ContentWindow *parent );
protected:
	void paintEvent( QPaintEvent *event ) override;
private:
	virtual size_t triggerCoreStackedWidgetEvent( CoreStackedWidget *sender_core_stacked_widget, const CoreStackedWidgeEventInfo &core_stacked_widge_event_info ) {
		return 0;
	}
};
class CoreInfo {

};

class CoreStackedWidgetEvent {
	friend class CoreStackedWidget;
	static size_t triggerCoreStackedWidgetEvent( CoreWindow *receive_content_window, CoreStackedWidget *sender_core_stacked_widget, const CoreStackedWidgeEventInfo &core_stacked_widge_event_info ) {
		return receive_content_window->triggerCoreStackedWidgetEvent( sender_core_stacked_widget, core_stacked_widge_event_info );
	}
};

#endif // COREWINDOW_H_H_HEAD__FILE__
