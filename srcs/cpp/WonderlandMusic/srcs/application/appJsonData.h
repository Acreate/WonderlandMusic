#ifndef APPJSONDATA_H_H_HEAD__FILE__
#define APPJSONDATA_H_H_HEAD__FILE__

class QJsonObject;

class AppJsonData {
protected:
	virtual ~AppJsonData( ) = default;

	virtual bool readJsonData( ) = 0;

	virtual bool writeJsonData( ) = 0;

public:
	virtual bool getJsonData( QJsonObject &get_json_object ) const = 0;

	virtual bool setJsonData( const QJsonObject &set_json_object ) = 0;
};

#endif // APPJSONDATA_H_H_HEAD__FILE__
