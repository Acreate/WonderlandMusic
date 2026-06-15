#ifndef MUSICLISTITEMWIDGET_H_H_HEAD__FILE__
#define MUSICLISTITEMWIDGET_H_H_HEAD__FILE__

#include <base/baseWidget/baseWidget.h>

class LabelItem;
class MusicListItemWidget : public BaseWidget {
	Q_OBJECT;
protected:
	std::vector< LabelItem * > labelItemVector;
	/// @brief 音乐文件路径
	QString filePath;
	/// @brief 音乐名称
	QString musicName;
	/// @brief 歌手
	QString singerName;
	/// @brief 时长（毫秒）
	qint64 duration_ms;
	bool activity;
	int penWdith;
	int drawX;
	int drawY;
	int drawWidth;
	int drawHeight;
	QPen *pen;
private:
	QString msToHMS( qint64 totalMs );
public:
	MusicListItemWidget( QWidget *parent, const QString &file_path, const QString &music_name, const QString &singer_name, qint64 duration_ms );
	virtual const QString & getFilePath( ) const { return filePath; }
	virtual const QString & getMusicName( ) const { return musicName; }
	virtual const QString & getSinger( ) const { return singerName; }
	virtual qint64 getDurationMs( ) const { return duration_ms; }
	virtual bool isActivity( ) const { return activity; }
	virtual void setActivity( const bool activity );
protected:
	void paintEvent( QPaintEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
};

#endif // MUSICLISTITEMWIDGET_H_H_HEAD__FILE__
