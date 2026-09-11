#ifndef PLAYERINFOLISTWIDGET_H_H_HEAD__FILE__
#define PLAYERINFOLISTWIDGET_H_H_HEAD__FILE__
#include <component/optionWindow/optionWindow.h>

#include <component/playWindow/interface/widget/iPlayerInfoListWidget.h>

class PlayerInfoListWidget : public OptionWindow, public IPlayerInfoListWidget {
	Q_OBJECT;

protected:
	IPlayerWindowCentreWidget *playerWindowCentreWidget = nullptr;

public:
	PlayerInfoListWidget( );
	QWidget * toWidget( ) override;
	IPlayerWindowCentreWidget * getPlayerWindowCentre( ) const override;
	bool setPlayerWindowCentre( IPlayerWindowCentreWidget *player_window_centre_widget ) override;
	bool updateLayout( ) override;
	~PlayerInfoListWidget( ) override;
};

#endif // PLAYERINFOLISTWIDGET_H_H_HEAD__FILE__
