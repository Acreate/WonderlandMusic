#ifndef APPMUSICMANAGE_H_H_HEAD__FILE__
#define APPMUSICMANAGE_H_H_HEAD__FILE__

#include <interface/iAppCore.h>
#include <interface/iAppJsonData.h>
class UserMutex;
class AppMusicDecoder;

class AppMusicManage : public QObject, public IAppCore, public IAppJsonData {
	Q_OBJECT;

protected:
	UserMutex *loadMutex = nullptr;
	AppMusicDecoder *appMusicDecoder = nullptr;
	std::vector< QString > loadFileVector;
	size_t loadCount;
	QString openMultipleFilePath;
	QString openMultipleDirPath;

protected:
	bool deleteResource( ) override;

public:
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;

	bool init( ) override;
	bool initBefore( ) override;
	bool initAfter( ) override;

	virtual AppMusicDecoder * getAppMusicDecoder( ) const;
	virtual bool getMusicWindowInfoJsonData( QJsonObject &result_json_object );
	virtual bool setMusicWindowInfoJsonData( const QJsonObject &result_json_object );
};
#endif // APPMUSICMANAGE_H_H_HEAD__FILE__
