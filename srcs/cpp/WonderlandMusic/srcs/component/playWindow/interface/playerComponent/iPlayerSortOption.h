#ifndef IPLAYERSORTOPTION_H_H_HEAD__FILE__
#define IPLAYERSORTOPTION_H_H_HEAD__FILE__
#include "../../../../classTypeInfo/classTypeInfoVar.h"

#include "../../../../interface/iAppResourceCore.h"

class IPlayerControlWidget;

class IPlayerSortOption : public IAppResourceCore, public ClassTypeInfoVar {
	friend class IPlayerControlWidget;

protected:
	IPlayerSortOption( );
	~IPlayerSortOption( ) override;

protected:
	virtual bool setPlayerControlWidget( IPlayerControlWidget *player_control_widget ) = 0;
	virtual QWidget * toWidget( ) = 0;
	virtual bool updateLayout( ) = 0;

public:
	virtual IPlayerControlWidget * getPlayerControlWidget( ) const = 0;
	virtual bool sortToMusicName( ) = 0;
	virtual bool sortToMusicSinger( ) = 0;
	virtual bool sortToMusicDuration( ) = 0;
	virtual bool sortToMusicRandom( ) = 0;
};

#endif // IPLAYERSORTOPTION_H_H_HEAD__FILE__
