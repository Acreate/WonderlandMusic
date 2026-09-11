#include "iMusicTitleWidget.h"

#include "../info/iMusicItemWidthInfo.h"

bool IMusicTitleWidget::setPosItemWidthPtrVar( const int *&result_width_var_ptr, int &result_index, int new_width ) {
	auto iMusicItemWidthInfo = getMusicItemWidthInfo( );
	if( iMusicItemWidthInfo == nullptr )
		return false;
	return iMusicItemWidthInfo->setPosItemWidthPtrVar( result_width_var_ptr, result_index, new_width );
}

IMusicTitleWidget::IMusicTitleWidget( ) {
	regClassTypeInfoRef( this );
}
IMusicTitleWidget::~IMusicTitleWidget( ) {
	
}
