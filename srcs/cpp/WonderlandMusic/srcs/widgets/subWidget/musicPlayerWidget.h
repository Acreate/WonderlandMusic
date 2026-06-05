#ifndef MUSICPLAYERWIDGET_H_H_HEAD__FILE__
#define MUSICPLAYERWIDGET_H_H_HEAD__FILE__

#include <QWidget>
class MusicPlayerItem;
/// @brief 音乐播放面板
class MusicPlayerWidget : public QWidget {
	Q_OBJECT;
protected:
	QPoint offset;
	std::vector<MusicPlayerItem*> musicPlayerItems;
public:
	MusicPlayerWidget( QWidget *parent = nullptr ) : QWidget( parent ) { }
protected:
	void paintEvent( QPaintEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	/// @brief 功能项被点击
	/// @param click_item 点击项
	void clickFunctionItem( const MusicPlayerItem &click_item );
};

#endif // MUSICPLAYERWIDGET_H_H_HEAD__FILE__
