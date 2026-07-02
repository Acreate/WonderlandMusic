#include "appDataManage.h"

#include <QJsonObject>
#include <qtranslator.h>

#include "appInstance.h"
#include "appTranslate.h"
#include "jsonFileKey.h"

#include "../tools/pathTools.h"
#include "../tools/templateArgs.h"

bool AppDataManage::init( ) {
	deleteResource( );
	auto appInstance = AppInstance::getAppInstance( );
	QString dirPath = appInstance->applicationDirPath( );
	appSettingPath = dirPath + "/program/";

	constAppSettingPath = appSettingPath + "/json/AppInstance.json";
	constAppDefaultTranslatePath = appSettingPath + "/translations/WonderlandMusic.qm";
	constAppIniDirHomePathJsonKey = "app.ini.dir.home.path";
	appSettingPath = PathTools::getAutoShortenPathName( appSettingPath );
	setAppStringTranslate( constAppDefaultTranslatePath );

	translate = new AppTranslate;
	jsonFileKey = new JsonFileKey;

	Init_Resource_App_Core_Ptr( translate );
	Init_Resource_App_Core_Ptr( jsonFileKey );
	return true;
}

AppDataManage::~AppDataManage( ) {
	deleteResource( );
}

bool AppDataManage::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( translate );
	Delete_Resource_App_Core_Ptr( jsonFileKey );
	return true;
}

AppTranslate * AppDataManage::getTranslate( ) const {
	return translate;
}

JsonFileKey * AppDataManage::getJsonFileKey( ) const {
	return jsonFileKey;
}

QString AppDataManage::getAppSettingPath( ) const {
	return appSettingPath;
}

void AppDataManage::setAppSettingPath( const QString &app_setting_dir_home_path, bool is_move_old_files ) {
	QFileInfo info( app_setting_dir_home_path );
	if( info.exists( ) && info.isFile( ) )
		return;// 存在并且是文件，返回
	auto newFileAbsoluteFilePath = info.absoluteFilePath( );
	info.setFile( appSettingPath );
	auto oldFileAbsoluteFilePath = info.absoluteFilePath( );
	if( oldFileAbsoluteFilePath == newFileAbsoluteFilePath )
		return; // 路径相同，返回
	if( is_move_old_files )
		PathTools::copyPath( oldFileAbsoluteFilePath, newFileAbsoluteFilePath );
	// 赋值
	appSettingPath = PathTools::getAutoShortenPathName( app_setting_dir_home_path );
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
	auto appInstance = AppInstance::getAppInstance( );
	if( appTranslator ) {
		appInstance->removeTranslator( appTranslator );
		delete appTranslator;
	}
	appTranslator = newTranslator;
	appInstance->installTranslator( appTranslator );
	return true;
}

bool AppDataManage::hasRegSettingFilePath( const QString &check_file_path ) const {
	QFileInfo fileInfo( check_file_path );
	auto absolute = fileInfo.absoluteFilePath( );

	if( constAppSettingPath == absolute )
		return true;
	if( constAppDefaultTranslatePath == absolute )
		return true;
	size_t count = regSettingFilePtahVector.size( );
	if( count == 0 )
		return false;
	auto data = regSettingFilePtahVector.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		if( data[ index ] == absolute )
			return true;
	return false;
}

size_t AppDataManage::regSettingFilePath( const QString &check_file_path ) {
	QFileInfo fileInfo( check_file_path );
	auto absolute = fileInfo.absoluteFilePath( );

	if( constAppSettingPath == absolute )
		return 1;
	if( constAppDefaultTranslatePath == absolute )
		return 2;
	regSettingFilePtahVector.emplace_back( absolute );
	return 0;
}

bool AppDataManage::readJsonData( ) {
	QJsonObject appJsonObject;
	if( PathTools::readJsonObject( appJsonObject, constAppSettingPath ) == false )
		return true;
	auto end = appJsonObject.end( );
	auto find = appJsonObject.find( constAppIniDirHomePathJsonKey );
	if( end != find ) {
		auto string = find.value( ).toString( );
		appSettingPath = PathTools::getAutoShortenPathName( string );
	}
	return true;
}

bool AppDataManage::writeJsonData( ) {
	QJsonObject appJsonObject;
	appJsonObject.insert( constAppIniDirHomePathJsonKey, PathTools::getAutoShortenPathName( appSettingPath ) );
	PathTools::writeJsonObject( appJsonObject, constAppSettingPath );
	return true;
}

bool AppDataManage::getJsonData( QJsonObject &get_json_object ) const {
	return false;
}

bool AppDataManage::setJsonData( const QJsonObject &set_json_object ) {
	return false;
}
