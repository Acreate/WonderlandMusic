#ifndef MUSICTITLEWIDGET_H_H_HEAD__FILE__
#define MUSICTITLEWIDGET_H_H_HEAD__FILE__
#include <QWidget>
#include <interface/iAppCore.h>

class MusicTitleWidthInfo;
class MusicWindow;

class MusicTitleWidget : public QWidget, public IAppCore {
	Q_OBJECT;
	friend class MusicTitleDockWidget;
	friend class MusicTitleDockWidget;

private:
	MusicTitleWidthInfo *musicTitleWidthInfo = nullptr;

private:
	MusicTitleWidget( QWidget *parent );
	~MusicTitleWidget( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	virtual void setMusicTitleWidthInfo( MusicTitleWidthInfo &music_title_width_info );
	virtual MusicTitleWidthInfo getMusicTitleWidthInfo( ) const;
Q_SIGNALS:
	void changeWidth( MusicTitleWidget *music_title_widget );
};

#endif // MUSICTITLEWIDGET_H_H_HEAD__FILE__
