#ifndef MESSAGEERROROUT_H_H_HEAD__FILE__
#define MESSAGEERROROUT_H_H_HEAD__FILE__
#include <qstring.h>
#include <source_location>

class MessageErrorOut {
	std::vector< QString > outMsgVector;
	std::source_location location;
	QString logHomePtah;
public:
	MessageErrorOut( const QString &log_home_path = "log", const std::source_location &source_location = std::source_location::current( ) );
	MessageErrorOut & operator<<( const QString &msg );
	virtual ~MessageErrorOut( );
};

#endif // MESSAGEERROROUT_H_H_HEAD__FILE__
