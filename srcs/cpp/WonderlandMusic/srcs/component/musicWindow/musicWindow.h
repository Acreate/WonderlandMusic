#ifndef MUSICWINDOW_H_H_HEAD__FILE__
#define MUSICWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>

#include "../../component/optionWindow/interface/optionPanel.h"

class MusicCentreWidget;
class UserMutex;

class MusicWindow : public QMainWindow, public OptionPanel {
	Q_OBJECT;
	friend class MusicItem;

private:
	UserMutex *userMutex = nullptr;
	MusicCentreWidget *musicCentreWidget = nullptr;

public:
	MusicWindow( );
	~MusicWindow( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	QWidget * toWidget( ) override;
	virtual MusicCentreWidget * getMusicCentreWidget( ) const;
};

#endif // MUSICWINDOW_H_H_HEAD__FILE__
