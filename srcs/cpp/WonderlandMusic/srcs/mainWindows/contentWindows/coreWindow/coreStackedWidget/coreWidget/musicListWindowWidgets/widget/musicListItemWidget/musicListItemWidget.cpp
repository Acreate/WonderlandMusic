#include "musicListItemWidget.h"

#include <QFileInfo>
#include <musics/musicInfo.h>
MusicListItemWidget::MusicListItemWidget( QWidget *parent, const QString &file_path ) : BaseWidget( parent ) {
	musicInfo = new MusicInfo( );
	if( musicInfo->open( file_path ) == false ) {
		delete musicInfo;
		musicInfo = nullptr;
		return;
	}

}
