#ifndef JSONOBJECTTOOLS_H_H_HEAD__FILE__
#define JSONOBJECTTOOLS_H_H_HEAD__FILE__
#include <string>
#include <vector>

class QString;
class QJsonObject;

namespace JsonObjectTools {
	bool toJson( QJsonObject &result_json_object, const int8_t &conver );
	bool toJson( QJsonObject &result_json_object, const int16_t &conver );
	bool toJson( QJsonObject &result_json_object, const int32_t &conver );
	bool toJson( QJsonObject &result_json_object, const int64_t &conver );
	bool toJson( QJsonObject &result_json_object, const uint8_t &conver );
	bool toJson( QJsonObject &result_json_object, const uint16_t &conver );
	bool toJson( QJsonObject &result_json_object, const uint32_t &conver );
	bool toJson( QJsonObject &result_json_object, const uint64_t &conver );
	bool toJson( QJsonObject &result_json_object, const QString &conver );
	bool toJson( QJsonObject &result_json_object, const std::string &conver );
	bool toJson( QJsonObject &result_json_object, const std::wstring &conver );

	bool toJson( QJsonObject &result_json_object, const std::vector< int8_t > &conver );
	bool toJson( QJsonObject &result_json_object, const std::vector< int16_t > &conver );
	bool toJson( QJsonObject &result_json_object, const std::vector< int32_t > &conver );
	bool toJson( QJsonObject &result_json_object, const std::vector< int64_t > &conver );
	bool toJson( QJsonObject &result_json_object, const std::vector< uint8_t > &conver );
	bool toJson( QJsonObject &result_json_object, const std::vector< uint16_t > &conver );
	bool toJson( QJsonObject &result_json_object, const std::vector< uint32_t > &conver );
	bool toJson( QJsonObject &result_json_object, const std::vector< uint64_t > &conver );
	bool toJson( QJsonObject &result_json_object, const std::vector< QString > &conver );
	bool toJson( QJsonObject &result_json_object, const std::vector< std::string > &conver );
	bool toJson( QJsonObject &result_json_object, const std::vector< std::wstring > &conver );

	bool toObject( int8_t &result_conver, const QJsonObject &json_object );
	bool toObject( int16_t &result_conver, const QJsonObject &json_object );
	bool toObject( int32_t &result_conver, const QJsonObject &json_object );
	bool toObject( int64_t &result_conver, const QJsonObject &json_object );
	bool toObject( uint8_t &result_conver, const QJsonObject &json_object );
	bool toObject( uint16_t &result_conver, const QJsonObject &json_object );
	bool toObject( uint32_t &result_conver, const QJsonObject &json_object );
	bool toObject( uint64_t &result_conver, const QJsonObject &json_object );
	bool toObject( QString &result_conver, const QJsonObject &json_object );
	bool toObject( std::string &result_conver, const QJsonObject &json_object );
	bool toObject( std::wstring &result_conver, const QJsonObject &json_object );

	bool toObject( std::vector< int8_t > &result_conver, const QJsonObject &json_object );
	bool toObject( std::vector< int16_t > &result_conver, const QJsonObject &json_object );
	bool toObject( std::vector< int32_t > &result_conver, const QJsonObject &json_object );
	bool toObject( std::vector< int64_t > &result_conver, const QJsonObject &json_object );
	bool toObject( std::vector< uint8_t > &result_conver, const QJsonObject &json_object );
	bool toObject( std::vector< uint16_t > &result_conver, const QJsonObject &json_object );
	bool toObject( std::vector< uint32_t > &result_conver, const QJsonObject &json_object );
	bool toObject( std::vector< uint64_t > &result_conver, const QJsonObject &json_object );
	bool toObject( std::vector< QString > &result_conver, const QJsonObject &json_object );
	bool toObject( std::vector< std::string > &result_conver, const QJsonObject &json_object );
	bool toObject( std::vector< std::wstring > &result_conver, const QJsonObject &json_object );
};

#endif // JSONOBJECTTOOLS_H_H_HEAD__FILE__
