#include "messageString.h"

const QString & MessageString::getJion( ) const {
	return jion;
}

void MessageString::setJion( const QString &jion ) {
	this->jion = jion;
}

MessageString::~MessageString( ) {
}

MessageString::MessageString( const QStringList &message_list ) : messageList( message_list ) {
}

MessageString::MessageString( const QString &message ) {
	messageList << message;
}

MessageString::MessageString( const MessageString &message_string ) {
	operator=( message_string );
}

MessageString::operator QStringList( ) const {
	return messageList;
}

MessageString::operator QString( ) const {
	QString result;
	auto count = messageList.size( );
	if( count ) {
		count -= 1;
		decltype(count) index = 0;
		auto data = messageList.data( );
		QString jionTranslate = QObject::tr( jion.toUtf8( ).data( ) );
		for( ; index < count; index += 1 )
			result = result + QObject::tr( data[ index ].toUtf8( ).data( ) ) + jionTranslate;
		result = result + QObject::tr( data[ index ].toUtf8( ).data( ) );
	}
	return result;
}

MessageString & MessageString::operator=( const MessageString &source_obj ) {
	this->messageList = source_obj.messageList;
	this->jion = source_obj.jion;
	return *this;
}

MessageString MessageString::operator+( const MessageString &source_obj ) const {
	MessageString result( *this );
	result.messageList << source_obj.messageList;
	result.jion += source_obj.jion;
	return result;
}

MessageString & MessageString::operator+=( const MessageString &source_obj ) {
	this->messageList << source_obj.messageList;
	this->jion += source_obj.jion;
	return *this;
}

MessageString & MessageString::operator<<( const void_ptr &in_obj ) {
	constexpr size_t base = sizeof( void_ptr ) * 2;
	this->messageList << QString( "0x%1" ).arg( ( qulonglong ) in_obj, 16, base, '0' ).toUpper( );
	return *this;
}

MessageString & MessageString::operator<<( const uint8_t &in_obj ) {
	this->messageList << QString::number( in_obj );
	return *this;
}

MessageString & MessageString::operator<<( const uint16_t &in_obj ) {
	this->messageList << QString::number( in_obj );
	return *this;
}

MessageString & MessageString::operator<<( const uint32_t &in_obj ) {
	this->messageList << QString::number( in_obj );
	return *this;
}

MessageString & MessageString::operator<<( const uint64_t &in_obj ) {
	this->messageList << QString::number( in_obj );
	return *this;
}

MessageString & MessageString::operator<<( const int8_t &in_obj ) {
	this->messageList << QString::number( in_obj );
	return *this;
}

MessageString & MessageString::operator<<( const int16_t &in_obj ) {
	this->messageList << QString::number( in_obj );
	return *this;
}

MessageString & MessageString::operator<<( const int32_t &in_obj ) {
	this->messageList << QString::number( in_obj );
	return *this;
}

MessageString & MessageString::operator<<( const int64_t &in_obj ) {
	this->messageList << QString::number( in_obj );
	return *this;
}

MessageString & MessageString::operator<<( const char *&in_obj ) {
	this->messageList << QString::fromLocal8Bit( in_obj );
	return *this;
}

MessageString & MessageString::operator<<( const wchar_t *&in_obj ) {
	this->messageList << QString::fromWCharArray( in_obj );
	return *this;
}

MessageString & MessageString::operator<<( const std::wstring &in_obj ) {
	this->messageList << QString::fromStdWString( in_obj );
	return *this;
}

MessageString & MessageString::operator<<( const std::string &in_obj ) {
	this->messageList << QString::fromStdString( in_obj );
	return *this;
}

MessageString & MessageString::operator<<( const QString &in_obj ) {
	this->messageList << in_obj;
	return *this;
}

MessageString & MessageString::operator<<( const QStringList &in_obj ) {
	this->messageList << in_obj;
	return *this;
}

MessageString & MessageString::operator>>( QString &out_obj ) {
	out_obj = operator QString( );
	return *this;
}

QString MessageString::toQString( ) const {
	return operator QString( );
}
