#ifndef MUSICPLAYERSCROLLAREA_H_H_HEAD__FILE__
#define MUSICPLAYERSCROLLAREA_H_H_HEAD__FILE__

#include <QScrollArea>

class MusicPlayerButtonWidget;
class MusicPlayerScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	MusicPlayerButtonWidget *musicPlayerButtonWidget;
public:
	MusicPlayerScrollArea( QWidget *parent ) : QScrollArea( parent ) { }
};
#endif // MUSICPLAYERSCROLLAREA_H_H_HEAD__FILE__
