#ifndef MUSICINFOITEMWIDGET_H_H_HEAD__FILE__
#define MUSICINFOITEMWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include "../item/musicInfoItem.h"

class MusicInfoItemWidget : public QWidget, public MusicInfoItem {
	Q_OBJECT;
	friend class PlayerWindow;

protected:
	int widgetBeforeWidth;
	int widgetAfterWidth;
	int splitWidth;
	int indexWidth;
	int musicNameWidth;
	int musicSingerWidth;
	int musicDurationWidth;
public:
	MusicInfoItemWidget( PlayerWindow *parent );

protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // MUSICINFOITEMWIDGET_H_H_HEAD__FILE__
