#ifndef MAINWINDOWJSONKEY_H_H_HEAD__FILE__
#define MAINWINDOWJSONKEY_H_H_HEAD__FILE__

#include <interface/iJsonKey.h>

class MainWindowJsonKey : public IJsonKey {
	QString objectName;
	QString pointXPos;
	QString pointYPos;
	QString sizeWidth;
	QString sizeHeight;

public:
	bool init( ) override;

public:
	virtual const QString & getPointXPos( ) const;

	virtual const QString & getPointYPos( ) const;

	virtual const QString & getSizeWidth( ) const;

	virtual const QString & getSizeHeight( ) const;

	virtual const QString & getObjectName( ) const;
};

namespace AppJsonKeyTools {
	Declaration_Get_JsonKey( MainWindow );
}
#endif // MAINWINDOWJSONKEY_H_H_HEAD__FILE__
