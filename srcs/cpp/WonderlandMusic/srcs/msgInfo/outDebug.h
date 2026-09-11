#ifndef OUTDEBUG_H_H_HEAD__FILE__
#define OUTDEBUG_H_H_HEAD__FILE__

class MessageString;
class QString;

class OutDebug {
	QString *string;

public:
	OutDebug( const QString &text );
	OutDebug( );
	~OutDebug( );
	OutDebug & operator <<( const QString &text );
	OutDebug & operator <<( const MessageString &text );
};
#endif // OUTDEBUG_H_H_HEAD__FILE__
