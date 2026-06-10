#include "musicListWidget.h"

#include <QDir>
#include <QFileInfo>
#include <QMediaMetaData>
#include <QPainter>

#include "../../../../../../../msgInfo/messageErrorOut.h"

#include "../../../../../../../musics/musicInfo.h"

#include "musicListItemWidget/musicListItemWidget.h"
MusicListWidget::MusicListWidget( QWidget *parent ) : BaseWidget( parent ) {

}
bool MusicListWidget::appendItem( const QMediaMetaData &media_meta_data ) {

	auto musicName = media_meta_data.value( QMediaMetaData::Title ).toString( );
	auto singer = media_meta_data.value( QMediaMetaData::ContributingArtist ).toString( );
	auto duration_ms = media_meta_data.value( QMediaMetaData::Duration ).toLongLong( );
	//Message_Error_Out << musicName << ", " << singer << ", " << duration_ms;
	return false;
}
bool MusicListWidget::sort( ) {
	return false;
}
void MusicListWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::black );
}
