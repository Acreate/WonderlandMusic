#ifndef JSONFILEKEY_H_H_HEAD__FILE__
#define JSONFILEKEY_H_H_HEAD__FILE__
#include <QString>

class JsonFileKey {
protected:
	QString mainWindowSettingJsonPath;
	QString mainWindowPointXPos;
	QString mainWindowPointYPos;
	QString mainWindowSizeWidth;
	QString mainWindowSizeHeight;
public:
	virtual ~JsonFileKey( ) = default;
	JsonFileKey( );
	virtual bool init( );
	virtual const QString & getMainWindowSettingJsonPath( ) const { return mainWindowSettingJsonPath; }
	virtual const QString & getMainWindowPointXPos( ) const { return mainWindowPointXPos; }
	virtual const QString & getMainWindowPointYPos( ) const { return mainWindowPointYPos; }
	virtual const QString & getMainWindowSizeWidth( ) const { return mainWindowSizeWidth; }
	virtual const QString & getMainWindowSizeHeight( ) const { return mainWindowSizeHeight; }
};

#endif // JSONFILEKEY_H_H_HEAD__FILE__
