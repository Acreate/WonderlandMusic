#ifndef MESSAGESTRING_H_H_HEAD__FILE__
#define MESSAGESTRING_H_H_HEAD__FILE__
#include <QObject>

class MessageErrorOut;
class QDebug;

namespace std {
	struct source_location;
}

class MessageString {
protected:
	QStringList messageList;
	QString jion;
	bool isTranslate = false;

protected:

public:
	using void_ptr = void *;
	using void_const_ptr = void const *;

	virtual ~MessageString( );
	MessageString( const MessageString &other );
	MessageString( );
	MessageString( const QStringList &message_list, const QString &jion );
	MessageString( const QStringList &message_list, const QString &jion, bool is_translate );
	MessageString( const std::source_location &source_location );
	MessageString( const QStringList &message_list );
	MessageString( const QString &message );
	MessageString( const QRect &message );
	MessageString( const QRectF &message );
	MessageString( const QPoint &message );
	MessageString( const QPointF &message );
	MessageString( const void_ptr &in_obj );
	MessageString( const void_const_ptr &in_obj );
	MessageString( const nullptr_t &in_obj );
	MessageString( const uint8_t &in_obj );
	MessageString( const uint16_t &in_obj );
	MessageString( const uint32_t &in_obj );
	MessageString( const uint64_t &in_obj );
	MessageString( const int8_t &in_obj );
	MessageString( const int16_t &in_obj );
	MessageString( const int32_t &in_obj );
	MessageString( const int64_t &in_obj );
	MessageString( const double &in_obj );
	MessageString( const float &in_obj );
	MessageString( const char in_obj[ ] );
	MessageString( const wchar_t in_obj[ ] );
	MessageString( const char * &in_obj );
	MessageString( const char8_t * &in_obj );
	MessageString( const char8_t *const &in_obj );
	MessageString( const wchar_t * &in_obj );
	MessageString( const std::wstring &in_obj );
	MessageString( const std::string &in_obj );

	virtual MessageString operator+( const MessageString &source_obj ) const;

	virtual MessageString & operator=( const MessageString &other );
	virtual MessageString & operator+=( const MessageString &source_obj );

	virtual MessageString & operator<<( const std::source_location &source_location );
	virtual MessageString & operator<<( const void_ptr &in_obj );
	virtual MessageString & operator<<( const void_const_ptr &in_obj );
	virtual MessageString & operator<<( const nullptr_t &in_obj );
	virtual MessageString & operator<<( const uint8_t &in_obj );
	virtual MessageString & operator<<( const uint16_t &in_obj );
	virtual MessageString & operator<<( const uint32_t &in_obj );
	virtual MessageString & operator<<( const uint64_t &in_obj );
	virtual MessageString & operator<<( const int8_t &in_obj );
	virtual MessageString & operator<<( const int16_t &in_obj );
	virtual MessageString & operator<<( const int32_t &in_obj );
	virtual MessageString & operator<<( const int64_t &in_obj );
	virtual MessageString & operator<<( const double &in_obj );
	virtual MessageString & operator<<( const float &in_obj );
	virtual MessageString & operator<<( const char in_obj[ ] );
	virtual MessageString & operator<<( const wchar_t in_obj[ ] );
	virtual MessageString & operator<<( const char * &in_obj );
	virtual MessageString & operator<<( const wchar_t * &in_obj );
	virtual MessageString & operator<<( const std::wstring &in_obj );
	virtual MessageString & operator<<( const std::string &in_obj );
	virtual MessageString & operator<<( const QString &in_obj );
	virtual MessageString & operator<<( const QRect &message );
	virtual MessageString & operator<<( const QRectF &message );
	virtual MessageString & operator<<( const QPoint &message );
	virtual MessageString & operator<<( const QPointF &message );
	virtual MessageString & operator<<( const QStringList &in_obj );
	virtual MessageString & operator<<( const MessageString &in_obj );

	virtual MessageString & operator>>( QString &out_obj );
	virtual const QStringList & getMessageList( ) const;

	virtual bool isIsTranslate( ) const;

	virtual void setIsTranslate( const bool is_translate );

	virtual QString toQString( ) const;
	virtual std::string toStdString( ) const;

	virtual operator QStringList( ) const;
	virtual operator QString( ) const;

	virtual const QString & getJion( ) const;
	virtual MessageString & setJion( const QString &jion );
};

#endif // MESSAGESTRING_H_H_HEAD__FILE__
