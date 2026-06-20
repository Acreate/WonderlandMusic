#ifndef ABOUTWIDGETJSONKEY_H_H_HEAD__FILE__
#define ABOUTWIDGETJSONKEY_H_H_HEAD__FILE__
#include "iJsonKey.h"

class AboutWidgetJsonKey : public IJsonKey {
	/// @brief qt 标识
	QString qtLogoIconPath;

public:
	bool init( ) override;

	virtual const QString & getQtLogoIconPath( ) const;
};
#endif // ABOUTWIDGETJSONKEY_H_H_HEAD__FILE__
