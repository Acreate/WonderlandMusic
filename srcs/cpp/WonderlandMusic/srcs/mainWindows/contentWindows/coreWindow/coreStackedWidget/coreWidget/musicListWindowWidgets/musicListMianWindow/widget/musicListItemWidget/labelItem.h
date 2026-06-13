#ifndef LABELITEM_H_H_HEAD__FILE__
#define LABELITEM_H_H_HEAD__FILE__

#include <base/baseWidget/baseWidget.h>
class LabelItem : public BaseWidget {
	Q_OBJECT;
protected:
	QLabel *titleName;
	/// @brief 绘制的分隔符宽度
	int drawDecollatorWidth;
	/// @brief 绘制的分隔符占用空间
	int drawDecollatorInterspace;
public:
	LabelItem( const QString &title_name, QWidget *parent );
	virtual QString getTitleName( ) const;
	virtual bool isContainsDecollator( const QPoint &parent_point ) const;
protected:
	void paintEvent( QPaintEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
};

#endif // LABELITEM_H_H_HEAD__FILE__
