#ifndef PLAYERLISTMENUTRANSLATE_H_H_HEAD__FILE__
#define PLAYERLISTMENUTRANSLATE_H_H_HEAD__FILE__
#include "iTranslate.h"

class PlayerListMenuTranslate : public ITranslate {
	QString playerListMenuFileLoadMenu;
	QString playerListAddMultiMusicFileToCollectionAction;
	QString playerListAddMultiMusicDirToCollectionAction;
	
	QString playerListMenuenuPlayerMenu;
	QString playerListMenuPlayerMenuSetCurrentPlayAction;
	QString playerListMenuPlayerMenuInsterCurrentPlayAction;
	
	QString playerListMenuControlMenu;
	QString playerListMenuControlMenuRemoveMusicAction;
	QString playerListMenuControlMenuDeleteMusicAction;
	
	QString playerListMenuMoveMenu;
	QString playerListMenuControlMenuMoveTopMusicAction;
	QString playerListMenuControlMenuMoveBottomMusicAction;

	QString musicTypeName;
	QString loadDiskFileTitle;
	QString loadDiskDirTitle;
public:
	bool init( ) override;

	virtual const QString & getLoadDiskFileTitle( ) const;

	virtual const QString & getLoadDiskDirTitle( ) const;

	virtual const QString & getPlayerListMenuFileLoadMenu( ) const;

	virtual const QString & getPlayerListAddMultiMusicFileToCollectionAction( ) const;

	virtual const QString & getPlayerListAddMultiMusicDirToCollectionAction( ) const;

	virtual const QString & getPlayerListMenuenuPlayerMenu( ) const;

	virtual const QString & getPlayerListMenuPlayerMenuSetCurrentPlayAction( ) const;

	virtual const QString & getPlayerListMenuPlayerMenuInsterCurrentPlayAction( ) const;

	virtual const QString & getPlayerListMenuControlMenu( ) const;

	virtual const QString & getPlayerListMenuControlMenuRemoveMusicAction( ) const;

	virtual const QString & getPlayerListMenuControlMenuDeleteMusicAction( ) const;

	virtual const QString & getPlayerListMenuMoveMenu( ) const;

	virtual const QString & getPlayerListMenuControlMenuMoveTopMusicAction( ) const;

	virtual const QString & getPlayerListMenuControlMenuMoveBottomMusicAction( ) const;

	virtual const QString & getMusicTypeName( ) const;
};

#endif // PLAYERLISTMENUTRANSLATE_H_H_HEAD__FILE__
