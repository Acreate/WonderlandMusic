#ifndef PLAYERLISTTOPWIDGET_H_H_HEAD__FILE__
#define PLAYERLISTTOPWIDGET_H_H_HEAD__FILE__

#include <QWidget>

class PlayerListTopWidget : public QWidget {
protected:
	int splitWidth;
	int musicNameWidth;
	int musicSingerWidth;
	int musicDurationWidth;
	bool isDrag;
	Qt::CursorShape cursorShape;

public:
	PlayerListTopWidget( QWidget *parent );

	virtual bool loadJsonPathInfo( );

	virtual bool writeJsonPathInfo( );

	virtual int getSplitWidth( ) const;

	virtual void setSplitWidth( const int split_width );

	virtual int getMusicNameWidth( ) const;

	virtual void setMusicNameWidth( const int music_name_width );

	virtual int getMusicSingerWidth( ) const;

	virtual void setMusicSingerWidth( const int music_singer_width );

	virtual int getMusicDurationWidth( ) const;

	virtual void setMusicDurationWidth( const int music_duration_width );

protected:
	void mouseMoveEvent( QMouseEvent *event ) override;

	void mousePressEvent( QMouseEvent *event ) override;

	void mouseReleaseEvent( QMouseEvent *event ) override;

	void paintEvent( QPaintEvent *event ) override;

	void leaveEvent( QEvent *event ) override;

public:
Q_SIGNALS:
	void changedSpliteWidth( int new_size );

	void changedMusicNameWidth( int new_size );

	void changedMusicSingerWidth( int new_size );

	void changedMusicDurationWidth( int new_size );
};

#endif // PLAYERLISTTOPWIDGET_H_H_HEAD__FILE__
