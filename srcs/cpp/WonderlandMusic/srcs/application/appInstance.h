#ifndef APPINSTANCE_H_H_HEAD__FILE__
#define APPINSTANCE_H_H_HEAD__FILE__

#include <QApplication>

class SystemTrayIcon;
class MusicPlayerInstance;
class RenderImage;
class MainWindow;
class JsonFileKey;
class MusicDecoder;
class AppTranslate;
class MessageErrorOut;

class AppInstance : public QApplication {
	Q_OBJECT;

private:
	static AppInstance *instance;

protected:
	/// @brief 起始时间
	QDateTime *startDateTime = nullptr;
	/// @brief 翻译
	AppTranslate *translate = nullptr;
	/// @brief json 关联的 key
	JsonFileKey *jsonFileKey = nullptr;
	/// @brief 音频解码实例
	MusicDecoder *musicDecoder = nullptr;
	/// @brief 音频播放实例
	MusicPlayerInstance *musicPlayerInstance = nullptr;
	/// @brief 渲染对象
	RenderImage *renderImage = nullptr;
	/// @brief 主要执行窗口
	MainWindow *mainWindow = nullptr;
	/// @brief 系统托盘
	SystemTrayIcon *systemTrayIcon = nullptr;
	/// @brief 退出代码
	int exitCode;
	/// @brief 应用配置路径
	QString appSettingPath;
	/// @brief 固定的配置路径
	QString constAppSettingPath;
	/// @brief 默认的翻译文件
	QString constAppDefaultTranslatePath;
	/// @brief 获取 json 中的关键 key
	QString constAppIniDirHomePathJsonKey;
	/// @brief 翻译
	QTranslator *appTranslator = nullptr;

protected:
	virtual bool initVar( );

	virtual bool initReadJson( );

	virtual bool writeJson( );

	virtual bool initTranslate( );

public:
	static AppInstance * getAppInstance( );

	AppInstance( int &argc, char **argv, int app_flag_s = ApplicationFlags );

	~AppInstance( ) override;

	bool notify( QObject *, QEvent * ) override;

	virtual bool init( );

	virtual int run( );

	virtual void deleteResource( );

public:
	virtual const QDateTime * getStartDateTime( ) const;

	virtual const JsonFileKey * getJsonFileKey( ) const;

	virtual const AppTranslate * getTranslate( ) const;

	virtual MusicDecoder * getMusicDecoder( ) const;

	virtual int getExitCode( ) const;

	virtual const RenderImage * getRenderImage( ) const;

	virtual QString getAppSettingPath( ) const;

	virtual void setAppSettingPath( const QString &app_setting_dir_home_path, bool is_move_old_files );

	virtual bool showMainWindow( ) const;

	virtual bool hideMainWindow( ) const;

	virtual MainWindow * getMainWindow( ) const;

	virtual bool setAppStringTranslate( const QString &translate_file_path );
};
#endif // APPINSTANCE_H_H_HEAD__FILE__
