#ifndef MUSICLISTWIDGET_H_H_HEAD__FILE__
#define MUSICLISTWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include <interface/iAppCore.h>

#include <interface/iAppJsonData.h>

class MusicItem;

class MusicListWidget : public QWidget, public IAppCore, public IAppJsonData {
	Q_OBJECT;
	friend class MusicCentreWidget;
	MusicCentreWidget *musicCentreWidget;
	std::vector< MusicItem * > musicItems;

protected:
	MusicListWidget( MusicCentreWidget *music_centre_widget );
	~MusicListWidget( ) override;

protected:
	bool deleteResource( ) override;
	void paintEvent( QPaintEvent *event ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
};
#endif // MUSICLISTWIDGET_H_H_HEAD__FILE__
