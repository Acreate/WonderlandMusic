#ifndef MUSICPLAYERBUTTONWIDGET_H_H_HEAD__FILE__
#define MUSICPLAYERBUTTONWIDGET_H_H_HEAD__FILE__

#include <QWidget>
/// @brief 音乐播放功能面板
class MusicPlayerButtonWidget : public QWidget {
	Q_OBJECT;
public:
	MusicPlayerButtonWidget( QWidget *parent = nullptr ) : QWidget( parent ) { }
protected:
	void paintEvent( QPaintEvent *event ) override;
};
#endif // MUSICPLAYERBUTTONWIDGET_H_H_HEAD__FILE__
