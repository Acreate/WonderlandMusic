#ifndef APPMUSICMANAGETRANSLATE_H_H_HEAD__FILE__
#define APPMUSICMANAGETRANSLATE_H_H_HEAD__FILE__
#include "../../interface/iTranslate.h"

class AppMusicManageTranslate : public ITranslate{
	QString rootFavoriteName;
public:
	bool init( ) override;

	virtual const QString & getRootFavoriteName( ) const;
};

#endif // APPMUSICMANAGETRANSLATE_H_H_HEAD__FILE__
