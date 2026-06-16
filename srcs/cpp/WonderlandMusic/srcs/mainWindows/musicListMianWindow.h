#ifndef MUSICLISTMIANWINDOW_H_H_HEAD__FILE__
#define MUSICLISTMIANWINDOW_H_H_HEAD__FILE__

#include <base/baseWindow/baseWidgetTypeMainWindow.h>
class QVBoxLayout;
class MusicListTopWidget;
class QScrollArea;
class MusicListWidget;
class MusicListMianWindow : public BaseWidgetTypeMainWindow {
	Q_OBJECT;
protected:
	QWidget* mainWidget;
	MusicListTopWidget *musicListTopWidget;
	MusicListWidget *musicListWidget;
	QScrollArea* musicScrollArea;
	QVBoxLayout* mainLayout;
public:
	MusicListMianWindow( QWidget *parent );
	virtual MusicListWidget * getMusicListWidget( ) const { return musicListWidget; }
protected:
	void resizeEvent( QResizeEvent *event ) override;
	void showEvent( QShowEvent *event ) override;
	void paintEvent( QPaintEvent *event ) override;
public:
	bool eventFilter( QObject *watched, QEvent *event ) override;
};

#endif // MUSICLISTMIANWINDOW_H_H_HEAD__FILE__
