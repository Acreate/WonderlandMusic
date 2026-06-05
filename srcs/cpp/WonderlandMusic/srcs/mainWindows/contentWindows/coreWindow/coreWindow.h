#ifndef COREWINDOW_H_H_HEAD__FILE__
#define COREWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>
class ContentWindow;
class CoreWindow : public QMainWindow {
	Q_OBJECT;
protected:
	ContentWindow *contentWindow;
public:
	CoreWindow( ContentWindow *parent );
protected:
	void paintEvent( QPaintEvent *event ) override;
};
class CoreInfo {

};
#endif // COREWINDOW_H_H_HEAD__FILE__
