#ifndef MUSICTITLEWIDGETTRANSLATE_H_H_HEAD__FILE__
#define MUSICTITLEWIDGETTRANSLATE_H_H_HEAD__FILE__
#include "../../interface/iTranslate.h"

class MusicTitleWidgetTranslate : public ITranslate {
	QString musicCode;
	QString musicName;
	QString musicSingeName;
	QString musicDurationTime;

public:
	bool init( ) override;
	virtual const QString & getMusicCode( ) const;
	virtual const QString & getMusicName( ) const;
	virtual const QString & getMusicSingeName( ) const;
	virtual const QString & getMusicDurationTime( ) const;
};

namespace AppTranslateTools {
	Declaration_Get_Translate( MusicTitleWidget );
}
#endif // MUSICTITLEWIDGETTRANSLATE_H_H_HEAD__FILE__
