#ifndef MUSICINFOITEMTRANSLATE_H_H_HEAD__FILE__
#define MUSICINFOITEMTRANSLATE_H_H_HEAD__FILE__
#include "iTranslate.h"

class MusicInfoItemTranslate : public ITranslate{
	QString musichumanBeingNameNone;
public:
	bool init( ) override;

	virtual const QString & getMusichumanBeingNameNone( ) const;
};

#endif // MUSICINFOITEMTRANSLATE_H_H_HEAD__FILE__
