#include "musicListMainWidget.h"

#include <QMediaMetaData>
#include <QMediaPlayer>
#include <QMenu>
#include <QMouseEvent>
#include <QMutex>
#include <mutex>

#include <applications/applicationEvenTrigger.h>
#include <applications/applicationInstance.h>

#include <msgInfo/messageErrorOut.h>

#include <musics/musicInfo.h>

#include <tools/pathTools.h>
#include <tools/vectorTools.h>

#include "musicCollectionWidget.h"
#include "musicListWidget.h"

#include "../mainWindows/musicListMianWindow.h"

#include "../scrollAreas/musicCollectionScrollArea.h"
MusicListMainWidget::MusicListMainWidget( QWidget *parent ) : BaseWidget( parent ) {
	loadFileOverCount = 0;
	minCollectionWidth = 10;
	isragWidgetWidth = readyDragWidgetWidth = false;
	musicInfoVectorWRMutex = new QMutex;
	musicCollectionScrollArea = new MusicCollectionScrollArea( this );
	musicListMianWindow = new MusicListMianWindow( this );
	musicListMianWindow->show( );

	auto applicationInstance = ApplicationInstance::getApplicationInstance( );
	auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
	connect( applicationEvenTrigger, &ApplicationEvenTrigger::triggerApplicationInstanceEvent, [this] ( auto, const ApplicationInstanceEventInfo &info ) {
		switch( info.getEventType( ) ) {
			case ApplicationInstanceEventInfo::EventType::Init_Music_Widget_Width :
			case ApplicationInstanceEventInfo::EventType::Update_Music_Widget_Width : {
				int newMusicWidgetWidth = info.getNewMusicWidgetWidth( );
				if( musicCollectionScrollArea->width( ) == newMusicWidgetWidth )
					return;
				setMusicCollectionWidth( newMusicWidgetWidth );
			}
			break;
			case ApplicationInstanceEventInfo::EventType::Move_Global_Mouse_Pos : {
				auto pos = mapFromGlobal( QCursor::pos( ) );
				int x = pos.x( );
				int width = musicCollectionScrollArea->width( );
				if( isragWidgetWidth ) {
					if( width == x )
						return;
					setMusicCollectionWidth( x );
				} else {
					auto applicationInstance = ApplicationInstance::getApplicationInstance( );
					auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
					int abs = std::abs( x - width );
					if( abs < 5 ) {
						// 拉伸
						readyDragWidgetWidth = true;
						MusicListMainWidgetEvent::triggerMusicListMainWidgetEvent( applicationEvenTrigger, this, MusicListMainWidgetEventInfo( MusicListMainWidgetEventInfo::EventType::Show_Draw_Mouse_ICO, musicCollectionScrollArea->width( ) ) );
					} else if( readyDragWidgetWidth == true ) {
						readyDragWidgetWidth = false;
						MusicListMainWidgetEvent::triggerMusicListMainWidgetEvent( applicationEvenTrigger, this, MusicListMainWidgetEventInfo( MusicListMainWidgetEventInfo::EventType::HIDE_Draw_Mouse_ICO, musicCollectionScrollArea->width( ) ) );
					}
				}

			}
			break;
			case ApplicationInstanceEventInfo::EventType::Press_Global_Mouse_Pos :
				if( readyDragWidgetWidth ) {
					isragWidgetWidth = true;
					auto applicationInstance = ApplicationInstance::getApplicationInstance( );
					auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
					MusicListMainWidgetEvent::triggerMusicListMainWidgetEvent( applicationEvenTrigger, this, MusicListMainWidgetEventInfo( MusicListMainWidgetEventInfo::EventType::Start_Draw_Music_Widget_Width, musicCollectionScrollArea->width( ) ) );
				}
				break;
			case ApplicationInstanceEventInfo::EventType::Release_Global_Mouse_Pos : {

				auto applicationInstance = ApplicationInstance::getApplicationInstance( );
				if( readyDragWidgetWidth ) {
					isragWidgetWidth = readyDragWidgetWidth = false;
					auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
					MusicListMainWidgetEvent::triggerMusicListMainWidgetEvent( applicationEvenTrigger, this, MusicListMainWidgetEventInfo( MusicListMainWidgetEventInfo::EventType::Over_Draw_Music_Widget_Width, musicCollectionScrollArea->width( ) ) );
				}
			}
			break;
			case ApplicationInstanceEventInfo::EventType::Init_Music_Info_Path : {
				auto object = info.getJsonObject( );
				if( serializeForJsonObject( object ) == false ) {
					Message_Error_Out << tr( "反序列化加载失败..." );
					break;
				}
				MusicListMainWidgetEvent( this, MusicListMainWidgetEventInfo( MusicListMainWidgetEventInfo::EventType::Load_Music_File_Over ) );
				//clearMusicInfoVector( );
			}
			break;
			case ApplicationInstanceEventInfo::EventType::Collection_Top_Menu_Select_Over_Music_Dir_Path :
			case ApplicationInstanceEventInfo::EventType::Collection_Top_Menu_Select_Over_Music_File_Path : {
				if( loadFileOverCount != 0 ) {
					Message_Error_Out << tr( "因列表未加载完成，跳过这次加载，请等候完成再加载..." );
					break;
				}
				loadAppSelctMusicFilePathEvent( info, nullptr );
			}
			break;
			case ApplicationInstanceEventInfo::EventType::Collection_Sub_Menu_Select_Over_Music_Dir_Path
			:
			case ApplicationInstanceEventInfo::EventType::Collection_Sub_Menu_Select_Over_Music_File_Path : {
				if( loadFileOverCount != 0 ) {
					Message_Error_Out << tr( "因列表未加载完成，跳过这次加载，请等候完成再加载..." );
					break;
				}
				loadAppSelctMusicFilePathEvent( info, musicCollectionScrollArea->getMusicCollectionWidget( )->getSelectCurrentCollectionItemWidget( ) );
			}
			break;
			case ApplicationInstanceEventInfo::EventType::Create_Music_Collection_Item : {
				auto newItemName = info.getInputString( );
				auto musicCollectionWidget = musicCollectionScrollArea->getMusicCollectionWidget( );
				if( musicCollectionWidget->appendItemWidget( newItemName ) == false ) {
					Message_Error_Out << tr( "创建" ) << "\"" << newItemName << "\"" << tr( "收藏夹失败" );
					return;
				}
			}
			break;
		}
	} );

}
MusicListMainWidget::~MusicListMainWidget( ) {

	clearMusicInfoVector( );
	delete musicInfoVectorWRMutex;
	delete musicCollectionScrollArea;
	delete musicListMianWindow;
}
int MusicListMainWidget::getMusicCollectionWidth( ) const {
	return musicCollectionScrollArea->width( );
}
void MusicListMainWidget::setMusicCollectionWidth( int new_width ) {
	if( minCollectionWidth > new_width || minCollectionWidth > ( currentWidgetWidth - new_width ) )
		return;
	musicCollectionScrollArea->setGeometry( 0, 0, new_width, currentWidgetHeight );
	musicListMianWindow->setGeometry( new_width, 0, currentWidgetWidth - new_width, currentWidgetHeight );
}
bool MusicListMainWidget::serializeToJsonObject( QJsonObject &out_json_object ) const {

	QString collectionCode = "0";
	QJsonObject jsonValue;
	if( serializeToJsonObject( collectionCode, jsonValue ) == false )
		return false;
	// 收藏夹
	out_json_object.insert( collectionCode, jsonValue );
	return true;
}
bool MusicListMainWidget::serializeForJsonObject( QJsonObject &in_json_object ) {
	QString collectionCode = "0";
	std::vector< MusicInfo * > resultMusicInfoVector;
	size_t forJsonObjectCount = serializeForJsonObject( collectionCode, in_json_object, resultMusicInfoVector );
	if( forJsonObjectCount == 0 )
		return false;

	auto insterSourceData = resultMusicInfoVector.data( );
	size_t index;
	size_t findIndex;
	QString currentFindFilePath;
	size_t insterIndex;
	MusicInfo **insterDesData;

	musicInfoVectorWRMutex->lock( ); // 数组上锁
	insterIndex = musicInfos.size( );
	musicInfos.resize( insterIndex + forJsonObjectCount );
	insterDesData = musicInfos.data( );
	for( index = 0; index < forJsonObjectCount; ++index ) {
		currentFindFilePath = insterSourceData[ index ]->getFilePath( );
		for( findIndex = 0; findIndex < insterIndex; ++findIndex )
			if( insterDesData[ findIndex ]->getFilePath( ) == currentFindFilePath )
				break;
		if( findIndex != insterIndex ) {
			delete insterSourceData[ index ];
			insterSourceData[ index ] = nullptr;
			continue;
		}
		insterDesData[ insterIndex ] = insterSourceData[ index ];
		insterIndex += 1;
		insterSourceData[ index ] = nullptr;
	}
	musicInfos.resize( insterIndex );
	musicInfoVectorWRMutex->unlock( ); // 数组解锁
	return true;
}
std::vector< const MusicInfo * > MusicListMainWidget::getMusicInfos( ) const {
	musicInfoVectorWRMutex->lock( );
	auto data = musicInfos.data( );
	size_t size = musicInfos.size( );
	size_t index = 0;

	std::vector< const MusicInfo * > result( size );
	auto des = result.data( );
	for( ; index < size; ++index )
		des[ index ] = data[ index ];
	musicInfoVectorWRMutex->unlock( );
	return result;
}
bool MusicListMainWidget::serializeToJsonObject( const QString &collection_key, QJsonObject &out_json_object ) const {
	// 目前只有 0 可序列化到 json
	if( collection_key == "0" ) {
		QMutexLocker lock( musicInfoVectorWRMutex );
		size_t count = musicInfos.size( );
		if( count == 0 )
			return false;
		auto data = musicInfos.data( );
		size_t index = 0;
		QJsonObject collectionCodeJsonValue;
		for( ; index < count; ++index ) {
			QJsonObject jsonValue;
			auto filePath = data[ index ]->getFilePath( );
			auto singer = data[ index ]->getSinger( );
			auto musicName = data[ index ]->getMusicName( );
			qint64 durationMs = data[ index ]->getDurationMs( );
			jsonValue.insert( "filePath", filePath );
			jsonValue.insert( "singer", singer );
			jsonValue.insert( "musicName", musicName );
			jsonValue.insert( "durationMs", durationMs );
			// 序列
			collectionCodeJsonValue.insert( QString::number( index ), jsonValue );
		}
		out_json_object.insert( "size", QString::number( count ) );
		out_json_object.insert( "data", collectionCodeJsonValue );
	}
	return true;
}
size_t MusicListMainWidget::serializeForJsonObject( const QString &collection_key, QJsonObject &in_json_object, std::vector< MusicInfo * > &result_music_info_vector ) {

	auto find = in_json_object.find( collection_key ); // 找到收藏夹
	auto end = in_json_object.end( );
	if( find == end )
		return false;
	auto jsonObject = find.value( ).toObject( );
	find = jsonObject.find( "size" ); // 找到收藏夹个数
	end = jsonObject.end( );
	if( find == end )
		return false;

	auto key = find.value( ).toString( );
	bool conver;
	qulonglong count = key.toULongLong( &conver );
	if( count == 0 || conver == false )
		return false;
	find = jsonObject.find( "data" ); // 找到收藏数据
	if( find == end )
		return false;
	auto oldSize = result_music_info_vector.size( );
	auto newSize = oldSize + count;
	result_music_info_vector.resize( newSize, nullptr );
	auto data = result_music_info_vector.data( );
	data += oldSize; // 偏移到新建内存
	qulonglong index;

	jsonObject = find.value( ).toObject( );
	auto musicIterator = jsonObject.begin( );
	auto musicEnd = jsonObject.end( );
	QString filePath;
	QString musicName;
	QString singer;
	qint64 durationMs;
	QJsonObject musicJsonInfo;
	QString keyString;
	QJsonObject::iterator musicInfoIterator;
	QJsonObject::iterator musicInfoEnd;
	newSize = 0;
	for( ; musicIterator != musicEnd; ++musicIterator ) {
		key = musicIterator.key( );
		index = key.toULongLong( &conver );
		if( conver == false || index > count )
			continue;
		filePath.clear( );
		musicName.clear( );
		singer.clear( );
		durationMs = 0;

		musicJsonInfo = musicIterator.value( ).toObject( );
		musicInfoIterator = musicJsonInfo.begin( );
		musicInfoEnd = musicJsonInfo.end( );

		for( ; musicInfoIterator != musicInfoEnd; ++musicInfoIterator ) {
			keyString = musicInfoIterator.key( );
			if( keyString == "filePath" )
				filePath = musicInfoIterator.value( ).toString( );
			else if( keyString == "singer" )
				singer = musicInfoIterator.value( ).toString( );
			else if( keyString == "musicName" )
				musicName = musicInfoIterator.value( ).toString( );
			else if( keyString == "durationMs" )
				durationMs = musicInfoIterator.value( ).toInteger( );
		}

		if( durationMs == 0 || filePath.isEmpty( ) || musicName.isEmpty( ) || singer.isEmpty( ) )
			continue;
		newSize += 1;
		data[ index ] = new MusicInfo( filePath, musicName, singer, durationMs );
	}
	return newSize;
}
bool MusicListMainWidget::hasMusicFileInfo( const QString &music_file_path ) const {

	musicInfoVectorWRMutex->lock( );
	size_t count = musicInfos.size( );
	bool cond = false;
	if( count != 0 ) {
		auto data = musicInfos.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ] && data[ index ]->getFilePath( ) == music_file_path ) {
				cond = true;
				break;
			}
	}
	musicInfoVectorWRMutex->unlock( );
	return cond;
}

void MusicListMainWidget::clearMusicInfoVector( ) {
	musicInfoVectorWRMutex->lock( );
	size_t count = musicInfos.size( );
	if( count == 0 ) {
		musicInfoVectorWRMutex->unlock( );
		return;
	}
	auto data = musicInfos.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] )
			delete data[ index ];
	musicInfos.clear( );
	musicInfoVectorWRMutex->unlock( );
}
void MusicListMainWidget::updateSubWidgetSize( ) {
	setMusicCollectionWidth( musicCollectionScrollArea->width( ) );
}
void MusicListMainWidget::loadAppSelctMusicFilePathEvent( const ApplicationInstanceEventInfo &info, CollectionItemWidget *collection_item_widget ) {
	QStringList allFilePath;
	if( PathTools::entryList( allFilePath, info.getInputStringList( ), true ) == false )
		return;// 没有正确的文件
	QStringList filterMusicFilePath;
	qsizetype fileCount = PathTools::filterMusicFile( filterMusicFilePath, allFilePath );
	if( fileCount == 0 )
		return; // 无法匹配支持后缀名
	allFilePath.clear( );
	qsizetype index = 0;
	auto data = filterMusicFilePath.data( );
	loadFileOverCount += fileCount;
	auto musicListWidget = musicListMianWindow->getMusicListWidget( );
	QMediaPlayer *mediaPlayer;
	for( ; index < fileCount; ++index ) {
		if( hasMusicFileInfo( data[ index ] ) )
			continue; // 存在则跳过
		if( musicListWidget->existMusicFilePath( data[ index ] ) )
			continue; // 存在则跳过
		mediaPlayer = new QMediaPlayer;
		connect( mediaPlayer, &QMediaPlayer::mediaStatusChanged, [this,mediaPlayer,collection_item_widget] ( QMediaPlayer::MediaStatus media_status ) {
			if( media_status != QMediaPlayer::LoadedMedia )
				return; // 必须标识为加载完成

			QMediaMetaData mediaMetaData = mediaPlayer->metaData( );
			auto localFile = mediaPlayer->source( ).toLocalFile( );
			if( mediaMetaData.isEmpty( ) ) {
				MessageErrorOut( ) << QObject::tr( "没有匹配音频文件信息" ) << " : " << localFile;
				return; // 加载失败
			}
			mediaPlayer->deleteLater( );
			loadFileOverCount -= 1;
			QString musicName = mediaMetaData.stringValue( QMediaMetaData::Title );
			QString albumArtistName = mediaMetaData.stringValue( QMediaMetaData::ContributingArtist );
			if( albumArtistName.isEmpty( ) )
				albumArtistName = mediaMetaData.stringValue( QMediaMetaData::AlbumArtist );
			if( albumArtistName.isEmpty( ) )
				albumArtistName = mediaMetaData.stringValue( QMediaMetaData::Author );
			qint64 duration = mediaMetaData.value( QMediaMetaData::Duration ).toLongLong( );

			musicInfoVectorWRMutex->lock( );
			size_t count = musicInfos.size( );
			auto data = musicInfos.data( );
			size_t index = 0;
			for( ; index < count; ++index )
				if( data[ index ] && data[ index ]->getFilePath( ) == localFile )
					break;
			if( index == count ) {
				MusicInfo *musicInfo = new MusicInfo( localFile, musicName, albumArtistName, duration );
				musicInfos.emplace_back( musicInfo );
			}
			musicInfoVectorWRMutex->unlock( );
			if( loadFileOverCount == 0 ) {
				MusicListMainWidgetEvent( this, MusicListMainWidgetEventInfo( MusicListMainWidgetEventInfo::EventType::Load_Music_File_Over ) );
				if( collection_item_widget == nullptr )
					musicCollectionScrollArea->getMusicCollectionWidget( )->appendItemMusicInfoList( collection_item_widget, musicInfos );
				//clearMusicInfoVector( );
			}

		} );
		mediaPlayer->setSource( QUrl::fromLocalFile( data[ index ] ) );
	}
}
void MusicListMainWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	auto *view = musicCollectionScrollArea->viewport( );
	minCollectionWidth = 10 + musicCollectionScrollArea->width( ) - view->width( );
	currentContentsRect = this->contentsRect( );
	currentWidgetWidth = currentContentsRect.width( ) - currentContentsRect.x( );
	currentWidgetHeight = currentContentsRect.height( ) - currentContentsRect.y( );
	updateSubWidgetSize( );
}
