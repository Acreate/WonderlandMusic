#include "pathTools.h"

#include "../applications/applicationInstance.h"
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
	auto applicationInstance = ApplicationInstance::getApplicationInstance( );
	for( index = 0; index < count; ++index )
		if( applicationInstance->musicFileNmaeSupperDecoder( foreachData[ index ] ) ) {
			resultData[ resultCount ] = foreachData[ index ];
			resultCount += 1;
		}
	result_get_path.resize( resultCount );
	return resultCount;
}
