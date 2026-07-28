#ifndef MUSICCENTREWIDGET_H_H_HEAD__FILE__
#define MUSICCENTREWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include "../../../interface/iAppCore.h"

class MusicTitleWidget;
class MusicListScrollArea;
class MusicWindow;
class MusicCentreScrollArea;

class MusicCentreWidget : public QWidget, public IAppCore {
	Q_OBJECT;
	friend class MusicWindow;

private:
	MusicWindow *musicWindow;

	MusicCentreWidget( MusicWindow *parent );

protected:
	~MusicCentreWidget( ) override;
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	virtual void clearShow( );
};

#endif // MUSICCENTREWIDGET_H_H_HEAD__FILE__
