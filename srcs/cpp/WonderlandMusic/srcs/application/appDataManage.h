#ifndef APPDATAMANAGE_H_H_HEAD__FILE__
#define APPDATAMANAGE_H_H_HEAD__FILE__
#include <QObject>

#include "appCore.h"
#include "appDiskJsonData.h"

class QTranslator;
class AppTranslate;
class JsonFileKey;

class AppDataManage : public QObject, public AppCore, public AppDiskJsonData {
	Q_OBJECT;

protected:
	/// @brief 翻译
	AppTranslate *translate = nullptr;
	/// @brief json 关联的 key
	JsonFileKey *jsonFileKey = nullptr;

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
	/// @brief 注册的配置文件
	std::vector< QString > regSettingFilePtahVector;

public:
	bool init( ) override;

	~AppDataManage( ) override;

protected:
	bool deleteResource( ) override;

public:
	virtual AppTranslate * getTranslate( ) const;

	virtual JsonFileKey * getJsonFileKey( ) const;

	virtual QString getAppSettingPath( ) const;

	virtual void setAppSettingPath( const QString &app_setting_dir_home_path, bool is_move_old_files );

	virtual bool setAppStringTranslate( const QString &translate_file_path );

	virtual bool hasRegSettingFilePath( const QString &check_file_path ) const;

	virtual size_t regSettingFilePath( const QString &check_file_path );

protected:
	bool readJsonData( ) override;

	bool writeJsonData( ) override;

public:
	bool getJsonData( QJsonObject &get_json_object ) const override;

	bool setJsonData( const QJsonObject &set_json_object ) override;
};

#endif // APPDATAMANAGE_H_H_HEAD__FILE__
