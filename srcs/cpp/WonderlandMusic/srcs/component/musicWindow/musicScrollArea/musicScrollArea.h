#ifndef MUSICSCROLLAREA_H_H_HEAD__FILE__
#define MUSICSCROLLAREA_H_H_HEAD__FILE__
#include <QScrollArea>

class MusicScrollArea : public QScrollArea {
	Q_OBJECT;

protected:

public:
	MusicScrollArea( QWidget *parent );

	~MusicScrollArea( ) override {
	}

protected:
	void mouseMoveEvent( QMouseEvent * ) override;
	void mousePressEvent( QMouseEvent * ) override;
	void mouseReleaseEvent( QMouseEvent * ) override;

	bool event( QEvent * ) override;

public:
	virtual bool containsPosInView( bool &result_is_contains_music_scroll_area, bool &result_is_contains_viewport, const QPoint &global_pos ) const;
};

#endif // MUSICSCROLLAREA_H_H_HEAD__FILE__
