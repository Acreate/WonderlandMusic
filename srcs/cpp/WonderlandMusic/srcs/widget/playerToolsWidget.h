#ifndef PLAYERTOOLSWIDGET_H_H_HEAD__FILE__
#define PLAYERTOOLSWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include "../application/appCore.h"

class PlayerWindow;
class QPushButton;
class QProgressBar;

class PlayerToolsWidget : public QWidget, public AppCore {
	Q_OBJECT;

protected:
	PlayerWindow *playerWindow;
	/// @brief 上一曲
	QPushButton *thePreviousSong = nullptr;
	/// @brief 播放控制
	QPushButton *controlPlay = nullptr;
	/// @brief 下一曲
	QPushButton *theNextSong = nullptr;
	/// @brief 播放进度
	QProgressBar *playProgress = nullptr;
	/// @brief 播放总时长
	QLabel *playAllDateTime = nullptr;
	/// @brief 播放时间信息的间隔
	QLabel *playDateTimeSpace = nullptr;
	/// @brief 播放使用时间
	QLabel *playUseDateTime = nullptr;
	/// @brief 播放按钮
	QIcon *playIcon = nullptr;
	/// @brief 暂停按钮
	QIcon *pauseIcon = nullptr;
	/// @brief 进度条最小宽度
	int progressBarMinWidth;
	/// @brief 组件的空格
	int widgetSpace;
	/// @brief 是否控制进度条
	bool isControlPlayProgress;
	/// @brief 当前播放时间
	qint64 useDuratction;
	/// @brief 音乐总时长
	qint64 musicDuratction;

protected:
	bool deleteResource( ) override;

public:
	PlayerToolsWidget( PlayerWindow *parent );

	~PlayerToolsWidget( ) override;

	bool init( ) override;

	virtual bool compLayout( );

	virtual int getMinHeight( );

	virtual int getMinWidth( int progress_bar_width );

	virtual bool setDuratctionPlayerTime( qint64 duratction );

	virtual bool compMinSize( QSize &result_min_size, int progress_bar_width );

	virtual void suggestWidth( int suggest_width );

	virtual qint64 getUseDuratction( ) const;

	virtual qint64 getMusicDuratction( ) const;

protected:
	void resizeEvent( QResizeEvent *event ) override;

	void mouseMoveEvent( QMouseEvent *event ) override;

	void mousePressEvent( QMouseEvent *event ) override;

	void mouseReleaseEvent( QMouseEvent *event ) override;

Q_SIGNALS:
	void previousSong( );

	void changePlay( );

	void nextSong( );

	void setUseduratctionChange( qint64 new_use_duratction );
};

#endif // PLAYERTOOLSWIDGET_H_H_HEAD__FILE__
