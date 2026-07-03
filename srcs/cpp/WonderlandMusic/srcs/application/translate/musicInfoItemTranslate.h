#ifndef MUSICINFOITEMTRANSLATE_H_H_HEAD__FILE__
#define MUSICINFOITEMTRANSLATE_H_H_HEAD__FILE__

#include <interface/iTranslate.h>

class MusicInfoItemTranslate : public ITranslate {
	QString musichumanBeingNameNone;

public:
	bool init( ) override;

public:
	virtual const QString & getMusichumanBeingNameNone( ) const;
};

#endif // MUSICINFOITEMTRANSLATE_H_H_HEAD__FILE__
