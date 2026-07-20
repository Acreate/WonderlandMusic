#ifndef MUSICWIDGET_H_H_HEAD__FILE__
#define MUSICWIDGET_H_H_HEAD__FILE__
#include "../component/favoriteWindow/favoriteWindow.h"
#include "../component/optionWindow/interface/optionPanel.h"

class MusicWidget : public FavoriteWindow, public OptionPanel {
	Q_OBJECT;

public:
	MusicWidget( OptionWindow *parent );
	~MusicWidget( ) override;
	void response( ) override;
	QWidget * toWidget( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
};
#endif // MUSICWIDGET_H_H_HEAD__FILE__
