#include "optionWindow.h"

#include "../../head/after_init_macro.h"
#include "../../head/before_init_macro.h"
#include "../../head/init_macro.h"
#include "../../head/release_macro.h"

#include "../../mutex/userMutex.h"
#include "interface/optionPanel.h"

#include "optionButton/optionButton.h"

#include "optionContentsScroll/optionContentsScroll.h"
#include "optionListDockWidget/optionListDockWidget.h"
#include "widget/optionListWidget.h"

void OptionWindow::removeOptionPanel( OptionPanel *option_panel ) {
	size_t index;
	if( getOptionPanelIndex( index, option_panel ) == false )
		return;
	OptionButton *optionButton = option_panel->optionButton;
	optionListDockWidget->optionListWidget->removeOptionButton( optionButton );
	mutex->lock( );
	option_panel->optionWindow = nullptr;
	optionButton->optionWindow = nullptr;
	optionButton->optionPanel = nullptr;
	option_panel->optionButton = nullptr;
	optionPanelVector.erase( optionPanelVector.begin( ) + index );
	mutex->unlock( );
	updateWindow( );
	delete optionButton;
	//	goto : OptionWindow::deleteOptionPanel
	//	delete option_item;
}
void OptionWindow::removeAllOptionPanel( ) {
	size_t count = optionPanelVector.size( );
	if( count == 0 )
		return;
	optionListDockWidget->optionListWidget->removeAllOptionButton( );
	mutex->lock( );
	size_t index = 0;
	auto data = optionPanelVector.data( );
	for( ; index < count; index += 1 ) {
		auto optionPanel = data[ index ];
		optionPanel->optionWindow = nullptr;
		optionPanel->optionButton->optionWindow = nullptr;
		optionPanel->optionButton->optionPanel = nullptr;
		delete optionPanel->optionButton;
		optionPanel->optionButton = nullptr;
		//	goto : OptionWindow::deleteAllOptionPanel
		//	delete optionPanel;
	}
	optionPanelVector.clear( );
	mutex->unlock( );
	updateWindow( );
}
void OptionWindow::deleteOptionPanel( OptionPanel *option_panel ) {
	size_t index;
	if( getOptionPanelIndex( index, option_panel ) == false )
		return;
	OptionButton *optionButton = option_panel->optionButton;
	optionListDockWidget->optionListWidget->removeOptionButton( optionButton );
	mutex->lock( );
	option_panel->optionWindow = nullptr;
	optionButton->optionWindow = nullptr;
	optionButton->optionPanel = nullptr;
	option_panel->optionButton = nullptr;
	optionPanelVector.erase( optionPanelVector.begin( ) + index );
	mutex->unlock( );
	updateWindow( );
	delete optionButton;
	delete option_panel;
}
void OptionWindow::deleteAllOptionPanel( ) {
	size_t count = optionPanelVector.size( );
	if( count == 0 )
		return;
	optionListDockWidget->optionListWidget->removeAllOptionButton( );
	decltype(optionPanelVector) deleteVector( count );
	mutex->lock( );
	size_t index;
	auto data = optionPanelVector.data( );
	auto deletePtr = deleteVector.data( );
	for( index = 0; index < count; index += 1 )
		deletePtr[ index ] = data[ index ];

	optionPanelVector.clear( );
	mutex->unlock( );
	updateWindow( );
	for( index = 0; index < count; index += 1 ) {
		auto optionPanel = deletePtr[ index ];
		optionPanel->optionWindow = nullptr;
		optionPanel->optionButton->optionWindow = nullptr;
		optionPanel->optionButton->optionPanel = nullptr;
		delete optionPanel->optionButton;
		delete optionPanel;
	}
}

OptionWindow::OptionWindow( QWidget *paretn ) : QMainWindow( paretn ) {
}

OptionWindow::~OptionWindow( ) {
	deleteResource( );
}

void OptionWindow::updateOptionPanelInfo( OptionPanel *option_panel ) {
}

bool OptionWindow::addOptionPanel( OptionPanel *option_panel ) {
	if( option_panel == nullptr )
		return false;
	size_t index;
	if( getOptionPanelIndex( index, option_panel ) == true )
		return true;
	// 去除老旧
	if( option_panel->optionWindow )
		option_panel->optionWindow->removeOptionPanel( option_panel );

	option_panel->optionWindow = this;

	option_panel->optionButton = new OptionButton( this );
	option_panel->optionButton->optionPanel = option_panel;
	option_panel->optionButton->optionWindow = this;

	if( option_panel->initBefore( ) == false || option_panel->init( ) == false || option_panel->initAfter( ) == false ) {
		option_panel->optionButton->optionWindow = nullptr;
		option_panel->optionButton->optionPanel = nullptr;
		delete option_panel->optionButton;
		option_panel->optionButton = nullptr;
		return false;
	}
	mutex->lock( );
	optionPanelVector.emplace_back( option_panel );
	optionListDockWidget->optionListWidget->addOptionButton( option_panel->optionButton );
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
bool OptionWindow::getOptionButtonIndex( size_t &result_index, const OptionButton *option_button ) {
	mutex->lock( );
	size_t count = optionPanelVector.size( );
	if( count ) {
		auto data = optionPanelVector.data( );
		result_index = 0;
		for( ; result_index < count; result_index += 1 )
			if( data[ result_index ]->optionButton == option_button ) {
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
	if( optionListDockWidget == nullptr )
		return;
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
bool OptionWindow::showOptionButton( OptionButton *option_button ) {
	size_t index;
	if( getOptionButtonIndex( index, option_button ) == false || option_button->optionWindow != this )
		return false;
	mutex->lock( );

	mutex->unlock( );
	return true;
}
bool OptionWindow::setOptionPanelName( OptionPanel *option_panel, const QString &name ) {
	size_t index;
	if( getOptionPanelIndex( index, option_panel ) == false || option_panel->optionWindow != this )
		return false;
	*option_panel->name = name;
	return true;
}
bool OptionWindow::setOptionPanelIcon( OptionPanel *option_panel, const QImage &icon ) {
	size_t index;
	if( getOptionPanelIndex( index, option_panel ) == false || option_panel->optionWindow != this )
		return false;
	*option_panel->icon = icon;
	return true;
}

bool OptionWindow::deleteResource( ) {
	if( mutex == nullptr )
		return true;
	deleteAllOptionPanel( );
	mutex->lock( );
	Delete_Resource_App_Core_Ptr( optionContentsScroll );
	Delete_Resource_App_Core_Ptr( optionListDockWidget );
	mutex->unlock( );
	Delete_Resource_App_Core_Ptr( mutex );
	updateWindow( );
	return true;
}

bool OptionWindow::initBefore( ) {
	deleteResource( );
	optionContentsScroll = new OptionContentsScroll( this );
	optionListDockWidget = new OptionListDockWidget( this );
	mutex = new UserMutex;
	auto parentObjectPtr = parent( );
	// 存在父窗口节点，则使用组件模式
	if( qobject_cast< QWidget * >( parentObjectPtr ) )
		setWindowFlags( Qt::WindowType::Widget );

	Before_Init_Resource_App_Core_Ptr( optionListDockWidget );
	Before_Init_Resource_App_Core_Ptr( optionContentsScroll );

	return true;
}

bool OptionWindow::init( ) {
	Init_Resource_App_Core_Ptr( optionListDockWidget );
	Init_Resource_App_Core_Ptr( optionContentsScroll );
	return true;
}

bool OptionWindow::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( optionListDockWidget );
	After_Init_Resource_App_Core_Ptr( optionContentsScroll );
	return true;
}

bool OptionWindow::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}

bool OptionWindow::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
