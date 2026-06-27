#include "pathTools.h"

#include <QJsonObject>
#include <qjsondocument.h>
#include <qjsonparseerror.h>

#include "../application/appInstance.h"
#include "../application/musicDecoder.h"

#include "../msgInfo/messageErrorOut.h"

namespace entryList {
	namespace sort {
		inline bool entryList( QStringList &result_get_path, const QString &entry_path, QDir::Filters filters, QDir::SortFlags sort ) {
			QFileInfo fileInfo( entry_path );
			if( fileInfo.exists( ) == false )
				return false;
			QString absFilePath = fileInfo.absoluteFilePath( );
			if( fileInfo.isFile( ) ) {
				result_get_path = { absFilePath };
				return true;
			}
			QDir dir( absFilePath );
			result_get_path = dir.entryList( filters, sort );
			qint64 entryCount = result_get_path.size( );
			if( entryCount == 0 )
				return false;
			auto data = result_get_path.data( );
			qint64 index = 0;
			for( ; index < entryCount; ++index )
				data[ index ] = absFilePath + "/" + data[ index ];
			return true;
		}
	}

	namespace inDir {
		inline bool entryList( QStringList &result_get_path, const QString &entry_path, bool foreach_in_dir_path, QDir::Filters filters ) {
			QFileInfo fileInfo( entry_path );
			if( fileInfo.exists( ) == false )
				return false;
			QString absFilePath = fileInfo.absoluteFilePath( );
			if( fileInfo.isFile( ) ) {
				result_get_path = { absFilePath };
				return true;
			}
			QDir dir( absFilePath );
			result_get_path = dir.entryList( filters );
			qint64 entryCount = result_get_path.size( );
			if( entryCount == 0 )
				return false;
			auto data = result_get_path.data( );
			qint64 index = 0;

			if( foreach_in_dir_path ) {
				QStringList appendList;
				QStringList subResult;
				for( ; index < entryCount; ++index ) {
					data[ index ] = absFilePath + "/" + data[ index ];

					fileInfo.setFile( data[ index ] );
					if( fileInfo.isFile( ) )
						continue;
					if( entryList( subResult, data[ index ], foreach_in_dir_path, filters ) == false )
						continue;
					appendList.append( subResult );
				}
				result_get_path.append( appendList );
			} else
				for( ; index < entryCount; ++index )
					data[ index ] = absFilePath + "/" + data[ index ];
			return true;
		}
	}
}

bool PathTools::entryList( QStringList &result_get_path, const QString &entry_path, bool foreach_in_dir_path, QDir::Filters filters ) {
	return ::entryList::inDir::entryList( result_get_path, entry_path, foreach_in_dir_path, filters );
}

bool PathTools::entryList( QStringList &result_get_path, const QString &entry_path, bool foreach_in_dir_path ) {
	return ::entryList::inDir::entryList( result_get_path, entry_path, foreach_in_dir_path, QDir::NoDotAndDotDot | QDir::AllEntries | QDir::NoSymLinks );
}

bool PathTools::entryList( QStringList &result_get_path, const QString &entry_path, QDir::Filters filters, QDir::SortFlags sort ) {
	return ::entryList::sort::entryList( result_get_path, entry_path, filters, sort );
}

bool PathTools::entryList( QStringList &result_get_path, const QString &entry_path, QDir::Filters filters ) {
	return ::entryList::sort::entryList( result_get_path, entry_path, filters, QDir::NoSort );
}

bool PathTools::entryList( QStringList &result_get_path, const QString &entry_path ) {
	return ::entryList::sort::entryList( result_get_path, entry_path, QDir::NoDotAndDotDot | QDir::AllEntries | QDir::NoSymLinks, QDir::NoSort );
}

bool PathTools::entryList( QStringList &result_get_path, const QStringList &entry_path, bool foreach_in_dir_path, QDir::Filters filters ) {
	qsizetype count = entry_path.size( );
	if( count == 0 )
		return false;
	QStringList entryResult;
	result_get_path.clear( );
	auto data = entry_path.data( );
	qsizetype index = 0;
	for( ; index < count; ++index )
		if( ::entryList::inDir::entryList( entryResult, data[ index ], foreach_in_dir_path, filters ) )
			result_get_path.append( entryResult );
	return result_get_path.size( );
}

bool PathTools::entryList( QStringList &result_get_path, const QStringList &entry_path, bool foreach_in_dir_path ) {
	return entryList( result_get_path, entry_path, foreach_in_dir_path, QDir::AllEntries | QDir::NoDotAndDotDot | QDir::NoSymLinks );
}

bool PathTools::entryList( QStringList &result_get_path, const QStringList &entry_path, QDir::Filters filters ) {
	qsizetype count = entry_path.size( );
	if( count == 0 )
		return false;
	QStringList entryResult;
	result_get_path.clear( );
	auto data = entry_path.data( );
	qsizetype index = 0;
	for( ; index < count; ++index )
		if( ::entryList::sort::entryList( entryResult, data[ index ], filters, QDir::NoSort ) )
			result_get_path.append( entryResult );
	return result_get_path.size( );
}

bool PathTools::entryList( QStringList &result_get_path, const QStringList &entry_path ) {
	return entryList( result_get_path, entry_path, QDir::AllEntries | QDir::NoDotAndDotDot | QDir::NoSymLinks );
}

bool PathTools::entryList( QStringList &result_get_path, const std::vector< QString > &entry_path, bool foreach_in_dir_path, QDir::Filters filters ) {
	auto count = entry_path.size( );
	if( count == 0 )
		return false;
	QStringList entryResult;
	result_get_path.clear( );
	auto data = entry_path.data( );
	decltype(count) index = 0;
	for( ; index < count; ++index )
		if( ::entryList::inDir::entryList( entryResult, data[ index ], foreach_in_dir_path, filters ) )
			result_get_path.append( entryResult );
	return result_get_path.size( );
}

bool PathTools::entryList( QStringList &result_get_path, const std::vector< QString > &entry_path, bool foreach_in_dir_path ) {
	return entryList( result_get_path, entry_path, foreach_in_dir_path, QDir::AllEntries | QDir::NoDotAndDotDot | QDir::NoSymLinks );
}

bool PathTools::entryList( QStringList &result_get_path, const std::vector< QString > &entry_path, QDir::Filters filters ) {
	auto count = entry_path.size( );
	if( count == 0 )
		return false;
	QStringList entryResult;
	result_get_path.clear( );
	auto data = entry_path.data( );
	decltype(count) index = 0;
	for( ; index < count; ++index )
		if( ::entryList::sort::entryList( entryResult, data[ index ], filters, QDir::NoSort ) )
			result_get_path.append( entryResult );
	return result_get_path.size( );
}

bool PathTools::entryList( QStringList &result_get_path, const std::vector< QString > &entry_path ) {
	return entryList( result_get_path, entry_path, QDir::AllEntries | QDir::NoDotAndDotDot | QDir::NoSymLinks );
}

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
	auto applicationFilePath = appInstance->applicationDirPath( );
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
	auto musicDecoder = applicationInstance->getMusicDecoder( );
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
	auto musicDecoder = applicationInstance->getMusicDecoder( );
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

bool PathTools::writeJsonObject( const QJsonObject &result_json_object, const QString &json_file_path ) {
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
	QJsonDocument writeJsonDocument( result_json_object );
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
