#include "playerListWidget.h"

#include <QFileDialog>
#include <QPaintEvent>
#include <QJsonObject>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QUrl>
#include <QPainter>
#include <mutex>
#include <qdialog.h>

#include "playerListTopWidget.h"

#include "../application/appDataManage.h"
#include "../application/appDrawManage.h"
#include "../application/appEventManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/jsonFileKey.h"
#include "../application/musicDecoder.h"
#include "../application/musicManage.h"
#include "../application/renderImage.h"
#include "../application/jsonKey/playerListJsonKey.h"
#include "../application/translate/playerListWidgetTranslate.h"

#include "../item/musicInfoItem.h"

#include "../itemWidget/musicInfoItemWidget.h"

#include "../menu/playerWidgetMenu.h"

#include "../msgInfo/messageErrorOut.h"

#include "../musicPlayer/musicPlayer.h"

#include "../mutex/userMutex.h"

#include "../tools/arrayTools.h"
#include "../tools/pathTools.h"
#include "../tools/vectorTools.h"
#include "../tools/widgetTools.h"

void PlayerListWidget::clearMusicInfoVector( ) {
	musicInfoMutex->lock( );
	auto count = musicInfoVector->size( );
	if( count ) {
		auto data = musicInfoVector->data( );
		decltype(count) index = 0;
		for( ; index < count; index += 1 )
			delete data[ index ];
		musicInfoVector->clear( );
	}
	musicInfoMutex->unlock( );
}

PlayerListWidget::~PlayerListWidget( ) {
	releaseResource( );
}

PlayerListWidget::PlayerListWidget( QWidget *parent ) : QWidget( parent ) {
	setMouseTracking( true );
}

void PlayerListWidget::setItemWidth( const PlayerListTopWidget *player_list_top_widget ) {
	int widgetBeforeWidth = player_list_top_widget->getWidgetBeforeWidth( );
	int splitWidth = player_list_top_widget->getSplitWidth( );
	int musicNameWidth = player_list_top_widget->getMusicNameWidth( );
	int musicSingerWidth = player_list_top_widget->getMusicSingerWidth( );
	int musicDurationWidth = player_list_top_widget->getMusicDurationWidth( );
	int widgetAfterWidth = player_list_top_widget->getWidgetAfterWidth( );
	int indexWidth = player_list_top_widget->getIndexWidth( );
	setItemWidth( widgetBeforeWidth, splitWidth, indexWidth, musicNameWidth, musicSingerWidth, musicDurationWidth, widgetAfterWidth );
}

void PlayerListWidget::setItemWidth( int widget_before_width, int splite_width, int index_width, int music_name_width, int music_singer_width, int music_duration_width, int widget_after_width ) {
	widgetBeforeWidth = widget_before_width;
	splitWidth = splite_width;
	musicNameWidth = music_name_width;
	musicSingerWidth = music_singer_width;
	musicDurationWidth = music_duration_width;
	widgetAfterWidth = widget_after_width;
	indexWidth = index_width;
	updateItemWidget( );
}

int PlayerListWidget::getSplitWidth( ) const {
	return splitWidth;
}

int PlayerListWidget::getMusicNameWidth( ) const {
	return musicNameWidth;
}

int PlayerListWidget::getMusicSingerWidth( ) const {
	return musicSingerWidth;
}

int PlayerListWidget::getMusicDurationWidth( ) const {
	return musicDurationWidth;
}

MusicInfoItemWidget * PlayerListWidget::getActiveLeftItemWidget( ) const {
	return activeLeftItemWidget;
}

MusicInfoItemWidget * PlayerListWidget::getSelectLeftItemWidget( ) const {
	return selectLeftItemWidget;
}

std::vector< MusicInfoItemWidget * > & PlayerListWidget::getSelectItemWidgetVector( std::vector< MusicInfoItemWidget * > &result_vector ) const {
	musicInfoMutex->lock( );
	result_vector = *selectItemWidgetVector;
	musicInfoMutex->unlock( );
	return result_vector;
}

bool PlayerListWidget::loadJsonPathInfo( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getAppDataManage( )->getJsonFileKey( );
	auto playerListJsonKey = jsonFileKey->getPlayerList( );
	auto fileJsonPath = playerListJsonKey->getMusicPlayerListInfoFileJsonPath( );
	QJsonObject fileJsonObject;
	if( PathTools::readJsonObject( fileJsonObject, fileJsonPath ) == false )
		return true;
	auto end = fileJsonObject.end( );
	QJsonObject::iterator find;

	find = fileJsonObject.find( playerListJsonKey->getFileSelectWorkPath( ) );
	if( find != end )
		fileSelectWorkPath = find.value( ).toString( fileSelectWorkPath );
	find = fileJsonObject.find( playerListJsonKey->getDirSelectWorkPath( ) );
	if( find != end )
		dirSelectWorkPath = find.value( ).toString( dirSelectWorkPath );

	find = fileJsonObject.find( playerListJsonKey->getMusicInfoListCount( ) );
	if( end == find )
		return true;
	auto valueRef = find.value( );
	QString error = "none";
	auto string = valueRef.toString( error );

	qulonglong count;
	if( error == string )
		count = valueRef.toInteger( 0 );
	else {
		bool conver;
		count = string.toULongLong( &conver );
		if( conver == false )
			return true;
	}
	if( count == 0 )
		return true;
	find = fileJsonObject.find( playerListJsonKey->getMusicInfoListName( ) );
	if( end == find )
		return true;

	QJsonObject subJsonObject;
	subJsonObject = find.value( ).toObject( );
	auto foreachIterator = subJsonObject.begin( );
	auto foreachEnd = subJsonObject.end( );

	std::vector< MusicInfoItemWidget * > buff( count, nullptr );
	auto maxIndex = count - 1;
	auto data = buff.data( );
	size_t validCount = 0; // 有效个数
	for( ; foreachIterator != foreachEnd; ++foreachIterator ) {
		auto indexJsonKey = foreachIterator.key( );
		bool isConverOk;
		auto converResultIndex = indexJsonKey.toULongLong( &isConverOk );
		if( isConverOk == false )
			continue;
		if( converResultIndex > maxIndex )
			continue;
		auto musicInfoJsonObject = foreachIterator.value( ).toObject( );
		auto ctreaItem = new MusicInfoItemWidget( this );
		if( MusicInfoItem::forJsonObject( *ctreaItem, musicInfoJsonObject ) == false ) {
			delete ctreaItem;
			continue;
		}
		ctreaItem->parentPlayListWidget = this;
		data[ converResultIndex ] = ctreaItem;
		validCount += 1;
	}
	musicInfoMutex->lock( );

	// 以前大小
	auto oldCount = musicInfoVector->size( );

	std::vector< MusicInfoItemWidget * > releaseVector( oldCount, nullptr );
	auto buffToData = releaseVector.data( );
	auto copyToData = musicInfoVector->data( );
	for( maxIndex = 0; maxIndex < oldCount; maxIndex += 1 )
		buffToData[ maxIndex ] = copyToData[ maxIndex ];
	// 拷贝新的目标
	musicInfoVector->resize( validCount );
	// 充当下标
	validCount = 0;
	copyToData = musicInfoVector->data( );
	for( maxIndex = 0; maxIndex < count; maxIndex += 1 )
		if( data[ maxIndex ] ) {
			copyToData[ validCount ] = data[ maxIndex ];
			validCount += 1;
		}
	selectItemWidgetVector->clear( );
	activeLeftItemWidget = nullptr;
	selectLeftItemWidget = nullptr;
	// 释放以前的目标
	for( maxIndex = 0; maxIndex < oldCount; maxIndex += 1 )
		delete buffToData[ maxIndex ];
	musicInfoMutex->unlock( );
	return true;
}

bool PlayerListWidget::writeJsonPathInfo( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getAppDataManage( )->getJsonFileKey( );

	QJsonObject fileJsonObject;
	size_t count = musicInfoVector->size( );

	auto musicPlayerListJsonKey = jsonFileKey->getPlayerList( );
	if( count ) {
		fileJsonObject.insert( musicPlayerListJsonKey->getMusicInfoListCount( ), QString::number( count ) );
		auto sourceData = musicInfoVector->data( );
		std::vector< MusicInfoItemWidget * > buff( count );
		MusicInfoItemWidget **destData = buff.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			destData[ index ] = sourceData[ index ];
		QJsonObject arrayJsonObject;

		for( index = 0; index < count; index += 1 ) {
			QJsonObject subJsonObject;
			if( MusicInfoItem::toJsonObect( subJsonObject, *destData[ index ] ) == false )
				continue;
			arrayJsonObject.insert( QString::number( index ), subJsonObject );
		}
		fileJsonObject.insert( musicPlayerListJsonKey->getMusicInfoListName( ), arrayJsonObject );
	}

	auto fileJsonPath = musicPlayerListJsonKey->getMusicPlayerListInfoFileJsonPath( );

	fileJsonObject.insert( musicPlayerListJsonKey->getFileSelectWorkPath( ), PathTools::getAutoShortenPathName( fileSelectWorkPath ) );
	fileJsonObject.insert( musicPlayerListJsonKey->getDirSelectWorkPath( ), PathTools::getAutoShortenPathName( dirSelectWorkPath ) );

	PathTools::writeJsonObject( fileJsonObject, fileJsonPath );
	return true;
}

bool PlayerListWidget::appendItem( const QString &music_file_path, const QString &music_name, const QString &music_singer, const qint64 &duration ) {
	musicInfoMutex->lock( );
	QFileInfo fileInfo( music_file_path );
	bool resultBool = true;
	auto absFilePath = fileInfo.absoluteFilePath( );

	size_t count = loadMusicFileHistory.size( );
	if( count ) {
		size_t index = 0;
		auto data = loadMusicFileHistory.data( );
		for( ; index < count; index += 1 )
			if( data[ index ] == absFilePath ) {
				musicInfoMutex->unlock( );
				return false; // 已经在任务列表
			}
	}
	// 在等待完成列表没找到，则在完成列表匹配
	if( resultBool ) {
		count = musicInfoVector->size( );
		auto data = musicInfoVector->data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( data[ index ]->isFile( absFilePath ) ) {
				musicInfoMutex->unlock( );
				return false;
			}
	}

	auto musicInfoItemWidget = new MusicInfoItemWidget( this );
	if( musicInfoItemWidget->init( music_file_path, music_name, music_singer, duration ) == false ) {
		delete musicInfoItemWidget;
		musicInfoMutex->unlock( );
		return false;
	}
	musicInfoItemWidget->parentPlayListWidget = this;
	musicInfoVector->emplace_back( musicInfoItemWidget );
	musicInfoMutex->unlock( );
	return true;
}

bool PlayerListWidget::fromFileLoadItemInfo( const QString &music_file_path ) {
	QFileInfo fileInfo( music_file_path );
	bool resultBool = fileInfo.exists( );
	if( resultBool == false )
		return false; // 不存在
	auto absFilePath = fileInfo.absoluteFilePath( );
	musicInfoMutex->lock( );
	size_t count = loadMusicFileHistory.size( );
	if( count ) {
		size_t index = 0;
		auto data = loadMusicFileHistory.data( );
		for( ; index < count; index += 1 )
			if( data[ index ] == absFilePath ) {
				resultBool = false;
				break; // 存在
			}
	}
	// 在等待完成列表没找到，则在完成列表匹配
	if( resultBool ) {
		count = musicInfoVector->size( );
		if( count ) {
			auto data = musicInfoVector->data( );
			size_t index = 0;
			for( ; index < count; index += 1 )
				if( data[ index ]->isFile( absFilePath ) ) {
					resultBool = false;
					break; // 存在
				}
		}
	}
	// 都找不到，则加入等待列表
	if( resultBool )
		loadMusicFileHistory.append( absFilePath );
	else {
		musicInfoMutex->unlock( );
		return false;
	}
	// 开始工作
	QMediaPlayer *mediaPlayer = new QMediaPlayer;
	mediaPlayer->setSource( QUrl::fromLocalFile( absFilePath ) );
	connect( mediaPlayer, &QMediaPlayer::mediaStatusChanged, [mediaPlayer, this, absFilePath] ( QMediaPlayer::MediaStatus status ) {
		musicInfoMutex->lock( );

		if( status != QMediaPlayer::LoadedMedia ) {
			musicInfoMutex->unlock( );
			return; // 没加载完成，则跳过 
		}

		size_t count = loadMusicFileHistory.size( );
		if( count ) {
			size_t index = 0;
			auto data = loadMusicFileHistory.data( );
			for( ; index < count; index += 1 )
				if( data[ index ] == absFilePath ) {
					loadMusicFileHistory.erase( loadMusicFileHistory.begin( ) + index );
					break; // 存在
				}
			count = loadMusicFileHistory.size( );
		}
		MusicInfoItemWidget *itemWidget = new MusicInfoItemWidget( this );
		QMediaMetaData mediaMetaData = mediaPlayer->metaData( );
		if( itemWidget->init( absFilePath, mediaMetaData ) == true ) {
			itemWidget->parentPlayListWidget = this;
			musicInfoVector->emplace_back( itemWidget );
		} else
			delete itemWidget;
		mediaPlayer->deleteLater( );
		musicInfoMutex->unlock( );
		if( count == 0 )
			updateItemWidget( );
	} );
	musicInfoMutex->unlock( );
	return true;
}

std::vector< MusicInfoItemWidget * > & PlayerListWidget::getMusicInfoVector( std::vector< MusicInfoItemWidget * > &result_vector ) const {
	musicInfoMutex->lock( );
	result_vector = *musicInfoVector;
	musicInfoMutex->unlock( );
	return result_vector;
}

std::vector< QString > & PlayerListWidget::getListMusicFile( std::vector< QString > &result_vector ) const {
	musicInfoMutex->lock( );

	size_t count = musicInfoVector->size( );
	if( count == 0 ) {
		musicInfoMutex->unlock( );
		return result_vector;
	}

	result_vector.resize( count );
	auto copyToData = result_vector.data( );
	auto musicInfoData = musicInfoVector->data( );
	size_t index;
	for( index = 0; index < count; index += 1 )
		copyToData[ index ] = musicInfoData[ index ]->getMusicFilePath( );

	index = count;
	count = loadMusicFileHistory.size( );
	auto loadMusciFileHistoryData = loadMusicFileHistory.data( );
	size_t newSize = count + index;
	result_vector.resize( newSize );
	copyToData = result_vector.data( ) + index;
	for( index = 0; index < count; index += 1 )
		copyToData[ index ] = loadMusciFileHistoryData[ index ];
	musicInfoMutex->unlock( );
	return result_vector;
}

bool PlayerListWidget::renderMusicInfoItem( QImage &result_render_image, const MusicInfoItem *render_target ) const {
	musicInfoMutex->lock( );

	size_t count = musicInfoVector->size( );
	if( count == 0 ) {
		musicInfoMutex->unlock( );
		return false;
	}

	auto data = musicInfoVector->data( );
	size_t index;
	for( index = 0; index < count; index += 1 )
		if( render_target == data[ index ] ) {
			musicInfoMutex->unlock( );
			return false;
		}

	auto renderTarget = data[ index ];
	musicInfoMutex->unlock( );
	return renderAtMusicInfoItem( result_render_image, renderTarget );
}

bool PlayerListWidget::init( ) {
	releaseResource( );

	fileSelectWorkPath = QDir::currentPath( );
	dirSelectWorkPath = QDir::currentPath( );
	musicInfoMutex = new UserMutex;
	playerMutex = new UserMutex;
	doubleClickIntervalTimeMilliSecond = 300;
	activeLeftItemWidget = nullptr;
	selectLeftItemWidget = nullptr;
	beforeClickTime = new QDateTime;
	pen = new QPen;
	musicPlayer = new MusicPlayer;
	selectItemWidgetVector = new std::vector< MusicInfoItemWidget * >;
	musicInfoVector = new std::vector< MusicInfoItemWidget * >;
	indexWidth = splitWidth = musicNameWidth = musicSingerWidth = musicDurationWidth = 4;
	drawPenWidth = 4;
	drawPenColor = QColor( "#7bffa1" );
	drawFillColor = QColor( "#50a2ff" );
	drawFillColor.setAlpha( 100 );
	pen->setWidth( drawPenWidth );
	pen->setColor( drawPenColor );
	if( musicPlayer->init( ) == false )
		return false;
	loadJsonPathInfo( );
	updateItemWidget( );

	// 信号
	AppEventManage::Connect_MusicPlayer_Signal( [this] ( AppEventManage *sender_ptr, MusicPlayer *event_obj_ptr, const MusicPlayerEventInfo &event_info_ref ) {
		auto eventType = event_info_ref.getEventType( );
		switch( eventType ) {
			case MusicPlayerEventInfo::EventType::Player_Over :
				playerOver_slot( event_obj_ptr->getMusicFilePath( ) );
				break;
			case MusicPlayerEventInfo::EventType::Player_Start :
				playerStart_slot( event_obj_ptr->getMusicFilePath( ) );
				break;
			case MusicPlayerEventInfo::EventType::Player_Duration :
				break;
		}
	} );

	AppEventManage::Connect_PlayerWidgetMenu_Signal( [this] ( AppEventManage *sender_ptr, PlayerWidgetMenu *event_obj_ptr, const PlayerWidgetMenuEventInfo &event_info_ref ) {
		auto eventType = event_info_ref.getEventType( );
		switch( eventType ) {
			case PlayerWidgetMenuEventInfo::EventType::Load_Disk_File : {
				QFileInfo fileInfo;
				QFileDialog dialog( this );
				auto appInstance = AppInstance::getAppInstance( );
				auto appDataManage = appInstance->getAppDataManage( );
				auto appTranslate = appDataManage->getTranslate( );
				auto playerListWidgetTranslate = appTranslate->getPlayerListWidget( );
				dialog.setWindowTitle( playerListWidgetTranslate->getLoadDiskDirTitle( ) );
				fileInfo.setFile( fileSelectWorkPath );
				auto openDirPath = fileInfo.absoluteFilePath( );
				dialog.setDirectory( openDirPath );
				dialog.setFileMode( QFileDialog::ExistingFiles );
				auto musicManage = appInstance->getMusicManage( );
				auto musicDecoder = musicManage->getMusicDecoder( );
				auto decodeFileSuffix = musicDecoder->getSupperDecodeFileSuffix( );
				QStringList filterSuffixList;
				size_t count = decodeFileSuffix.size( );
				auto data = decodeFileSuffix.data( );
				size_t index = 0;
				for( ; index < count; index += 1 )
					filterSuffixList.append( "*." + data[ index ] );
				auto musicTypeName = playerListWidgetTranslate->getMusicTypeName( );
				auto filterSuffix = filterSuffixList.join( " " );
				auto filterName = musicTypeName + "(" + filterSuffix + ");;" + playerListWidgetTranslate->getAnyTypeName( ) + "(*.*)";
				dialog.setNameFilter( filterName );
				QRect geometry = this->geometry( );
				auto curentWindowSize = geometry.size( );
				dialog.resize( curentWindowSize );
				auto center = geometry.center( );
				center = mapToGlobal( center );
				WidgetTools::moveWidgetToCenterPos( center, &dialog );
				if( dialog.exec( ) != QDialog::Accepted )
					return;
				QStringList files = dialog.selectedFiles( );
				count = files.size( );
				auto selectFileData = files.data( );
				fileInfo.setFile( selectFileData[ 0 ] );
				auto dir = fileInfo.dir( );
				fileSelectWorkPath = PathTools::getAutoShortenPathName( dir.absolutePath( ) );
				writeJsonPathInfo( );
				std::vector< QString > loadVector( count );
				auto dataPtr = loadVector.data( );
				for( index = 0; index < count; index += 1 )
					dataPtr[ index ] = selectFileData[ index ];
				loadDiskMusicFileList( loadVector );
			}
			break;
			case PlayerWidgetMenuEventInfo::EventType::Load_Disk_Dir : {
				QFileInfo fileInfo;

				QFileDialog dialog( this );
				auto appInstance = AppInstance::getAppInstance( );
				auto appDataManage = appInstance->getAppDataManage( );
				auto appTranslate = appDataManage->getTranslate( );
				auto playerListWidgetTranslate = appTranslate->getPlayerListWidget( );
				dialog.setWindowTitle( playerListWidgetTranslate->getLoadDiskDirTitle( ) );
				fileInfo.setFile( dirSelectWorkPath );
				auto openDirPath = fileInfo.absoluteFilePath( );
				dialog.setDirectory( openDirPath );
				dialog.setFileMode( QFileDialog::Directory );

				QRect geometry = this->geometry( );
				auto curentWindowSize = geometry.size( );
				dialog.resize( curentWindowSize );
				auto center = geometry.center( );
				center = mapToGlobal( center );
				WidgetTools::moveWidgetToCenterPos( center, &dialog );
				if( dialog.exec( ) != QDialog::Accepted )
					return;

				QStringList files = dialog.selectedFiles( );
				qsizetype count = files.size( );
				auto data = files.data( );
				dirSelectWorkPath = PathTools::getAutoShortenPathName( data[ 0 ] );
				writeJsonPathInfo( );
				size_t index;
				std::vector< QString > loadVector( count );
				auto dataPtr = loadVector.data( );
				for( index = 0; index < count; index += 1 )
					dataPtr[ index ] = data[ index ];
				loadDiskMusicDirList( loadVector );
			}
			break;
			case PlayerWidgetMenuEventInfo::EventType::Set_Current_Select_Play :
				setCurrentPlayerMusicList( );
				break;
			case PlayerWidgetMenuEventInfo::EventType::Inster_Current_Select_Play :
				setInsertPlayerMusicList( );
				break;
			case PlayerWidgetMenuEventInfo::EventType::Remove_Play_List_Select_Info :
				removeListMusicFileList( );
				break;
			case PlayerWidgetMenuEventInfo::EventType::Delete_Play_List_Select_File :
				deleteDiskMusicFileList( );
				break;
			case PlayerWidgetMenuEventInfo::EventType::Select_List_Move_Top :
				moveMusicToListTop( );
				break;
			case PlayerWidgetMenuEventInfo::EventType::Select_List_Move_Bottom :
				moveMusicToListBottom( );
				break;
		}
	} );

	return true;
}

bool PlayerListWidget::renderAtMusicInfoItem( QImage &result_render_image, MusicInfoItem *render_target ) const {
	return renderAtMusicInfoItem( result_render_image, render_target, splitWidth );
}

bool PlayerListWidget::renderAtMusicInfoItem( QImage &result_render_image, MusicInfoItem *render_target, int split_width ) const {
	auto appInstance = AppInstance::getAppInstance( );
	auto renderImage = appInstance->getAppDrawManage( )->getRenderImage( );
	auto font = renderImage->getFont( );
	auto fontMetrics = renderImage->getFontMetrics( );
	int itemHeight = fontMetrics->height( );
	auto musicName = render_target->getMusicName( );
	auto musicSinger = render_target->getMusicSinger( );
	auto formatStringDuration = render_target->getFormatStringDuration( );
	int musicNameWidth = fontMetrics->horizontalAdvance( musicName );
	int musicSingerWidth = fontMetrics->horizontalAdvance( musicSinger );
	int formatStringDurationeWidth = fontMetrics->horizontalAdvance( formatStringDuration );
	return renderAtMusicInfoItem( result_render_image, render_target, itemHeight, split_width, musicNameWidth, musicSingerWidth, formatStringDurationeWidth, font );
}

void PlayerListWidget::doubleClickMusicItemWidget( MusicInfoItemWidget *double_target ) {
	if( widgetState != PlayerListWidgetState::None )
		return; // 如果不是被设置成任意状态，则返回，不处理事件
	widgetState = PlayerListWidgetState::Set_Player_Run;
	bool playerMusic = musicPlayer->playerMusic( double_target->getMusicFilePath( ) );
	widgetState = PlayerListWidgetState::None;
	if( playerMusic == false )
		return; // 播放失败，则返回
}

void PlayerListWidget::apendSelectMusicItemWidget( MusicInfoItemWidget *append_select_target, bool check_key_board_modifier ) {
	activeLeftItemWidget = append_select_target;
	selectLeftItemWidget = append_select_target;
	if( check_key_board_modifier == false )
		selectKeyControlModifier( );
	else {
		auto appInstance = AppInstance::getAppInstance( );
		auto keyboardModifiers = ( Qt::KeyboardModifier ) appInstance->keyboardModifiers( ).toInt( );
		switch( keyboardModifiers ) {
			case Qt::KeyboardModifier::ControlModifier :
				selectKeyControlModifier( );
				break;
			case Qt::KeyboardModifier::ShiftModifier :
				if( selectKeyShiftModifier( ) == true )
					break;
			default : {
				selectItemWidgetVector->resize( 1 );
				auto musicInfoItemWidget = selectItemWidgetVector->data( );
				musicInfoItemWidget[ 0 ] = selectLeftItemWidget;
			}
		}
	}
}

void PlayerListWidget::releaseResource( ) {
	#define r_d(ptr) if(ptr)  (delete ptr,ptr = nullptr)
	disconnect( );
	if( playerMutex ) {
		playerMutex->lock( );
		widgetState = PlayerListWidgetState::Set_Player_Run;
		musicPlayer->playerStop( );
		playerItemWidget = nullptr;
		widgetState = PlayerListWidgetState::None;
		playerMutex->unlock( );
		musicInfoMutex->lock( );
		if( selectItemWidgetVector )
			r_d( selectItemWidgetVector );
		r_d( selectItemWidgetVector );

		selectLeftItemWidget = nullptr;
		activeLeftItemWidget = nullptr;

		musicInfoMutex->unlock( );
		clearMusicInfoVector( );
		if( musicInfoVector ) {
			r_d( musicInfoVector );
		}
		r_d( musicInfoMutex );

		r_d( beforeClickTime );
		r_d( pen );
		r_d( musicPlayer );
	}
}

bool PlayerListWidget::selectKeyShiftModifier( ) {
	auto count = selectItemWidgetVector->size( );
	if( count > 0 ) {
		auto selectItemWidgetData = selectItemWidgetVector->data( );
		auto findFirstItemWidth = selectItemWidgetData[ 0 ];
		size_t musicCount = musicInfoVector->size( );
		auto findSourceData = musicInfoVector->data( );
		size_t musicIndex = 0;
		// 匹配 getBegIndex
		for( ; musicIndex < musicCount; musicIndex += 1 )
			if( findSourceData[ musicIndex ] == findFirstItemWidth )
				break;
		if( musicIndex == musicCount )
			return false;

		size_t getBegIndex = musicIndex;

		// 匹配 getEndIndex
		for( musicIndex = 0; musicIndex < musicCount; musicIndex += 1 )
			if( findSourceData[ musicIndex ] == selectLeftItemWidget )
				break;
		if( musicIndex == musicCount )
			return false;

		size_t getEndIndex = musicIndex;
		if( getEndIndex != getBegIndex ) {
			if( getEndIndex > getBegIndex ) {
				auto endIndex = getEndIndex + 1;
				count = endIndex - getBegIndex;
				selectItemWidgetVector->resize( count );
				selectItemWidgetData = selectItemWidgetVector->data( );
				findSourceData += getBegIndex;
				musicIndex = 0;
				for( ; musicIndex < count; musicIndex += 1 )
					selectItemWidgetData[ musicIndex ] = findSourceData[ musicIndex ];
			} else {
				auto endIndex = getBegIndex + 1;
				count = endIndex - getEndIndex;
				selectItemWidgetVector->resize( count );
				selectItemWidgetData = selectItemWidgetVector->data( );
				findSourceData += getEndIndex;
				qint64 destIndex = count - 1;
				musicIndex = 0;
				for( ; musicIndex < count; musicIndex += 1, destIndex -= 1 )
					selectItemWidgetData[ destIndex ] = findSourceData[ musicIndex ];
			}
		}
		return true;
	}
	return false; // 未处理
}

bool PlayerListWidget::selectKeyControlModifier( ) {
	auto count = selectItemWidgetVector->size( );
	if( count ) {
		auto musicInfoItemWidget = selectItemWidgetVector->data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( musicInfoItemWidget[ index ] == selectLeftItemWidget )
				break;
		if( index < count ) {
			count -= 1;
			for( ; index < count; index += 1 )
				musicInfoItemWidget[ index ] = musicInfoItemWidget[ index + 1 ];
			musicInfoItemWidget[ index ] = selectLeftItemWidget; // 排序到末尾
			return true;
		}
	}
	selectItemWidgetVector->emplace_back( selectLeftItemWidget );
	return true;
}

void PlayerListWidget::removeRepetition( ) {
	using compUnity = MusicInfoItemWidget *;
	VectorTools::compIdenticalTypeFinction< compUnity > compFunction = [] ( const compUnity &left, const compUnity &right ) ->bool {
		if( left->musicFilePath == right->musicFilePath )
			return true;
		return false;
	};
	std::vector< MusicInfoItemWidget * > release;
	std::vector< MusicInfoItemWidget * > buff;
	VectorTools::getRepetition( buff, release, *musicInfoVector, compFunction );
	VectorTools::deleteVectorPtr( release );
	*musicInfoVector = buff;
}

void PlayerListWidget::playerStart_slot( const QString &player_music_file ) {
	if( this == nullptr )
		return;
	if( musicInfoMutex == nullptr )
		return;
	size_t index;
	size_t count;
	musicInfoMutex->lock( );
	count = musicInfoVector->size( );
	if( count == 0 ) {
		playerItemWidget = nullptr;
		musicInfoMutex->unlock( );
		return;
	}
	auto data = musicInfoVector->data( );
	index = 0;
	for( ; index < count; index += 1 )
		if( data[ index ]->isFile( player_music_file ) ) {
			playerItemWidget = musicInfoVector->data( )[ index ];
			musicInfoMutex->unlock( );
			return;
		}
	playerItemWidget = nullptr;
	musicInfoMutex->unlock( );
}

void PlayerListWidget::playerOver_slot( const QString &player_music_file ) {
	if( this == nullptr )
		return;
	if( musicInfoMutex == nullptr )
		return;
	size_t index;
	size_t count;
	QString nextPlayerFile;
	musicInfoMutex->lock( );
	count = musicInfoVector->size( );
	if( count == 0 ) {
		musicInfoMutex->unlock( );
		return;
	}
	auto data = musicInfoVector->data( );
	index = 0;
	for( ; index < count; index += 1 )
		if( data[ index ]->isFile( player_music_file ) ) {
			playerItemWidget = nullptr;
			index += 1;
			if( index == count )
				nextPlayerFile = data[ 0 ]->getMusicFilePath( );
			else
				nextPlayerFile = data[ index ]->getMusicFilePath( );
			break;
		}
	musicInfoMutex->unlock( );
	widgetState = PlayerListWidgetState::Set_Player_Next;
	musicPlayer->playerMusic( nextPlayerFile );
	widgetState = PlayerListWidgetState::None;
}

void PlayerListWidget::updateItemWidget( ) {
	musicInfoMutex->lock( );

	int offsetY = 0;
	auto appInstance = AppInstance::getAppInstance( );
	auto renderImage = appInstance->getAppDrawManage( )->getRenderImage( );
	auto fontMetrics = renderImage->getFontMetrics( );
	int height = fontMetrics->height( );
	auto newWidth = this->widgetBeforeWidth + this->widgetAfterWidth + this->splitWidth * 5 + this->musicNameWidth + this->musicSingerWidth + this->musicDurationWidth + this->indexWidth;
	size_t count = musicInfoVector->size( );
	if( count == 0 ) {
		if( newWidth > 0 )
			setFixedWidth( newWidth );
		musicInfoMutex->unlock( );
		return;
	}
	decltype(musicInfoVector) buff = new std::vector< MusicInfoItemWidget * >;
	// 删除空指针
	VectorTools::removeNullptrVectorPtr( *buff, *musicInfoVector );
	*musicInfoVector = *buff;
	// 删除重复
	removeRepetition( );
	count = musicInfoVector->size( );
	delete buff;
	auto data = musicInfoVector->data( );
	size_t index;
	for( index = 0; index < count; index += 1 ) {
		auto itemWidget = data[ index ];
		itemWidget->widgetBeforeWidth = this->widgetBeforeWidth;
		itemWidget->widgetAfterWidth = this->widgetAfterWidth;
		itemWidget->splitWidth = this->splitWidth;
		itemWidget->musicNameWidth = this->musicNameWidth;
		itemWidget->musicSingerWidth = this->musicSingerWidth;
		itemWidget->musicDurationWidth = this->musicDurationWidth;
		itemWidget->indexWidth = this->indexWidth;
		itemWidget->setIndex( index + 1 );
		itemWidget->update( );
		itemWidget->show( );
		itemWidget->setGeometry( 0, offsetY, newWidth, height );
		offsetY += height;
	}
	if( offsetY > 0 && newWidth > 0 )
		this->setFixedSize( newWidth, offsetY );
	else if( offsetY == 0 && newWidth > 0 )
		setFixedWidth( newWidth );
	else if( offsetY > 0 && newWidth == 0 )
		setFixedHeight( offsetY );
	musicInfoMutex->unlock( );
}

bool PlayerListWidget::renderAtMusicInfoItem( QImage &result_render_image, MusicInfoItem *render_target, int item_height, int split_width, int name_item_width, int singer_item_width, int duration_item_width, const QFont *item_font ) const {
	if( item_font == nullptr )
		return false;
	int imageWidth = split_width * 4 + name_item_width + singer_item_width + duration_item_width;
	QImage buff = QImage( imageWidth, item_height, QImage::Format_RGBA8888 );
	if( buff.isNull( ) )
		return false;
	buff.fill( 0 );
	int offsetSplitX = split_width / 2;
	QPainter painter;
	painter.begin( &buff );
	auto pen = painter.pen( );
	pen.setWidth( split_width );
	painter.setPen( pen );
	painter.setFont( *item_font );

	int drawOffsetX = offsetSplitX;
	QRect drawRect;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, item_height );
	drawOffsetX += offsetSplitX;
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( name_item_width, item_height ) );
	painter.drawText( drawRect, render_target->musicName );
	drawOffsetX += name_item_width + offsetSplitX;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, item_height );
	drawOffsetX += offsetSplitX;
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( musicSingerWidth, item_height ) );
	painter.drawText( drawRect, render_target->musicSinger );
	drawOffsetX += singer_item_width + offsetSplitX;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, item_height );
	drawOffsetX += offsetSplitX;
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( duration_item_width, item_height ) );
	painter.drawText( drawRect, render_target->formatStringDuration );
	drawOffsetX += duration_item_width + offsetSplitX;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, item_height );

	painter.end( );
	result_render_image = buff;
	return true;
}

void PlayerListWidget::paintEvent( QPaintEvent *event ) {
	if( widgetState != PlayerListWidgetState::None )
		return; // 如果不是被设置成任意状态，则返回，不处理事件
	if( musicInfoMutex->tryLock( ) == false )
		return;
	QPainter painter;
	painter.begin( this );
	painter.setPen( *pen );
	size_t count = selectItemWidgetVector->size( );
	if( count ) {
		auto data = selectItemWidgetVector->data( );
		size_t index;
		for( index = 0; index < count; index += 1 )
			painter.fillRect( data[ index ]->geometry( ), drawFillColor );
	}
	if( activeLeftItemWidget ) {
		auto drawPenWidthOffset = drawPenWidth / 2;
		auto geometry = activeLeftItemWidget->geometry( );
		int x = geometry.x( ) + drawPenWidthOffset;
		int y = geometry.y( ) + drawPenWidthOffset;
		int width = geometry.width( ) - drawPenWidth;
		int height = geometry.height( ) - drawPenWidth;

		painter.drawRect( x, y, width, height );
	}
	painter.end( );
	musicInfoMutex->unlock( );
}

void PlayerListWidget::resizeEvent( QResizeEvent *event ) {
	auto size = event->size( );
	currentWidgetHeight = size.height( );
	currentWidgetWidth = size.width( );
	//update();
}

void PlayerListWidget::mouseMoveEvent( QMouseEvent *event ) {
	if( widgetState != PlayerListWidgetState::None )
		return; // 如果不是被设置成任意状态，则返回，不处理事件
	if( musicInfoMutex->tryLock( ) == false )
		return;
	size_t count = musicInfoVector->size( );
	if( count == 0 ) {
		musicInfoMutex->unlock( );
		return;
	}

	auto point = event->pos( );
	auto data = musicInfoVector->data( );
	size_t index;
	for( index = 0; index < count; index += 1 )
		if( data[ index ]->geometry( ).contains( point ) ) {
			activeLeftItemWidget = data[ index ];
			break;
		}
	musicInfoMutex->unlock( );
	update( );
}

void PlayerListWidget::hideEvent( QHideEvent *event ) {
	musicInfoMutex->lock( );
	writeJsonPathInfo( );
	musicInfoMutex->unlock( );
	QWidget::hideEvent( event );
}

void PlayerListWidget::mouseReleaseEvent( QMouseEvent *event ) {
	if( widgetState != PlayerListWidgetState::None )
		return; // 如果不是被设置成任意状态，则返回，不处理事件
	Qt::MouseButton mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::MouseButton::LeftButton : {
			bool isDoubleClick = false;
			MusicInfoItemWidget *selectItem = nullptr;
			musicInfoMutex->lock( );
			size_t count = musicInfoVector->size( );
			if( count == 0 ) {
				musicInfoMutex->unlock( );
				return;
			}

			auto point = event->pos( );
			auto data = musicInfoVector->data( );
			size_t index;
			for( index = 0; index < count; index += 1 )
				if( data[ index ]->geometry( ).contains( point ) ) {
					selectItem = data[ index ];

					// 双击检测
					auto currentDateTime = QDateTime::currentDateTime( );
					if( selectLeftItemWidget == selectItem )
						isDoubleClick = doubleClickIntervalTimeMilliSecond > ( currentDateTime - *beforeClickTime ).count( );
					*beforeClickTime = currentDateTime;
					break;
				}
			musicInfoMutex->unlock( );
			// 双击或单击，二选一
			if( isDoubleClick ) {
				doubleClickMusicItemWidget( selectItem );

				// 触发信号
				PlayerListWidgetEventInfo eventInfo;
				eventInfo.eventSenderPtr = this;
				eventInfo.event = PlayerListWidgetEventInfo::EventType::Item_Double_Select;
				Emit_PlayerListWidget_Event( this, eventInfo );
			} else if( selectItem ) { // 单击
				std::vector< MusicInfoItemWidget * > resultVector;
				musicInfoMutex->lock( );
				apendSelectMusicItemWidget( selectItem, true );
				resultVector = *selectItemWidgetVector;
				musicInfoMutex->unlock( );

				// 触发信号
				PlayerListWidgetEventInfo eventInfo;
				eventInfo.eventSenderPtr = this;
				eventInfo.event = PlayerListWidgetEventInfo::EventType::Item_Select;
				Emit_PlayerListWidget_Event( this, eventInfo );
				update( );
			}
		}
		break;
		case Qt::MouseButton::RightButton : {
			MusicInfoItemWidget *selectItem = nullptr;
			musicInfoMutex->lock( );

			size_t count = musicInfoVector->size( );
			if( count ) {
				auto point = event->pos( );
				auto data = musicInfoVector->data( );
				size_t index;
				for( index = 0; index < count; index += 1 )
					if( data[ index ]->geometry( ).contains( point ) ) {
						selectItem = data[ index ];
						break;
					}
			}
			musicInfoMutex->unlock( );
			if( selectItem ) {
				std::vector< MusicInfoItemWidget * > resultVector;
				musicInfoMutex->lock( );
				apendSelectMusicItemWidget( selectItem, false );
				resultVector = *selectItemWidgetVector;
				musicInfoMutex->unlock( );
				update( );
				// 触发信号
				PlayerListWidgetEventInfo eventInfo;
				eventInfo.eventSenderPtr = this;
				eventInfo.event = PlayerListWidgetEventInfo::EventType::Item_Select;
				Emit_PlayerListWidget_Event( this, eventInfo );
			}
			// 触发信号
			PlayerListWidgetEventInfo eventInfo;
			eventInfo.eventSenderPtr = this;
			eventInfo.event = PlayerListWidgetEventInfo::EventType::Pop_Menu;
			Emit_PlayerListWidget_Event( this, eventInfo );
		}
		break;
	}
}

bool PlayerListWidget::removeMusicInfoVector( const std::vector< MusicInfoItemWidget * > &remove_source_target, std::vector< MusicInfoItemWidget * > &result_move_target ) {
	std::vector< MusicInfoItemWidget * > unionSetVector;

	VectorTools::unionSetVector( unionSetVector, *musicInfoVector, remove_source_target );
	size_t count = unionSetVector.size( );
	if( count == 0 )
		return false;
	VectorTools::differenceSetVector( result_move_target, *musicInfoVector, unionSetVector );
	*musicInfoVector = result_move_target;
	result_move_target = unionSetVector;
	return true;
}

bool PlayerListWidget::deleteDiskMusicFileList( ) {
	std::vector< MusicInfoItemWidget * > deleteSetVector;
	musicInfoMutex->lock( );

	if( removeMusicInfoVector( *selectItemWidgetVector, deleteSetVector ) == false ) {
		musicInfoMutex->unlock( );
		return false;
	}
	selectItemWidgetVector->clear( );
	selectLeftItemWidget = nullptr;
	activeLeftItemWidget = nullptr;
	musicInfoMutex->unlock( );

	updateItemWidget( );
	update( );
	auto deleteFileData = deleteSetVector.data( );
	size_t deleteFileCount = deleteSetVector.size( );
	size_t deleteFileIndex;
	QFile file;
	PlayerListWidgetTranslate *playerListWidget = AppInstance::getAppInstance( )->getAppDataManage( )->getTranslate( )->getPlayerListWidget( );

	for( deleteFileIndex = 0; deleteFileIndex < deleteFileCount; deleteFileIndex += 1 ) {
		QString musicFilePath = deleteFileData[ deleteFileIndex ]->musicFilePath;
		file.setFileName( musicFilePath );
		bool moveToTrash = file.moveToTrash( );
		if( deleteFileData[ deleteFileIndex ] == playerItemWidget ) {
			musicInfoMutex->lock( );
			playerItemWidget = nullptr;
			musicInfoMutex->unlock( );
			widgetState = PlayerListWidgetState::Set_Player_Run;
			musicPlayer->playerStop( );
			widgetState = PlayerListWidgetState::None;
		}
		delete deleteFileData[ deleteFileIndex ];
		if( moveToTrash )
			continue;
		Message_Error_Out << playerListWidget->getRemoveDiskFileError( ) + " : " + musicFilePath;
	}
	return true;
}

bool PlayerListWidget::removeListMusicFileList( ) {
	std::vector< MusicInfoItemWidget * > deleteSetVector;
	musicInfoMutex->lock( );
	if( removeMusicInfoVector( *selectItemWidgetVector, deleteSetVector ) == false ) {
		musicInfoMutex->unlock( );
		return false;
	}
	selectItemWidgetVector->clear( );
	selectLeftItemWidget = nullptr;
	activeLeftItemWidget = nullptr;
	musicInfoMutex->unlock( );
	updateItemWidget( );
	update( );
	auto deleteFileData = deleteSetVector.data( );
	size_t deleteFileCount = deleteSetVector.size( );
	size_t deleteFileIndex;
	for( deleteFileIndex = 0; deleteFileIndex < deleteFileCount; deleteFileIndex += 1 ) {
		if( deleteFileData[ deleteFileIndex ] == playerItemWidget ) {
			musicInfoMutex->lock( );
			playerItemWidget = nullptr;
			musicInfoMutex->unlock( );

			widgetState = PlayerListWidgetState::Set_Player_Run;
			musicPlayer->playerStop( );
			widgetState = PlayerListWidgetState::None;
		}
		delete deleteFileData[ deleteFileIndex ];
	}
	return true;
}

bool PlayerListWidget::loadDiskMusicFileList( const std::vector< QString > &load_vector ) {
	QStringList superMusicList;
	if( PathTools::filterMusicFile( superMusicList, load_vector ) == 0 )
		return false;
	qsizetype count = superMusicList.size( );
	qsizetype index;
	auto selectFileData = superMusicList.data( );
	for( index = 0; index < count; index += 1 )
		fromFileLoadItemInfo( selectFileData[ index ] );
	return true;
}

bool PlayerListWidget::loadDiskMusicDirList( const std::vector< QString > &load_vector ) {
	QStringList result;

	bool entryList = PathTools::entryFilePath( result, load_vector );
	if( entryList == false )
		return false;

	QStringList superMusicList;
	if( PathTools::filterMusicFile( superMusicList, result ) == 0 )
		return false;
	qsizetype count = superMusicList.size( );
	qsizetype index;
	auto selectFileData = superMusicList.data( );
	for( index = 0; index < count; index += 1 )
		fromFileLoadItemInfo( selectFileData[ index ] );
	return true;
}

bool PlayerListWidget::setoutStatusTranslationMoveCurrentPlayer( const std::vector< MusicInfoItemWidget * > &translation_vector_source ) {// 列表当中是否存在播放项
	size_t translCount = translation_vector_source.size( );
	if( translCount == 0 )
		return false;
	auto translData = translation_vector_source.data( );
	size_t translIndex;

	size_t playerListCount = musicInfoVector->size( ); // 原始列表个数
	auto playerListData = musicInfoVector->data( ); // 原始列表起始指针
	size_t playerListIndex;
	translCount -= 1;
	auto selectLastItem = translData[ translCount ];
	std::vector< MusicInfoItemWidget * > cloneOrgVector( playerListCount ); // 克隆数据放置序列
	auto cloneOrgData = cloneOrgVector.data( ); // 克隆数据列表起始指针
	size_t cloneOrgIndex = 0; // 克隆数据的放置下标
	for( playerListIndex = 0; playerListIndex < playerListCount; playerListIndex += 1 ) {
		auto cmpItem = playerListData[ playerListIndex ];
		if( selectLastItem == cmpItem ) {
			// 偏移指针到起始克隆数据放置位置
			auto offsetClonePtr = cloneOrgData + cloneOrgIndex;
			// 拷贝移动列表到克隆序列
			for( translIndex = 0; translIndex < translCount; translIndex += 1 )
				offsetClonePtr[ translIndex ] = translData[ translIndex ];
			offsetClonePtr[ translIndex ] = translData[ translIndex ]; // 拷贝末尾
			cloneOrgIndex += translIndex;// 增加扩张数据
			// 接手循环
			for( ; playerListIndex < playerListCount; playerListIndex += 1 ) {
				cmpItem = playerListData[ playerListIndex ];
				for( translIndex = 0; translIndex < translCount; translIndex += 1 )
					if( cmpItem == translData[ translIndex ] )
						break;
				if( translIndex < translCount )
					continue;
				cloneOrgData[ cloneOrgIndex ] = cmpItem;
				cloneOrgIndex += 1;
			}
			break; // 已经实现循环
		}
		for( translIndex = 0; translIndex < translCount; translIndex += 1 )
			if( cmpItem == translData[ translIndex ] )
				break;
		if( translIndex < translCount )
			continue;
		cloneOrgData[ cloneOrgIndex ] = cmpItem;
		cloneOrgIndex += 1;
	}
	*musicInfoVector = cloneOrgVector;
	*selectItemWidgetVector = translation_vector_source;
	selectLeftItemWidget = activeLeftItemWidget = selectLastItem;
	return true;
}

bool PlayerListWidget::playerStatusTranslationMoveCurrentPlayer( const std::vector< MusicInfoItemWidget * > &translation_vector_source ) {
	// 列表当中是否存在播放项
	size_t translCount = translation_vector_source.size( );
	if( translCount == 0 )
		return false;
	// 移动的序列
	std::vector< MusicInfoItemWidget * > moveVector( translCount );
	auto moveData = moveVector.data( );
	size_t moveIndex;
	auto translData = translation_vector_source.data( );
	size_t translIndex = 0;
	// 排序移动序列
	for( ; translIndex < translCount; translIndex += 1 )
		if( translData[ translIndex ] == playerItemWidget ) {
			moveIndex = translIndex;
			for( ; moveIndex > 0; moveIndex -= 1 )
				moveData[ moveIndex ] = moveData[ moveIndex - 1 ];
			moveData[ 0 ] = playerItemWidget;
		} else
			moveData[ translIndex ] = translData[ translIndex ];
	// 找到选择列表的末尾项

	translCount -= 1; // 排除末尾
	auto moveLastItem = moveData[ translCount ]; // 获取末尾项
	size_t playerListCount = musicInfoVector->size( ); // 原始列表个数
	auto playerListData = musicInfoVector->data( ); // 原始列表起始指针
	std::vector< MusicInfoItemWidget * > cloneOrgVector( playerListCount ); // 克隆数据放置序列
	auto cloneOrgData = cloneOrgVector.data( ); // 克隆数据列表起始指针
	size_t cloneOrgIndex = 0; // 克隆数据的放置下标
	for( translIndex = 0; translIndex < playerListCount; translIndex += 1 ) {
		auto cmpItem = playerListData[ translIndex ];
		if( cmpItem == moveLastItem ) /* 如果匹配到末尾项，则把移动序列拷贝到克隆序列 */ {
			// 偏移指针到起始克隆数据放置位置
			auto offsetClonePtr = cloneOrgData + cloneOrgIndex;
			// 拷贝移动列表到克隆序列
			for( moveIndex = 0; moveIndex < translCount; moveIndex += 1 )
				offsetClonePtr[ moveIndex ] = moveData[ moveIndex ];
			offsetClonePtr[ moveIndex ] = moveData[ moveIndex ]; // 拷贝末尾
			cloneOrgIndex += moveIndex + 1;// 增加扩张数据
			translIndex += 1;
			// 接手循环
			for( ; translIndex < playerListCount; translIndex += 1 ) {
				cmpItem = playerListData[ translIndex ];
				for( moveIndex = 0; moveIndex < translCount; moveIndex += 1 )
					if( cmpItem == moveData[ moveIndex ] )
						break;
				if( moveIndex < translCount )
					continue; // 在移动列表当中时，不拷贝到克隆序列
				cloneOrgData[ cloneOrgIndex ] = cmpItem;
				cloneOrgIndex += 1;
			}
			break; // 已经实现循环
		}
		for( moveIndex = 0; moveIndex < translCount; moveIndex += 1 )
			if( cmpItem == moveData[ moveIndex ] )
				break;
		if( moveIndex < translCount )
			continue; // 在移动列表当中时，不拷贝到克隆序列
		cloneOrgData[ cloneOrgIndex ] = cmpItem;
		cloneOrgIndex += 1;
	}
	*musicInfoVector = cloneOrgVector;
	*selectItemWidgetVector = moveVector;
	selectLeftItemWidget = activeLeftItemWidget = moveLastItem;
	return true;
}

bool PlayerListWidget::setCurrentPlayerMusicList( ) {
	bool result;
	// 如果存在播放
	musicInfoMutex->lock( );
	if( playerItemWidget )
		/* 正在播放音乐 */
		result = playerStatusTranslationMoveCurrentPlayer( *selectItemWidgetVector );
	else
		/* 不在播放音乐 */
		result = setoutStatusTranslationMoveCurrentPlayer( *selectItemWidgetVector );
	musicInfoMutex->unlock( );
	if( result ) {
		updateItemWidget( );
		if( playerItemWidget ) {
			widgetState = PlayerListWidgetState::Set_Player_Run;
			musicPlayer->playerStop( );
			widgetState = PlayerListWidgetState::None;
			auto appInstance = AppInstance::getAppInstance( );
			while( widgetState != PlayerListWidgetState::None )
				appInstance->processEvents( );
		}
		widgetState = PlayerListWidgetState::Set_Player_Run;
		result = musicPlayer->playerMusic( selectItemWidgetVector->data( )[ 0 ]->getMusicFilePath( ) );
		widgetState = PlayerListWidgetState::None;
		return result;
	}
	return result;
}

bool PlayerListWidget::playerStatusTranslationMoveCurrentPlayerNext( const std::vector< MusicInfoItemWidget * > &translation_vector_source ) {
	size_t translationCount = translation_vector_source.size( );
	auto translationData = translation_vector_source.data( );
	size_t translationIndex = 0;
	for( ; translationIndex < translationCount; translationIndex += 1 )
		if( translationData[ translationIndex ] == playerItemWidget ) // 如果选择在内
			return playerStatusTranslationMoveCurrentPlayer( translation_vector_source );

	size_t count = musicInfoVector->size( );
	auto data = musicInfoVector->data( );
	std::vector< MusicInfoItemWidget * > clone( count );
	auto cloneData = clone.data( );
	size_t cloneIndex = 0;
	size_t index = 0;
	for( ; index < count; index += 1 ) {
		auto comp = data[ index ];

		// 如果当前放置项为播放，则接管循环
		if( comp == playerItemWidget ) {
			cloneData[ cloneIndex ] = comp;
			cloneIndex += 1;
			auto offsetCloneData = cloneData + cloneIndex;
			for( translationIndex = 0; translationIndex < translationCount; translationIndex += 1 )
				offsetCloneData[ translationIndex ] = translationData[ translationIndex ];
			cloneIndex += translationCount;
			for( index += 1; index < count; index += 1 ) {
				comp = data[ index ]; // 跳过 playerItemWidget 项
				for( translationIndex = 0; translationIndex < translationCount; translationIndex += 1 )
					if( comp == translationData[ translationIndex ] )
						break;
				if( translationIndex < translationCount )
					continue;
				if( cloneIndex >= count )
					break;
				cloneData[ cloneIndex ] = comp;
				cloneIndex += 1;
			}
			break;
		}

		for( translationIndex = 0; translationIndex < translationCount; translationIndex += 1 )
			if( comp == translationData[ translationIndex ] )
				break;
		if( translationIndex < translationCount )
			continue;
		cloneData[ cloneIndex ] = comp;
		cloneIndex += 1;
	}
	*musicInfoVector = clone;
	return true;
}

bool PlayerListWidget::setoutStatusTranslationMoveCurrentPlayerNext( const std::vector< MusicInfoItemWidget * > &translation_vector_source ) {
	return setoutStatusTranslationMoveCurrentPlayer( translation_vector_source );;
}

bool PlayerListWidget::setInsertPlayerMusicList( ) {
	bool result;
	// 如果存在播放
	musicInfoMutex->lock( );
	if( playerItemWidget )
		/* 正在播放音乐 */
		result = playerStatusTranslationMoveCurrentPlayerNext( *selectItemWidgetVector );
	else
		/* 不在播放音乐 */
		result = setoutStatusTranslationMoveCurrentPlayerNext( *selectItemWidgetVector );
	musicInfoMutex->unlock( );
	if( result )
		updateItemWidget( );
	return result;
}

bool PlayerListWidget::moveMusicToListTop( ) {
	musicInfoMutex->lock( );
	size_t count = musicInfoVector->size( );
	auto data = musicInfoVector->data( );
	size_t index = 0;
	auto checkCount = selectItemWidgetVector->size( );
	auto checkData = selectItemWidgetVector->data( );
	std::vector< MusicInfoItemWidget * > clone( count );
	auto cloneData = clone.data( );
	size_t cloneIndex = 0;
	size_t checkIndex;

	for( checkIndex = 0; checkIndex < checkCount; checkIndex += 1, cloneIndex += 1 )
		cloneData[ cloneIndex ] = checkData[ checkIndex ];
	for( ; index < count; index += 1 ) {
		auto comp = data[ index ];
		for( checkIndex = 0; checkIndex < checkCount; checkIndex += 1 )
			if( comp == checkData[ checkIndex ] )
				break;
		if( checkIndex < checkCount )
			continue;
		cloneData[ cloneIndex ] = comp;
		cloneIndex += 1;
	}
	*musicInfoVector = clone;
	musicInfoMutex->unlock( );
	updateItemWidget( );
	return true;
}

bool PlayerListWidget::moveMusicToListBottom( ) {
	musicInfoMutex->lock( );
	size_t count = musicInfoVector->size( );
	auto data = musicInfoVector->data( );
	size_t index = 0;
	size_t checkCount = selectItemWidgetVector->size( );
	auto checkData = selectItemWidgetVector->data( );
	std::vector< MusicInfoItemWidget * > clone( count );
	auto cloneData = clone.data( );
	size_t cloneIndex = 0;
	size_t checkIndex;

	for( ; index < count; index += 1 ) {
		auto comp = data[ index ];
		for( checkIndex = 0; checkIndex < checkCount; checkIndex += 1 )
			if( comp == checkData[ checkIndex ] )
				break;
		if( checkIndex < checkCount )
			continue;
		cloneData[ cloneIndex ] = comp;
		cloneIndex += 1;
	}
	for( checkIndex = 0; checkIndex < checkCount; checkIndex += 1, cloneIndex += 1 )
		cloneData[ cloneIndex ] = checkData[ checkIndex ];
	*musicInfoVector = clone;
	musicInfoMutex->unlock( );
	updateItemWidget( );
	return true;
}
