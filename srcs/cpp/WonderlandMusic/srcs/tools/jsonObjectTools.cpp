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
	return true;
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
	return true;
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
	return true;
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
	return true;
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
	return true;
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
	return true;
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
	return true;
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
	return true;
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
	return true;
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
	return true;
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
	return true;
}

bool JsonObjectTools::toObject( int8_t &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	auto find = json_object.find( "int_8" );
	if( find == json_object.end( ) )
		return false;
	auto object = find->toObject( );
	find = object.find( "var" );
	if( find == object.end( ) )
		return false;
	auto string = find.value( ).toString( );
	bool conver;
	result_conver = string.toLongLong( &conver );
	return conver;
}

bool JsonObjectTools::toObject( int16_t &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	auto find = json_object.find( "int16_t" );
	if( find == json_object.end( ) )
		return false;
	auto object = find->toObject( );
	find = object.find( "var" );
	if( find == object.end( ) )
		return false;
	auto string = find.value( ).toString( );
	bool conver;
	result_conver = string.toLongLong( &conver );
	return conver;
}

bool JsonObjectTools::toObject( int32_t &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	auto find = json_object.find( "int32_t" );
	if( find == json_object.end( ) )
		return false;
	auto object = find->toObject( );
	find = object.find( "var" );
	if( find == object.end( ) )
		return false;
	auto string = find.value( ).toString( );
	bool conver;
	result_conver = string.toLongLong( &conver );
	return conver;
}

bool JsonObjectTools::toObject( int64_t &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	auto find = json_object.find( "int64_t" );
	if( find == json_object.end( ) )
		return false;
	auto object = find->toObject( );
	find = object.find( "var" );
	if( find == object.end( ) )
		return false;
	auto string = find.value( ).toString( );
	bool conver;
	result_conver = string.toLongLong( &conver );
	return conver;
}

bool JsonObjectTools::toObject( uint8_t &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	auto find = json_object.find( "uint8_t" );
	if( find == json_object.end( ) )
		return false;
	auto object = find->toObject( );
	find = object.find( "var" );
	if( find == object.end( ) )
		return false;
	auto string = find.value( ).toString( );
	bool conver;
	result_conver = string.toULongLong( &conver );
	return conver;
}

bool JsonObjectTools::toObject( uint16_t &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	auto find = json_object.find( "uint16_t" );
	if( find == json_object.end( ) )
		return false;
	auto object = find->toObject( );
	find = object.find( "var" );
	if( find == object.end( ) )
		return false;
	auto string = find.value( ).toString( );
	bool conver;
	result_conver = string.toULongLong( &conver );
	return conver;
}

bool JsonObjectTools::toObject( uint32_t &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	auto find = json_object.find( "uint32_t" );
	if( find == json_object.end( ) )
		return false;
	auto object = find->toObject( );
	find = object.find( "var" );
	if( find == object.end( ) )
		return false;
	auto string = find.value( ).toString( );
	bool conver;
	result_conver = string.toULongLong( &conver );
	return conver;
}

bool JsonObjectTools::toObject( uint64_t &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	auto find = json_object.find( "uint64_t" );
	if( find == json_object.end( ) )
		return false;
	auto object = find->toObject( );
	find = object.find( "var" );
	if( find == object.end( ) )
		return false;
	auto string = find.value( ).toString( );
	bool conver;
	result_conver = string.toULongLong( &conver );
	return conver;
}

bool JsonObjectTools::toObject( QString &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	auto find = json_object.find( "string" );
	if( find == json_object.end( ) )
		return false;
	auto object = find->toObject( );
	find = object.find( "var" );
	if( find == object.end( ) )
		return false;
	result_conver = find.value( ).toString( );
	return true;
}

bool JsonObjectTools::toObject( std::string &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	auto find = json_object.find( "string" );
	if( find == json_object.end( ) )
		return false;
	auto object = find->toObject( );
	find = object.find( "var" );
	if( find == object.end( ) )
		return false;
	result_conver = find.value( ).toString( ).toStdString( );
	return true;
}

bool JsonObjectTools::toObject( std::wstring &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	auto find = json_object.find( "string" );
	if( find == json_object.end( ) )
		return false;
	auto object = find->toObject( );
	find = object.find( "var" );
	if( find == object.end( ) )
		return false;
	result_conver = find.value( ).toString( ).toStdWString( );
	return true;
}

bool JsonObjectTools::toObject( std::vector< int8_t > &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	int8_t resultVar;
	auto find = json_object.find( "std::vector< int8_t >" );
	auto end = json_object.end( );
	if( find == end )
		return false;

	auto object = find.value( ).toObject( );
	find = object.find( "count" );
	end = object.end( );
	if( find == end )
		return false;
	bool conver;
	size_t count = find.value( ).toString( ).toULongLong( &conver );
	if( conver == false )
		return false;
	find = object.find( "data" );
	end = object.end( );
	if( find == end )
		return false;
	result_conver.resize( count );
	if( count == 0 )
		return true;
	object = find.value( ).toObject( );
	if( object.empty( ) )
		return false;
	find = object.begin( );
	end = object.end( );
	auto data = result_conver.data( );
	size_t index;
	for( ; find != end; ++find ) {
		index = find.key( ).toULongLong( &conver );
		if( conver == false )
			return false;
		if( index >= count )
			return false;

		auto jsonObject = find.value( ).toObject( );
		if( jsonObject.isEmpty( ) )
			return false;
		auto iterator = jsonObject.begin( );
		if( toObject( resultVar, iterator.value( ).toObject( ) ) == false )
			return false;
		data[ index ] = resultVar;
	}
	return true;
}

bool JsonObjectTools::toObject( std::vector< int16_t > &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	int16_t resultVar;
	auto find = json_object.find( "std::vector< int16_t >" );
	auto end = json_object.end( );
	if( find == end )
		return false;

	auto object = find.value( ).toObject( );
	find = object.find( "count" );
	end = object.end( );
	if( find == end )
		return false;
	bool conver;
	size_t count = find.value( ).toString( ).toULongLong( &conver );
	if( conver == false )
		return false;
	find = object.find( "data" );
	end = object.end( );
	if( find == end )
		return false;
	result_conver.resize( count );
	if( count == 0 )
		return true;
	object = find.value( ).toObject( );
	if( object.empty( ) )
		return false;
	find = object.begin( );
	end = object.end( );
	auto data = result_conver.data( );
	size_t index;
	for( ; find != end; ++find ) {
		index = find.key( ).toULongLong( &conver );
		if( conver == false )
			return false;
		if( index >= count )
			return false;

		auto jsonObject = find.value( ).toObject( );
		if( jsonObject.isEmpty( ) )
			return false;
		auto iterator = jsonObject.begin( );
		if( toObject( resultVar, iterator.value( ).toObject( ) ) == false )
			return false;
		data[ index ] = resultVar;
	}
	return true;
}

bool JsonObjectTools::toObject( std::vector< int32_t > &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	int32_t resultVar;
	auto find = json_object.find( "std::vector< int32_t >" );
	auto end = json_object.end( );
	if( find == end )
		return false;

	auto object = find.value( ).toObject( );
	find = object.find( "count" );
	end = object.end( );
	if( find == end )
		return false;
	bool conver;
	size_t count = find.value( ).toString( ).toULongLong( &conver );
	if( conver == false )
		return false;
	find = object.find( "data" );
	end = object.end( );
	if( find == end )
		return false;
	result_conver.resize( count );
	if( count == 0 )
		return true;
	object = find.value( ).toObject( );
	if( object.empty( ) )
		return false;
	find = object.begin( );
	end = object.end( );
	auto data = result_conver.data( );
	size_t index;
	for( ; find != end; ++find ) {
		index = find.key( ).toULongLong( &conver );
		if( conver == false )
			return false;
		if( index >= count )
			return false;

		auto jsonObject = find.value( ).toObject( );
		if( jsonObject.isEmpty( ) )
			return false;
		auto iterator = jsonObject.begin( );
		if( toObject( resultVar, iterator.value( ).toObject( ) ) == false )
			return false;
		data[ index ] = resultVar;
	}
	return true;
}

bool JsonObjectTools::toObject( std::vector< int64_t > &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	int64_t resultVar;
	auto find = json_object.find( "std::vector< int64_t >" );
	auto end = json_object.end( );
	if( find == end )
		return false;

	auto object = find.value( ).toObject( );
	find = object.find( "count" );
	end = object.end( );
	if( find == end )
		return false;
	bool conver;
	size_t count = find.value( ).toString( ).toULongLong( &conver );
	if( conver == false )
		return false;
	find = object.find( "data" );
	end = object.end( );
	if( find == end )
		return false;
	result_conver.resize( count );
	if( count == 0 )
		return true;
	object = find.value( ).toObject( );
	if( object.empty( ) )
		return false;
	find = object.begin( );
	end = object.end( );
	auto data = result_conver.data( );
	size_t index;
	for( ; find != end; ++find ) {
		index = find.key( ).toULongLong( &conver );
		if( conver == false )
			return false;
		if( index >= count )
			return false;

		auto jsonObject = find.value( ).toObject( );
		if( jsonObject.isEmpty( ) )
			return false;
		auto iterator = jsonObject.begin( );
		if( toObject( resultVar, iterator.value( ).toObject( ) ) == false )
			return false;
		data[ index ] = resultVar;
	}
	return true;
}

bool JsonObjectTools::toObject( std::vector< uint8_t > &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	uint8_t resultVar;
	auto find = json_object.find( "std::vector< uint8_t >" );
	auto end = json_object.end( );
	if( find == end )
		return false;

	auto object = find.value( ).toObject( );
	find = object.find( "count" );
	end = object.end( );
	if( find == end )
		return false;
	bool conver;
	size_t count = find.value( ).toString( ).toULongLong( &conver );
	if( conver == false )
		return false;
	find = object.find( "data" );
	end = object.end( );
	if( find == end )
		return false;
	result_conver.resize( count );
	if( count == 0 )
		return true;
	object = find.value( ).toObject( );
	if( object.empty( ) )
		return false;
	find = object.begin( );
	end = object.end( );
	auto data = result_conver.data( );
	size_t index;
	for( ; find != end; ++find ) {
		index = find.key( ).toULongLong( &conver );
		if( conver == false )
			return false;
		if( index >= count )
			return false;

		auto jsonObject = find.value( ).toObject( );
		if( jsonObject.isEmpty( ) )
			return false;
		auto iterator = jsonObject.begin( );
		if( toObject( resultVar, iterator.value( ).toObject( ) ) == false )
			return false;
		data[ index ] = resultVar;
	}
	return true;
}

bool JsonObjectTools::toObject( std::vector< uint16_t > &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	uint16_t resultVar;
	auto find = json_object.find( "std::vector< uint16_t >" );
	auto end = json_object.end( );
	if( find == end )
		return false;

	auto object = find.value( ).toObject( );
	find = object.find( "count" );
	end = object.end( );
	if( find == end )
		return false;
	bool conver;
	size_t count = find.value( ).toString( ).toULongLong( &conver );
	if( conver == false )
		return false;
	find = object.find( "data" );
	end = object.end( );
	if( find == end )
		return false;
	result_conver.resize( count );
	if( count == 0 )
		return true;
	object = find.value( ).toObject( );
	if( object.empty( ) )
		return false;
	find = object.begin( );
	end = object.end( );
	auto data = result_conver.data( );
	size_t index;
	for( ; find != end; ++find ) {
		index = find.key( ).toULongLong( &conver );
		if( conver == false )
			return false;
		if( index >= count )
			return false;

		auto jsonObject = find.value( ).toObject( );
		if( jsonObject.isEmpty( ) )
			return false;
		auto iterator = jsonObject.begin( );
		if( toObject( resultVar, iterator.value( ).toObject( ) ) == false )
			return false;
		data[ index ] = resultVar;
	}
	return true;
}

bool JsonObjectTools::toObject( std::vector< uint32_t > &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	uint32_t resultVar;
	auto find = json_object.find( "std::vector< uint32_t >" );
	auto end = json_object.end( );
	if( find == end )
		return false;

	auto object = find.value( ).toObject( );
	find = object.find( "count" );
	end = object.end( );
	if( find == end )
		return false;
	bool conver;
	size_t count = find.value( ).toString( ).toULongLong( &conver );
	if( conver == false )
		return false;
	find = object.find( "data" );
	end = object.end( );
	if( find == end )
		return false;
	result_conver.resize( count );
	if( count == 0 )
		return true;
	object = find.value( ).toObject( );
	if( object.empty( ) )
		return false;
	find = object.begin( );
	end = object.end( );
	auto data = result_conver.data( );
	size_t index;
	for( ; find != end; ++find ) {
		index = find.key( ).toULongLong( &conver );
		if( conver == false )
			return false;
		if( index >= count )
			return false;

		auto jsonObject = find.value( ).toObject( );
		if( jsonObject.isEmpty( ) )
			return false;
		auto iterator = jsonObject.begin( );
		if( toObject( resultVar, iterator.value( ).toObject( ) ) == false )
			return false;
		data[ index ] = resultVar;
	}
	return true;
}

bool JsonObjectTools::toObject( std::vector< uint64_t > &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	uint64_t resultVar;
	auto find = json_object.find( "std::vector< uint64_t >" );
	auto end = json_object.end( );
	if( find == end )
		return false;

	auto object = find.value( ).toObject( );
	find = object.find( "count" );
	end = object.end( );
	if( find == end )
		return false;
	bool conver;
	size_t count = find.value( ).toString( ).toULongLong( &conver );
	if( conver == false )
		return false;
	find = object.find( "data" );
	end = object.end( );
	if( find == end )
		return false;
	result_conver.resize( count );
	if( count == 0 )
		return true;
	object = find.value( ).toObject( );
	if( object.empty( ) )
		return false;
	find = object.begin( );
	end = object.end( );
	auto data = result_conver.data( );
	size_t index;
	for( ; find != end; ++find ) {
		index = find.key( ).toULongLong( &conver );
		if( conver == false )
			return false;
		if( index >= count )
			return false;

		auto jsonObject = find.value( ).toObject( );
		if( jsonObject.isEmpty( ) )
			return false;
		auto iterator = jsonObject.begin( );
		if( toObject( resultVar, iterator.value( ).toObject( ) ) == false )
			return false;
		data[ index ] = resultVar;
	}
	return true;
}

bool JsonObjectTools::toObject( std::vector< QString > &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	QString resultVar;
	auto find = json_object.find( "std::vector< string >" );
	auto end = json_object.end( );
	if( find == end )
		return false;

	auto object = find.value( ).toObject( );
	find = object.find( "count" );
	end = object.end( );
	if( find == end )
		return false;
	bool conver;
	size_t count = find.value( ).toString( ).toULongLong( &conver );
	if( conver == false )
		return false;
	find = object.find( "data" );
	end = object.end( );
	if( find == end )
		return false;
	result_conver.resize( count );
	if( count == 0 )
		return true;
	object = find.value( ).toObject( );
	if( object.empty( ) )
		return false;
	find = object.begin( );
	end = object.end( );
	auto data = result_conver.data( );
	size_t index;
	for( ; find != end; ++find ) {
		index = find.key( ).toULongLong( &conver );
		if( conver == false )
			return false;
		if( index >= count )
			return false;

		auto jsonObject = find.value( ).toObject( );
		if( jsonObject.isEmpty( ) )
			return false;
		auto iterator = jsonObject.begin( );
		if( toObject( resultVar, iterator.value( ).toObject( ) ) == false )
			return false;
		data[ index ] = resultVar;
	}
	return true;
}

bool JsonObjectTools::toObject( std::vector< std::string > &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	std::string resultVar;
	auto find = json_object.find( "std::vector< string >" );
	auto end = json_object.end( );
	if( find == end )
		return false;

	auto object = find.value( ).toObject( );
	find = object.find( "count" );
	end = object.end( );
	if( find == end )
		return false;
	bool conver;
	size_t count = find.value( ).toString( ).toULongLong( &conver );
	if( conver == false )
		return false;
	find = object.find( "data" );
	end = object.end( );
	if( find == end )
		return false;
	result_conver.resize( count );
	if( count == 0 )
		return true;
	object = find.value( ).toObject( );
	if( object.empty( ) )
		return false;
	find = object.begin( );
	end = object.end( );
	auto data = result_conver.data( );
	size_t index;
	for( ; find != end; ++find ) {
		index = find.key( ).toULongLong( &conver );
		if( conver == false )
			return false;
		if( index >= count )
			return false;

		auto jsonObject = find.value( ).toObject( );
		if( jsonObject.isEmpty( ) )
			return false;
		auto iterator = jsonObject.begin( );
		if( toObject( resultVar, iterator.value( ).toObject( ) ) == false )
			return false;
		data[ index ] = resultVar;
	}
	return true;
}

bool JsonObjectTools::toObject( std::vector< std::wstring > &result_conver, const QJsonObject &json_object ) {
	if( json_object.isEmpty( ) )
		return false;
	std::wstring resultVar;
	auto find = json_object.find( "std::vector< string >" );
	auto end = json_object.end( );
	if( find == end )
		return false;

	auto object = find.value( ).toObject( );
	find = object.find( "count" );
	end = object.end( );
	if( find == end )
		return false;
	bool conver;
	size_t count = find.value( ).toString( ).toULongLong( &conver );
	if( conver == false )
		return false;
	find = object.find( "data" );
	end = object.end( );
	if( find == end )
		return false;
	result_conver.resize( count );
	if( count == 0 )
		return true;
	object = find.value( ).toObject( );
	if( object.empty( ) )
		return false;
	find = object.begin( );
	end = object.end( );
	auto data = result_conver.data( );
	size_t index;
	for( ; find != end; ++find ) {
		index = find.key( ).toULongLong( &conver );
		if( conver == false )
			return false;
		if( index >= count )
			return false;

		auto jsonObject = find.value( ).toObject( );
		if( jsonObject.isEmpty( ) )
			return false;
		auto iterator = jsonObject.begin( );
		if( toObject( resultVar, iterator.value( ).toObject( ) ) == false )
			return false;
		data[ index ] = resultVar;
	}
	return true;
}
