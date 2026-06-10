#ifndef MUSICLISTWIDGET_H_H_HEAD__FILE__
#define MUSICLISTWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include <base/baseWidget/baseWidget.h>

class MusicInfo;
class MusicListItemWidget;
class MusicListWidget : public BaseWidget {
	Q_OBJECT;
protected:
	std::vector< MusicListItemWidget * > musicListItemWidgets;
public:
	MusicListWidget( QWidget *parent );
	virtual bool appendItem( MusicInfo *music_info_ptr );
	virtual bool sort( );
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // MUSICLISTWIDGET_H_H_HEAD__FILE__
