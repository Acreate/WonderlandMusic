#ifndef APPINSTANCE_H_H_HEAD__FILE__
#define APPINSTANCE_H_H_HEAD__FILE__

#include <QApplication>
#include <QLoggingCategory>

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
	int exitCode;
public:
	static AppInstance * getAppInstance( );
	AppInstance( int &argc, char **argv, int app_flag_s = ApplicationFlags );
	~AppInstance( ) override;
public:
	virtual bool init( );
	virtual int run( );
public:
	virtual const QDateTime * getStartDateTime( ) const { return startDateTime; }
	virtual const JsonFileKey * getJsonFileKey( ) const { return jsonFileKey; }
	virtual const AppTranslate * getTranslate( ) const { return translate; }
	virtual MusicDecoder * getMusicDecoder( ) const { return musicDecoder; }
	virtual int getExitCode( ) const { return exitCode; }
};
#endif // APPINSTANCE_H_H_HEAD__FILE__
