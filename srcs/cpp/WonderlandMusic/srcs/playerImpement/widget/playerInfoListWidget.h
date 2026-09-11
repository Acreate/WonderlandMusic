#ifndef PLAYERINFOLISTWIDGET_H_H_HEAD__FILE__
#define PLAYERINFOLISTWIDGET_H_H_HEAD__FILE__
#include <component/optionWindow/optionWindow.h>

#include <component/playWindow/interface/widget/iPlayerInfoListWidget.h>

class PlayerInfoListWidget : public OptionWindow, public IPlayerInfoListWidget {
	Q_OBJECT;

protected:
	IPlayerWindowCentreWidget *playerWindowCentreWidget = nullptr;

	bool deleteResource( ) override;
	void paintEvent( QPaintEvent *event ) override;
	void mouseDoubleClickEvent( QMouseEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	bool hideOptionPanel( ) override;
	bool hideOptionPanel( OptionPanel *option_panel ) override;

public:
	bool showOptionButton( OptionButton *option_button ) override;
	bool showOptionPanel( ) override;
	bool showOptionPanel( OptionPanel *option_panel ) override;
	void updateOptionPanelInfo( OptionPanel *option_panel ) override;

	bool init( ) override;
	bool initAfter( ) override;
	bool initBefore( ) override;
	PlayerInfoListWidget( );
	QWidget * toWidget( ) override;
	IPlayerWindowCentreWidget * getPlayerWindowCentre( ) const override;
	bool setPlayerWindowCentre( IPlayerWindowCentreWidget *player_window_centre_widget ) override;
	bool updateLayout( ) override;
	~PlayerInfoListWidget( ) override;
};

#endif // PLAYERINFOLISTWIDGET_H_H_HEAD__FILE__
