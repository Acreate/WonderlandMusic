#ifndef MUSICLISTMAINWIDGET_H_H_HEAD__FILE__
#define MUSICLISTMAINWIDGET_H_H_HEAD__FILE__

#include <macro/eventMacroDefine.h>
#include <base/baseWidget/baseWidget.h>

#include "../../../../../../applications/applicationInstance.h"

class MusicListMianWindow;
class CollectionItemWidget;
class MusicInfo;
class QMutex;
class MusicCollectionScrollArea;
class MusicListScrollArea;
class MusicListMainWidget : public BaseWidget {
	Q_OBJECT;
protected:
	MusicCollectionScrollArea *musicCollectionScrollArea;
	MusicListMianWindow *musicListMianWindow;
	bool readyDragWidgetWidth;
	bool isragWidgetWidth;
	QRect currentContentsRect;
	int currentWidgetWidth;
	int currentWidgetHeight;
	int minCollectionWidth;
	size_t loadFileOverCount;
	QMutex *musicInfoVectorWRMutex;
	std::vector< MusicInfo * > musicInfos;
public:
	MusicListMainWidget( QWidget *parent );
	~MusicListMainWidget( ) override;
	virtual int getMusicCollectionWidth( ) const;
	virtual void setMusicCollectionWidth( int new_width );
	virtual bool serializeToJsonObject( QJsonObject &out_json_object ) const;
	virtual bool serializeForJsonObject( QJsonObject &in_json_object );
	virtual std::vector<const MusicInfo *> getMusicInfos( ) const;
	virtual bool hasMusicFileInfo( const QString &music_file_path ) const;
protected:
	virtual bool serializeToJsonObject( const QString &collection_key, QJsonObject &out_json_object ) const;
	virtual size_t serializeForJsonObject( const QString &collection_key, QJsonObject &in_json_object, std::vector< MusicInfo * > &result_music_info_vector );
protected:
	virtual void clearMusicInfoVector( );
	virtual void updateSubWidgetSize( );
	virtual void loadAppSelctMusicFilePathEvent( const ApplicationInstanceEventInfo &info, CollectionItemWidget *collection_item_widget );
	void resizeEvent( QResizeEvent *event ) override;
};

class Event_Define_Event_Info_Type_Name( MusicListMainWidget ) {
public:
	enum class EventType {
		None,
		Show_Draw_Mouse_ICO,
		HIDE_Draw_Mouse_ICO,
		Start_Draw_Music_Widget_Width,
		Over_Draw_Music_Widget_Width,
		Load_Music_File_Over,
	};
protected:
	EventType enventType;
	int newMusicWidgetWidth;
public:
	virtual ~MusicListMainWidgetEventInfo( ) = default;
	MusicListMainWidgetEventInfo( const EventType envent_type )
		: enventType( envent_type ) { }
	MusicListMainWidgetEventInfo( const EventType envent_type, const int new_music_widget_width ) : enventType( envent_type ), newMusicWidgetWidth( new_music_widget_width ) { }
	virtual int getNewMusicWidgetWidth( ) const { return newMusicWidgetWidth; }
	virtual EventType getEventType( ) const { return enventType; }
};

#endif // MUSICLISTMAINWIDGET_H_H_HEAD__FILE__
