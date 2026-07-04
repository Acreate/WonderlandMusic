#include "appDataManage.h"

#include <QJsonObject>
#include <qtranslator.h>

#include "appDataJsonKey.h"
#include "appInstance.h"
#include "appMusicManage.h"
#include "appTranslate.h"

#include "../tools/pathTools.h"

#include "jsonKey/appDataManageJsonKey.h"

bool AppDataManage::init( ) {
	deleteResource( );
	auto appInstance = AppInstance::getAppInstance( );
	QString dirPath = appInstance->applicationDirPath( );
	appSettingPath = dirPath + "/program/";
	constAppDefaultTranslatePath = appSettingPath + "/translations/WonderlandMusic.qm";
	appSettingPath = PathTools::getAutoShortenPathName( appSettingPath );
	setAppStringTranslate( constAppDefaultTranslatePath );

	translate = new AppTranslate;
	appDataJsonKey = new AppDataJsonKey;
	appMusicManage = new AppMusicManage;

	Init_Resource_App_Core_Ptr( translate );
	Init_Resource_App_Core_Ptr( appDataJsonKey );
	Init_Resource_App_Core_Ptr( appMusicManage );

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
}

AppMusicManage * AppDataManage::getAppMusicManage( ) const {
	return appMusicManage;
}

bool AppDataManage::readJsonData( ) {
	auto appDataManage = appDataJsonKey->getAppDataManage( );
	auto jsonFilePath = appDataManage->getJsonFilePath( );
	QJsonObject appJsonObject;
	if( PathTools::readJsonObject( appJsonObject, jsonFilePath ) == false )
		return false;

	return setJsonData( appJsonObject );
}

bool AppDataManage::writeJsonData( ) {
	QJsonObject appJsonObject;
	if( getJsonData( appJsonObject ) == false )
		return false;

	auto appDataManage = appDataJsonKey->getAppDataManage( );
	auto jsonFilePath = appDataManage->getJsonFilePath( );
	PathTools::writeJsonObject( appJsonObject, jsonFilePath );
	return true;
}

bool AppDataManage::getJsonData( QJsonObject &get_json_object ) const {
	QJsonObject appMusicManageJsonObject;
	if( appMusicManage->getJsonData( appMusicManageJsonObject ) == false )
		return false;
	auto appDataManage = appDataJsonKey->getAppDataManage( );
	get_json_object.insert( appDataManage->getIniDirHomePath( ), PathTools::getAutoShortenPathName( appSettingPath ) );
	return true;
}

bool AppDataManage::setJsonData( const QJsonObject &set_json_object ) {
	auto appDataManage = appDataJsonKey->getAppDataManage( );
	auto end = set_json_object.end( );

	auto find = set_json_object.find( appDataManage->getIniDirHomePath( ) );
	if( end != find )
		appSettingPath = PathTools::getAutoShortenPathName( find.value( ).toString( appSettingPath ) );

	QJsonObject json;
	if( PathTools::readJsonObject( json, appSettingPath ) == false )
		return true;
	find = json.find( appDataManage->getAppMusicManage( ) );
	if( end != find )
		appMusicManage->setJsonData( find.value( ).toObject( ) );
	return false;
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
