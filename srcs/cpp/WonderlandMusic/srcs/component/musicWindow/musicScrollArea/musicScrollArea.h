#ifndef MUSICSCROLLAREA_H_H_HEAD__FILE__
#define MUSICSCROLLAREA_H_H_HEAD__FILE__
#include <QScrollArea>

class MusicScrollArea : public QScrollArea {
	Q_OBJECT;

public:
	MusicScrollArea( QWidget *parent );

protected:
	bool event( QEvent * ) override;
};

#endif // MUSICSCROLLAREA_H_H_HEAD__FILE__
