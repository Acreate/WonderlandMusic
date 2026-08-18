#ifndef MUSICTITLEWIDGET_H_H_HEAD__FILE__
#define MUSICTITLEWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include "../component/musicWindow/interface/widget/iMusicTitleWidget.h"

#include "../interface/iAppResourceCore.h"

class MusicTitleWidget : public QWidget, public IMusicTitleWidget, public IAppResourceCore {
	Q_OBJECT;

public:
	MusicTitleWidget( );
	~MusicTitleWidget( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;

protected:
	bool setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) override;
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;

	QWidget * toWidget( ) override;
	bool drawWidgeTarget( QWidget *widget ) override;
	MusicCentreWidget * getMusicCentreWidget( ) const override;
	bool sendMouseMoveEvent( const QMouseEvent &mouse_event ) override;
	bool sendMouseRelaseEvent( const QMouseEvent &mouse_event ) override;
	bool sendMousePressEvent( const QMouseEvent &mouse_event ) override;
};

#endif // MUSICTITLEWIDGET_H_H_HEAD__FILE__
