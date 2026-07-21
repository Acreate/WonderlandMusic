#ifndef OPTIONBUTTON_H_H_HEAD__FILE__
#define OPTIONBUTTON_H_H_HEAD__FILE__
#include <QLabel>
class OptionItem;

class OptionButton : public QLabel {
	Q_OBJECT;

protected:
	bool click = false;
	OptionItem *bindItem;

public:
	OptionButton( OptionItem *bind_item );
	~OptionButton( ) override;
	virtual OptionItem * getBindItem( ) const;
	virtual bool isClick( ) const;

protected:
	void paintEvent( QPaintEvent * ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void enterEvent( QEnterEvent *event ) override;
	void leaveEvent( QEvent *event ) override;
Q_SIGNALS:
	void signal_click_item( OptionItem *option_item );
};
#endif // OPTIONBUTTON_H_H_HEAD__FILE__
