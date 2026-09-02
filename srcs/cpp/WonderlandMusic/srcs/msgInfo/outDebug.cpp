#include "outDebug.h"

#include <QString>
#include <QDebug>

#include "messageString.h"

#define To_WriteConsoleW_Out 1

#if To_WriteConsoleW_Out == 1
#include <windows.h>
// 核心：直接输出 UTF-16，不走 qDebug、不走本地编码
static void StdErrorConsoleOut( const QString &text ) {
	HANDLE h = GetStdHandle( STD_ERROR_HANDLE );
	if( h == INVALID_HANDLE_VALUE )
		return;
	// QString → UTF-16（直接给控制台）
	auto stdU16String = text.toStdU16String( );
	auto data = stdU16String.data( );
	WriteConsoleW( h, data, stdU16String.length( ), nullptr, nullptr );
	WriteConsoleW( h, L"\r\n", 2, nullptr, nullptr );
}
#else
static void StdErrorConsoleOut( const QString &text ) {
	qDebug( ) << text.toStdString( ).c_str( )
}
#endif
OutDebug::OutDebug( const QString &text ) : OutDebug( ) {
	string->append( text );
}
OutDebug::OutDebug( ) {
	string = new QString( "" );
}
OutDebug::~OutDebug( ) {
	StdErrorConsoleOut( *string );
	delete string;
}
OutDebug & OutDebug::operator<<( const QString &text ) {
	string->append( text );
	return *this;
}
OutDebug & OutDebug::operator<<( const MessageString &text ) {
	string->append( text.toQString( ) );
	return *this;
}
