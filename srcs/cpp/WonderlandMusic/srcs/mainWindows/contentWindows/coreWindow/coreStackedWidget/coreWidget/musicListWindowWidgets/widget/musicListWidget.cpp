#include "musicListWidget.h"

#include <QDir>
#include <QFileInfo>
#include <QPainter>

#include "musicListItemWidget/musicListItemWidget.h"
MusicListWidget::MusicListWidget( QWidget *parent ) : BaseWidget( parent ) {

}
std::vector< MusicListItemWidget * > MusicListWidget::appendMusicFile( const QString &file_path ) {
	std::vector< MusicListItemWidget * > result;
	QFileInfo *fileInfo = new QFileInfo( file_path );
	if( fileInfo->exists( ) == false ) {
		delete fileInfo;
		return result;
	}
	QString path = fileInfo->absoluteFilePath( );
	if( fileInfo->isDir( ) ) {
		QDir *dir = new QDir( path );
		auto stringList = dir->entryList( QDir::NoDotAndDotDot | QDir::AllEntries );
		delete fileInfo;
		delete dir;
		qsizetype count = stringList.size( );
		if( count == 0 )
			return result;
		auto data = stringList.data( );
		qsizetype index = 0;
		size_t buffIndex = 0;
		result.resize( count );
		auto destData = result.data( );
		for( ; index < count; ++index ) {
			QString filePath = path + "/" + data[ index ];
			std::vector< MusicListItemWidget * > musicListItemWidgets = appendMusicFile( filePath );
			if( musicListItemWidgets.size( ) == 0 )
				continue;
			destData[ buffIndex ] = musicListItemWidgets.data( )[ 0 ];
			buffIndex += 1;
		}
		result.resize( buffIndex );
		return result;
	}

	delete fileInfo;
	MusicListItemWidget *musicListItemWidget = new MusicListItemWidget( this, path );
	if( musicListItemWidget->getMusicInfo( ) == nullptr )
		return result;
	// 加入类成员
	musicListItemWidgets.emplace_back( musicListItemWidget );
	// 加入返回
	result.emplace_back( musicListItemWidget );
	return result;
}
std::vector< MusicListItemWidget * > MusicListWidget::appendMusicFile( const QStringList &file_path_list ) {

	std::vector< MusicListItemWidget * > result;

	qsizetype count = file_path_list.size( );
	auto data = file_path_list.data( );
	qsizetype index = 0;
	for( ; index < count; ++index ) {
		auto musicListItemWidgets = appendMusicFile( data[ index ] );
		if( musicListItemWidgets.size( ) == 0 )
			continue;
		result.append_range( musicListItemWidgets );
	}
	return result;
}
bool MusicListWidget::sort( ) {
	return false;
}
void MusicListWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::black );
}
