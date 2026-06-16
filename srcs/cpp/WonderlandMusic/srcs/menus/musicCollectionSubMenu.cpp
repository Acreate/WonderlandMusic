#include "musicCollectionSubMenu.h"

#include "../applications/applicationEvenTrigger.h"
#include "../applications/applicationInstance.h"

#include "../widgets/musicCollectionWidget.h"

MusicCollectionSubMenu::MenuKey::MenuKey( ) {
	this->appendMusicFilePath = QObject::tr( "加载音频音乐文件" );
	this->loadMusicDirPath = QObject::tr( "加载音乐文件夹" );
	this->insterCollectionItem = QObject::tr( "插入收藏夹" );
	this->removeCurrentCollectionItem = QObject::tr( "移除收藏夹" );
}
MusicCollectionSubMenu::MusicCollectionSubMenu( ) {
	this->loadMusicDirPathAction = addAction( menuKey.loadMusicDirPath );
	this->appendMusicFileAction = addAction( menuKey.appendMusicFilePath );
	this->insterCollectionItemAction = addAction( menuKey.insterCollectionItem );
	this->removeCurrentCollectionItemAction = addAction( menuKey.removeCurrentCollectionItem );

	connect( this, &QMenu::triggered, [this] ( QAction *trigged_action ) {
		if( trigged_action == appendMusicFileAction ) {
			auto applicationInstance = ApplicationInstance::getApplicationInstance( );
			auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
			MusicCollectionSubMenuEvent::triggerMusicCollectionSubMenuEvent( applicationEvenTrigger, this, MusicCollectionSubMenuEventInfo( MusicCollectionSubMenuEventInfo::EventType::Load_Music_File_Path ) );
		} else if( trigged_action == loadMusicDirPathAction ) {
			auto applicationInstance = ApplicationInstance::getApplicationInstance( );
			auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
			MusicCollectionSubMenuEvent::triggerMusicCollectionSubMenuEvent( applicationEvenTrigger, this, MusicCollectionSubMenuEventInfo( MusicCollectionSubMenuEventInfo::EventType::Load_Music_Dir_Path ) );
		} else if( trigged_action == insterCollectionItemAction ) {
			auto applicationInstance = ApplicationInstance::getApplicationInstance( );
			auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
			MusicCollectionSubMenuEvent::triggerMusicCollectionSubMenuEvent( applicationEvenTrigger, this, MusicCollectionSubMenuEventInfo( MusicCollectionSubMenuEventInfo::EventType::Inster_Current_Collection_Item ) );
		} else if( trigged_action == removeCurrentCollectionItemAction ) {
			auto applicationInstance = ApplicationInstance::getApplicationInstance( );
			auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
			MusicCollectionSubMenuEvent::triggerMusicCollectionSubMenuEvent( applicationEvenTrigger, this, MusicCollectionSubMenuEventInfo( MusicCollectionSubMenuEventInfo::EventType::Remove_Current_Collection_Item ) );
		}
	} );
	auto instance = ApplicationInstance::getApplicationInstance( );
	auto evenTrigger = instance->getApplicationEvenTrigger( );
	connect( evenTrigger, &ApplicationEvenTrigger::triggerApplicationInstanceEvent, [this] ( ApplicationInstance *sender, const ApplicationInstanceEventInfo &info ) {
		auto eventType = info.getEventType( );
		switch( eventType ) {
			case ApplicationInstanceEventInfo::EventType::Pop_Music_Collection_Sub_Menu : {
				auto supervisorObject = info.getSupervisorObject( );
				auto collectionWidget = qobject_cast< decltype(musicCollectionWidget) >( supervisorObject );
				
				if( collectionWidget == nullptr )
					return;
				this->musicCollectionWidget = collectionWidget;
				popup( QCursor::pos( ) );
			}

			break;
		}
	} );
}
