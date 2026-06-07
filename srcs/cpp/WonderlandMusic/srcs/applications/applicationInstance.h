#ifndef APPLICATIONINSTANCE_H_H_HEAD__FILE__
#define APPLICATIONINSTANCE_H_H_HEAD__FILE__


#include <QApplication>
class Render;
class ApplicationEvenTrigger;
class QFileInfo;
class QDir;
class MainWindow;
class QJsonObject;
class ApplicationInstance : public QApplication {
	Q_OBJECT;
private:
	static ApplicationInstance *current;
public:
	static ApplicationInstance * getApplicationInstance( );
public:
	ApplicationInstance( int &argc, char **const argv, const int i = ApplicationFlags );
	~ApplicationInstance( ) override;
	bool notify( QObject *object, QEvent *event ) override;
protected:
	bool event( QEvent * ) override;
private:
	class Translate {
		friend class ApplicationInstance;
		/// @brief 创建目录错误
		QString createDirError;
		/// @brief 打开文件错误
		QString openFileError;
		/// @brief 打开语言文件失败
		QString loadQTranslatorFile;
		/// @brief 加载语言文件打软件失败
		QString loadQTranslatorApp;
	public:
		Translate( );
	} *translate;
	class JSonKey {
		friend class ApplicationInstance;
		/// @brief 语言文件关键字
		QString app_QTranslator_path_key;
		/// @brief 主窗口横向关键字
		QString main_window_x_key;
		/// @brief 主窗口纵向关键字
		QString main_window_y_key;
		/// @brief 主窗口宽度关键字
		QString main_window_h_key;
		/// @brief 主窗口高度关键字
		QString main_window_w_key;
	public:
		JSonKey( );
	} jsonKey;
private:
	/// @brief 语言
	QTranslator *qTranslator;
	/// @brief 主要先显示的窗口
	MainWindow *mainWindowPtr;
	/// @brief 是否第一次显示
	bool firstShow;
	/// @brief 软件配置
	QJsonObject *appSetting;
	/// @brief 软件配置路径
	QString appSettingPath;
	/// @brief 目录工具
	QDir *qDirTool;
	/// @brief 路径工具
	QFileInfo *fileInfoTool;
	/// @brief 软件启动时间
	QDateTime *appStartRunTime;
	Render *render;
	ApplicationEvenTrigger *applicationEvenTrigger;
public:
	/// @brief 获取配置的主要窗口
	/// @return 主要窗口
	virtual MainWindow * getMainWindowPtr( ) const { return mainWindowPtr; }
	/// @brief 设置主要窗口，未配置该项时，窗口已经显示，则不会调用 firstMainWindowShow
	/// @param main_window_ptr 配置的主要窗口
	virtual void setMainWindowPtr( MainWindow *main_window_ptr );
	virtual const QDateTime & getAppStartRunDataTime( ) const {
		return *appStartRunTime;
	}
	virtual Render * getRender( ) const { return render; }
	virtual ApplicationEvenTrigger * getApplicationEvenTrigger( ) const { return applicationEvenTrigger; }
private:
	/// @brief 第一次显示主要窗口时调用该函数
	/// @param first_show_main_window 调用的主要窗口
	void firstMainWindowShow( MainWindow *first_show_main_window );
};

#endif // APPLICATIONINSTANCE_H_H_HEAD__FILE__
