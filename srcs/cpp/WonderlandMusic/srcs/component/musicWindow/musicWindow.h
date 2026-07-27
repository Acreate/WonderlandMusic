#ifndef MUSICWINDOW_H_H_HEAD__FILE__
#define MUSICWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>

#include "../../component/optionWindow/interface/optionPanel.h"

class MusicCentreWidget;

class MusicWindow : public QMainWindow, public OptionPanel {
	Q_OBJECT;

private:
	MusicCentreWidget *musicCentreWidget = nullptr;

public:
	MusicWindow( );

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	QWidget * toWidget( ) override;
};

#endif // MUSICWINDOW_H_H_HEAD__FILE__
