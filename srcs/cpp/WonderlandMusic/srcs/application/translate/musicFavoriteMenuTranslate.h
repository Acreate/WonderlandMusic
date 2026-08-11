#ifndef MUSICFAVORITEMENUTRANSLATE_H_H_HEAD__FILE__
#define MUSICFAVORITEMENUTRANSLATE_H_H_HEAD__FILE__
#include "../../interface/iTranslate.h"

class MusicFavoriteMenuTranslate : public ITranslate {
	QString createFavoriteItem;
	QString renameFavoriteItem;
	QString deleteFavoriteItem;
	QString addMusicFileToFavoriteItem;
	QString addMusicDirToFavoriteItem;

	QString illegalRenameFavoriteItem;
	QString illegalDeleteFavoriteItem;
	QString illegalAddMusicFileToFavoriteItem;
	QString illegalAddMusicDirToFavoriteItem;

	QString selectMusicFile;
	QString selectMusicDir;

public:
	bool init( ) override;
	virtual const QString & getCreateFavoriteItem( ) const;
	virtual const QString & getRenameFavoriteItem( ) const;
	virtual const QString & getDeleteFavoriteItem( ) const;
	virtual const QString & getAddMusicFileToFavoriteItem( ) const;
	virtual const QString & getAddMusicDirToFavoriteItem( ) const;
	virtual const QString & getIllegalRenameFavoriteItem( ) const;
	virtual const QString & getIllegalDeleteFavoriteItem( ) const;
	virtual const QString & getIllegalAddMusicFileToFavoriteItem( ) const;
	virtual const QString & getIllegalAddMusicDirToFavoriteItem( ) const;
	virtual const QString & getSelectMusicFile( ) const;
	virtual const QString & getSelectMusicDir( ) const;
};

namespace AppTranslateTools {
	Declaration_Get_Translate( MusicFavoriteMenu );
}
#endif // MUSICFAVORITEMENUTRANSLATE_H_H_HEAD__FILE__
