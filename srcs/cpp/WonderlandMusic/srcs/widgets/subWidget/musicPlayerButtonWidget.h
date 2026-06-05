#ifndef MUSICPLAYERBUTTONWIDGET_H_H_HEAD__FILE__
#define MUSICPLAYERBUTTONWIDGET_H_H_HEAD__FILE__

#include <QWidget>
class MusicPlayerButtonItem;
/// @brief 音乐播放功能面板
class MusicPlayerButtonWidget : public QWidget {
	Q_OBJECT;
protected:
	QPoint offset;
	std::vector< MusicPlayerButtonItem * > musicPlayerButtonItems;
public:
	MusicPlayerButtonWidget( QWidget *parent = nullptr ) : QWidget( parent ) { }
protected:
	void paintEvent( QPaintEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	/// @brief 功能项被点击
	/// @param click_item 点击项
	void clickFunctionItem( const MusicPlayerButtonItem &click_item );
};
#endif // MUSICPLAYERBUTTONWIDGET_H_H_HEAD__FILE__
