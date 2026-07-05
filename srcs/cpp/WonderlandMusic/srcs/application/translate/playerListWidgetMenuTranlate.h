#ifndef PLAYERLISTWIDGETMENUTRANLATE_H_H_HEAD__FILE__
#define PLAYERLISTWIDGETMENUTRANLATE_H_H_HEAD__FILE__

#include <interface/iTranslate.h>

class PlayerListWidgetMenuTranlate : public ITranslate {
	QString filePathLoadMenu;
	QString loadFileAction;
	QString loadDirAction;

	QString playerMusicMenu;
	QString aggregateToPlayerAfter;
	QString aggregateToPlayerBefore;

	QString controlMenu;
	QString removeMusciItemAction;
	QString deleteMusicFileAction;

	QString removeMenu;
	QString moveTopAction;
	QString moveBottomAction;
	QString aggregateToSelectFirst;
	QString aggregateToSelectLast;

public:
	bool init( ) override;

public:
	virtual const QString & getFilePathLoadMenu( ) const;

	virtual const QString & getLoadFileAction( ) const;

	virtual const QString & getLoadDirAction( ) const;

	virtual const QString & getPlayerMusicMenu( ) const;

	virtual const QString & getAggregateToPlayerAfter( ) const;

	virtual const QString & getAggregateToPlayerBefore( ) const;

	virtual const QString & getControlMenu( ) const;

	virtual const QString & getRemoveMusciItemAction( ) const;

	virtual const QString & getDeleteMusicFileAction( ) const;

	virtual const QString & getRemoveMenu( ) const;

	virtual const QString & getMoveTopAction( ) const;

	virtual const QString & getMoveBottomAction( ) const;

	virtual const QString & getAggregateToSelectFirst( ) const;

	virtual const QString & getAggregateToSelectLast( ) const;
};

#endif // PLAYERLISTWIDGETMENUTRANLATE_H_H_HEAD__FILE__
