#include "musicCollectionTopMenu.h"

#include "../applications/applicationEvenTrigger.h"
#include "../applications/applicationInstance.h"

#include "../widgets/musicCollectionWidget.h"

MusicCollectionTopMenu::MenuKey::MenuKey( ) {
	loadMusicDirPath = QObject::tr( "加载音频目录..." );
	appendMusicFilePath = QObject::tr( "加载音频文件..." );
	this->addCollectionItem = QObject::tr( "添加收藏夹..." );
}
MusicCollectionTopMenu::MusicCollectionTopMenu( ) {
	appendMusicFileAction = addAction( menuKey.appendMusicFilePath );
	loadMusicDirPathAction = addAction( menuKey.loadMusicDirPath );
	appendMusicCollectionItemActionAction = addAction( menuKey.addCollectionItem );
	connect( this, &QMenu::triggered, [this] ( QAction *trigged_action ) {
		if( trigged_action == appendMusicFileAction ) {
			auto applicationInstance = ApplicationInstance::getApplicationInstance( );
			auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
			MusicCollectionTopMenuEvent( applicationEvenTrigger, this, MusicCollectionTopMenuEventInfo( MusicCollectionTopMenuEventInfo::EventType::Append_Muisc_File_Path ) );
		} else if( trigged_action == loadMusicDirPathAction ) {
			auto applicationInstance = ApplicationInstance::getApplicationInstance( );
			auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
			MusicCollectionTopMenuEvent( applicationEvenTrigger, this, MusicCollectionTopMenuEventInfo( MusicCollectionTopMenuEventInfo::EventType::Append_Muisc_Dir_Path ) );
		} else if( trigged_action == appendMusicCollectionItemActionAction ) {
			auto applicationInstance = ApplicationInstance::getApplicationInstance( );
			auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
			MusicCollectionTopMenuEvent( applicationEvenTrigger, this, MusicCollectionTopMenuEventInfo( MusicCollectionTopMenuEventInfo::EventType::Append_Collection_Item, this->musicCollectionWidget ) );
		}
	} );
	auto instance = ApplicationInstance::getApplicationInstance( );
	auto evenTrigger = instance->getApplicationEvenTrigger( );
	connect( evenTrigger, &ApplicationEvenTrigger::triggerApplicationInstanceEvent, [this] ( ApplicationInstance *sender, const ApplicationInstanceEventInfo &info ) {
		auto eventType = info.getEventType( );
		switch( eventType ) {
			case ApplicationInstanceEventInfo::EventType::Pop_Music_Collection_Top_Menu : {
				QObject *supervisorObject = info.getSupervisorObject( );
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
