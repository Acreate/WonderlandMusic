#include "optionWindow.h"
#include "../../mutex/userMutex.h"
#include "interface/optionPanel.h"
#include "optionItem/optionItem.h"

void OptionWindow::removeOptionPanel( OptionPanel *option_item ) {
	size_t index;
	if( getOptionPanelIndex( index, option_item ) == false )
		return;
	mutex->lock( );
	optionPanelVector.erase( optionPanelVector.begin( ) + index );
	mutex->unlock( );
	updateWindow( );
}

OptionWindow::OptionWindow( QWidget *paretn ) : QMainWindow( paretn ) {
}

OptionWindow::~OptionWindow( ) {
	deleteResource( );
}

void OptionWindow::updateOptionPanelInfo( OptionPanel *option_panel ) {
}

void OptionWindow::deleteOptionPanel( OptionPanel *option_item ) {
	size_t index;
	if( getOptionPanelIndex( index, option_item ) == false )
		return;
	mutex->lock( );
	disconnect( option_item->getOptionItem( ), &OptionItem::signal_delete_OptionPanel, this, &OptionWindow::removeOptionPanel );
	optionPanelVector.erase( optionPanelVector.begin( ) + index );
	delete option_item;
	mutex->unlock( );
	updateWindow( );
}

bool OptionWindow::addOptionPanel( OptionPanel *option_panel ) {
	if( option_panel == nullptr )
		return false;
	size_t index;
	if( getOptionPanelIndex( index, option_panel ) == true )
		return true;
	if( option_panel->initBefore( ) == true && option_panel->init( ) == true && option_panel->initAfter( ) == true )
		return false;
	mutex->lock( );
	connect( option_panel->getOptionItem( ), &OptionItem::signal_delete_OptionPanel, this, &OptionWindow::removeOptionPanel );
	optionPanelVector.emplace_back( option_panel );
	mutex->unlock( );
	updateWindow( );
	return true;
}

bool OptionWindow::getOptionPanelIndex( size_t &result_index, const OptionPanel *option_panel ) {
	mutex->lock( );
	size_t count = optionPanelVector.size( );
	if( count ) {
		auto data = optionPanelVector.data( );
		result_index = 0;
		for( ; result_index < count; result_index += 1 )
			if( data[ result_index ] == option_panel ) {
				mutex->unlock( );
				return true;
			}
	}
	mutex->unlock( );
	return false;
}

bool OptionWindow::moveOptionPanelIndex( const OptionPanel *option_panel, const size_t &target_index ) {
	mutex->lock( );
	size_t count = optionPanelVector.size( );
	if( count ) {
		auto data = optionPanelVector.data( );

		size_t index = 0;
		for( ; index < count; index += 1 )
			if( data[ index ] == option_panel ) {
				auto ptr = data[ index ];
				if( target_index > index )
					for( ; index < target_index; index += 1 )
						data[ index ] = data[ index + 1 ];
				else
					for( ; index > target_index; index -= 1 )
						data[ index ] = data[ index - 1 ];
				data[ target_index ] = ptr;
				mutex->unlock( );
				updateWindow( );
				return true;
			}
	}
	mutex->unlock( );
	return false;
}

void OptionWindow::updateWindow( ) {
}

bool OptionWindow::deleteResource( ) {
	if( mutex == nullptr )
		return true;
	mutex->lock( );
	size_t count = optionPanelVector.size( );
	if( count ) {
		auto data = optionPanelVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 ) {
			disconnect( data[ index ]->getOptionItem( ), &OptionItem::signal_delete_OptionPanel, this, &OptionWindow::removeOptionPanel );
			delete data[ index ];
		}
		optionPanelVector.clear( );
	}
	mutex->unlock( );
	Delete_Resource_App_Core_Ptr( mutex );
	updateWindow( );
	return true;
}

bool OptionWindow::initBefore( ) {
	deleteResource( );
	auto parentObjectPtr = parent( );
	// 存在父窗口节点，则使用组件模式
	if( qobject_cast< QWidget * >( parentObjectPtr ) )
		setWindowFlags( Qt::WindowType::Widget );
	return true;
}

bool OptionWindow::init( ) {
	return true;
}

bool OptionWindow::initAfter( ) {
	return true;
}

bool OptionWindow::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}

bool OptionWindow::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
