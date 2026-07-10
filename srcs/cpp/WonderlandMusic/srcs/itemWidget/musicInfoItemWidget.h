#ifndef MUSICINFOITEMWIDGET_H_H_HEAD__FILE__
#define MUSICINFOITEMWIDGET_H_H_HEAD__FILE__
#include <QWidget>
#include "../interface/iAppJsonData.h"
#include "../interface/iAppRenderBuff.h"
class MusicItem;
class QMediaMetaData;

class MusicInfoItemWidget : public QWidget, public IAppJsonData, public IAppRenderBuff {
	Q_OBJECT;

protected:
	MusicItem *musicItem;
	size_t index;
	bool equFilePath;
	QString absFilePath;
	QString musicFilePath;
	QString musicName;
	QString musicSinger;
	qint64 duration;
	QString formatStringDuration;
	QString formatStringIndex;
	int widgetBeforeWidth;
	int widgetAfterWidth;
	int splitWidth;
	int indexWidth;
	int musicNameWidth;
	int musicSingerWidth;
	int musicDurationWidth;

public:
	/// @brief 设置选项的空间
	/// @param brfore 项前
	/// @param after 项后
	/// @param split 项之间
	/// @param index 编号
	/// @param name 名称
	/// @param singer 歌手
	/// @param duation 时长
	virtual void setItemWidth( int brfore, int after, int split, int index, int name, int singer, int duation );
	virtual int getWidgetBeforeWidth( ) const;
	virtual int getWidgetAfterWidth( ) const;
	virtual int getSplitWidth( ) const;
	virtual int getIndexWidth( ) const;
	virtual int getMusicNameWidth( ) const;
	virtual int getMusicSingerWidth( ) const;
	virtual int getMusicDurationWidth( ) const;

public:
	virtual MusicItem * getMusicItem( ) const;
	MusicInfoItemWidget( MusicItem *music_item );
	bool renderToBuff( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	virtual bool init( const QString &music_file_path, const QString &music_name, const QString &music_singer, qint64 duration_ms );
	virtual bool init( const QString &file_path, const QMediaMetaData &mediaMetaData );
	virtual bool isFile( const QString &comp_file ) const;
	virtual bool isFile( const MusicInfoItemWidget *comp_file ) const;

	virtual bool isFile( const MusicInfoItemWidget &comp_file ) const {
		return isFile( &comp_file );
	}

	virtual const QString & getMusicFilePath( ) const;
	virtual const QString & getMusicName( ) const;
	virtual const QString & getMusicSinger( ) const;
	virtual qint64 getDuration( ) const;
	virtual const QString & getFormatStringDuration( ) const;
	virtual size_t getIndex( ) const;
	virtual void setIndex( const size_t index );
	virtual const QString & getFormatStringIndex( ) const;

protected:
	void paintEvent( QPaintEvent *event ) override;
	void enterEvent( QEnterEvent *event ) override;
	void leaveEvent( QEvent *event ) override;
	void mouseDoubleClickEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	void signal_enter_item( MusicInfoItemWidget *signal_item );
	void signal_leave_item( MusicInfoItemWidget *signal_item );
	void signal_single_click_item( MusicInfoItemWidget *signal_item );
	void signal_double_click_item( MusicInfoItemWidget *signal_item );
};
#endif // MUSICINFOITEMWIDGET_H_H_HEAD__FILE__
