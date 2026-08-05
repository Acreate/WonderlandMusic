#ifndef USERMUTEXTRANSLATE_H_H_HEAD__FILE__
#define USERMUTEXTRANSLATE_H_H_HEAD__FILE__

#include <interface/iTranslate.h>

class UserMutexTranslate : public ITranslate {
	QString nodeSetUnlockError;
	QString trylockError;
	QString lastTrylock;
	QString lastLock;
	QString lastUnlock;

public:
	bool init( ) override;

public:
	virtual const QString & getNodeSetUnlockError( ) const;

	virtual const QString & getTrylockError( ) const;

	virtual const QString & getLastTrylock( ) const;

	virtual const QString & getLastLock( ) const;

	virtual const QString & getLastUnlock( ) const;
};

namespace AppTranslateTools {
	Declaration_Get_Translate( UserMutex );
}
#endif // USERMUTEXTRANSLATE_H_H_HEAD__FILE__
