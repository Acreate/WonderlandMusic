#ifndef PLAYERLISTWIDGETTRANSLATE_H_H_HEAD__FILE__
#define PLAYERLISTWIDGETTRANSLATE_H_H_HEAD__FILE__
#include "iTranslate.h"

class PlayerListWidgetTranslate : public ITranslate {
	QString removeDiskFileError;
	QString removeListMusicItemError;
	QString musicTypeName;
	QString anyTypeName;
	QString loadDiskFileTitle;
	QString loadDiskDirTitle;

public:
	bool init( ) override;

public:
	virtual const QString & getRemoveDiskFileError( ) const;

	virtual const QString & getRemoveListMusicItemError( ) const;

	virtual const QString & getMusicTypeName( ) const;

	virtual const QString & getAnyTypeName( ) const;

	virtual const QString & getLoadDiskFileTitle( ) const;

	virtual const QString & getLoadDiskDirTitle( ) const;
};

#endif // PLAYERLISTWIDGETTRANSLATE_H_H_HEAD__FILE__
