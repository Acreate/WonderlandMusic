#ifndef SETTINGWIDGET_H_H_HEAD__FILE__
#define SETTINGWIDGET_H_H_HEAD__FILE__
#include <QWidget>
#include "../component/optionWindow/interface/optionPanel.h"

class SettingWidget : public QWidget, public OptionPanel {
	Q_OBJECT;

public:
	SettingWidget( OptionWindow *parent );
	~SettingWidget( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	QWidget * toWidget( ) override;
};
#endif // SETTINGWIDGET_H_H_HEAD__FILE__
