#ifndef MUSICTITLEWIDGET_H_H_HEAD__FILE__
#define MUSICTITLEWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include <interface/iAppCore.h>

class UserMutex;
class MusicCentreWidget;

class MusicTitleWidget : public QWidget, public IAppCore {
	Q_OBJECT;

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
	DragItemType dragSeparator;

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
	virtual int getSuggestHeight( ) const;
	virtual int getCalculateMinWidth( ) const;

protected:
	bool deleteResource( ) override;
	void paintEvent( QPaintEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	virtual bool isDragSeparator( DragItemType &index, int x_pos ) const;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
};
#endif // MUSICTITLEWIDGET_H_H_HEAD__FILE__
