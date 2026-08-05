#ifndef MUSICLISTWIDGET_H_H_HEAD__FILE__
#define MUSICLISTWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include <interface/iAppCore.h>

class MusicListWidget : public QWidget, public IAppCore {
	Q_OBJECT;
	friend class MusicCentreWidget;
	MusicCentreWidget *musicCentreWidget;
	MusicListWidget( MusicCentreWidget *music_centre_widget );

protected:
	~MusicListWidget( ) override {
		deleteResource( );
	}

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
};
#endif // MUSICLISTWIDGET_H_H_HEAD__FILE__
