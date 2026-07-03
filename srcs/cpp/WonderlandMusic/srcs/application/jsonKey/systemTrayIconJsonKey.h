#ifndef SYSTEMTRAYICONJSONKEY_H_H_HEAD__FILE__
#define SYSTEMTRAYICONJSONKEY_H_H_HEAD__FILE__

#include <interface/iJsonKey.h>

class SystemTrayIconJsonKey : public IJsonKey {
	QString iconFilePath;

public:
	bool init( ) override;

	virtual const QString & getIconFilePath( ) const;
};

#endif // SYSTEMTRAYICONJSONKEY_H_H_HEAD__FILE__
