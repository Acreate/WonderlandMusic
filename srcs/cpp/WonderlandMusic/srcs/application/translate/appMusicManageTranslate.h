#ifndef APPMUSICMANAGETRANSLATE_H_H_HEAD__FILE__
#define APPMUSICMANAGETRANSLATE_H_H_HEAD__FILE__
#include <interface/iTranslate.h>

class AppMusicManageTranslate : public ITranslate {
	QString rootFavoriteName;
	QString anyFileTypeName;
	QString musicFileTypeName;
	QString selectMultipleFileTitle;
	QString selectMultipleDirTitle;

public:
	bool init( ) override;

	virtual const QString & getRootFavoriteName( ) const;

	virtual const QString & getAnyFileTypeName( ) const;

	virtual const QString & getMusicFileTypeName( ) const;

	virtual const QString & getSelectMultipleFileTitle( ) const;

	virtual const QString & getSelectMultipleDirTitle( ) const;
};

namespace AppTranslateTools {
	Declaration_Get_Translate( AppMusicManage );
}
#endif // APPMUSICMANAGETRANSLATE_H_H_HEAD__FILE__
