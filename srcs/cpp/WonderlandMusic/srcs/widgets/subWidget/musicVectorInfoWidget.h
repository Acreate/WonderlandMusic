#ifndef MUSICVECTORINFOWIDGET_H_H_HEAD__FILE__
#define MUSICVECTORINFOWIDGET_H_H_HEAD__FILE__

#include <QWidget>
class MusicVectorInfoItem;
/// @brief 音乐列表信息面板
class MusicVectorInfoWidget : public QWidget {
	Q_OBJECT;
protected:
	QPoint offset;
	std::vector< MusicVectorInfoItem * > musicVectorInfoItems;
public:
	MusicVectorInfoWidget( QWidget *parent = nullptr ) : QWidget( parent ) { }
protected:
	void paintEvent( QPaintEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	/// @brief 功能项被点击
	/// @param click_item 点击项
	void clickFunctionItem( const MusicVectorInfoItem &click_item );
};

#endif // MUSICVECTORINFOWIDGET_H_H_HEAD__FILE__
