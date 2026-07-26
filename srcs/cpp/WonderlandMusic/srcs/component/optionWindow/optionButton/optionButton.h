#ifndef OPTIONBUTTON_H_H_HEAD__FILE__
#define OPTIONBUTTON_H_H_HEAD__FILE__
#include <QLabel>
class OptionPanel;

class OptionButton : public QWidget {
	Q_OBJECT;

	friend class OptionWindow;
	friend class OptionPanel;

	OptionWindow *optionWindow;

	OptionPanel *optionPanel = nullptr;

public:
	enum class Show_Type {
		All,
		Txt,
		Icon
	};

protected:
	bool click = false;
	Show_Type show;
	~OptionButton( ) override;

public:
	OptionButton( OptionWindow *option_window );
	virtual bool isClick( ) const;
	virtual Show_Type getShow( ) const;
	virtual void setShow( const Show_Type show );
	virtual QSize updateSize( );

protected:
	void paintEvent( QPaintEvent * ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void enterEvent( QEnterEvent *event ) override;
	void leaveEvent( QEvent *event ) override;
};
#endif // OPTIONBUTTON_H_H_HEAD__FILE__
