#ifndef MUSICLISTWINDOW_H_H_HEAD__FILE__
#define MUSICLISTWINDOW_H_H_HEAD__FILE__


#include "../../../../../baseWindow/baseMainWindow.h"

class CoreStackedWidget;
class MusicListWindow : public BaseMainWindow {
	Q_OBJECT;
protected:
	CoreStackedWidget *coreStackedWidget;
public:
	MusicListWindow( CoreStackedWidget *parent );
};
#endif // MUSICLISTWINDOW_H_H_HEAD__FILE__
