#ifndef SETTINGWIDGET_H_H_HEAD__FILE__
#define SETTINGWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include "../interface/iAppCore.h"
#include "../interface/iAppJsonData.h"

class QPushButton;
class QLineEdit;
class QScrollArea;

class SettingWidget : public QWidget, public IAppCore, public IAppJsonData {
	Q_OBJECT;

protected:
	QLineEdit *selectDirPathLineEdit = nullptr;
	QWidget *mainSettingWdiget = nullptr;

protected:
	bool deleteResource( ) override;

protected Q_SLOTS:
	/// @brief 点击了软件配置选择路径
	virtual void clickSelectAppSettingPathBtn( );

	/// @brief 软件选择路径被修改完毕
	virtual void changedSelectAppSettingPathEditor( );

	/// @brief 点击确定按钮
	virtual void clickOkBtn( );

	/// @brief 点击取消按钮
	virtual void clickCancelBtn( );

protected:
	virtual QWidget * initMainSettingWdiget( );

	virtual QWidget * initSettingScrollWdiget( );

	virtual QWidget * initSettingButtonWdiget( );

	virtual QWidget * initSelectSettingPathGroupBoxWdiget( );

	virtual QWidget * initAppSettingPathWdiget( );

public:
	SettingWidget( QWidget *parent );

	~SettingWidget( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	bool initWidget( );

	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;

protected:
	void hideEvent( QHideEvent *event ) override;
Q_SIGNALS:
	void signal_change_setting_path( const QString &new_setting_home_path );
};

#endif // SETTINGWIDGET_H_H_HEAD__FILE__
