#include "jsonObjectTools.h"

#include <QJsonObject>

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const int8_t &conver ) {
	QJsonObject varJson;
	varJson.insert( "var", QString::number( conver ) );
	result_json_object.insert( "int8_t", varJson );
	return true;
}

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const int16_t &conver ) {
	QJsonObject varJson;
	varJson.insert( "var", QString::number( conver ) );
	result_json_object.insert( "int16_t", varJson );
	return true;
}

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const int32_t &conver ) {
	QJsonObject varJson;
	varJson.insert( "var", QString::number( conver ) );
	result_json_object.insert( "int32_t", varJson );
	return true;
}

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const int64_t &conver ) {
	QJsonObject varJson;
	varJson.insert( "var", QString::number( conver ) );
	result_json_object.insert( "int64_t", varJson );
	return true;
}

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const uint8_t &conver ) {
	QJsonObject varJson;
	varJson.insert( "var", QString::number( conver ) );
	result_json_object.insert( "uint8_t", varJson );
	return true;
}

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const uint16_t &conver ) {
	QJsonObject varJson;
	varJson.insert( "var", QString::number( conver ) );
	result_json_object.insert( "uint16_t", varJson );
	return true;
}

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const uint32_t &conver ) {
	QJsonObject varJson;
	varJson.insert( "var", QString::number( conver ) );
	result_json_object.insert( "uint32_t", varJson );
	return true;
}

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const uint64_t &conver ) {
	QJsonObject varJson;
	varJson.insert( "var", QString::number( conver ) );
	result_json_object.insert( "uint64_t", varJson );
	return true;
}

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const QString &conver ) {
	QJsonObject varJson;
	varJson.insert( "var", conver );
	result_json_object.insert( "string", varJson );
	return true;
}

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const std::string &conver ) {
	QJsonObject varJson;
	varJson.insert( "var", QString::fromStdString( conver ) );
	result_json_object.insert( "string", varJson );
	return true;
}

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const std::wstring &conver ) {
	QJsonObject varJson;
	varJson.insert( "var", QString::fromStdWString( conver ) );
	result_json_object.insert( "string", varJson );
	return true;
}

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const std::vector< int8_t > &conver ) {
	size_t count = conver.size( );
	QJsonObject countJson;
	if( toJson( countJson, count ) == false )
		return false;
	QJsonObject dataJson;
	auto data = conver.data( );
	size_t index = 0;
	for( ; index < count; index += 1 ) {
		QJsonObject vectorValue;
		if( toJson( vectorValue, data[ index ] ) == false )
			return false;
		dataJson.insert( QString::number( index ), vectorValue );
	}
	QJsonObject vectorJson;
	vectorJson.insert( "count", countJson );
	vectorJson.insert( "data", dataJson );
	result_json_object.insert( "std::vector< int8_t >", vectorJson );
	return false;
}

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const std::vector< int16_t > &conver ) {
	size_t count = conver.size( );
	QJsonObject countJson;
	if( toJson( countJson, count ) == false )
		return false;
	QJsonObject dataJson;
	auto data = conver.data( );
	size_t index = 0;
	for( ; index < count; index += 1 ) {
		QJsonObject vectorValue;
		if( toJson( vectorValue, data[ index ] ) == false )
			return false;
		dataJson.insert( QString::number( index ), vectorValue );
	}
	QJsonObject vectorJson;
	vectorJson.insert( "count", countJson );
	vectorJson.insert( "data", dataJson );
	result_json_object.insert( "std::vector< int16_t >", vectorJson );
	return false;
}

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const std::vector< int32_t > &conver ) {
	size_t count = conver.size( );
	QJsonObject countJson;
	if( toJson( countJson, count ) == false )
		return false;
	QJsonObject dataJson;
	auto data = conver.data( );
	size_t index = 0;
	for( ; index < count; index += 1 ) {
		QJsonObject vectorValue;
		if( toJson( vectorValue, data[ index ] ) == false )
			return false;
		dataJson.insert( QString::number( index ), vectorValue );
	}
	QJsonObject vectorJson;
	vectorJson.insert( "count", countJson );
	vectorJson.insert( "data", dataJson );
	result_json_object.insert( "std::vector< int32_t >", vectorJson );
	return false;
}

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const std::vector< int64_t > &conver ) {
	size_t count = conver.size( );
	QJsonObject countJson;
	if( toJson( countJson, count ) == false )
		return false;
	QJsonObject dataJson;
	auto data = conver.data( );
	size_t index = 0;
	for( ; index < count; index += 1 ) {
		QJsonObject vectorValue;
		if( toJson( vectorValue, data[ index ] ) == false )
			return false;
		dataJson.insert( QString::number( index ), vectorValue );
	}
	QJsonObject vectorJson;
	vectorJson.insert( "count", countJson );
	vectorJson.insert( "data", dataJson );
	result_json_object.insert( "std::vector< int64_t >", vectorJson );
	return false;
}

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const std::vector< uint8_t > &conver ) {
	size_t count = conver.size( );
	QJsonObject countJson;
	if( toJson( countJson, count ) == false )
		return false;
	QJsonObject dataJson;
	auto data = conver.data( );
	size_t index = 0;
	for( ; index < count; index += 1 ) {
		QJsonObject vectorValue;
		if( toJson( vectorValue, data[ index ] ) == false )
			return false;
		dataJson.insert( QString::number( index ), vectorValue );
	}
	QJsonObject vectorJson;
	vectorJson.insert( "count", countJson );
	vectorJson.insert( "data", dataJson );
	result_json_object.insert( "std::vector< uint8_t >", vectorJson );
	return false;
}

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const std::vector< uint16_t > &conver ) {
	size_t count = conver.size( );
	QJsonObject countJson;
	if( toJson( countJson, count ) == false )
		return false;
	QJsonObject dataJson;
	auto data = conver.data( );
	size_t index = 0;
	for( ; index < count; index += 1 ) {
		QJsonObject vectorValue;
		if( toJson( vectorValue, data[ index ] ) == false )
			return false;
		dataJson.insert( QString::number( index ), vectorValue );
	}
	QJsonObject vectorJson;
	vectorJson.insert( "count", countJson );
	vectorJson.insert( "data", dataJson );
	result_json_object.insert( "std::vector< uint16_t >", vectorJson );
	return false;
}

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const std::vector< uint32_t > &conver ) {
	size_t count = conver.size( );
	QJsonObject countJson;
	if( toJson( countJson, count ) == false )
		return false;
	QJsonObject dataJson;
	auto data = conver.data( );
	size_t index = 0;
	for( ; index < count; index += 1 ) {
		QJsonObject vectorValue;
		if( toJson( vectorValue, data[ index ] ) == false )
			return false;
		dataJson.insert( QString::number( index ), vectorValue );
	}
	QJsonObject vectorJson;
	vectorJson.insert( "count", countJson );
	vectorJson.insert( "data", dataJson );
	result_json_object.insert( "std::vector< uint32_t >", vectorJson );
	return false;
}

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const std::vector< uint64_t > &conver ) {
	size_t count = conver.size( );
	QJsonObject countJson;
	if( toJson( countJson, count ) == false )
		return false;
	QJsonObject dataJson;
	auto data = conver.data( );
	size_t index = 0;
	for( ; index < count; index += 1 ) {
		QJsonObject vectorValue;
		if( toJson( vectorValue, data[ index ] ) == false )
			return false;
		dataJson.insert( QString::number( index ), vectorValue );
	}
	QJsonObject vectorJson;
	vectorJson.insert( "count", countJson );
	vectorJson.insert( "data", dataJson );
	result_json_object.insert( "std::vector< uint64_t >", vectorJson );
	return false;
}

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const std::vector< QString > &conver ) {
	size_t count = conver.size( );
	QJsonObject countJson;
	if( toJson( countJson, count ) == false )
		return false;
	QJsonObject dataJson;
	auto data = conver.data( );
	size_t index = 0;
	for( ; index < count; index += 1 ) {
		QJsonObject vectorValue;
		if( toJson( vectorValue, data[ index ] ) == false )
			return false;
		dataJson.insert( QString::number( index ), vectorValue );
	}
	QJsonObject vectorJson;
	vectorJson.insert( "count", countJson );
	vectorJson.insert( "data", dataJson );
	result_json_object.insert( "std::vector< string >", vectorJson );
	return false;
}

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const std::vector< std::string > &conver ) {
	size_t count = conver.size( );
	QJsonObject countJson;
	if( toJson( countJson, count ) == false )
		return false;
	QJsonObject dataJson;
	auto data = conver.data( );
	size_t index = 0;
	for( ; index < count; index += 1 ) {
		QJsonObject vectorValue;
		if( toJson( vectorValue, data[ index ] ) == false )
			return false;
		dataJson.insert( QString::number( index ), vectorValue );
	}
	QJsonObject vectorJson;
	vectorJson.insert( "count", countJson );
	vectorJson.insert( "data", dataJson );
	result_json_object.insert( "std::vector< string >", vectorJson );
	return false;
}

bool JsonObjectTools::toJson( QJsonObject &result_json_object, const std::vector< std::wstring > &conver ) {
	size_t count = conver.size( );
	QJsonObject countJson;
	if( toJson( countJson, count ) == false )
		return false;
	QJsonObject dataJson;
	auto data = conver.data( );
	size_t index = 0;
	for( ; index < count; index += 1 ) {
		QJsonObject vectorValue;
		if( toJson( vectorValue, data[ index ] ) == false )
			return false;
		dataJson.insert( QString::number( index ), vectorValue );
	}
	QJsonObject vectorJson;
	vectorJson.insert( "count", countJson );
	vectorJson.insert( "data", dataJson );
	result_json_object.insert( "std::vector< string >", vectorJson );
	return false;
}

bool JsonObjectTools::toObject( int8_t &result_conver, const QJsonObject &json_object ) {
	return false;
}

bool JsonObjectTools::toObject( int16_t &result_conver, const QJsonObject &json_object ) {
	return false;
}

bool JsonObjectTools::toObject( int32_t &result_conver, const QJsonObject &json_object ) {
	return false;
}

bool JsonObjectTools::toObject( int64_t &result_conver, const QJsonObject &json_object ) {
	return false;
}

bool JsonObjectTools::toObject( uint8_t &result_conver, const QJsonObject &json_object ) {
	return false;
}

bool JsonObjectTools::toObject( uint16_t &result_conver, const QJsonObject &json_object ) {
	return false;
}

bool JsonObjectTools::toObject( uint32_t &result_conver, const QJsonObject &json_object ) {
	return false;
}

bool JsonObjectTools::toObject( uint64_t &result_conver, const QJsonObject &json_object ) {
	return false;
}

bool JsonObjectTools::toObject( QString &result_conver, const QJsonObject &json_object ) {
	return false;
}

bool JsonObjectTools::toObject( std::string &result_conver, const QJsonObject &json_object ) {
	return false;
}

bool JsonObjectTools::toObject( std::wstring &result_conver, const QJsonObject &json_object ) {
	return false;
}

bool JsonObjectTools::toObject( std::vector< int8_t > &result_conver, const QJsonObject &json_object ) {
	return false;
}

bool JsonObjectTools::toObject( std::vector< int16_t > &result_conver, const QJsonObject &json_object ) {
	return false;
}

bool JsonObjectTools::toObject( std::vector< int32_t > &result_conver, const QJsonObject &json_object ) {
	return false;
}

bool JsonObjectTools::toObject( std::vector< int64_t > &result_conver, const QJsonObject &json_object ) {
	return false;
}

bool JsonObjectTools::toObject( std::vector< uint8_t > &result_conver, const QJsonObject &json_object ) {
	return false;
}

bool JsonObjectTools::toObject( std::vector< uint16_t > &result_conver, const QJsonObject &json_object ) {
	return false;
}

bool JsonObjectTools::toObject( std::vector< uint32_t > &result_conver, const QJsonObject &json_object ) {
	return false;
}

bool JsonObjectTools::toObject( std::vector< uint64_t > &result_conver, const QJsonObject &json_object ) {
	return false;
}

bool JsonObjectTools::toObject( std::vector< QString > &result_conver, const QJsonObject &json_object ) {
	return false;
}

bool JsonObjectTools::toObject( std::vector< std::string > &result_conver, const QJsonObject &json_object ) {
	return false;
}

bool JsonObjectTools::toObject( std::vector< std::wstring > &result_conver, const QJsonObject &json_object ) {
	return false;
}
