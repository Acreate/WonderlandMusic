#ifndef WIDGETTHREAD_H_H_HEAD__FILE__
#define WIDGETTHREAD_H_H_HEAD__FILE__

#include <QThread>
#include <QWidget>

class WidgetThread : public QThread {
	Q_OBJECT;

protected:
	QWidget *bindWidget;
	std::function< void ( WidgetThread *, QWidget * ) > runCallFunction;
	std::function< void ( WidgetThread *, QWidget * ) > finishedCallFunction;

public:
	WidgetThread( QWidget *bind_widget );

	virtual const QWidget * getBindWidget( ) const;

	virtual const std::function< void( WidgetThread *, QWidget * ) > & getCall( ) const;

	virtual void setCall( const std::function< void( WidgetThread *, QWidget * ) > &call );

	virtual const std::function< void( WidgetThread *, QWidget * ) > & getFinishedCallFunction( ) const;

	virtual void setFinishedCallFunction( const std::function< void( WidgetThread *, QWidget * ) > &finished_call_function );

protected:
	void run( ) override;
};

#endif // WIDGETTHREAD_H_H_HEAD__FILE__
