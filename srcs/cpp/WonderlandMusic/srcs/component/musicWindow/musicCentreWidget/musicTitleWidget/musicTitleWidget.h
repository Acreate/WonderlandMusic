#ifndef MUSICTITLEWIDGET_H_H_HEAD__FILE__
#define MUSICTITLEWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include <interface/iAppCore.h>

class MusicTitleWidget : public QWidget, public IAppCore {
	Q_OBJECT;
	friend class MusicCentreWidget;
	MusicCentreWidget *musicCentreWidget;
	MusicTitleWidget( MusicCentreWidget *music_centre_widget );
	int suggestHeight;

protected:
	~MusicTitleWidget( ) override;

protected:
	bool deleteResource( ) override;
	void paintEvent( QPaintEvent *event ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	virtual int getSuggestHeight( ) const;
};
#endif // MUSICTITLEWIDGET_H_H_HEAD__FILE__
