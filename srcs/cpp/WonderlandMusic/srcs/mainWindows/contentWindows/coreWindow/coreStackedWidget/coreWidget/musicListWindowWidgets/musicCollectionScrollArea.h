#ifndef MUSICCOLLECTIONSCROLLAREA_H_H_HEAD__FILE__
#define MUSICCOLLECTIONSCROLLAREA_H_H_HEAD__FILE__

#include <base/baseWidget/baseScrollArea.h>

class MusicCollectionWidget;
class MusicCollectionScrollArea : public BaseScrollArea {
	Q_OBJECT;
protected:
	MusicCollectionWidget *musicCollectionWidget;
public:
	MusicCollectionScrollArea( QWidget *parent );
	~MusicCollectionScrollArea( ) override;
};

#endif // MUSICCOLLECTIONSCROLLAREA_H_H_HEAD__FILE__
