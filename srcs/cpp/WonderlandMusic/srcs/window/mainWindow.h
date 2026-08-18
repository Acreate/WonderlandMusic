#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>
#include "../interface/iAppCore.h"
#include "../interface/iAppJsonData.h"
#include "../interface/iAppResourceCore.h"
class MusicTitleWidget;
class MusicListWidget;
class MusicFavoriteWidget;
class IMusicFavoriteWidget;
class MusicWindow;
class OptionWindow;
class JsonFileKey;
class QStackedWidget;
class PlayerListWidget;
class SettingWidget;
class AboutWidget;
class AppTranslate;
class AppInstance;

class MainWindow : public QMainWindow, public IAppCore, public IAppJsonData, public IAppResourceCore {
	Q_OBJECT;

protected:

public:
	~MainWindow( ) override;
	MainWindow( QWidget *parent, Qt::WindowFlags flags );
	MainWindow( QWidget *parent );
	MainWindow( Qt::WindowFlags flags );
	MainWindow( );
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	bool init( ) override;
	bool initBefore( ) override;
	bool initAfter( ) override;

protected:
	bool deleteResource( ) override;
	bool event( QEvent *event ) override;
};
#endif // MAINWINDOW_H_H_HEAD__FILE__
