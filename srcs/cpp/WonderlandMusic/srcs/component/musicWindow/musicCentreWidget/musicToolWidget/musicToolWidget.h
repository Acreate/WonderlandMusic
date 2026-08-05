#ifndef MUSICTOOLWIDGET_H_H_HEAD__FILE__
#define MUSICTOOLWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include <interface/iAppCore.h>

class MusicToolWidget : public QWidget, public IAppCore {
	Q_OBJECT;
	friend class MusicCentreWidget;
	MusicCentreWidget *musicCentreWidget;
	MusicToolWidget( MusicCentreWidget *music_centre_widget );

protected:
	~MusicToolWidget( ) override;

protected:
	bool deleteResource( ) override;

	void paintEvent( QPaintEvent *event ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	virtual int getSuggestHeight( ) const;
};
#endif // MUSICTOOLWIDGET_H_H_HEAD__FILE__
