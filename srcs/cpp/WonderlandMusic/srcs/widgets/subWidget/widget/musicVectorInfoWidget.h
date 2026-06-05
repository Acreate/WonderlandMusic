#ifndef MUSICVECTORINFOWIDGET_H_H_HEAD__FILE__
#define MUSICVECTORINFOWIDGET_H_H_HEAD__FILE__

#include <QWidget>
/// @brief 音乐列表信息面板
class MusicVectorInfoWidget : public QWidget {
	Q_OBJECT;
public:
	MusicVectorInfoWidget( QWidget *parent = nullptr ) : QWidget( parent ) { }
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // MUSICVECTORINFOWIDGET_H_H_HEAD__FILE__
