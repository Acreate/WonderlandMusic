#ifndef APPINSTANCE_H_H_HEAD__FILE__
#define APPINSTANCE_H_H_HEAD__FILE__

#include <QApplication>
#include <QLoggingCategory>

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
	QDateTime *startDateTime;
	/// @brief 翻译
	AppTranslate *translate;
	/// @brief json 关联的 key
	JsonFileKey *jsonFileKey;
	/// @brief 音频解码实例
	MusicDecoder *musicDecoder;
	/// @brief 渲染对象
	RenderImage *renderImage;
	/// @brief 主要执行窗口
	MainWindow *mainWindow;
	/// @brief 退出代码
	int exitCode;
public:
	static AppInstance * getAppInstance( );
	AppInstance( int &argc, char **argv, int app_flag_s = ApplicationFlags );
	~AppInstance( ) override;
public:
	virtual bool init( );
	virtual int run( );
public:
	virtual const QDateTime * getStartDateTime( ) const;
	virtual const JsonFileKey * getJsonFileKey( ) const;
	virtual const AppTranslate * getTranslate( ) const;
	virtual MusicDecoder * getMusicDecoder( ) const;
	virtual int getExitCode( ) const;
	virtual const RenderImage * getRenderImage( ) const;
};
#endif // APPINSTANCE_H_H_HEAD__FILE__
