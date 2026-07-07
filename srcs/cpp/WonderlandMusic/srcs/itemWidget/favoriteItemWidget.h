#ifndef FAVORITEITEMWIDGET_H_H_HEAD__FILE__
#define FAVORITEITEMWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include "../interface/iAppJsonData.h"

class MusicItem;
class QLineEdit;

class FavoriteItemWidget : public QWidget, public IAppJsonData {
	Q_OBJECT;
	friend class AppMusicManage;

protected:
	QLineEdit *lineEdit;

public:
	~FavoriteItemWidget( ) override;
	FavoriteItemWidget( );
	FavoriteItemWidget( QWidget *parent );
	virtual QString getFavoriteName( ) const;
	virtual void setFavoriteName( const QString &name );
	virtual void updateWidth( );

public:
	static bool getJsonDataVector( QJsonObject &get_json_object, const std::vector< std::pair< FavoriteItemWidget *, std::vector< MusicItem * > > > &conver_vector );
	static bool setJsonDataVector( std::vector< std::pair< FavoriteItemWidget *, std::vector< MusicItem * > > > &result_vector, const QJsonObject &set_json_object );
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;

protected:
	void mouseDoubleClickEvent( QMouseEvent *event ) override;
	void focusOutEvent( QFocusEvent *event ) override;
Q_SIGNALS:
	void signal_change_name_finished( );
};

#endif // FAVORITEITEMWIDGET_H_H_HEAD__FILE__
