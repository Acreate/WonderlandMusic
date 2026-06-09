#ifndef MUSICLISTITEMWIDGET_H_H_HEAD__FILE__
#define MUSICLISTITEMWIDGET_H_H_HEAD__FILE__

#include <base/baseWidget/baseWidget.h>
class MusicInfo;
class Music;
class MusicListItemWidget : public BaseWidget {
	Q_OBJECT;
protected:
	MusicInfo *musicInfo;
public:
	MusicListItemWidget( QWidget *parent, const QString &file_path );
	virtual const MusicInfo * getMusicInfo( ) const { return musicInfo; }
};

#endif // MUSICLISTITEMWIDGET_H_H_HEAD__FILE__
