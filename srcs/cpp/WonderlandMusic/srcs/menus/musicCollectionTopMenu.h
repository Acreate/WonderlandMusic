#ifndef MUSICCOLLECTIONTOPMENU_H_H_HEAD__FILE__
#define MUSICCOLLECTIONTOPMENU_H_H_HEAD__FILE__

#include <base/baseMenu/baseMenu.h>
class MusicCollectionWidget;
class MusicCollectionTopMenu : public BaseMenu {
	Q_OBJECT;
public:
protected:
	class MenuKey {
		friend class MusicCollectionTopMenu;
		/// @brief 导入音频文件
		QString appendMusicFilePath;
		/// @brief 导入音频路径
		QString loadMusicDirPath;
		/// @brief 添加音频子集
		QString addCollectionItem;
	public:
		MenuKey( );
	} menuKey;
protected:
	QAction *appendMusicFileAction;
	QAction *loadMusicDirPathAction;
	QAction *appendMusicCollectionItemActionAction;
	MusicCollectionWidget *musicCollectionWidget;
public:
	MusicCollectionTopMenu( );
	virtual MusicCollectionWidget * getMusicCollectionWidget( ) const { return musicCollectionWidget; }
};

#include <macro/eventMacroDefine.h>
class Event_Define_Event_Info_Type_Name( MusicCollectionTopMenu ) {
public:
	enum class EventType {
		Append_Collection_Item,
		Append_Muisc_File_Path,
		Append_Muisc_Dir_Path,
	};
protected:
	EventType eventType;
	MusicCollectionWidget *musicCollectionWidget;
public:
	virtual ~MusicCollectionTopMenuEventInfo( ) = default;
	MusicCollectionTopMenuEventInfo( const EventType event_type )
		: eventType( event_type ) { }
	MusicCollectionTopMenuEventInfo( EventType event_type, MusicCollectionWidget *pop_music_collection_widget )
		: eventType( event_type ),
		musicCollectionWidget( pop_music_collection_widget ) { }
	virtual EventType getEventType( ) const { return eventType; }
	virtual MusicCollectionWidget * getMusicCollectionWidget( ) const { return musicCollectionWidget; }
};

#endif // MUSICCOLLECTIONTOPMENU_H_H_HEAD__FILE__
