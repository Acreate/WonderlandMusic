#include "opetionListWidget.h"
#include "../../../mutex/userMutex.h"

#include "../interface/optionPanel.h"

#include "../optionButton/optionButton.h"

#include "../optionItem/optionItem.h"
OpetionListWidget::OpetionListWidget( QWidget *parent ) : QWidget( parent ) {
	suggestWidth = 0;
	suggestHeight = 0;
}
OpetionListWidget::~OpetionListWidget( ) {
	deleteResource( );
}
bool OpetionListWidget::hasItem( size_t &result_index, const OptionItem *option_item ) {
	bool has = false;
	mutex->lock( );
	auto count = optionButtonVector.size( );
	if( count ) {
		auto data = optionButtonVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( has = data[ index ]->getBindItem( ) == option_item, has )
				break;
	}
	mutex->unlock( );
	return has;
}

void OpetionListWidget::updateOptionButtonLayout( ) {
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

int OpetionListWidget::getSuggestWidth( ) const {
	return suggestWidth;
}
int OpetionListWidget::getSuggestHeight( ) const {
	return suggestHeight;
}
QSize OpetionListWidget::getSuggestSize( ) const {
	return QSize( suggestWidth, suggestHeight );
}
void OpetionListWidget::addItem( OptionItem *option_item ) {
	size_t index;
	if( hasItem( index, option_item ) == true )
		return;
	auto optionButton = new OptionButton( this, option_item );
	mutex->lock( );
	optionButtonVector.emplace_back( optionButton );
	connect( optionButton, &OptionButton::signal_click_item, this, &OpetionListWidget::signal_click_item );
	mutex->unlock( );
}
void OpetionListWidget::deleteItem( OptionItem *option_item ) {
	size_t index;
	if( hasItem( index, option_item ) == true )
		return;
	mutex->lock( );
	auto iterator = optionButtonVector.begin( ) + index;
	OptionButton *optionButton = *iterator;
	optionButtonVector.erase( iterator );
	disconnect( optionButton, &OptionButton::signal_click_item, this, &OpetionListWidget::signal_click_item );
	delete optionButton;
	mutex->unlock( );
}
bool OpetionListWidget::deleteResource( ) {
	if( mutex ) {
		mutex->lock( );
		auto count = optionButtonVector.size( );
		if( count ) {
			auto data = optionButtonVector.data( );
			size_t index = 0;
			for( ; index < count; index += 1 ) {
				disconnect( data[ index ], &OptionButton::signal_click_item, this, &OpetionListWidget::signal_click_item );
				delete data[ index ];
			}
			optionButtonVector.clear( );
		}
		mutex->unlock( );
		Delete_Resource_App_Core_Ptr( mutex );
		suggestWidth = 0;
		suggestHeight = 0;
	}
	return true;
}
bool OpetionListWidget::initBefore( ) {
	deleteResource( );
	mutex = new UserMutex;
	return true;
}
bool OpetionListWidget::init( ) {
	return true;
}
bool OpetionListWidget::initAfter( ) {
	return true;
}
