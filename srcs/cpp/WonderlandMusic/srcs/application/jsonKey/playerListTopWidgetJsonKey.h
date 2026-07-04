#ifndef PLAYERLISTTOPWIDGETJSONKEY_H_H_HEAD__FILE__
#define PLAYERLISTTOPWIDGETJSONKEY_H_H_HEAD__FILE__

#include <interface/iJsonKey.h>

class PlayerListTopWidgetJsonKey : public IJsonKey {
	QString itemWidth;
	QString itemSplitWidth;
	QString itemIndexWidth;
	QString itemMusicNameWidth;
	QString itemMusicSingerWidth;
	QString itemMusicDurationWidth;
	QString itemWidgetBeforeWidth;
	QString itemWidgetAfterWidth;

public:
	bool init( ) override;

	virtual const QString & getItemWidth( ) const;

	virtual const QString & getItemSplitWidth( ) const;

	virtual const QString & getItemIndexWidth( ) const;

	virtual const QString & getItemMusicNameWidth( ) const;

	virtual const QString & getItemMusicSingerWidth( ) const;

	virtual const QString & getItemMusicDurationWidth( ) const;

	virtual const QString & getItemWidgetBeforeWidth( ) const;

	virtual const QString & getItemWidgetAfterWidth( ) const;
};

#endif // PLAYERLISTTOPWIDGETJSONKEY_H_H_HEAD__FILE__
