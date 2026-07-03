#ifndef MESSAGETRANSLATE_H_H_HEAD__FILE__
#define MESSAGETRANSLATE_H_H_HEAD__FILE__

#include <interface/iTranslate.h>

class MessageTranslate : public ITranslate {
	QString sourceFile;
	QString sourceFunction;
	QString sourceLine;

	QString createDirError;
	QString createFileError;

	QString openFileError;
	QString writeFileError;
	QString readFileError;

public:
	bool init( ) override;

public:
	virtual const QString & getSourceFile( ) const;

	virtual const QString & getSourceFunction( ) const;

	virtual const QString & getSourceLine( ) const;

	virtual const QString & getCreateDirError( ) const;

	virtual const QString & getCreateFileError( ) const;

	virtual const QString & getOpenFileError( ) const;

	virtual const QString & getWriteFileError( ) const;

	virtual const QString & getReadFileError( ) const;
};

#endif // MESSAGETRANSLATE_H_H_HEAD__FILE__
