#ifndef IPLAYWINDOWCHILDWDIGET_H_H_HEAD__FILE__
#define IPLAYWINDOWCHILDWDIGET_H_H_HEAD__FILE__
#include <interface/iAppCore.h>

class PlayWindow;

class IPlayWindowChildWdiget : public IAppCore {
protected:
	IPlayWindowChildWdiget( );
	~IPlayWindowChildWdiget( ) override;

public:
	virtual QWidget * toWidget( ) = 0;
	virtual bool setPlayerWindow( PlayWindow *play_window ) =0;
	virtual PlayWindow * getPlayerWindow( ) const = 0;
	virtual bool updateLayout( ) = 0;
};

#endif // IPLAYWINDOWCHILDWDIGET_H_H_HEAD__FILE__
