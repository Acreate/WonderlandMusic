#ifndef IAPPJSONDATA_H_H_HEAD__FILE__
#define IAPPJSONDATA_H_H_HEAD__FILE__

#include <QString>
#include <QObject>


class QJsonObject;

class IAppJsonData {
protected:
	virtual ~IAppJsonData( );

public:
	virtual bool getJsonData( QJsonObject &get_json_object ) const = 0;

	virtual bool setJsonData( const QJsonObject &set_json_object ) = 0;
};

#endif // IAPPJSONDATA_H_H_HEAD__FILE__
