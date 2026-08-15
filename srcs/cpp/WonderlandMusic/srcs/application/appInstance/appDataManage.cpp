#include "appDataManage.h"
#include <QJsonObject>
#include <qtranslator.h>

#include "appUserInterfaceManage.h"
#include "applicationManage.h"

#include "../appInstance.h"

#include "../../head/after_init_macro.h"
#include "../../head/before_init_macro.h"
#include "../../head/init_macro.h"
#include "../../head/release_macro.h"

#include "../../tools/instanceTools.h"
#include "../../tools/pathTools.h"

#include "appDataManage/appDataJsonKey.h"
#include "appDataManage/appMusicManage.h"
#include "appDataManage/appTranslate.h"
#include "appDataManage/jsonKey/appDataManageJsonKey.h"

bool AppDataManage::init( ) {
	Init_Resource_App_Core_Ptr( translate );
	Init_Resource_App_Core_Ptr( appDataJsonKey );
	Init_Resource_App_Core_Ptr( appMusicManage );

	return true;
}

bool AppDataManage::initBefore( ) {
	auto appInstance = AppInstance::getAppInstance( );
	QString dirPath = appInstance->getApplicationManage( )->applicationDirPath( );
	appSettingPath = dirPath + "/program/";
	emit signal_change_setting_path( appSettingPath );
	constAppDefaultTranslatePath = appSettingPath + "/translations/WonderlandMusic.qm";
	appSettingPath = PathTools::getAutoShortenPathName( appSettingPath );
	setAppStringTranslate( constAppDefaultTranslatePath );

	translate = new AppTranslate;
	appDataJsonKey = new AppDataJsonKey;
	appMusicManage = new AppMusicManage;

	Before_Init_Resource_App_Core_Ptr( translate );
	Before_Init_Resource_App_Core_Ptr( appDataJsonKey );
	Before_Init_Resource_App_Core_Ptr( appMusicManage );

	return true;
}

bool AppDataManage::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( translate );
	After_Init_Resource_App_Core_Ptr( appDataJsonKey );
	After_Init_Resource_App_Core_Ptr( appMusicManage );

	return true;
}

AppDataManage::~AppDataManage( ) {
	deleteResource( );
}

bool AppDataManage::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( translate );
	Delete_Resource_App_Core_Ptr( appDataJsonKey );
	Delete_Resource_App_Core_Ptr( appMusicManage );
	return true;
}

AppTranslate * AppDataManage::getTranslate( ) const {
	return translate;
}

AppDataJsonKey * AppDataManage::getAppDataJsonKey( ) const {
	return appDataJsonKey;
}

QString AppDataManage::getAppSettingPath( ) const {
	return appSettingPath;
}

void AppDataManage::setAppSettingPath( const QString &new_set_path, bool is_move_file ) {
	QFileInfo info( new_set_path );
	if( info.exists( ) && info.isFile( ) )
		return;// 存在并且是文件，返回
	auto newFileAbsoluteFilePath = info.absoluteFilePath( );
	info.setFile( appSettingPath );
	auto oldFileAbsoluteFilePath = info.absoluteFilePath( );
	if( oldFileAbsoluteFilePath == newFileAbsoluteFilePath )
		return; // 路径相同，返回
	if( is_move_file )
		PathTools::copyPath( oldFileAbsoluteFilePath, newFileAbsoluteFilePath );
	// 赋值
	appSettingPath = PathTools::getAutoShortenPathName( new_set_path );
	emit signal_change_setting_path( appSettingPath );
}

AppMusicManage * AppDataManage::getAppMusicManage( ) const {
	return appMusicManage;
}

bool AppDataManage::readJsonData( ) {
	// 从磁盘获取 json 数据
	auto appDataManage = appDataJsonKey->getAppDataManage( );
	auto jsonFilePath = appDataManage->getFilePath( );
	QJsonObject appJsonObject;
	if( PathTools::readJsonObject( appJsonObject, jsonFilePath ) == false )
		return false;
	// 把 json 数据加载到 AppDataManage
	if( setJsonData( appJsonObject ) == false )
		return false;

	return true;
}

bool AppDataManage::writeJsonData( ) {
	// 转换 AppDataManage 到 json 数据
	QJsonObject appJsonObject;
	if( getJsonData( appJsonObject ) == false )
		return false;

	// 写入 json 数据到磁盘
	auto appDataManage = appDataJsonKey->getAppDataManage( );
	auto jsonFilePath = appDataManage->getFilePath( );
	PathTools::writeJsonObject( appJsonObject, jsonFilePath );

	return true;
}

bool AppDataManage::getJsonData( QJsonObject &get_json_object ) const {
	// 从 appUserInterfaceManage 获取数据
	QJsonObject uiJsonObject;
	auto appUserInterfaceManage = InstanceTools::getAppUserInterfaceManage( );
	if( appUserInterfaceManage == nullptr )
		return false;
	if( appUserInterfaceManage->getJsonData( uiJsonObject ) == false )
		return false;
	// 从 appMusicManage 获取数据
	QJsonObject appMusicManageJsonObject;
	if( appMusicManage->getJsonData( appMusicManageJsonObject ) == false )
		return false;
	// 获取路径数据
	auto writePath = PathTools::getAutoShortenPathName( appSettingPath );

	// 写入 get_json_object
	auto appDataManage = appDataJsonKey->getAppDataManage( );
	get_json_object.insert( appDataManage->getAppSettingPath( ), writePath );
	get_json_object.insert( appDataManage->getAppMusicManageJsonObject( ), appMusicManageJsonObject );
	get_json_object.insert( appDataManage->getUiJsonObject( ), uiJsonObject );
	return true;
}

bool AppDataManage::setJsonData( const QJsonObject &set_json_object ) {
	auto appDataManage = appDataJsonKey->getAppDataManage( );
	auto end = set_json_object.end( );

	QJsonObject::const_iterator find;
	// 把 json 数据加载到 appMusicManage
	find = set_json_object.find( appDataManage->getAppMusicManageJsonObject( ) );
	if( end != find ) {
		auto jsonObject = find.value( ).toObject( );
		if( appMusicManage->setJsonData( jsonObject ) == false )
			return false;
	}
	// 把 json 数据加载到 appUserInterfaceManage
	find = set_json_object.find( appDataManage->getUiJsonObject( ) );
	if( end != find ) {
		auto jsonObject = find.value( ).toObject( );
		auto appUserInterfaceManage = InstanceTools::getAppUserInterfaceManage( );
		if( appUserInterfaceManage == nullptr )
			return false;
		if( appUserInterfaceManage->setJsonData( jsonObject ) == false )
			return false;
	}
	find = set_json_object.find( appDataManage->getAppSettingPath( ) );
	if( end == find )
		return false;

	appSettingPath = find.value( ).toString( appSettingPath );
	appSettingPath = PathTools::getAutoShortenPathName( appSettingPath );
	emit signal_change_setting_path( appSettingPath );
	return true;
}

bool AppDataManage::setAppStringTranslate( const QString &translate_file_path ) {
	QFileInfo info( translate_file_path );
	if( info.exists( ) == false )
		return false;
	QTranslator *newTranslator = new QTranslator;
	if( newTranslator->load( info.absoluteFilePath( ) ) == false ) {
		delete newTranslator;
		return false;
	}
	auto appInstance = AppInstance::getAppInstance( )->getApplicationManage( );
	if( appTranslator ) {
		appInstance->removeTranslator( appTranslator );
		delete appTranslator;
	}
	appTranslator = newTranslator;
	appInstance->installTranslator( appTranslator );
	return true;
}
