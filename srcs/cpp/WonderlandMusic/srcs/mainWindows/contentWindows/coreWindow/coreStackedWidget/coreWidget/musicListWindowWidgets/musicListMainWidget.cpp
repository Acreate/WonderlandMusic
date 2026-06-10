#include "musicListMainWidget.h"

#include <QJsonObject>
#include <QMediaMetaData>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QMenu>

#include "musicCollectionScrollArea.h"
#include "musicListScrollArea.h"

#include "../../../../../../applications/applicationEvenTrigger.h"
#include "../../../../../../applications/applicationInstance.h"

#include "../../../../../../msgInfo/messageErrorOut.h"

#include "../../../../../../musics/musicInfo.h"

#include "../../../../../../tools/pathTools.h"

#include "widget/musicCollectionWidget.h"
#include "widget/musicListWidget.h"
#include <QMutex>

#include "../../../../../../tools/vectorTools.h"
MusicListMainWidget::MusicListMainWidget( QWidget *parent ) : BaseWidget( parent ) {
	loadFileOverCount = 0;
	minCollectionWidth = 10;
	isragWidgetWidth = readyDragWidgetWidth = false;
	json = new QJsonObject;
	musicInfoVectorWRMutex = new QMutex;
	musicCollectionScrollArea = new MusicCollectionScrollArea( this );
	musicListScrollArea = new MusicListScrollArea( this );

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
				} else {
					auto mouseButtons = applicationInstance->mouseButtons( );
					if( mouseButtons.testFlag( Qt::RightButton ) ) {
						// todo : 发送弹出菜单信号
					}
				}
			}
			break;
			case ApplicationInstanceEventInfo::EventType::Collection_Top_Menu_Select_Over_Music_Dir_Path :
			case ApplicationInstanceEventInfo::EventType::Collection_Top_Menu_Select_Over_Music_File_Path : {
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

				std::vector< QString > over;

				for( ; index < fileCount; ++index ) {
					QMediaPlayer *mediaPlayer = new QMediaPlayer;
					connect( mediaPlayer, &QMediaPlayer::mediaStatusChanged, [this,mediaPlayer, fileCount] ( QMediaPlayer::MediaStatus media_status ) {
						if( media_status != QMediaPlayer::LoadedMedia )
							return; // 必须标识为加载完成

						QMediaMetaData mediaMetaData = mediaPlayer->metaData( );
						auto localFile = mediaPlayer->source( ).toLocalFile( );
						if( mediaMetaData.isEmpty( ) ) {
							MessageErrorOut( ) << QObject::tr( "没有匹配音频文件信息" ) << " : " << mediaPlayer->source( ).toLocalFile( );
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
						MusicInfo *musicInfo = new MusicInfo( localFile, musicName, albumArtistName, duration );
						musicInfoVectorWRMutex->lock( );
						musicInfos.emplace_back( musicInfo );
						musicInfoVectorWRMutex->unlock( );
						if( loadFileOverCount == 0 )
							MusicListMainWidgetEvent( this, MusicListMainWidgetEventInfo( MusicListMainWidgetEventInfo::EventType::Music_Load_Over ) );
					} );
					mediaPlayer->setSource( QUrl::fromLocalFile( data[ index ] ) );
					size_t findRsultIndex;
					if( VectorTools::findIndex( over, data[ index ], findRsultIndex ) == true ) {
						Message_Error_Out << "找到重复: " << data[ index ] << " ,下标=" << QString::number( findRsultIndex );
					}
					over.emplace_back( data[ index ] );
				}
			}
			break;
			case ApplicationInstanceEventInfo::EventType::Collection_Sub_Menu_Select_Over_Music_Dir_Path
			:
			case ApplicationInstanceEventInfo::EventType::Collection_Sub_Menu_Select_Over_Music_File_Path : {
				QStringList allFilePath;
				if( PathTools::entryList( allFilePath, info.getInputStringList( ), true ) == false )
					return;// 没有正确的文件
				Message_Error_Out << allFilePath;
				// todo : 追加到收藏夹
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
	delete musicListScrollArea;
}
int MusicListMainWidget::getMusicCollectionWidth( ) const {
	return musicCollectionScrollArea->width( );
}
void MusicListMainWidget::setMusicCollectionWidth( int new_width ) {
	if( minCollectionWidth > new_width || minCollectionWidth > ( currentWidgetWidth - new_width ) )
		return;
	musicCollectionScrollArea->setGeometry( 0, 0, new_width, currentWidgetHeight );
	musicListScrollArea->setGeometry( new_width, 0, currentWidgetWidth - new_width, currentWidgetHeight );
}
const QJsonObject & MusicListMainWidget::serializeToJsonObject( ) const {

	return *json;
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
		delete data[ index ];
	musicInfos.clear( );
	musicInfoVectorWRMutex->unlock( );
}
void MusicListMainWidget::updateSubWidgetSize( ) {
	setMusicCollectionWidth( musicCollectionScrollArea->width( ) );
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
