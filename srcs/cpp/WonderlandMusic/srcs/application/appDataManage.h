#ifndef APPDATAMANAGE_H_H_HEAD__FILE__
#define APPDATAMANAGE_H_H_HEAD__FILE__

#include "../interface/iAppCore.h"
#include "../interface/iAppDiskJsonData.h"

class MusicItem;
class AppMusicManage;
class AppDataJsonKey;
class QTranslator;
class AppTranslate;

/// @brief 数据管理
class AppDataManage : public QObject, public IAppDiskJsonData, public IAppCore {
	Q_OBJECT;

protected:
	/// @brief 翻译
	AppTranslate *translate = nullptr;
	/// @brief json 关联的 key
	AppDataJsonKey *appDataJsonKey = nullptr;

	/// @brief 应用配置路径
	QString appSettingPath;
	/// @brief 默认的翻译文件
	QString constAppDefaultTranslatePath;
	/// @brief 翻译
	QTranslator *appTranslator = nullptr;
	/// @brief 音频管理
	AppMusicManage *appMusicManage = nullptr;

public:
	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;

	~AppDataManage( ) override;

protected:
	bool deleteResource( ) override;

public:
	virtual AppTranslate * getTranslate( ) const;

	virtual AppDataJsonKey * getAppDataJsonKey( ) const;

	virtual QString getAppSettingPath( ) const;

	virtual void setAppSettingPath( const QString &new_set_path, bool is_move_file );

	virtual bool setAppStringTranslate( const QString &translate_file_path );

	virtual AppMusicManage * getAppMusicManage( ) const;

	bool readJsonData( ) override;

	bool writeJsonData( ) override;

public:
	bool getJsonData( QJsonObject &get_json_object ) const override;

	bool setJsonData( const QJsonObject &set_json_object ) override;

Q_SIGNALS:
	void signal_change_setting_path( const QString &new_setting_home_path );

	void signal_load_error( const QString &music_file_path );

	void signal_load_over( const std::vector< MusicItem * > &music_item_vector );

	void signal_load_star( const QString &music_file_path );

	void signal_load_unity( const MusicItem &music_item );
};

#endif // APPDATAMANAGE_H_H_HEAD__FILE__
