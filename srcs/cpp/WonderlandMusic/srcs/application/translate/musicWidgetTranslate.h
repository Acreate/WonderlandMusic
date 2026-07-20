#ifndef MUSICWIDGETTRANSLATE_H_H_HEAD__FILE__
#define MUSICWIDGETTRANSLATE_H_H_HEAD__FILE__
#include "../../interface/iTranslate.h"

class MusicWidgetTranslate : public ITranslate {
	QString titleName;

public:
	bool init( ) override;

	virtual const QString & getTitleName( ) const;
};
#endif // MUSICWIDGETTRANSLATE_H_H_HEAD__FILE__
