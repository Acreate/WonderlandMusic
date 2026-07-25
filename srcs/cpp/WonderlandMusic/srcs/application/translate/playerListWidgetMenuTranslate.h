#ifndef PLAYERLISTWIDGETMENUTRANSLATE_H_H_HEAD__FILE__
#define PLAYERLISTWIDGETMENUTRANSLATE_H_H_HEAD__FILE__
#include "../../interface/iTranslate.h"

class PlayerListWidgetMenuTranslate : public ITranslate {
	QString add;
	QString addMusicFile;
	QString addMusicDir;
	QString remove;
	QString removeMusicFile;
	QString deleteMusicFile;
	QString move;
	QString moveToPlayerAfter;
	QString moveToPlayerBefore;
	QString moveToSelectFirst;
	QString moveToSelectEnd;
	QString moveToListFrist;
	QString moveToListEnd;
	QString sort;
	QString sortName;
	QString sortTime;
	QString sortSinger;

public:
	bool init( ) override;
	virtual const QString & getMoveToSelectFirst( ) const;
	virtual const QString & getMoveToSelectEnd( ) const;
	virtual const QString & getAdd( ) const;
	virtual const QString & getRemove( ) const;
	virtual const QString & getAddMusicFile( ) const;
	virtual const QString & getAddMusicDir( ) const;
	virtual const QString & getRemoveMusicFile( ) const;
	virtual const QString & getDeleteMusicFile( ) const;
	virtual const QString & getMove( ) const;
	virtual const QString & getMoveToPlayerAfter( ) const;
	virtual const QString & getMoveToPlayerBefore( ) const;
	virtual const QString & getMoveToListFrist( ) const;
	virtual const QString & getMoveToListEnd( ) const;
	virtual const QString & getSort( ) const;
	virtual const QString & getSortName( ) const;
	virtual const QString & getSortTime( ) const;
	virtual const QString & getSortSinger( ) const;
};

#endif // PLAYERLISTWIDGETMENUTRANSLATE_H_H_HEAD__FILE__
