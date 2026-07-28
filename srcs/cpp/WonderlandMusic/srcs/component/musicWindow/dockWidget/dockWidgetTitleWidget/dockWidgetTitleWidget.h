#ifndef DOCKWIDGETTITLEWIDGET_H_H_HEAD__FILE__
#define DOCKWIDGETTITLEWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include <interface/iAppCore.h>

class QDockWidget;

class DockWidgetTitleWidget : public QWidget, public IAppCore {
	Q_OBJECT;
private:
	QDockWidget *dockWidget;
public:
	DockWidgetTitleWidget( QDockWidget *parent );
	~DockWidgetTitleWidget( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
};
#endif // DOCKWIDGETTITLEWIDGET_H_H_HEAD__FILE__
