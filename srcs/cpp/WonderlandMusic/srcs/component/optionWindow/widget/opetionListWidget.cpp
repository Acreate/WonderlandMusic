#include "opetionListWidget.h"
#include "../../../mutex/userMutex.h"
#include "../optionButton/optionButton.h"

OpetionListWidget::OpetionListWidget( QWidget *parent ) : QWidget( parent ) {
}

OpetionListWidget::~OpetionListWidget( ) {
	deleteResource( );
}

bool OpetionListWidget::hasItem( size_t &result_index, const OptionItem *option_item ) {
	bool has = false;
	mutex->lock( );
	auto count = labelVector.size( );
	if( count ) {
		auto data = labelVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( has = data[ index ]->getBindItem( ) == option_item, has )
				break;
	}
	mutex->unlock( );
	return has;
}

void OpetionListWidget::addItem( OptionItem *option_item ) {
	size_t index;
	if( hasItem( index, option_item ) == true )
		return;
}

void OpetionListWidget::deleteItem( OptionItem *option_item ) {
}

bool OpetionListWidget::deleteResource( ) {
	if( mutex ) {
		mutex->lock( );
		auto count = labelVector.size( );
		if( count ) {
			auto data = labelVector.data( );
			size_t index = 0;
			for( ; index < count; index += 1 ) {
				disconnect( data[ index ], &OptionButton::signal_click_item, this, &OpetionListWidget::signal_click_item );
				delete data[ index ];
			}
			labelVector.clear( );
		}
		mutex->unlock( );
		Delete_Resource_App_Core_Ptr( mutex );
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
