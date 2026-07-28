#include "appMusicManage.h"
#include <QJsonObject>
#include "appMusicDecoder.h"

#include "../head/after_init_macro.h"
#include "../head/before_init_macro.h"
#include "../head/init_macro.h"

#include "../mutex/userMutex.h"
#include "../tools/appJsonKeyTools.h"
#include "../tools/pathTools.h"
#include "../window/mainWindow.h"
#include "jsonKey/appMusicManageJsonKey.h"

bool AppMusicManage::deleteResource( ) {
	return true;
}

bool AppMusicManage::readJsonData( ) {
	bool resultBool = false;
	AppJsonKeyTools::getAppMusicManage( [this,&resultBool] ( const AppMusicManageJsonKey &json_key ) {
		QJsonObject readJson;
		if( PathTools::readJsonObject( readJson, json_key.getFilePath( ) ) == false )
			return;
		resultBool = setJsonData( readJson );
	} );

	return resultBool;
}

bool AppMusicManage::writeJsonData( ) {
	bool resultBool = false;
	AppJsonKeyTools::getAppMusicManage( [this,&resultBool] ( const AppMusicManageJsonKey &json_key ) {
		QJsonObject getJson;
		if( getJsonData( getJson ) == false )
			return;
		resultBool = PathTools::writeJsonObject( getJson, json_key.getFilePath( ) );
	} );

	return resultBool;
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
bool AppMusicManage::getMusicWindowInfoJsonData( QJsonObject &result_json_object ) {
	return false;
}
bool AppMusicManage::setMusicWindowInfoJsonData( const QJsonObject &result_json_object ) {
	return false;
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
