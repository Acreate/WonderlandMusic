#ifndef IPLAYERSELECTOPTION_H_H_HEAD__FILE__
#define IPLAYERSELECTOPTION_H_H_HEAD__FILE__
#include "../../../../classTypeInfo/classTypeInfoVar.h"

#include "../../../../interface/iAppResourceCore.h"

class IPlayerControlWidget;

class IPlayerSelectOption : public IAppResourceCore, public ClassTypeInfoVar {
	friend class IPlayerControlWidget;

protected:
	IPlayerSelectOption( );
	~IPlayerSelectOption( ) override;

protected:
	virtual bool setPlayerControlWidget( IPlayerControlWidget *player_control_widget ) = 0;
	virtual QWidget * toWidget( ) = 0;
	virtual bool updateLayout( ) = 0;

public:
	virtual IPlayerControlWidget * getPlayerControlWidget( ) const = 0;
	virtual bool nextTrack( ) = 0;
	virtual bool previousTrack( ) = 0;
	virtual bool nextPace( ) = 0;
	virtual bool previousPace( ) = 0;
	virtual bool player( ) = 0;
	virtual bool stop( ) = 0;
	virtual bool abort( ) = 0;
};

#endif // IPLAYERSELECTOPTION_H_H_HEAD__FILE__
