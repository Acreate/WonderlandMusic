#ifndef SETTINGWIDGET_H_H_HEAD__FILE__
#define SETTINGWIDGET_H_H_HEAD__FILE__

#include <QWidget>

class SelectDirPathWidget;

class SettingWidget : public QWidget {
	Q_OBJECT;

protected:
	SelectDirPathWidget *appJsonPathWidget = nullptr;

protected:
	virtual void deleteResource( );

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
