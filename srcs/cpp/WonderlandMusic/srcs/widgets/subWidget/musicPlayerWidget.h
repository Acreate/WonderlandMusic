#ifndef MUSICPLAYERWIDGET_H_H_HEAD__FILE__
#define MUSICPLAYERWIDGET_H_H_HEAD__FILE__

#include <QWidget>
/// @brief 音乐播放面板
class MusicPlayerWidget : public QWidget {
	Q_OBJECT;
public:
	MusicPlayerWidget( QWidget *parent = nullptr ) : QWidget( parent ) { }
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // MUSICPLAYERWIDGET_H_H_HEAD__FILE__
