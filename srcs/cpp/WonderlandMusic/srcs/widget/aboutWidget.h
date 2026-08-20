#ifndef ABOUTAPPLICATIONWIDGET_H_H_HEAD__FILE__
#define ABOUTAPPLICATIONWIDGET_H_H_HEAD__FILE__
#include "../component/optionWindow/interface/optionPanel.h"

#include "../interface/iAppResourceCore.h"
class QTextEdit;
class QHBoxLayout;
class OptionStackWidget;

class AboutWidget : public QWidget, public OptionPanel, public IAppResourceCore {
	Q_OBJECT;

protected:
	QHBoxLayout *mainLayout = nullptr;
	QLabel *qtIco = nullptr;
	QTextEdit *textBox = nullptr;

protected:
	/// @brief 获取软件信息（协议内容-开发内容）
	/// @return 不存在返回空字符串
	virtual bool getSoftwareProtocolInfo( QString &result_info );

public:
	AboutWidget( );
	bool init( ) override;
	~AboutWidget( ) override;

protected:
	bool deleteResource( ) override;

public:
	QWidget * toWidget( ) override;

	bool initBefore( ) override;
	bool initAfter( ) override;
	bool showPanelBefore( ) override;
	bool hidePanelBefore( ) override;
	bool releasePanelBefore( ) override;
	QString getTypeName( ) const override;
};
#endif // ABOUTAPPLICATIONWIDGET_H_H_HEAD__FILE__
