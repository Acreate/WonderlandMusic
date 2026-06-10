#include "musicListWidget.h"

#include <QDir>
#include <QFileInfo>
#include <QPainter>

#include "../../../../../../../musics/musicInfo.h"

#include "musicListItemWidget/musicListItemWidget.h"
MusicListWidget::MusicListWidget( QWidget *parent ) : BaseWidget( parent ) {

}
bool MusicListWidget::appendItem( MusicInfo *music_info_ptr ) {
	if( music_info_ptr->isOpenOver( ) == false )
		return false;
	return true;
}
bool MusicListWidget::sort( ) {
	return false;
}
void MusicListWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::black );
}
