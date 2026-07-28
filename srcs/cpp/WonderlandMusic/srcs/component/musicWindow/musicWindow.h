#ifndef MUSICWINDOW_H_H_HEAD__FILE__
#define MUSICWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>

#include "../../component/optionWindow/interface/optionPanel.h"

class UserMutex;
class MusicItem;
class MusicCentreWidget;

class MusicWindow : public QMainWindow, public OptionPanel {
	Q_OBJECT;
	friend class MusicItem;

private:
	UserMutex *userMutex = nullptr;
	MusicCentreWidget *musicCentreWidget = nullptr;
	std::vector< MusicItem * > musicItemVector;
	std::vector< QImage * > musicItemRenderImageVector;

public:
	MusicWindow( );

protected:
	bool deleteResource( ) override;

	virtual void unSafetyClearInfo( );
	virtual void unSafetyClearShow( );
	virtual bool updateItem( MusicItem *music_item );
	virtual bool removeItem( MusicItem *music_item );

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	QWidget * toWidget( ) override;
	virtual bool hasItem( size_t &result_index, const MusicItem *music_item ) const;
	virtual bool addItem( MusicItem *music_item );
	virtual void updateWindow( );
	virtual void updateWindow( const QRect &update_rect );
	virtual void clear( );
};

#endif // MUSICWINDOW_H_H_HEAD__FILE__
