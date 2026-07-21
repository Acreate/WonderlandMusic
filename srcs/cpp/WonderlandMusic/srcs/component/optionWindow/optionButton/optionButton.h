#ifndef OPTIONBUTTON_H_H_HEAD__FILE__
#define OPTIONBUTTON_H_H_HEAD__FILE__
#include <QLabel>
class OpetionListWidget;
class OptionItem;

class OptionButton : public QLabel {
	Q_OBJECT;

protected:
	bool click = false;
	OpetionListWidget *opetionListWidget;
	OptionItem *bindItem;

public:
	OptionButton( OpetionListWidget *opetion_list_widget, OptionItem *bind_item );
	~OptionButton( ) override;
	virtual OpetionListWidget * getOpetionListWidget( ) const;
	virtual OptionItem * getBindItem( ) const;
	virtual bool isClick( ) const;

protected:
	void paintEvent( QPaintEvent * ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void enterEvent( QEnterEvent *event ) override;
	void leaveEvent( QEvent *event ) override;
Q_SIGNALS:
	void signal_click_item( OptionButton *option_button );
};
#endif // OPTIONBUTTON_H_H_HEAD__FILE__
