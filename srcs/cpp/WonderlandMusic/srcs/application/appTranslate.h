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
	QString writeFileError;
	QString readFileError;
	
	QString appWindowTitleName;
	QString playMusic;
	QString stopMusic;
	QString pauseMusic;
	QString playListWidget;
	QString settingWidget;
	QString aboutWidget;
	/// @brief 年
	QString year;
	/// @brief 月
	QString month;
	/// @brief 日
	QString day;
	/// @brief 小时
	QString hour;
	/// @brief 分钟
	QString minute;
	/// @brief 秒
	QString second;
	/// @brief 毫秒
	QString millsecond;
	
	QString fileConverJsonDocError;
	QString notFindJsonKey;
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
	virtual const QString & getYear( ) const { return year; }
	virtual const QString & getMonth( ) const { return month; }
	virtual const QString & getDay( ) const { return day; }
	virtual const QString & getHour( ) const { return hour; }
	virtual const QString & getMinute( ) const { return minute; }
	virtual const QString & getSecond( ) const { return second; }
	virtual const QString & getMillsecond( ) const { return millsecond; }
	virtual const QString & getWriteFileError( ) const { return writeFileError; }
	virtual const QString & getReadFileError( ) const { return readFileError; }
	virtual const QString & getFileConverJsonDocError( ) const { return fileConverJsonDocError; }
	virtual const QString & getNotFindJsonKey( ) const { return notFindJsonKey; }
};

#endif // APPTRANSLATE_H_H_HEAD__FILE__
