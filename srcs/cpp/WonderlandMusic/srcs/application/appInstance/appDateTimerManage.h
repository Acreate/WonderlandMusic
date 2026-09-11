#ifndef APPDATETIMERMANAGE_H_H_HEAD__FILE__
#define APPDATETIMERMANAGE_H_H_HEAD__FILE__

#include <interface/iAppResourceCore.h>

#include "../../classTypeInfo/classTypeInfoVar.h"

class QDateTime;

class AppDateTimerManage : public QObject, public IAppResourceCore, public ClassTypeInfoVar {
protected:
	/// @brief 起始时间
	QDateTime *startDateTime = nullptr;

public:
	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;

protected:
	bool deleteResource( ) override;

public:
	AppDateTimerManage( );
	~AppDateTimerManage( ) override;

	virtual const QDateTime * getStartDateTime( ) const;
};

#endif // APPDATETIMERMANAGE_H_H_HEAD__FILE__
