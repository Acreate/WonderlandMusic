#ifndef DELETEEXCEPTION_H_H_HEAD__FILE__
#define DELETEEXCEPTION_H_H_HEAD__FILE__
#include <QString>
#include <exception>
#include <source_location>
#include "messageString.h"
#define Delete_Ptr_Exception( this_ptr, call_ptr ) \
	if( this_ptr == call_ptr ) { \
		QString error;\
		if(AppTranslateTools::getDeleteException( [&error] ( DeleteExceptionTranslate &delete_exception_translate ) {\
			error = delete_exception_translate.getDeletePtrError( );\
		} ) == false ) error = "异常删除";\
		MessageString message;\
		message << error << " : " << call_ptr;\
		Message_Error_Out << message;\
		throw DeleteException( message );\
	}

class DeleteException : public std::exception {
	std::string error;
	std::source_location sourceLocation;

public:
	DeleteException( const QString &error, const std::source_location &source_location = std::source_location::current( ) );
	DeleteException( const std::string &error, const std::source_location &source_location = std::source_location::current( ) );
	[[nodiscard]]
	const char * what( ) const override;
	~DeleteException( ) noexcept override;
	operator MessageString( ) const;
};
#endif // DELETEEXCEPTION_H_H_HEAD__FILE__
