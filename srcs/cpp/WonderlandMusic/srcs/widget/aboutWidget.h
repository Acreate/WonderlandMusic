#ifndef ABOUTAPPLICATIONWIDGET_H_H_HEAD__FILE__
#define ABOUTAPPLICATIONWIDGET_H_H_HEAD__FILE__

#include <QWidget>

class QTextEdit;
class QHBoxLayout;
class OptionStackWidget;

class AboutWidget : public QWidget {
	Q_OBJECT;

protected:
	QHBoxLayout *mainLayout;
	QLabel *qtIco;
	QTextEdit *textBox;

protected:
	/// @brief 获取软件信息（协议内容-开发内容）
	/// @return 不存在返回空字符串
	virtual QString getSoftwareProtocolInfo( );

public:
	AboutWidget( QWidget *parent );

	virtual bool init( );
};

#endif // ABOUTAPPLICATIONWIDGET_H_H_HEAD__FILE__
