#ifndef ABOUTWIDGETJSONKEY_H_H_HEAD__FILE__
#define ABOUTWIDGETJSONKEY_H_H_HEAD__FILE__

#include <interface/iJsonKey.h>

class AboutWidgetJsonKey : public IJsonKey {
	/// @brief qt 标识
	QString qtLogoIconPath;

public:
	bool init( ) override;

public:
	virtual const QString & getQtLogoIconPath( ) const;
};
#endif // ABOUTWIDGETJSONKEY_H_H_HEAD__FILE__
