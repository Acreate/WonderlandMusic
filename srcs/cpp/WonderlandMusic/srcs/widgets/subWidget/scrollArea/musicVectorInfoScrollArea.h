#ifndef MUSICVECTORINFOSCROLLAREA_H_H_HEAD__FILE__
#define MUSICVECTORINFOSCROLLAREA_H_H_HEAD__FILE__

#include <QScrollArea>

class MusicVectorInfoWidget;

class MusicVectorInfoScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	MusicVectorInfoWidget *musicVectorInfoWidget;
public:
	MusicVectorInfoScrollArea( QWidget *parent ) : QScrollArea( parent ) { }
};
#endif // MUSICVECTORINFOSCROLLAREA_H_H_HEAD__FILE__
