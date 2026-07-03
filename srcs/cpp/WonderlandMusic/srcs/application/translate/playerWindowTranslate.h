#ifndef PLAYERWINDOWTRANSLATE_H_H_HEAD__FILE__
#define PLAYERWINDOWTRANSLATE_H_H_HEAD__FILE__

#include <interface/iTranslate.h>

class PlayerWindowTranslate : public ITranslate {
	QString loadDiskFileTitle;
	QString loadDiskDirTitle;
	QString musicTypeName;
	QString anyTypeName;

public:
	bool init( ) override;

	~PlayerWindowTranslate( ) override;

	virtual const QString & getLoadDiskFileTitle( ) const;

	virtual const QString & getLoadDiskDirTitle( ) const;

	virtual const QString & getMusicTypeName( ) const;

	virtual const QString & getAnyTypeName( ) const;
};
#endif // PLAYERWINDOWTRANSLATE_H_H_HEAD__FILE__
