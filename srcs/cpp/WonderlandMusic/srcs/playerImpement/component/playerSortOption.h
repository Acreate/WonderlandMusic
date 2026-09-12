#ifndef PLAYERSORTOPTION_H_H_HEAD__FILE__
#define PLAYERSORTOPTION_H_H_HEAD__FILE__
#include <QWidget>

#include "../../component/playWindow/interface/playerComponent/iPlayerSortOption.h"

class PlayerSortOption : public QWidget, public IPlayerSortOption {
	Q_OBJECT;

protected:
	void deleteResource( );

public:
	PlayerSortOption( );
	~PlayerSortOption( ) override;
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;

protected:
	bool setPlayerControlWidget( IPlayerControlWidget *player_control_widget ) override;
	QWidget * toWidget( ) override;
	bool updateLayout( ) override;
	void mouseDoubleClickEvent( QMouseEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;

public:
	IPlayerControlWidget * getPlayerControlWidget( ) const override;
	bool sortToMusicName( ) override;
	bool sortToMusicSinger( ) override;
	bool sortToMusicDuration( ) override;
	bool sortToMusicRandom( ) override;
};

#endif // PLAYERSORTOPTION_H_H_HEAD__FILE__
