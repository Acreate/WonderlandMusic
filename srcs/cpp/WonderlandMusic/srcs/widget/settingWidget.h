#ifndef SETTINGWIDGET_H_H_HEAD__FILE__
#define SETTINGWIDGET_H_H_HEAD__FILE__

#include <QWidget>

class QScrollArea;

class SettingWidget : public QWidget {
	Q_OBJECT;

protected:

protected:
	virtual void deleteResource( );

protected:
	virtual QWidget * initMainSettingWdiget( );

	virtual QWidget * initSettingScrollWdiget( );

	virtual QWidget * initSettingButtonWdiget( );

	virtual QWidget * initSelectSettingPathGroupBoxWdiget( );

	virtual QWidget * initAppSettingPathWdiget( );

public:
	SettingWidget( QWidget *parent );

	virtual bool loadJsonPathInfo( );

	virtual bool writeJsonPathInfo( );

	bool initWidget( );

	virtual bool init( );

protected:
	void hideEvent( QHideEvent *event ) override;
};

#endif // SETTINGWIDGET_H_H_HEAD__FILE__
