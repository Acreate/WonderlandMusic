#ifndef MUSICFAVORITEWIDGET_H_H_HEAD__FILE__
#define MUSICFAVORITEWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include <interface/iAppCore.h>

#include "../../../../interface/iAppJsonData.h"

class MusicfavoriteWidget : public QWidget, public IAppCore, public IAppJsonData {
	Q_OBJECT;
	friend class MusicCentreWidget;
	MusicCentreWidget *musicCentreWidget;
	MusicfavoriteWidget( MusicCentreWidget *music_centre_widget );

protected:
	~MusicfavoriteWidget( ) override;

protected:
	bool deleteResource( ) override;
	void paintEvent( QPaintEvent *event ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	virtual int getSuggestWidth( ) const;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
};

#endif // MUSICFAVORITEWIDGET_H_H_HEAD__FILE__
