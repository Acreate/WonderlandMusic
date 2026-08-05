#ifndef MUSICCENTREWIDGET_H_H_HEAD__FILE__
#define MUSICCENTREWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include <interface/iAppCore.h>

class TransparencyScrollBar;
class QScrollArea;
class MusicListWidget;
class UserMutex;
class MusicfavoriteWidget;
class MusicToolWidget;
class MusicTitleWidget;
class MusicWindow;

class MusicCentreWidget : public QWidget, public IAppCore {
	Q_OBJECT;
	friend class MusicWindow;

private:
	MusicWindow *musicWindow;
	UserMutex *userMutex = nullptr;
	QScrollArea *musicfavoriteWidgetScrollArea = nullptr;
	QScrollArea *musicTitleWidgetScrollArea = nullptr;
	QScrollArea *musicListWidgetScrollArea = nullptr;
	MusicfavoriteWidget *musicfavoriteWidget = nullptr;
	MusicTitleWidget *musicTitleWidget = nullptr;
	MusicListWidget *musicListWidget = nullptr;
	MusicToolWidget *musicToolWidget = nullptr;
	MusicCentreWidget( MusicWindow *parent );

protected:
	~MusicCentreWidget( ) override;
	bool deleteResource( ) override;
	virtual bool unSafetyClearShow( );
	void resizeEvent( QResizeEvent *event ) override;
	virtual QScrollArea * createControlScrollArea( QWidget *widget );

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	virtual void clearShowMusic( );
	virtual bool calculateSize( );
};

#endif // MUSICCENTREWIDGET_H_H_HEAD__FILE__
