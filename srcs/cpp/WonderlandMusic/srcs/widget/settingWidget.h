#ifndef SETTINGWIDGET_H_H_HEAD__FILE__
#define SETTINGWIDGET_H_H_HEAD__FILE__

#include <QWidget>

class SettingWidget : public QWidget {
	Q_OBJECT;

public:
	SettingWidget( QWidget *parent );

	virtual bool loadJsonPathInfo( );

	virtual bool writeJsonPathInfo( );

	virtual bool init( );

protected:
	void hideEvent( QHideEvent *event ) override;
};

#endif // SETTINGWIDGET_H_H_HEAD__FILE__
