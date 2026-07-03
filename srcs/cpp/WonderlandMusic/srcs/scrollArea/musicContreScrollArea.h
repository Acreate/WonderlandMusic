#ifndef MUSICCONTRESCROLLAREA_H_H_HEAD__FILE__
#define MUSICCONTRESCROLLAREA_H_H_HEAD__FILE__
#include <QScrollArea>

#include "../interface/iAppCore.h"

class MusicContreWidget;

class MusicContreScrollArea : public QScrollArea, public IAppCore {
	Q_OBJECT;

protected:
	MusicContreWidget *musicContreWidget = nullptr;

public:
	MusicContreScrollArea( QWidget *parent );

protected:
	bool deleteResource( ) override;

public:
	bool init( ) override;
};

#endif // MUSICCONTRESCROLLAREA_H_H_HEAD__FILE__
