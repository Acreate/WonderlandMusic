#ifndef PLAYERLISTWIDGETTRANSLATE_H_H_HEAD__FILE__
#define PLAYERLISTWIDGETTRANSLATE_H_H_HEAD__FILE__
#include "iTranslate.h"

class PlayerListWidgetTranslate : public ITranslate{
	QString removeDiskFileError;
	QString removeListMusicItemError;
public:
	bool init( ) override;

	virtual const QString & getRemoveDiskFileError( ) const;

	virtual const QString & getRemoveListMusicItemError( ) const;
};

#endif // PLAYERLISTWIDGETTRANSLATE_H_H_HEAD__FILE__
