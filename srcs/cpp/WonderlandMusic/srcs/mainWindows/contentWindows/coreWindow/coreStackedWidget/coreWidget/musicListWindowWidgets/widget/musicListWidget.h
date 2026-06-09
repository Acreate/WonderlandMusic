#ifndef MUSICLISTWIDGET_H_H_HEAD__FILE__
#define MUSICLISTWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include <base/baseWidget/baseWidget.h>

class MusicListItemWidget;
class MusicListWidget : public BaseWidget {
	Q_OBJECT;
protected:
	std::vector< MusicListItemWidget * > musicListItemWidgets;
public:
	MusicListWidget( QWidget *parent );
	virtual std::vector< MusicListItemWidget * > appendMusicFile( const QString &file_path );
	virtual std::vector< MusicListItemWidget * > appendMusicFile( const QStringList &file_path_list );
	virtual bool sort( );
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // MUSICLISTWIDGET_H_H_HEAD__FILE__
