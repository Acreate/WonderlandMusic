#ifndef IPLAYERCONTROLWIDGET_H_H_HEAD__FILE__
#define IPLAYERCONTROLWIDGET_H_H_HEAD__FILE__
#include <cstdint>

#include "iPlayerWindowCentreChildWidget.h"

class IPlayerSelectOption;
class IPlayerbackProgressBar;
class IPlayerSortOption;
class QString;

class IPlayerControlWidget : public IPlayerWindowCentreChildWidget {
protected:
	virtual bool setPlayerbackProgressBar( IPlayerbackProgressBar *playerback_progress_bar, IPlayerControlWidget *player_control_widget );
	virtual bool setPlayerSortOption( IPlayerSortOption *player_sort_option, IPlayerControlWidget *player_control_widget );
	virtual bool setPlayerSelectOption( IPlayerSelectOption *player_select_option, IPlayerControlWidget *player_control_widget );

public:
	virtual bool player( const QString &music_file_path ) = 0;
	virtual bool stop( ) = 0;
	virtual bool terminate( ) = 0;
	virtual bool setPlayerTime( const int64_t &player_mill_second_time ) = 0;
	virtual IPlayerSortOption * getPlayerSortOption( ) const =0;
	virtual IPlayerSelectOption * getPlayerSelectOption( ) const =0;
	virtual IPlayerbackProgressBar * getPlayerbackProgressBar( ) const =0;
	virtual bool setPlayerSortOption( IPlayerSortOption *player_sort_option ) = 0;
	virtual bool setPlayerSelectOption( IPlayerSelectOption *player_select_option ) = 0;
	virtual bool setPlayerbackProgressBar( IPlayerbackProgressBar *playerback_progress_bar ) = 0;

protected:
	IPlayerControlWidget( );
	~IPlayerControlWidget( ) override;
};

#endif // IPLAYERCONTROLWIDGET_H_H_HEAD__FILE__
