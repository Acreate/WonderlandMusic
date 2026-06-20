#ifndef PLAYERLISTTOPWIDGETJSONKEY_H_H_HEAD__FILE__
#define PLAYERLISTTOPWIDGETJSONKEY_H_H_HEAD__FILE__
#include "iJsonKey.h"

class PlayerListTopWidgetJsonKey : public IJsonKey {
	QString playerListWidgetTopJsonPath;
	QString playerListWidgetItemWidth;
	QString playerListWidgetItemSplitWidth;
	QString playerListWidgetItemWidgetIndexWidth;
	QString playerListWidgetItemMusicNameWidth;
	QString playerListWidgetItemMusicSingerWidth;
	QString playerListWidgetItemMusicDurationWidth;
	QString playerListWidgetItemWidgetBeforeWidth;
	QString playerListWidgetItemWidgetAfterWidth;

public:
	bool init( ) override;

	virtual const QString & getPlayerListWidgetTopJsonPath( ) const;

	virtual const QString & getPlayerListWidgetItemWidth( ) const;

	virtual const QString & getPlayerListWidgetItemSplitWidth( ) const;

	virtual const QString & getPlayerListWidgetItemWidgetIndexWidth( ) const;

	virtual const QString & getPlayerListWidgetItemMusicNameWidth( ) const;

	virtual const QString & getPlayerListWidgetItemMusicSingerWidth( ) const;

	virtual const QString & getPlayerListWidgetItemMusicDurationWidth( ) const;

	virtual const QString & getPlayerListWidgetItemWidgetBeforeWidth( ) const;

	virtual const QString & getPlayerListWidgetItemWidgetAfterWidth( ) const;
};

#endif // PLAYERLISTTOPWIDGETJSONKEY_H_H_HEAD__FILE__
