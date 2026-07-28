#ifndef MUSICCENTRESCROLLWIDGET_H_H_HEAD__FILE__
#define MUSICCENTRESCROLLWIDGET_H_H_HEAD__FILE__
#include <QScrollArea>

#include <interface/iAppCore.h>

class MusicCentreWidget;

class MusicCentreScrollWidget : public QScrollArea, public IAppCore {
	Q_OBJECT;
	friend class MusicWindow;

private:
	MusicWindow *musicWindow;
	MusicCentreWidget *musicCentreWidget = nullptr;
	MusicCentreScrollWidget( MusicWindow *music_window );
	~MusicCentreScrollWidget( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
};

#endif // MUSICCENTRESCROLLWIDGET_H_H_HEAD__FILE__
