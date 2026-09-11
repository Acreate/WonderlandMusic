#ifndef DELETEEXCEPTIONTRANSLATE_H_H_HEAD__FILE__
#define DELETEEXCEPTIONTRANSLATE_H_H_HEAD__FILE__
#include <interface/iTranslate.h>

class DeleteExceptionTranslate : public ITranslate {
	QString deletePtrError;

public:
	bool init( ) override;

	virtual const QString & getDeletePtrError( ) const;
};

namespace AppTranslateTools {
	Declaration_Get_Translate( DeleteException );
}
#endif // DELETEEXCEPTIONTRANSLATE_H_H_HEAD__FILE__
