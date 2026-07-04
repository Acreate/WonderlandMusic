#ifndef PLAYERLISTTOPWIDGET_H_H_HEAD__FILE__
#define PLAYERLISTTOPWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include "../interface/iAppJsonData.h"

class PlayerListTopWidget : public QWidget, public IAppJsonData {
	Q_OBJECT;

protected:
	int widgetBeforeWidth;
	int widgetAfterWidth;
	int splitWidth;
	int indexWidth;
	int musicNameWidth;
	int musicSingerWidth;
	int musicDurationWidth;
	bool isReadyDrag;
	bool isDrag;
	Qt::CursorShape cursorShape;
	size_t dragIndex;
	int *dragBeforeWidthOrgPtr;
	int dragWidth;
	int dragBeforeX;

protected:
	virtual void updateCurrentWidgetSize( );

public:
	PlayerListTopWidget( QWidget *parent );

	~PlayerListTopWidget( ) override;

	bool getJsonData( QJsonObject &get_json_object ) const override;

	bool setJsonData( const QJsonObject &set_json_object ) override;

	virtual int getSplitWidth( ) const;

	virtual int getIndexWidth( ) const;

	virtual int getMusicNameWidth( ) const;

	virtual int getMusicSingerWidth( ) const;

	virtual int getMusicDurationWidth( ) const;

	virtual int getWidgetBeforeWidth( ) const;

	virtual int getWidgetAfterWidth( ) const;

	virtual void autoSetItemSize( );

	virtual bool getMinSize( QSize &result_min_size );

	virtual bool getMinSize( );

	virtual void emitChangedWidth( );

	virtual bool init( );

	virtual void suggestWidth( int suggest_width );

	virtual bool averageItem( );

protected:
	void mouseMoveEvent( QMouseEvent *event ) override;

	void mousePressEvent( QMouseEvent *event ) override;

	void mouseReleaseEvent( QMouseEvent *event ) override;

	void closeEvent( QCloseEvent *event ) override;

	void hideEvent( QHideEvent *event ) override;

	void paintEvent( QPaintEvent *event ) override;

	void resizeEvent( QResizeEvent *event ) override;

	void leaveEvent( QEvent *event ) override;

Q_SIGNALS:
	void signal_changed_width( int split_width, int widget_before_width, int index_width, int music_name_width, int music_singer_width, int music_duration_width, int widget_after_width );
};

#endif // PLAYERLISTTOPWIDGET_H_H_HEAD__FILE__
