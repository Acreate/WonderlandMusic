#include "messageString.h"

#include <QDebug>
#include <QRect>
#include <source_location>

#include "../tools/sourceLocationTools.h"

const QString & MessageString::getJion( ) const {
	return jion;
}

void MessageString::setJion( const QString &jion ) {
	this->jion = jion;
}

MessageString::~MessageString( ) {
}

MessageString::MessageString( ) {
}

MessageString::MessageString( const std::source_location &source_location ) {
	QString sourceFile;
	QString sourceFun;
	QString sourceLine;
	SourceLocationTools::formatSourceFilePath( sourceFile, sourceFun, sourceLine, source_location );
	messageList << QString( "%1 : %2 : [%3]" ).arg( sourceFile ).arg( sourceFun ).arg( sourceLine );
}

MessageString & MessageString::operator<<( const std::source_location &source_location ) {
	QString sourceFile;
	QString sourceFun;
	QString sourceLine;
	SourceLocationTools::formatSourceFilePath( sourceFile, sourceFun, sourceLine, source_location );
	messageList << QString( "%1 : %2 : [%3]" ).arg( sourceFile ).arg( sourceFun ).arg( sourceLine );
	return *this;
}

MessageString::MessageString( const QStringList &message_list, const QString &jion ) : messageList( message_list ),
	jion( jion ) {
}

MessageString::MessageString( const QStringList &message_list, const QString &jion, bool is_translate ) : messageList( message_list ),
	jion( jion ),
	isTranslate( is_translate ) {
}

MessageString::MessageString( const QStringList &message_list ) : messageList( message_list ) {
}

MessageString::MessageString( const QString &message ) {
	messageList << message;
}
MessageString::MessageString( const QRect &message ) {
	messageList << ( QStringList( ) << "QRect { " <<
		QString::number( message.left( ) ) << ", "
		<< QString::number( message.right( ) ) << ", "
		<< QString::number( message.width( ) ) << ", "
		<< QString::number( message.height( ) ) << " };" ).join( "" );
}
MessageString::MessageString( const QRectF &message ) {
	messageList << ( QStringList( ) << "QRectF { " <<
		QString::number( message.left( ) ) << ", "
		<< QString::number( message.right( ) ) << ", "
		<< QString::number( message.width( ) ) << ", "
		<< QString::number( message.height( ) ) << " };" ).join( "" );
}
MessageString::MessageString( const QPoint &message ) {
	messageList << ( QStringList( ) << "QPoint { " <<
		QString::number( message.x( ) ) << ", "
		<< QString::number( message.y( ) ) << " };" ).join( "" );
}
MessageString::MessageString( const QPointF &message ) {
	messageList << ( QStringList( ) << "QPointF { " <<
		QString::number( message.x( ) ) << ", "
		<< QString::number( message.y( ) ) << " };" ).join( "" );
}
MessageString & MessageString::operator<<( const QRect &message ) {
	messageList << ( QStringList( ) << "QRect { " <<
		QString::number( message.left( ) ) << ", "
		<< QString::number( message.right( ) ) << ", "
		<< QString::number( message.width( ) ) << ", "
		<< QString::number( message.height( ) ) << " };" ).join( "" );
	return *this;
}
MessageString & MessageString::operator<<( const QRectF &message ) {
	messageList << ( QStringList( ) << "QRectF { " <<
		QString::number( message.left( ) ) << ", "
		<< QString::number( message.right( ) ) << ", "
		<< QString::number( message.width( ) ) << ", "
		<< QString::number( message.height( ) ) << " };" ).join( "" );
	return *this;
}
MessageString & MessageString::operator<<( const QPoint &message ) {
	messageList << ( QStringList( ) << "QPoint { " <<
		QString::number( message.x( ) ) << ", "
		<< QString::number( message.y( ) ) << " };" ).join( "" );
	return *this;
}
MessageString & MessageString::operator<<( const QPointF &message ) {
	messageList << ( QStringList( ) << "QPointF { " <<
		QString::number( message.x( ) ) << ", "
		<< QString::number( message.y( ) ) << " };" ).join( "" );
	return *this;
}
MessageString::MessageString( const MessageString &message_string ) {
	operator=( message_string );
}

MessageString::MessageString( const void_ptr &in_obj ) {
	constexpr size_t base = sizeof( void_ptr ) * 2;
	this->messageList << QString( "0x%1" ).arg( ( qulonglong ) in_obj, 16, base, '0' ).toUpper( );
}
MessageString::MessageString( const void_const_ptr &in_obj ) {
	constexpr size_t base = sizeof( void_ptr ) * 2;
	this->messageList << QString( "0x%1" ).arg( ( qulonglong ) in_obj, 16, base, '0' ).toUpper( );
}
MessageString::MessageString( const nullptr_t &in_obj ) {
	constexpr size_t base = sizeof( void_ptr ) * 2;
	this->messageList << QString( "0x%1" ).arg( ( qulonglong ) in_obj, 16, base, '0' ).toUpper( );
}
MessageString::MessageString( const char8_t *&in_obj ) {
	messageList << QString::fromUtf8( in_obj );
}
MessageString::MessageString( const char8_t *const &in_obj ) {
	messageList << QString::fromUtf8( in_obj );
}

MessageString::MessageString( const uint8_t &in_obj ) {
	this->messageList << QString::number( in_obj );
}

MessageString::MessageString( const uint16_t &in_obj ) {
	this->messageList << QString::number( in_obj );
}

MessageString::MessageString( const uint32_t &in_obj ) {
	this->messageList << QString::number( in_obj );
}

MessageString::MessageString( const uint64_t &in_obj ) {
	this->messageList << QString::number( in_obj );
}

MessageString::MessageString( const int8_t &in_obj ) {
	this->messageList << QString::number( in_obj );
}

MessageString::MessageString( const int16_t &in_obj ) {
	this->messageList << QString::number( in_obj );
}

MessageString::MessageString( const int32_t &in_obj ) {
	this->messageList << QString::number( in_obj );
}

MessageString::MessageString( const int64_t &in_obj ) {
	this->messageList << QString::number( in_obj );
}

MessageString::MessageString( const char in_obj[ ] ) {
	messageList << QString( in_obj );
}

MessageString::MessageString( const wchar_t in_obj[ ] ) {
	messageList << QString( in_obj );
}

MessageString::MessageString( const char *&in_obj ) {
	messageList << QString( in_obj );
}

MessageString::MessageString( const wchar_t *&in_obj ) {
	messageList << QString( in_obj );
}

MessageString::MessageString( const std::wstring &in_obj ) {
	messageList << QString( in_obj );
}

MessageString::MessageString( const std::string &in_obj ) {
	messageList << QString( in_obj.c_str( ) );
}

const QStringList & MessageString::getMessageList( ) const {
	return messageList;
}

bool MessageString::isIsTranslate( ) const {
	return isTranslate;
}

void MessageString::setIsTranslate( const bool is_translate ) {
	isTranslate = is_translate;
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
		if( isTranslate ) {
			QString jionTranslate = QObject::tr( jion.toUtf8( ).data( ) );
			for( ; index < count; index += 1 )
				result = result + QObject::tr( data[ index ].toUtf8( ).data( ) ) + jionTranslate;
			result = result + QObject::tr( data[ index ].toUtf8( ).data( ) );
		} else {
			for( ; index < count; index += 1 )
				result = result + data[ index ] + jion;
			result = result + data[ index ];
		}
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
MessageString & MessageString::operator<<( const void_const_ptr &in_obj ) {
	constexpr size_t base = sizeof( void_ptr ) * 2;
	this->messageList << QString( "0x%1" ).arg( ( qulonglong ) in_obj, 16, base, '0' ).toUpper( );
	return *this;
}
MessageString & MessageString::operator<<( const nullptr_t &in_obj ) {
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

MessageString & MessageString::operator<<( const char in_obj[ ] ) {
	this->messageList << QString::fromLocal8Bit( in_obj );
	return *this;
}

MessageString & MessageString::operator<<( const wchar_t in_obj[ ] ) {
	this->messageList << QString::fromWCharArray( in_obj );
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
MessageString & MessageString::operator<<( const MessageString &in_obj ) {
	this->messageList << in_obj.toQString( );
	return *this;
}

MessageString & MessageString::operator>>( QString &out_obj ) {
	out_obj = operator QString( );
	return *this;
}

QString MessageString::toQString( ) const {
	return operator QString( );
}
std::string MessageString::toStdString( ) const {
	return toQString( ).toStdString( );
}
QDebug & operator<<( QDebug &q_debug, const MessageString &message_string ) {
	q_debug << message_string.toQString( ).toStdString( ).c_str( );
	return q_debug;
}
