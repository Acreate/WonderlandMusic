#ifndef SETTINGWIDGET_H_H_HEAD__FILE__
#define SETTINGWIDGET_H_H_HEAD__FILE__

#include <QWidget>

class QPushButton;
class QLineEdit;
class QScrollArea;

class SettingWidget : public QWidget {
	Q_OBJECT;

protected:
	QLineEdit *selectDirPathLineEdit = nullptr;
	QWidget *mainSettingWdiget = nullptr;

protected:
	virtual void deleteResource( );

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

	virtual bool loadJsonPathInfo( );

	virtual bool writeJsonPathInfo( );

	bool initWidget( );

	virtual bool init( );

protected:
	void hideEvent( QHideEvent *event ) override;
};

#endif // SETTINGWIDGET_H_H_HEAD__FILE__
