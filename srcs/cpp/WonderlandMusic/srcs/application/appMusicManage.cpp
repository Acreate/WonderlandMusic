#include "appMusicManage.h"

#include <QFileInfo>

#include "appMusicDecoder.h"

#include "../tools/pathTools.h"

bool AppMusicManage::deleteResource( ) {
	disconnect( );
	loadMediaVector.clear( );
	loadFileVector.clear( );
	Delete_Resource_App_Core_Ptr( appMusicDecoder );
	return true;
}

void AppMusicManage::loadFile( const QString &music_file ) {
}

void AppMusicManage::loadMusciFromFileVector( const std::vector< QString > &music_file ) {
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

bool AppMusicManage::init( ) {
	deleteResource( );
	appMusicDecoder = new AppMusicDecoder;
	Init_Resource_App_Core_Ptr( appMusicDecoder );
	return true;
}

AppMusicDecoder * AppMusicManage::getAppMusicDecoder( ) const {
	return appMusicDecoder;
}
