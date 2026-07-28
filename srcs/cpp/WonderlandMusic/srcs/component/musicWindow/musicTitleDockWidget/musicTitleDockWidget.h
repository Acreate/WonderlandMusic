#ifndef MUSICTITLEDOCKWIDGET_H_H_HEAD__FILE__
#define MUSICTITLEDOCKWIDGET_H_H_HEAD__FILE__
#include <QDockWidget>

#include "../../../interface/iAppCore.h"

class MusicTitleWidget;

class MusicTitleDockWidget : public QDockWidget, public IAppCore {
	Q_OBJECT;
	friend class MusicWindow;

private:
	MusicWindow *musicWindow = nullptr;
	MusicTitleWidget *musicTitleWidget = nullptr;
	MusicTitleDockWidget( MusicWindow *music_window );
	~MusicTitleDockWidget( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
};

#endif // MUSICTITLEDOCKWIDGET_H_H_HEAD__FILE__
