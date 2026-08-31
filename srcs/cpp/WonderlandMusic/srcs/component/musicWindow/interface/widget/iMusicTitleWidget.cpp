#include "iMusicTitleWidget.h"

#include "../info/iMusicItemWidthInfo.h"

bool IMusicTitleWidget::setPosItemWidthPtrVar( const int *&result_width_var_ptr, int &result_index, int new_width ) {
	auto iMusicItemWidthInfo = getIMusicItemWidthInfo( );
	if( iMusicItemWidthInfo == nullptr )
		return false;
	return iMusicItemWidthInfo->setPosItemWidthPtrVar( result_width_var_ptr, result_index, new_width );
}
QString IMusicTitleWidget::getTypeName( ) const {
	return typeid( *this ).name( );
}
IMusicTitleWidget::IMusicTitleWidget( ) {
	appendTypeInfo( this );
}
IMusicTitleWidget::~IMusicTitleWidget( ) {
}
