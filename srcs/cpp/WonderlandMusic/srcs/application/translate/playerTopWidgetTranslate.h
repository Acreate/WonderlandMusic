#ifndef PLAYERTOPWIDGETTRANSLATE_H_H_HEAD__FILE__
#define PLAYERTOPWIDGETTRANSLATE_H_H_HEAD__FILE__

#include <interface/iTranslate.h>

class PlayerTopWidgetTranslate : public ITranslate {
	QString musicIndex;
	QString musicName;
	QString musicSinger;
	QString musicDuration;

public:
	bool init( ) override;

public:
	virtual const QString & getMusicIndex( ) const;

	virtual const QString & getMusicName( ) const;

	virtual const QString & getMusicSinger( ) const;

	virtual const QString & getMusicDuration( ) const;
};

#endif // PLAYERTOPWIDGETTRANSLATE_H_H_HEAD__FILE__
