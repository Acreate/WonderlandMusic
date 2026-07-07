#include "pathTools.h"

#include <QJsonObject>
#include <qjsondocument.h>
#include <qjsonparseerror.h>

#include "vectorTools.h"

#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appMusicDecoder.h"
#include "../application/appMusicManage.h"
#include "../application/applicationManage.h"

#include "../msgInfo/messageErrorOut.h"

qsizetype PathTools::filterFile( QStringList &result_get_path, const std::vector< QString > &entry_path ) {
	qsizetype resultDataIndex = 0;
	QFileInfo info;
	auto count = entry_path.size( );
	if( count == 0 )
		return resultDataIndex;
	auto data = entry_path.data( );
	auto resultData = result_get_path.data( );
	decltype(count) index = 0;
	for( ; index < count; ++index )
		if( info.setFile( data[ index ] ), info.isFile( ) )
			resultData[ resultDataIndex++ ];
	result_get_path.resize( resultDataIndex );
	return resultDataIndex;
}

qsizetype PathTools::filterDir( QStringList &result_get_path, const std::vector< QString > &entry_path ) {
	qsizetype resultDataIndex = 0;
	QFileInfo info;
	auto count = entry_path.size( );
	if( count == 0 )
		return resultDataIndex;
	auto data = entry_path.data( );
	auto resultData = result_get_path.data( );
	decltype(count) index = 0;
	for( ; index < count; ++index )
		if( info.setFile( data[ index ] ), info.isDir( ) )
			resultData[ resultDataIndex++ ];
	result_get_path.resize( resultDataIndex );
	return resultDataIndex;
}

QString PathTools::getAutoShortenPathName( const QString &org_file_path ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationFilePath = appInstance->getApplicationManage(  )->applicationDirPath( );
	QDir base( applicationFilePath );

	QString result = base.relativeFilePath( org_file_path );
	if( result == "." )
		return "./";
	if( result.startsWith( "../" ) == false )
		return "./" + result; // 不存在上级路径
	QFileInfo info( org_file_path );
	return info.absoluteFilePath( ); // 使用绝对路径
}

qsizetype PathTools::filterMusicFile( QStringList &result_get_path, const std::vector< QString > &entry_path ) {
	auto count = entry_path.size( );
	decltype(count) index;
	qsizetype resultCount = 0;
	if( count == 0 )
		return resultCount;
	result_get_path.resize( count );
	auto resultData = result_get_path.data( );
	auto foreachData = entry_path.data( );
	auto applicationInstance = AppInstance::getAppInstance( );
	auto musicDecoder = applicationInstance->getAppDataManage( )->getAppMusicManage( )->getAppMusicDecoder( );
	for( index = 0; index < count; ++index )
		if( musicDecoder->musicFileNmaeSupperDecoder( foreachData[ index ] ) ) {
			resultData[ resultCount ] = foreachData[ index ];
			resultCount += 1;
		}
	result_get_path.resize( resultCount );
	return resultCount;
}

qsizetype PathTools::filterFile( QStringList &result_get_path, const QStringList &entry_path ) {
	qsizetype resultDataIndex = 0;
	QFileInfo info;
	qsizetype count = entry_path.size( );
	if( count == 0 )
		return resultDataIndex;
	auto data = entry_path.data( );
	auto resultData = result_get_path.data( );
	qsizetype index = 0;
	for( ; index < count; ++index )
		if( info.setFile( data[ index ] ), info.isFile( ) )
			resultData[ resultDataIndex++ ];
	result_get_path.resize( resultDataIndex );
	return resultDataIndex;
}

qsizetype PathTools::filterDir( QStringList &result_get_path, const QStringList &entry_path ) {
	qsizetype resultDataIndex = 0;
	QFileInfo info;
	qsizetype count = entry_path.size( );
	if( count == 0 )
		return resultDataIndex;
	auto data = entry_path.data( );
	auto resultData = result_get_path.data( );
	qsizetype index = 0;
	for( ; index < count; ++index )
		if( info.setFile( data[ index ] ), info.isDir( ) )
			resultData[ resultDataIndex++ ];
	result_get_path.resize( resultDataIndex );
	return resultDataIndex;
}

qsizetype PathTools::filterMusicFile( QStringList &result_get_path, const QStringList &entry_path ) {
	qsizetype count = entry_path.size( );
	qsizetype index;
	qsizetype resultCount = 0;
	if( count == 0 )
		return resultCount;
	result_get_path.resize( count );
	auto resultData = result_get_path.data( );
	auto foreachData = entry_path.data( );
	auto applicationInstance = AppInstance::getAppInstance( );
	auto musicDecoder = applicationInstance->getAppDataManage( )->getAppMusicManage( )->getAppMusicDecoder( );
	for( index = 0; index < count; ++index )
		if( musicDecoder->musicFileNmaeSupperDecoder( foreachData[ index ] ) ) {
			resultData[ resultCount ] = foreachData[ index ];
			resultCount += 1;
		}
	result_get_path.resize( resultCount );
	return resultCount;
}

bool PathTools::readJsonObject( QJsonObject &result_json_object, const QString &json_file_path ) {
	// 查看是否存在
	QFileInfo info( json_file_path );
	if( info.exists( ) == false )
		return false;
	// 读取文件
	QFile readJson( json_file_path );
	if( readJson.open( QIODeviceBase::ReadOnly ) == false )
		return false;
	auto jsonFileAllData = readJson.readAll( );

	QJsonParseError jsonParseError;
	// 转化文件
	auto fromFileDataToDoc = QJsonDocument::fromJson( jsonFileAllData, &jsonParseError );
	if( jsonParseError.error != QJsonParseError::ParseError::NoError )
		return false;
	// 转换对象
	result_json_object = fromFileDataToDoc.object( );

	return true;
}

bool PathTools::writeJsonObject( const QJsonObject &write_json_object, const QString &json_file_path ) {
	QFileInfo info( json_file_path );
	if( info.exists( ) == false ) {
		QDir dir = info.dir( );
		auto absolutePathDir = dir.absolutePath( );
		if( dir.exists( absolutePathDir ) == false )
			if( dir.mkdir( absolutePathDir ) == false )
				return false;
	}
	QFile file( json_file_path );
	if( file.open( QIODeviceBase::WriteOnly ) == false )
		return false;
	QJsonDocument writeJsonDocument( write_json_object );
	auto byteArray = writeJsonDocument.toJson( );
	file.write( byteArray );
	return true;
}

#include <QFile>
#include <QDataStream>
#include <QByteArray>

// WAV头部结构体 44字节
struct WavHeader {
	// RIFF Chunk
	char riffId[ 4 ] = { 'R', 'I', 'F', 'F' };
	quint32 fileSize;       // 文件总长度 - 8
	char waveId[ 4 ] = { 'W', 'A', 'V', 'E' };

	// fmt Chunk
	char fmtId[ 4 ] = { 'f', 'm', 't', ' ' };
	quint32 fmtSize = 16;
	quint16 audioFormat = 1; // 1=PCM
	quint16 channels;        // 声道数
	quint32 sampleRate;      // 采样率
	quint32 byteRate;        // 采样率 * 通道 * 位深度/8
	quint16 blockAlign;      // 通道 * 位深度/8
	quint16 bitsPerSample;   // 16 / 8 / 32

	// data Chunk
	char dataId[ 4 ] = { 'd', 'a', 't', 'a' };
	quint32 dataSize;        // PCM数据字节长度
};

/**
 * @brief 将PCM 16bit数据写入wav文件
 * @param filePath 输出路径
 * @param pcmData 原始s16 PCM二进制数据
 * @param sampleRate 采样率
 * @param channels 声道 1/2
 * @return 成功true
 */
bool writeWavFile( const QString &filePath, const QByteArray &pcmData,
					int sampleRate = 44100, int channels = 2 ) {
	QFile file( filePath );
	if( !file.open( QIODevice::WriteOnly ) )
		return false;

	WavHeader header;
	header.channels = channels;
	header.sampleRate = sampleRate;
	header.bitsPerSample = 16;

	header.blockAlign = channels * header.bitsPerSample / 8;
	header.byteRate = sampleRate * header.blockAlign;
	header.dataSize = pcmData.size( );
	header.fileSize = 36 + header.dataSize; // 44-8=36

	QDataStream stream( &file );
	stream.setByteOrder( QDataStream::LittleEndian ); // WAV小端存储

	// 写入RIFF ID
	stream.writeRawData( header.riffId, 4 );
	stream << header.fileSize;
	stream.writeRawData( header.waveId, 4 );

	// fmt块
	stream.writeRawData( header.fmtId, 4 );
	stream << header.fmtSize;
	stream << header.audioFormat;
	stream << header.channels;
	stream << header.sampleRate;
	stream << header.byteRate;
	stream << header.blockAlign;
	stream << header.bitsPerSample;

	// data块
	stream.writeRawData( header.dataId, 4 );
	stream << header.dataSize;

	// 写入PCM音频数据
	file.write( pcmData );

	file.close( );
	return true;
}

bool PathTools::wirteWavFile( const QString &wirte_file_path, const std::vector< char > &wirte_pcm_vector_data ) {
	QByteArray pcm( wirte_pcm_vector_data.data( ), wirte_pcm_vector_data.size( ) );
	return writeWavFile( wirte_file_path, pcm );
}

bool PathTools::wirteWavFile( const QString &wirte_file_path, const std::vector< QAudioBuffer > &wirte_pcm_vector_data ) {
	auto data = wirte_pcm_vector_data.data( );
	size_t count = wirte_pcm_vector_data.size( );
	size_t index = 0;
	QByteArray pcm;
	auto audioFormat = data[ index ].format( );
	int channelCount = audioFormat.channelCount( );
	int sampleRate = audioFormat.sampleRate( );
	for( ; index < count; index += 1 )
		pcm.append( data[ index ].data< char >( ), data[ index ].byteCount( ) );
	return writeWavFile( wirte_file_path, pcm, sampleRate, channelCount );
}

bool PathTools::entryFilePath( QStringList &result_file_path, const QString &entry_path ) {
	QFileInfo info( entry_path );
	if( info.exists( ) == false )
		return false;
	QString absoluteFilePath = info.absoluteFilePath( );
	result_file_path.append( absoluteFilePath );
	if( info.isFile( ) )
		return true;
	QDir dir( absoluteFilePath );
	auto entryList = dir.entryInfoList( QDir::AllEntries | QDir::NoDotAndDotDot );
	qsizetype count = entryList.size( );
	if( count == 0 )
		return true;
	auto data = entryList.data( );
	qsizetype index = 0;
	for( ; index < count; index += 1 )
		if( data[ index ].isDir( ) ) {
			QStringList subList;
			entryFilePath( subList, data[ index ].absoluteFilePath( ) );
			result_file_path.append( subList );
		} else
			result_file_path.append( data[ index ].absoluteFilePath( ) );

	return true;
}

bool PathTools::entryFilePath( QStringList &result_file_path, const std::vector< QString > &entry_path_list ) {
	size_t count = entry_path_list.size( );

	if( count == 0 )
		return false;
	auto data = entry_path_list.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		entryFilePath( result_file_path, data[ index ] );

	return true;
}

bool PathTools::entryFinalPath( QStringList &result_final_path, const QString &entry_path ) {
	QFileInfo info( entry_path );
	if( info.exists( ) == false )
		return false;
	QString absoluteFilePath = info.absoluteFilePath( );
	if( info.isFile( ) ) {
		result_final_path.append( absoluteFilePath );
		return true;
	}
	QDir dir( absoluteFilePath );
	auto entryList = dir.entryInfoList( QDir::AllEntries | QDir::NoDotAndDotDot, QDir::DirsFirst );
	qsizetype count = entryList.size( );
	if( count == 0 ) {
		result_final_path.append( absoluteFilePath );
		return true;
	}
	auto data = entryList.data( );
	qsizetype index = 0;

	for( ; index < count; index += 1 )
		if( data[ index ].isDir( ) ) {
			QStringList subList;
			entryFinalPath( subList, data[ index ].absoluteFilePath( ) );
			result_final_path.append( subList );
		} else
			result_final_path.append( data[ index ].absoluteFilePath( ) );
	return true;
}

bool PathTools::copyPath( const QString &source_path, const QString &destination_path ) {
	QStringList resultFinal;
	if( entryFinalPath( resultFinal, source_path ) == false )
		return false;
	QFileInfo info( source_path );

	auto sourceAbsoluteFilePath = info.absoluteFilePath( );
	info.setFile( destination_path );
	auto destinationAbsoluteFilePath = info.absoluteFilePath( );
	auto removeFileError = QObject::tr( "文件删除失败" );
	if( info.exists( ) && info.isFile( ) )
		if( QFile::remove( destinationAbsoluteFilePath ) == false ) {
			Message_Error_Out << removeFileError + " : " << destinationAbsoluteFilePath;
			return false;
		}
	qsizetype sourceHomePathSize = sourceAbsoluteFilePath.size( );
	qsizetype sourceCount = resultFinal.size( );
	auto sourceData = resultFinal.data( );
	qsizetype index = 0;
	auto makeDirError = QObject::tr( "创建目录失败" );
	auto copyFileError = QObject::tr( "文件拷贝失败" );
	for( ; index < sourceCount; index += 1 ) {
		QString sourceFile = sourceData[ index ];
		sourceAbsoluteFilePath = destinationAbsoluteFilePath + "/" + sourceFile.mid( sourceHomePathSize );
		info.setFile( sourceFile );
		if( info.isDir( ) ) {
			QDir dir;
			if( dir.mkpath( sourceAbsoluteFilePath ) == false )
				Message_Error_Out << makeDirError + " : " << sourceAbsoluteFilePath;
		} else {
			// 覆盖目标文件
			if( QFile::exists( sourceAbsoluteFilePath ) )
				if( QFile::remove( sourceAbsoluteFilePath ) == false ) {
					Message_Error_Out << removeFileError + " : " << sourceAbsoluteFilePath;
					continue;
				}
			info.setFile( sourceAbsoluteFilePath );
			auto dir = info.dir( );
			if( dir.exists( ) == false ) {
				auto dirPath = info.absolutePath( );
				if( dir.mkpath( dirPath ) == false ) {
					Message_Error_Out << makeDirError + " : " << dirPath;
					continue;
				}
			}
			if( QFile::copy( sourceFile, sourceAbsoluteFilePath ) == false ) {
				Message_Error_Out << copyFileError + " : " << sourceFile << " => " << sourceAbsoluteFilePath;
				continue;
			}
		}
	}
	return true;
}
