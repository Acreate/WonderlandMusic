#include "appDataManage.h"
#include <QJsonObject>
#include <qtranslator.h>
#include "appDataJsonKey.h"
#include "appInstance.h"
#include "appMusicManage.h"
#include "appTranslate.h"
#include "applicationManage.h"
#include "../menu/playerListWidgetMenu.h"
#include "../tools/pathTools.h"
#include "jsonKey/appDataManageJsonKey.h"

bool AppDataManage::init( ) {
	Init_Resource_App_Core_Ptr( translate );
	Init_Resource_App_Core_Ptr( appDataJsonKey );
	Init_Resource_App_Core_Ptr( appMusicManage );

	return true;
}

bool AppDataManage::initBefore( ) {
	deleteResource( );
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
	disconnect( );
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
	auto jsonFilePath = appDataManage->getJsonFilePath( );
	QJsonObject appJsonObject;
	if( PathTools::readJsonObject( appJsonObject, jsonFilePath ) == false )
		return false;
	// 把 json 数据加载到 AppDataManage
	if( setJsonData( appJsonObject ) == false )
		return false;

	// 把 json 数据加载到 AppMusicManage
	appMusicManage->readJsonData( );

	return true;
}

bool AppDataManage::writeJsonData( ) {
	// 转换 AppDataManage 到 json 数据
	QJsonObject appJsonObject;
	if( getJsonData( appJsonObject ) == false )
		return false;

	// 写入 json 数据到磁盘
	auto appDataManage = appDataJsonKey->getAppDataManage( );
	auto jsonFilePath = appDataManage->getJsonFilePath( );
	PathTools::writeJsonObject( appJsonObject, jsonFilePath );
	// 写入音频 json 到磁盘
	appMusicManage->writeJsonData( );

	return true;
}

bool AppDataManage::getJsonData( QJsonObject &get_json_object ) const {
	auto appDataManage = appDataJsonKey->getAppDataManage( );
	auto writePath = PathTools::getAutoShortenPathName( appSettingPath );
	get_json_object.insert( appDataManage->getIniDirHomePath( ), writePath );
	return true;
}

bool AppDataManage::setJsonData( const QJsonObject &set_json_object ) {
	auto appDataManage = appDataJsonKey->getAppDataManage( );
	auto end = set_json_object.end( );

	auto find = set_json_object.find( appDataManage->getIniDirHomePath( ) );
	if( end != find ) {
		appSettingPath = find.value( ).toString( appSettingPath );
		appSettingPath = PathTools::getAutoShortenPathName( appSettingPath );
		emit signal_change_setting_path( appSettingPath );
	}

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
