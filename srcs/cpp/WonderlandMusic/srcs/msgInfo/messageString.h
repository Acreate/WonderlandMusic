#ifndef MESSAGESTRING_H_H_HEAD__FILE__
#define MESSAGESTRING_H_H_HEAD__FILE__
#include <QObject>

namespace std {
	struct source_location;
}

class MessageString {
protected:
	QStringList messageList;
	QString jion;
	bool isTranslate = false;

public:
	using void_ptr = void *;
	using void_const_ptr = void const *;

	virtual const QString & getJion( ) const;

	virtual void setJion( const QString &jion );

	virtual ~MessageString( );

	MessageString( );

	MessageString( const std::source_location &source_location );

	MessageString( const QStringList &message_list, const QString &jion );

	MessageString( const QStringList &message_list, const QString &jion, bool is_translate );

	MessageString( const QStringList &message_list );

	MessageString( const QString &message );

	MessageString( const MessageString &message_string );

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

	MessageString( const char in_obj[ ] );

	MessageString( const wchar_t in_obj[ ] );

	MessageString( const char * &in_obj );
	MessageString( const char8_t * &in_obj );
	MessageString( const char8_t  *const &in_obj );

	MessageString( const wchar_t * &in_obj );

	MessageString( const std::wstring &in_obj );

	MessageString( const std::string &in_obj );

	virtual const QStringList & getMessageList( ) const;

	virtual bool isIsTranslate( ) const;

	virtual void setIsTranslate( const bool is_translate );

	virtual operator QStringList( ) const;

	virtual operator QString( ) const;

	virtual MessageString & operator=( const MessageString &source_obj );

	virtual MessageString operator+( const MessageString &source_obj ) const;

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

	virtual MessageString & operator<<( const char in_obj[ ] );

	virtual MessageString & operator<<( const wchar_t in_obj[ ] );

	virtual MessageString & operator<<( const char * &in_obj );

	virtual MessageString & operator<<( const wchar_t * &in_obj );

	virtual MessageString & operator<<( const std::wstring &in_obj );

	virtual MessageString & operator<<( const std::string &in_obj );

	virtual MessageString & operator<<( const QString &in_obj );

	virtual MessageString & operator<<( const QStringList &in_obj );
	virtual MessageString & operator<<( const MessageString &in_obj );

	virtual MessageString & operator>>( QString &out_obj );

	virtual QString toQString( ) const;
};

#endif // MESSAGESTRING_H_H_HEAD__FILE__
