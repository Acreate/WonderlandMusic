#ifndef MUSICLISTWIDGET_H_H_HEAD__FILE__
#define MUSICLISTWIDGET_H_H_HEAD__FILE__

#include <base/baseWidget/baseWidget.h>

class QMediaMetaData;
class MusicInfo;
class MusicListItemWidget;
class MusicListWidget : public BaseWidget {
	Q_OBJECT;
protected:
	std::vector< MusicListItemWidget * > musicListItemWidgets;
public:
	MusicListWidget( QWidget *parent );
protected:
	virtual bool appendItem( const MusicInfo &media_meta_data );
	virtual bool sort( );

};

#endif // MUSICLISTWIDGET_H_H_HEAD__FILE__
