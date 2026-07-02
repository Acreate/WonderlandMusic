#ifndef SYSTEMTRAYICONMENU_H_H_HEAD__FILE__
#define SYSTEMTRAYICONMENU_H_H_HEAD__FILE__
#include <QMenu>

class SystemTrayIconMenu : public QMenu {
	Q_OBJECT;

protected:
	virtual bool deleteResource( );

public:
	SystemTrayIconMenu( QWidget *parent = nullptr );

	SystemTrayIconMenu( const QString &title, QWidget *parent );

	virtual bool init( );

	~SystemTrayIconMenu( ) override;
};

#endif // SYSTEMTRAYICONMENU_H_H_HEAD__FILE__
