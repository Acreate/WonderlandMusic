#ifndef MUSICLISTMENUTRANSLATE_H_H_HEAD__FILE__
#define MUSICLISTMENUTRANSLATE_H_H_HEAD__FILE__
#include <interface/iTranslate.h>

class MusicListMenuTranslate : public ITranslate {
	QString playMusicItem;
	QString removeMusicItem;
	QString deleteMusicItem;
	QString moveToTopMusicItem;
	QString moveToBottomMusicItem;
	QString moveToPlayTopMusicItem;
	QString moveToPlayBottomMusicItem;

public:
	bool init( ) override;
	virtual const QString & getPlayMusicItem( ) const;
	virtual const QString & getRemoveMusicItem( ) const;
	virtual const QString & getDeleteMusicItem( ) const;
	virtual const QString & getMoveToTopMusicItem( ) const;
	virtual const QString & getMoveToBottomMusicItem( ) const;
	virtual const QString & getMoveToPlayTopMusicItem( ) const;
	virtual const QString & getMoveToPlayBottomMusicItem( ) const;
};

namespace AppTranslateTools {
	Declaration_Get_Translate( MusicListMenu );
}
#endif // MUSICLISTMENUTRANSLATE_H_H_HEAD__FILE__
