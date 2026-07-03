#ifndef MUSICLISTSTACKEDWIDGET_H_H_HEAD__FILE__
#define MUSICLISTSTACKEDWIDGET_H_H_HEAD__FILE__
#include <QStackedWidget>

#include "../interface/iAppCore.h"

class MusicListStackedWidget : public QStackedWidget, public IAppCore {
	Q_OBJECT;

public:
	MusicListStackedWidget( QWidget *parent );

	~MusicListStackedWidget( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool init( ) override;
};

#endif // MUSICLISTSTACKEDWIDGET_H_H_HEAD__FILE__
