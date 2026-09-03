#ifndef APPDATAMANAGE_H_H_HEAD__FILE__
#define APPDATAMANAGE_H_H_HEAD__FILE__

#include <interface/iAppCore.h>
#include <interface/iAppDiskJsonData.h>

#include "../../interface/iAppResourceCore.h"

class FavoriteItem;
class IMusicItemWidthInfo;
class IMusicWidgetSizeInfo;
class MusicItemWidthInfo;
class MusicWidgetSizeInfo;
class AppMusicManage;
class AppDataJsonKey;
class QTranslator;
class AppTranslate;

/// @brief 数据管理
class AppDataManage : public QObject, public IAppDiskJsonData, public IAppCore, public IAppResourceCore {
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
	/// @brief 收藏夹
	std::vector< FavoriteItem * > favoriteItemVector;
	/// @brief 项宽度信息
	MusicItemWidthInfo *musicItemWidthInfo = nullptr;
	/// @brief 音频窗口大小信息
	MusicWidgetSizeInfo *musicWidgetSizeInfo = nullptr;

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
	virtual IMusicItemWidthInfo * getMusicItemWidthInfo( ) const;
	virtual IMusicWidgetSizeInfo * getMusicWidgetSizeInfo( ) const;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
};
#endif // APPDATAMANAGE_H_H_HEAD__FILE__
