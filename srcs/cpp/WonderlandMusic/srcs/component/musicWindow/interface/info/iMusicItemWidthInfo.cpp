#include "iMusicItemWidthInfo.h"
#include <qdebug.h>
#include <qpoint.h>
IMusicItemWidthInfo::IMusicItemWidthInfo( ) {
	appendTypeInfo( this );
}
bool IMusicItemWidthInfo::getPosItemWidthPtr( const int *&result_width_var_ptr, int &result_index, const QPoint &pos ) const {
	return getPosItemWidthPtr( result_width_var_ptr, result_index, pos.x( ), pos.y( ) );
}
bool IMusicItemWidthInfo::getPosItemWidthPtr( const int *&result_width_var_ptr, int &result_index, const int x, const int y ) const {
	if( y < 0 || x < 0 )
		return false;
	if( x > getCalculateMinWidth( ) || y > getSuggestHeight( ) )
		return false;
	return getPosItemWidthPtr( result_width_var_ptr, result_index, x );
}
