#ifndef MUSICCONTROLDOCWIDGET_H_H_HEAD__FILE__
#define MUSICCONTROLDOCWIDGET_H_H_HEAD__FILE__
#include <QDockWidget>

#include "../interface/iAppCore.h"
#include "../interface/iAppJsonData.h"

class PlayerToolsWidget;
class PlayerWindow;

class MusicControlDocWidget : public QDockWidget, public IAppCore, public IAppJsonData {
	Q_OBJECT;

protected:
	PlayerWindow *playerWindow;

	QWidget *titleBarWidget = nullptr;
	PlayerToolsWidget *playerToolsWidget = nullptr;

public:
	MusicControlDocWidget( PlayerWindow *player_window );

	~MusicControlDocWidget( ) override;

	virtual PlayerToolsWidget * getPlayerToolsWidget( ) const;

protected:
	bool deleteResource( ) override;

public:
	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
};

#endif // MUSICCONTROLDOCWIDGET_H_H_HEAD__FILE__
