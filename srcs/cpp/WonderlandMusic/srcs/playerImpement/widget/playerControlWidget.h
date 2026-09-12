#ifndef PLAYERCONTROLWIDGET_H_H_HEAD__FILE__
#define PLAYERCONTROLWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include <component/playWindow/interface/widget/iPlayerControlWidget.h>

#include "../../interface/iAppResourceCore.h"

class PlayerControlWidget : public QWidget, public IPlayerControlWidget, public IAppResourceCore {
	Q_OBJECT;

protected:
	UserMutex* userMutex =nullptr;
	IPlayerWindowCentreWidget *playerWindowCentreWidget = nullptr;
	IPlayerSortOption *playerSortOption = nullptr;
	IPlayerSelectOption *playerSelectOption = nullptr;
	IPlayerbackProgressBar *playerbackProgressBar = nullptr;

public:
	PlayerControlWidget( );
	~PlayerControlWidget( ) override;
	QWidget * toWidget( ) override;
	bool setPlayerWindowCentre( IPlayerWindowCentreWidget *play_window_centre_widget ) override;
	IPlayerWindowCentreWidget * getPlayerWindowCentre( ) const override;
	bool updateLayout( ) override;
	bool player( const QString &music_file_path ) override;
	bool stop( ) override;
	bool terminate( ) override;
	bool setPlayerTime( const int64_t &player_mill_second_time ) override;
	IPlayerSortOption * getPlayerSortOption( ) const override;
	IPlayerSelectOption * getPlayerSelectOption( ) const override;
	IPlayerbackProgressBar * getPlayerbackProgressBar( ) const override;
	bool setPlayerSortOption( IPlayerSortOption *player_sort_option ) override;
	bool setPlayerSelectOption( IPlayerSelectOption *player_select_option ) override;
	bool setPlayerbackProgressBar( IPlayerbackProgressBar *playerback_progress_bar ) override;

protected:
	bool deleteResource( ) override;
	void paintEvent( QPaintEvent *event ) override;
	void mouseDoubleClickEvent( QMouseEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
};

#endif // PLAYERCONTROLWIDGET_H_H_HEAD__FILE__
