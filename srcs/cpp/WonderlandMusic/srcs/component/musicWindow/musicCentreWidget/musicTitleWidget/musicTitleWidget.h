#ifndef MUSICTITLEWIDGET_H_H_HEAD__FILE__
#define MUSICTITLEWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include <interface/iAppCore.h>

class UserMutex;
class MusicCentreWidget;

class MusicTitleWidget : public QWidget, public IAppCore {
	Q_OBJECT;
	friend class MusicTitleWidgetTools;

public:
	enum class DragItemType {
		None,
		Code,
		Name,
		Singer,
		Duration
	};

	Q_ENUM( DragItemType )

private:
	MusicCentreWidget *musicCentreWidget;
	int suggestHeight;
	int intervalWidth;
	int separatorWidth;
	int musicCodeWidth;
	int musicNameWidth;
	int musicSingerNameWidth;
	int musicDurationTimeWidth;
	int minItemWidth;
	int clickWidth;
	DragItemType dragSeparator;
	int dragPosX;
	int *dragTargetPtr;
	int dragTargetValue;
	bool startDrag;
	QColor fillSeparatorColor;
	const QFontMetrics *fontMetrics;
	QPainter *painter;
	const QFont *font;
	UserMutex *userMutex = nullptr;
	QPen *pen = nullptr;

	QString musicCode;
	QString musicName;
	QString musicSingeName;
	QString musicDurationTime;

public:
	MusicTitleWidget( MusicCentreWidget *music_centre_widget );
	~MusicTitleWidget( ) override;
	virtual int getCalculateMinWidth( ) const;
	virtual int getSuggestHeight( ) const;
	virtual int getIntervalWidth( ) const;
	virtual int getSeparatorWidth( ) const;
	virtual int getMusicCodeWidth( ) const;
	virtual int getMusicNameWidth( ) const;
	virtual int getMusicSingerNameWidth( ) const;
	virtual int getMusicDurationTimeWidth( ) const;
	virtual void getTitleWidthInfo( int &result_interval_width, int &result_separator_width, int &result_music_code_width, int &result_music_name_width, int &result_music_singer_name_width, int &result_music_duration_time_width ) const;

protected:
	bool deleteResource( ) override;
	void paintEvent( QPaintEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void showEvent( QShowEvent *event ) override;
	virtual bool isDragSeparator( DragItemType &index, int x_pos ) const;

	virtual void updateTitleWidthInfo( );

	virtual void setTitleWidthInfo( int interval_width, int separator_width, int music_code_width, int music_name_width, int music_singer_name_width, int music_duration_time_width );

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
};
#endif // MUSICTITLEWIDGET_H_H_HEAD__FILE__
