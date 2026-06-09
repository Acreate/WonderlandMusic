#ifndef MUSICLISTSCROLLAREA_H_H_HEAD__FILE__
#define MUSICLISTSCROLLAREA_H_H_HEAD__FILE__
#include <base/baseWidget/baseScrollArea.h>

class MusicListWidget;
class MusicListScrollArea : public BaseScrollArea {
	Q_OBJECT;
protected:
	MusicListWidget *musicListWidget;
public:
	MusicListScrollArea( QWidget *parent );
	virtual MusicListWidget * getMusicListWidget( ) const { return musicListWidget; }
};

#endif // MUSICLISTSCROLLAREA_H_H_HEAD__FILE__
