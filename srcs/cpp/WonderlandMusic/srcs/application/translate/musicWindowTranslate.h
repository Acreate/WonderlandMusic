#ifndef MUSICWINDOWTRANSLATE_H_H_HEAD__FILE__
#define MUSICWINDOWTRANSLATE_H_H_HEAD__FILE__

#include "../../interface/iTranslate.h"

class MusicWindowTranslate : public ITranslate {
	QString titleName;

public:
	bool init( ) override;

	virtual const QString & getTitleName( ) const;
};

namespace AppTranslateTools {
	Declaration_Get_Translate( MusicWindow );
}
#endif // MUSICWINDOWTRANSLATE_H_H_HEAD__FILE__
