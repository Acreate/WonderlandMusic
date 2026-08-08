#ifndef MUSICTOOLWIDGET_H_H_HEAD__FILE__
#define MUSICTOOLWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include <interface/iAppCore.h>

#include "../../../../interface/iAppJsonData.h"

class MusicToolWidget : public QWidget, public IAppCore, public IAppJsonData {
	Q_OBJECT;
	friend class MusicCentreWidget;

private:
	MusicCentreWidget *musicCentreWidget;
	double playerVolume;
	QString playerMusicFile;
	qint64 playerDuration;

protected:
	MusicToolWidget( MusicCentreWidget *music_centre_widget );
	~MusicToolWidget( ) override;

protected:
	bool deleteResource( ) override;

	void paintEvent( QPaintEvent *event ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	virtual int getSuggestHeight( ) const;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
};
#endif // MUSICTOOLWIDGET_H_H_HEAD__FILE__
