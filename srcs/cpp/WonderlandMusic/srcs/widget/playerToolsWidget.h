#ifndef PLAYERTOOLSWIDGET_H_H_HEAD__FILE__
#define PLAYERTOOLSWIDGET_H_H_HEAD__FILE__

#include <QWidget>

class QPushButton;
class QProgressBar;

class PlayerToolsWidget : public QWidget {
	Q_OBJECT;

protected:
	/// @brief 上一曲
	QPushButton *thePreviousSong;
	/// @brief 播放控制
	QPushButton *controlPlay;
	/// @brief 下一曲
	QPushButton *theNextSong;
	/// @brief 播放进度
	QProgressBar *playProgress;
	/// @brief 播放总时长
	QLabel *playAllDateTime;
	/// @brief 播放时间信息的间隔
	QLabel *playDateTimeSpace;
	/// @brief 播放使用时间
	QLabel *playUseDateTime;
	/// @brief 显示播放列表
	QPushButton *showCurrentPlayerList;
	/// @brief 播放按钮
	QIcon *playIcon;
	/// @brief 暂停按钮
	QIcon *pauseIcon;
	/// @brief 进度条最小宽度
	int progressBarMinWidth;
	/// @brief 组件的空格
	int widgetSpace;

public:
	PlayerToolsWidget( QWidget *parent );

	~PlayerToolsWidget( ) override;

	virtual bool init( );

	virtual bool compLayout( );

	virtual int getMinHeight( );

	virtual int getMinWidth( int progress_bar_width );

	virtual bool setCurrentPlayerTime( qint64 current );

	virtual bool setDuratctionPlayerTime( qint64 duratction );

	virtual bool compMinSize( QSize &result_min_size, int progress_bar_width );

protected:
	void resizeEvent( QResizeEvent *event ) override;

	void mouseMoveEvent( QMouseEvent *event ) override;

	void mouseReleaseEvent( QMouseEvent *event ) override;

Q_SIGNALS:
	void clickPreviousSong( );

	void clickControlPlay( );

	void clickNextSong( );

	void clickShowPlayList( );

	void duratctionProgressBarChange( int new_var );
};

#endif // PLAYERTOOLSWIDGET_H_H_HEAD__FILE__
