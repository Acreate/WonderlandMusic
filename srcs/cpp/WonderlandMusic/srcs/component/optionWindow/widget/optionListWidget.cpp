#include "optionListWidget.h"

#include "../optionWindow.h"

#include "../../../head/release_macro.h"

#include "../../../mutex/userMutex.h"

#include "../optionButton/optionButton.h"

void OptionListWidget::resetUpdateOptionButton( const std::vector< OptionButton * > &option_buttons ) {
	mutex->lock( );
	optionButtonVector = option_buttons;
	mutex->unlock( );
}
OptionListWidget::OptionListWidget( OptionWindow *parent ) : QWidget( parent ), listParentWindow( parent ) {
	suggestWidth = 0;
	suggestHeight = 0;
}
OptionListWidget::~OptionListWidget( ) {
	deleteResource( );
}
bool OptionListWidget::hasItem( size_t &result_index, const OptionButton *option_item ) {
	bool has = false;
	mutex->lock( );
	auto count = optionButtonVector.size( );
	if( count ) {
		auto data = optionButtonVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( has = data[ index ] == option_item, has )
				break;
	}
	mutex->unlock( );
	return has;
}

void OptionListWidget::updateOptionButtonLayout( ) {
	suggestWidth = 0;
	suggestHeight = 0;
	mutex->lock( );
	auto count = optionButtonVector.size( );
	if( count ) {
		auto data = optionButtonVector.data( );
		size_t index;
		OptionButton *optionButton;
		for( index = 0; index < count; index += 1 ) {
			optionButton = data[ index ];
			if( optionButton == nullptr )
				continue;
			optionButton->adjustSize( );
			optionButton->move( 0, suggestHeight );
			int width = optionButton->width( );
			if( suggestWidth < width )
				suggestWidth = width;
			suggestHeight += optionButton->height( );
		}
	}
	mutex->unlock( );
}

int OptionListWidget::getSuggestWidth( ) const {
	return suggestWidth;
}
int OptionListWidget::getSuggestHeight( ) const {
	return suggestHeight;
}
QSize OptionListWidget::getSuggestSize( ) const {
	return QSize( suggestWidth, suggestHeight );
}

void OptionListWidget::addItem( OptionButton *option_item ) {
	size_t index;
	if( hasItem( index, option_item ) == true )
		return;
	mutex->lock( );
	optionButtonVector.emplace_back( option_item );
	mutex->unlock( );
}
void OptionListWidget::deleteItem( OptionButton *option_item ) {
	size_t index;
	if( hasItem( index, option_item ) == true )
		return;
	mutex->lock( );
	auto iterator = optionButtonVector.begin( ) + index;
	optionButtonVector.erase( iterator );
	mutex->unlock( );
}
bool OptionListWidget::deleteResource( ) {
	if( mutex ) {
		mutex->lock( );
		optionButtonVector.clear( );
		mutex->unlock( );
		Delete_Resource_App_Core_Ptr( mutex );
		suggestWidth = 0;
		suggestHeight = 0;
	}
	return true;
}
bool OptionListWidget::initBefore( ) {
	deleteResource( );
	mutex = new UserMutex;

	return true;
}
bool OptionListWidget::init( ) {
	return true;
}
bool OptionListWidget::initAfter( ) {
	return true;
}
