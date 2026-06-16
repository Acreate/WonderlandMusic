#ifndef APPTRANSLATE_H_H_HEAD__FILE__
#define APPTRANSLATE_H_H_HEAD__FILE__
#include <qstring.h>

class AppTranslate {
protected:
	QString sourceFile;
	QString sourceFunction;
	QString sourceLine;
	QString createDirError;
	QString createFileError;
	QString openFileError;
	QString appWindowTitleName;
	QString playMusic;
	QString stopMusic;
	QString pauseMusic;
	QString playListWidget;
	QString settingWidget;
	QString aboutWidget;
protected:
	void setCodecForLocale( );
	void translateString( );
public:
	virtual ~AppTranslate( ) = default;
	AppTranslate( );
	virtual bool init( );
	virtual const QString & getSourceFile( ) const { return sourceFile; }
	virtual const QString & getSourceFunction( ) const { return sourceFunction; }
	virtual const QString & getSourceLine( ) const { return sourceLine; }
	virtual const QString & getCreateDirError( ) const { return createDirError; }
	virtual const QString & getCreateFileError( ) const { return createFileError; }
	virtual const QString & getOpenFileError( ) const { return openFileError; }
	virtual const QString & getAppWindowTitleName( ) const { return appWindowTitleName; }
	virtual const QString & getPlay( ) const { return playMusic; }
	virtual const QString & getStop( ) const { return stopMusic; }
	virtual const QString & getPause( ) const { return pauseMusic; }
	virtual const QString & getPlayListWidget( ) const { return playListWidget; }
	virtual const QString & getSettingWidget( ) const { return settingWidget; }
	virtual const QString & getAboutWidget( ) const { return aboutWidget; }
};

#endif // APPTRANSLATE_H_H_HEAD__FILE__
