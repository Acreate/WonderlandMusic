#ifndef IMUSICWIDGET_H_H_HEAD__FILE__
#define IMUSICWIDGET_H_H_HEAD__FILE__

#include "../musicWidgetChild/musicWidgetChild.h"

class QWidget;

class IMusicWidget : public MusicWidgetChild {
protected:

public:
	virtual QWidget * toWidget( ) = 0;
	virtual bool drawWidgeTarget( QWidget *widget ) = 0;
	virtual MusicCentreWidget * getMusicCentreWidget( ) const = 0;
};

#endif // IMUSICWIDGET_H_H_HEAD__FILE__
