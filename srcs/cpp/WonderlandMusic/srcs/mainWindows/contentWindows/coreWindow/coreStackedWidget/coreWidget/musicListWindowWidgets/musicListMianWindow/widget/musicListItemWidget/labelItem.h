#ifndef LABELITEM_H_H_HEAD__FILE__
#define LABELITEM_H_H_HEAD__FILE__

#include <base/baseWidget/baseWidget.h>
class LabelItem : public BaseWidget {
	Q_OBJECT;
protected:
	/// @brief 绘制的分隔符宽度
	int drawDecollatorWidth;
	/// @brief 绘制的分隔符占用空间
	int drawDecollatorInterspace;
	/// @brief 渲染字符串的缓存
	QImage *renderTxtBuff;
	/// @brief 标签显示内容
	QString titleName;
public:
	~LabelItem( ) override;
	LabelItem( const QString &title_name, QWidget *parent );
	virtual QString getTitleName( ) const;
	virtual int getDrawDecollatorWidth( ) const { return drawDecollatorWidth; }
	virtual int getDrawDecollatorInterspace( ) const { return drawDecollatorInterspace; }
protected:
	void paintEvent( QPaintEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
};

#endif // LABELITEM_H_H_HEAD__FILE__
