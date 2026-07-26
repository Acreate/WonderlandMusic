#ifndef OPTIONBUTTON_H_H_HEAD__FILE__
#define OPTIONBUTTON_H_H_HEAD__FILE__
#include <QLabel>
class OptionPanel;

class OptionButton : public QWidget {
	Q_OBJECT;

	friend class OptionWindow;
	friend class OptionPanel;

	OptionWindow *optionWindow;
	QString *name;
	QImage *icon;

public:
	virtual const QString & getName( ) const;
	virtual const QImage & getIcon( ) const;
	virtual void setName( const QString &name );
	virtual void setIcon( const QImage &icon );

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
	OptionButton( OptionWindow *option_window, const QString &name, const QImage &icon );
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
Q_SIGNALS:
	void signal_click_item( OptionButton *option_button );
};
#endif // OPTIONBUTTON_H_H_HEAD__FILE__
