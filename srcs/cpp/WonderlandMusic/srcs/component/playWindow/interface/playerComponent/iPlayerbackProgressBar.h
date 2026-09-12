#ifndef IPLAYERBACKPROGRESSBAR_H_H_HEAD__FILE__
#define IPLAYERBACKPROGRESSBAR_H_H_HEAD__FILE__
#include "../../../../classTypeInfo/classTypeInfoVar.h"

#include "../../../../interface/iAppResourceCore.h"
class IPlayerControlWidget;

class IPlayerbackProgressBar : public IAppResourceCore, public virtual ClassTypeInfoVar {
	friend class IPlayerControlWidget;

protected:
	IPlayerbackProgressBar( );
	~IPlayerbackProgressBar( ) override;

protected:
	virtual bool setPlayerControlWidget( IPlayerControlWidget *player_control_widget ) = 0;
	virtual QWidget * toWidget( ) = 0;
	virtual bool updateLayout( ) = 0;

public:
	virtual IPlayerControlWidget * getPlayerControlWidget( ) const = 0;
	virtual bool setPlayerProgress( const qint64 &millisecond ) = 0;
	virtual qint64 getPlayerProgress( ) const = 0;
};

#endif // IPLAYERBACKPROGRESSBAR_H_H_HEAD__FILE__
