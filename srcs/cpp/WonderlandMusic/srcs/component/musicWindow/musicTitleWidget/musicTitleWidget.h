#ifndef MUSICTITLEWIDGET_H_H_HEAD__FILE__
#define MUSICTITLEWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include "../../../interface/iAppCore.h"

class MusicTitleWidget : public QWidget, public IAppCore{
	Q_OBJECT;
	friend class MusicTitleDockWidget;
private:
	MusicTitleWidget( );
	~MusicTitleWidget( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
};

#endif // MUSICTITLEWIDGET_H_H_HEAD__FILE__
