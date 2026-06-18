#ifndef MUSICINFOITEMWIDGET_H_H_HEAD__FILE__
#define MUSICINFOITEMWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include "../item/musicInfoItem.h"

class MusicInfoItemWidget : public QWidget, public MusicInfoItem {
	Q_OBJECT;
	friend class PlayListWidget;

protected:
	int widgetBeforeWidth;
	int widgetAfterWidth;
	int splitWidth;
	int musicNameWidth;
	int musicSingerWidth;
	int musicDurationWidth;

public:
	MusicInfoItemWidget( PlayListWidget *parent );

protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // MUSICINFOITEMWIDGET_H_H_HEAD__FILE__
