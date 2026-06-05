#ifndef MUSICPLAYERBUTTONSCROLLAREA_H_H_HEAD__FILE__
#define MUSICPLAYERBUTTONSCROLLAREA_H_H_HEAD__FILE__

#include <QScrollArea>

class MusicPlayerButtonWidget;
class MusicPlayerButtonScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	MusicPlayerButtonWidget *musicPlayerButtonWidget;
public:
	MusicPlayerButtonScrollArea( QWidget *parent ) : QScrollArea( parent ) { }
};

#endif // MUSICPLAYERBUTTONSCROLLAREA_H_H_HEAD__FILE__
