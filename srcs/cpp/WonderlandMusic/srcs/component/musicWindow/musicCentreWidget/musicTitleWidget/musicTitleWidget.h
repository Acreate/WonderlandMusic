#ifndef MUSICTITLEWIDGET_H_H_HEAD__FILE__
#define MUSICTITLEWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include <interface/iAppCore.h>

class MusicCentreWidget;

class MusicTitleWidget : public QWidget, public IAppCore {
	Q_OBJECT;
	MusicCentreWidget *musicCentreWidget;
	int suggestHeight;
	int intervalWidth;
	int separatorWidth;
	int musicCodeWidth;
	int musicNameWidth;
	int musicSingerNameWidth;
	int musicDurationTimeWidth;

public:
	MusicTitleWidget( MusicCentreWidget *music_centre_widget );
	~MusicTitleWidget( ) override;
	virtual int getSuggestHeight( ) const;

protected:
	bool deleteResource( ) override;
	void paintEvent( QPaintEvent *event ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
};
#endif // MUSICTITLEWIDGET_H_H_HEAD__FILE__
