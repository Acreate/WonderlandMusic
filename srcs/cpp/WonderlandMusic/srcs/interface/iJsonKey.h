#ifndef IJSONKEY_H_H_HEAD__FILE__
#define IJSONKEY_H_H_HEAD__FILE__

#include <head/declaration_get_jsonkey.h>
#include "iAppResourceCore.h"

namespace AppJsonKeyTools {
}

class IJsonKey : public IAppResourceCore {
protected:
	QString filePath;
	bool deleteResource( ) override;
	virtual QString getNormalJsonKeyFile( const QString &json_file_last_file_path ) const;
	~IJsonKey( ) override;

public:
	bool initBefore( ) override;

	bool initAfter( ) override;
	virtual QString getFilePath( ) const;
};

#endif // IJSONKEY_H_H_HEAD__FILE__
