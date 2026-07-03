#include "appMusicManage.h"

#include <QMediaPlayer>

#include "appMusicDecoder.h"

#include "../item/musicItem.h"

#include "../mutex/userMutex.h"

#include "../tools/pathTools.h"

bool AppMusicManage::deleteResource( ) {
	if( loadMutex ) {
		loadMutex->lock( );
		size_t index;
		size_t count;
		count = loadMediaVector.size( );
		if( count ) {
			auto data = loadMediaVector.data( );
			for( index = 0; index < count; index += 1 )
				delete data[ index ];
		}
		count = musicItemvVector.size( );
		if( count ) {
			auto data = musicItemvVector.data( );
			for( index = 0; index < count; index += 1 )
				delete data[ index ];
		}
		Delete_Resource_App_Core_Ptr( appMusicDecoder );
		disconnect( );
		loadMediaVector.clear( );
		loadFileVector.clear( );
		loadCount = 0;
		loadMutex->unlock( );
		Delete_Resource_App_Core_Ptr( loadMutex );
	}
	return true;
}

void AppMusicManage::loadFile( const QString &music_file ) {
	// 构建对象
	auto loadMusicFile = new QMediaPlayer;
	// 链接信号
	loadMusicFile->connect( loadMusicFile, &QMediaPlayer::mediaStatusChanged, this, [this, loadMusicFile] ( QMediaPlayer::MediaStatus status ) {
		MusicItem *musicItem = new MusicItem( *loadMusicFile );
		switch( status ) {
			case QMediaPlayer::EndOfMedia :
			case QMediaPlayer::InvalidMedia :
			case QMediaPlayer::NoMedia :
				emit signal_load_error( musicItem->getAbsFilePath( ) );
			case QMediaPlayer::LoadingMedia :
			case QMediaPlayer::StalledMedia :
			case QMediaPlayer::BufferingMedia :
			case QMediaPlayer::BufferedMedia :
				return; // 不是加载完成，则无法运行该功能
			case QMediaPlayer::LoadedMedia :
				break;
		}
		loadMutex->lock( );
		loadMusicFile->disconnect( );
		loadCount += 1;
		size_t loadOverCount = loadMediaVector.size( );
		musicItemvVector.emplace_back( musicItem );
		loadMutex->unlock( );
		emit signal_load_unity( *musicItem );
		if( loadOverCount == loadCount ) {
			loadMutex->lock( );
			auto mediaPlayer = loadMediaVector.data( );
			for( loadOverCount = 0; loadOverCount < loadCount; loadOverCount += 1 )
				delete mediaPlayer[ loadOverCount ];
			loadMediaVector.clear( );
			// 拷贝序列
			loadCount = musicItemvVector.size( );
			std::vector< const MusicItem * > buff( loadCount );
			auto buffData = buff.data( );
			auto sourceData = musicItemvVector.data( );
			for( loadOverCount = 0; loadOverCount < loadCount; loadOverCount += 1 )
				buffData[ loadOverCount ] = sourceData[ loadOverCount ];
			loadMutex->unlock( );
			// 触发信号
			emit signal_load_over( musicItemvVector );
		}
	} );

	// 存储
	loadMutex->lock( );
	loadMediaVector.emplace_back( loadMusicFile );
	loadMutex->unlock( );
	// 开始配置
	loadMusicFile->setSource( QUrl::fromLocalFile( music_file ) );
}

void AppMusicManage::loadMusciFromFileVector( const std::vector< QString > &music_file ) {
	loadMutex->lock( );
	size_t count = loadFileVector.size( );

	size_t compCount = music_file.size( );
	auto loadArray = music_file.data( );
	size_t loadIndex;
	std::vector< QString > loadBuff( compCount );
	std::vector< QString > dirVector;
	auto loadBuffData = loadBuff.data( );
	size_t loadBuffCount = 0;
	size_t index;
	QFileInfo fileInfo;
	QString compItem;
	if( count ) {
		auto data = loadFileVector.data( );
		for( loadIndex = 0; loadIndex < compCount; loadIndex += 1 ) {
			fileInfo.setFile( loadArray[ loadIndex ] );
			if( fileInfo.exists( ) == false )
				continue;
			compItem = fileInfo.absoluteFilePath( );
			if( fileInfo.isDir( ) ) {
				dirVector.emplace_back( compItem );
				continue;
			}
			for( index = 0; index < loadBuffCount; index += 1 )
				if( compItem == loadBuffData[ index ] )
					break;
			if( index != loadBuffCount )
				continue;
			for( index = 0; index < count; index += 1 )
				if( compItem == data[ index ] )
					break;
			if( index != count )
				continue;
			loadBuffData[ loadBuffCount ] = compItem;
			loadBuffCount += 1;
		}
		if( loadBuffCount != compCount )
			loadBuff.resize( loadBuffCount );
		loadFileVector.append_range( loadBuff );
	} else {
		for( loadIndex = 0; loadIndex < compCount; loadIndex += 1 ) {
			fileInfo.setFile( loadArray[ loadIndex ] );
			if( fileInfo.exists( ) == false )
				continue;
			compItem = fileInfo.absoluteFilePath( );
			if( fileInfo.isDir( ) ) {
				dirVector.emplace_back( compItem );
				continue;
			}
			compItem = fileInfo.absoluteFilePath( );
			for( index = 0; index < loadBuffCount; index += 1 )
				if( compItem == loadBuffData[ index ] )
					break;
			if( index != loadBuffCount )
				continue;
			loadBuffData[ loadBuffCount ] = compItem;
			loadBuffCount += 1;
		}
		if( loadBuffCount != compCount )
			loadBuff.resize( loadBuffCount );
		loadFileVector.append_range( loadBuff );
	}
	loadMutex->unlock( );
	for( index = 0; index < loadBuffCount; index += 1 )
		loadFile( loadBuffData[ index ] );
}

void AppMusicManage::loadMusciFromDir( const std::vector< QString > &music_dir ) {
	std::vector< QString > fileVector;
	QFileInfo fileInfo;
	QString compItem;
	size_t compCount = music_dir.size( );
	auto compData = music_dir.data( );
	size_t countIndex;
	std::vector< QString > loadDirVector( compCount );
	auto loadDirData = loadDirVector.data( );
	size_t loadDirCount = 0;
	size_t loadDirIndex;
	for( countIndex = 0; countIndex < compCount; countIndex += 1 ) {
		fileInfo.setFile( compData[ countIndex ] );
		if( fileInfo.exists( ) == false )
			continue;
		compItem = fileInfo.absoluteFilePath( );
		if( fileInfo.isFile( ) ) {
			fileVector.emplace_back( compItem );
			continue;
		}

		for( loadDirIndex = 0; loadDirIndex < loadDirCount; loadDirIndex += 1 )
			if( compItem == loadDirData[ loadDirIndex ] )
				break;
		if( loadDirIndex < loadDirCount )
			continue;
		loadDirData[ loadDirCount ] = compItem;
		loadDirCount += 1;
	}
	if( loadDirCount != compCount ) {
		loadDirVector.resize( loadDirCount );
		loadDirData = loadDirVector.data( );
	}
	QStringList resultFile;

	for( loadDirIndex = 0; loadDirIndex < loadDirCount; loadDirIndex += 1 )
		if( PathTools::entryFilePath( resultFile, loadDirData[ loadDirIndex ] ) ) {
			compCount = fileVector.size( ); // 旧的偏移
			size_t extendCount = resultFile.size( ); // 扩张数量
			auto sourceData = resultFile.data( ); // 拷贝指针
			size_t newsize = extendCount + compCount; // 新的大小
			fileVector.resize( newsize );
			auto setData = fileVector.data( ); // 原始地址
			auto offsetPtr = setData + compCount; // 目标起始地址
			for( countIndex = 0; countIndex < extendCount; countIndex += 1 )
				offsetPtr[ countIndex ] = sourceData[ countIndex ]; // 拷贝
			resultFile.clear( ); // 清空拷贝完成的目标
		}
	loadMusciFromFileVector( fileVector );
}

std::vector< MusicItem * > & AppMusicManage::getMusicItem( std::vector< MusicItem * > &result_vector ) const {
	loadMutex->lock( );
	result_vector = musicItemvVector;
	loadMutex->unlock( );
	return result_vector;
}

bool AppMusicManage::init( ) {
	deleteResource( );
	loadMutex = new UserMutex;
	appMusicDecoder = new AppMusicDecoder;
	Init_Resource_App_Core_Ptr( appMusicDecoder );
	return true;
}

AppMusicManage::~AppMusicManage( ) {
	deleteResource( );
}

AppMusicDecoder * AppMusicManage::getAppMusicDecoder( ) const {
	return appMusicDecoder;
}
