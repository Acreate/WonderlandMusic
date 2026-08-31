#ifndef MUSICTITLEWIDGET_H_H_HEAD__FILE__
#define MUSICTITLEWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include <component/musicWindow/interface/widget/iMusicTitleWidget.h>

#include <interface/iAppResourceCore.h>

class MusicTitleWidget : public QWidget, public IMusicTitleWidget, public IAppResourceCore {
	Q_OBJECT;

protected:
	MusicCentreWidget *musicCentreWidget = nullptr;
	IMusicItemWidthInfo *musicItemWidthInfo = nullptr;
	QImage *renderBuff = nullptr;
	UserMutex *userMutex = nullptr;
	const int *resuntIndexVarPtr = nullptr;
	int resultIndex;
	int orgX;
public:
	MusicTitleWidget( );
	~MusicTitleWidget( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;

protected:
	bool setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) override;
	bool deleteResource( ) override;
	void paintEvent( QPaintEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;

	QWidget * toWidget( ) override;
	MusicCentreWidget * getMusicCentreWidget( ) const override;
	bool setIMusicItemWidthInfo( IMusicItemWidthInfo *music_item_width_info ) override;
	IMusicItemWidthInfo * getIMusicItemWidthInfo( ) const override;
	bool autoLayout( ) override;
};

#endif // MUSICTITLEWIDGET_H_H_HEAD__FILE__
