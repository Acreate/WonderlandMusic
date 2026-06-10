#ifndef MUSICCOLLECTIONSUBMENU_H_H_HEAD__FILE__
#define MUSICCOLLECTIONSUBMENU_H_H_HEAD__FILE__

#include <base/baseMenu/baseMenu.h>
class MusicCollectionWidget;
class MusicCollectionSubMenu : public BaseMenu {
	Q_OBJECT;
protected:
	class MenuKey {
		friend class MusicCollectionSubMenu;
		/// @brief 导入音频文件
		QString appendMusicFilePath;
		/// @brief 导入音频路径
		QString loadMusicDirPath;
		/// @brief 插入音频子集
		QString insterCollectionItem;
		/// @brief 删除当前子集
		QString removeCurrentCollectionItem;
	public:
		MenuKey( );
	} menuKey;
protected:
	QAction *appendMusicFileAction;
	QAction *loadMusicDirPathAction;
	QAction *insterCollectionItemAction;
	QAction *removeCurrentCollectionItemAction;
	MusicCollectionWidget *musicCollectionWidget;
public:
	MusicCollectionSubMenu( );
	virtual MusicCollectionWidget * getMusicCollectionWidget( ) const { return musicCollectionWidget; }
};
#include <macro/eventMacroDefine.h>
class Event_Define_Event_Info_Type_Name( MusicCollectionSubMenu ) {
public:
	enum class EventType {
		Load_Music_File_Path,
		Load_Music_Dir_Path,
		Remove_Current_Collection_Item,
		Inster_Current_Collection_Item
	};
protected:
	EventType eventType;
	MusicCollectionWidget *popMusicCollectionWidget;
public:
	virtual ~MusicCollectionSubMenuEventInfo( ) = default;
	MusicCollectionSubMenuEventInfo( const EventType event_type )
		: eventType( event_type ) { }
	MusicCollectionSubMenuEventInfo( EventType event_type, MusicCollectionWidget *pop_music_collection_widget )
		: eventType( event_type ),
		popMusicCollectionWidget( pop_music_collection_widget ) { }
	virtual EventType getEventType( ) const { return eventType; }
	virtual MusicCollectionWidget * getPopMusicCollectionWidget( ) const { return popMusicCollectionWidget; }
};
#endif // MUSICCOLLECTIONSUBMENU_H_H_HEAD__FILE__
