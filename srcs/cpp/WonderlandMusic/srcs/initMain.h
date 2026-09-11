#ifndef INITMAIN_H_H_HEAD__FILE__
#define INITMAIN_H_H_HEAD__FILE__
#include "interface/iAppResourceCore.h"

class AppInstance;
class QLoggingCategory;

class MessageErrorOut;
class MessageString;
class QDateTime;

typedef void (* CategoryFilter)( QLoggingCategory * );

class InitMain : public IAppResourceCore {
private:
	static InitMain *initMainInstance;

private:
	MessageErrorOut *messageErrorOut = nullptr;
	MessageString *permit = nullptr;
	MessageString *screening = nullptr;
	CategoryFilter oldCategoryFilter = nullptr;
	QDateTime *startDateTime = nullptr;
	QDateTime *endDateTime = nullptr;
	int execCode = 0;
	int argc = 0;
	char **argv = nullptr;
	char **envp = nullptr;
	AppInstance *application = nullptr;

protected:
	void myCategoryFilter( QLoggingCategory *category );
	void initTimeInfo( );
	void satrtProcess( );
	int endProcess( int exit_code );
	bool deleteResource( ) override;

public:
	InitMain( int argc, char *argv[ ], char *envp[ ] );
	~InitMain( ) override;
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	virtual int runMain( );
	virtual int getExecCode( ) const;
};

#endif // INITMAIN_H_H_HEAD__FILE__
