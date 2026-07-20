#include "appMusicManage.h"
#include <QJsonObject>
#include "appDataJsonKey.h"
#include "appDataManage.h"
#include "appInstance.h"
#include "appMusicDecoder.h"
#include "applicationManage.h"
#include "../mutex/userMutex.h"
#include "../tools/appJsonKeyTools.h"
#include "../tools/pathTools.h"
#include "../window/mainWindow.h"
#include "jsonKey/appMusicManageJsonKey.h"

bool AppMusicManage::deleteResource( ) {
	return true;
}

bool AppMusicManage::readJsonData( ) {
	auto jsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getAppMusicManage( );
	QJsonObject readJson;
	if( PathTools::readJsonObject( readJson, jsonKey->getFilePath( ) ) == false )
		return false;
	if( setJsonData( readJson ) == false )
		return false;

	return true;
}

bool AppMusicManage::writeJsonData( ) {
	QJsonObject getJson;
	if( getJsonData( getJson ) == false )
		return false;
	auto jsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getAppMusicManage( );
	if( PathTools::writeJsonObject( getJson, jsonKey->getFilePath( ) ) == false )
		return false;
	return true;
}

bool AppMusicManage::init( ) {
	Init_Resource_App_Core_Ptr( appMusicDecoder );
	return true;
}

bool AppMusicManage::initBefore( ) {
	deleteResource( );
	loadCount = 0;
	appMusicDecoder = new AppMusicDecoder;
	Before_Init_Resource_App_Core_Ptr( appMusicDecoder );
	return true;
}

bool AppMusicManage::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( appMusicDecoder );

	return true;
}

AppMusicDecoder * AppMusicManage::getAppMusicDecoder( ) const {
	return appMusicDecoder;
}

bool AppMusicManage::getJsonData( QJsonObject &get_json_object ) const {
	QString jsonObejctJsonKey;
	QString selectDirPathJsonKey;
	QString selectFilePathJsonKey;

	if( AppJsonKeyTools::getAppMusicManage( [&] ( const AppMusicManageJsonKey &json_key ) {
		jsonObejctJsonKey = json_key.getJsonObejct( );
		selectDirPathJsonKey = json_key.getSelectDirPath( );
		selectFilePathJsonKey = json_key.getSelectFilePath( );
	} ) == false )
		return false;
	QJsonObject object;
	object.insert( selectFilePathJsonKey, this->openMultipleFilePath );
	object.insert( selectDirPathJsonKey, this->openMultipleDirPath );
	get_json_object.insert( jsonObejctJsonKey, object );
	return true;
}

bool AppMusicManage::setJsonData( const QJsonObject &set_json_object ) {
	if( set_json_object.empty( ) )
		return false;

	QString jsonObejctJsonKey;
	QString selectDirPathJsonKey;
	QString selectFilePathJsonKey;

	if( AppJsonKeyTools::getAppMusicManage( [&] ( const AppMusicManageJsonKey &json_key ) {
		jsonObejctJsonKey = json_key.getJsonObejct( );
		selectDirPathJsonKey = json_key.getSelectDirPath( );
		selectFilePathJsonKey = json_key.getSelectFilePath( );
	} ) == false )
		return false;
	auto find = set_json_object.find( jsonObejctJsonKey );
	auto end = set_json_object.end( );
	if( find == end )
		return false;
	auto jsonObject = find.value( ).toObject( );

	end = jsonObject.end( );
	// 获取文件选择路径
	find = jsonObject.find( selectFilePathJsonKey );
	if( find != end )
		openMultipleFilePath = find.value( ).toString( openMultipleFilePath );
	// 获取目录选择路径
	find = jsonObject.find( selectDirPathJsonKey );
	if( find != end )
		openMultipleDirPath = find.value( ).toString( openMultipleDirPath );

	return true;
}
