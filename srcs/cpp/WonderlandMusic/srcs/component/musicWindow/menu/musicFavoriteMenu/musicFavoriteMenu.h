#ifndef MUSICFAVORITEMENU_H_H_HEAD__FILE__
#define MUSICFAVORITEMENU_H_H_HEAD__FILE__
#include <QMenu>

#include <interface/iAppCore.h>

class MusicCentreWidget;

class MusicFavoriteMenu : public QMenu, public IAppCore {
	Q_OBJECT;

protected:
	MusicCentreWidget *musicCentreWidget;

public:
	MusicFavoriteMenu( MusicCentreWidget *music_centre_widget );
	~MusicFavoriteMenu( ) override;

protected:
	bool deleteResource( ) override;
	void showEvent( QShowEvent *event ) override;
	void hideEvent( QHideEvent * ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
};

#endif // MUSICFAVORITEMENU_H_H_HEAD__FILE__
