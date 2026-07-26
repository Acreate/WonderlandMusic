#include "optionWindow.h"

#include "../../head/after_init_macro.h"
#include "../../head/before_init_macro.h"
#include "../../head/init_macro.h"
#include "../../head/release_macro.h"

#include "../../mutex/userMutex.h"
#include "interface/optionPanel.h"

#include "optionListDockWidget/optionListDockWidget.h"

#include "widget/optionContentsWidget.h"
#include "widget/optionListWidget.h"

void OptionWindow::removeOptionPanel( OptionPanel *option_item ) {
	size_t index;
	if( getOptionPanelIndex( index, option_item ) == false )
		return;
	mutex->lock( );
	option_item->optionWindow = nullptr;
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
	if( option_item == nullptr )
		return;
	size_t index;
	if( getOptionPanelIndex( index, option_item ) == false )
		return;
	mutex->lock( );
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
	if( option_panel->initBefore( ) == false || option_panel->init( ) == false || option_panel->initAfter( ) == false )
		return false;
	mutex->lock( );
	optionPanelVector.emplace_back( option_panel );
	optionListDockWidget->optionListWidget->addItem( option_panel->optionButton );
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
	bool result = false;
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
				break;
			}
	}
	mutex->unlock( );
	if( result )
		updateWindow( );
	return result;
}

void OptionWindow::updateWindow( ) {
	optionListDockWidget->optionListWidget->updateOptionButtonLayout( );
}
bool OptionWindow::showOptionPanel( OptionPanel *option_panel ) {
	size_t index;
	if( getOptionPanelIndex( index, option_panel ) == false || option_panel->optionWindow != this )
		return false;
	mutex->lock( );

	mutex->unlock( );
	return true;
}

bool OptionWindow::deleteResource( ) {
	if( mutex == nullptr )
		return true;
	mutex->lock( );

	Delete_Resource_App_Core_Ptr( opetionContentsWidget );
	Delete_Resource_App_Core_Ptr( optionListDockWidget );
	size_t count = optionPanelVector.size( );
	if( count ) {
		auto data = optionPanelVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 ) {
			auto optionPanel = data[ index ];
			data[ index ] = nullptr;

			delete optionPanel;
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
	opetionContentsWidget = new OptionContentsWidget( this );
	optionListDockWidget = new OptionListDockWidget( this );
	mutex = new UserMutex;
	auto parentObjectPtr = parent( );
	// 存在父窗口节点，则使用组件模式
	if( qobject_cast< QWidget * >( parentObjectPtr ) )
		setWindowFlags( Qt::WindowType::Widget );

	Before_Init_Resource_App_Core_Ptr( optionListDockWidget );
	Before_Init_Resource_App_Core_Ptr( opetionContentsWidget );

	return true;
}

bool OptionWindow::init( ) {
	Init_Resource_App_Core_Ptr( optionListDockWidget );
	Init_Resource_App_Core_Ptr( opetionContentsWidget );
	return true;
}

bool OptionWindow::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( optionListDockWidget );
	After_Init_Resource_App_Core_Ptr( opetionContentsWidget );

	return true;
}

bool OptionWindow::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}

bool OptionWindow::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
