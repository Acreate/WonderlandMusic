#include "iPlayerControlWidget.h"

#include "../playerComponent/iPlayerSelectOption.h"
#include "../playerComponent/iPlayerSortOption.h"
#include "../playerComponent/iPlayerbackProgressBar.h"

bool IPlayerControlWidget::setPlayerbackProgressBar( IPlayerbackProgressBar *playerback_progress_bar, IPlayerControlWidget *player_control_widget ) {
	return playerback_progress_bar->setPlayerControlWidget( player_control_widget );;
}
bool IPlayerControlWidget::setPlayerSortOption( IPlayerSortOption *player_sort_option, IPlayerControlWidget *player_control_widget ) {
	return player_sort_option->setPlayerControlWidget( player_control_widget );
}
bool IPlayerControlWidget::setPlayerSelectOption( IPlayerSelectOption *player_select_option, IPlayerControlWidget *player_control_widget ) {
	return player_select_option->setPlayerControlWidget( player_control_widget );
}
IPlayerControlWidget::IPlayerControlWidget( ) {
	regClassTypeInfoRef( this );
}
IPlayerControlWidget::~IPlayerControlWidget( ) {
}
