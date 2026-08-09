#ifndef MUSICLISTMENU_H_H_HEAD__FILE__
#define MUSICLISTMENU_H_H_HEAD__FILE__
#include <QMenu>

#include <interface/iAppCore.h>

class MusicCentreWidget;

class MusicListMenu : public QMenu, public IAppCore{
	Q_OBJECT;
protected:
	MusicCentreWidget* musicCentreWidget;
public:
	MusicListMenu( MusicCentreWidget *music_centre_widget );
	~MusicListMenu( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
};

#endif // MUSICLISTMENU_H_H_HEAD__FILE__
