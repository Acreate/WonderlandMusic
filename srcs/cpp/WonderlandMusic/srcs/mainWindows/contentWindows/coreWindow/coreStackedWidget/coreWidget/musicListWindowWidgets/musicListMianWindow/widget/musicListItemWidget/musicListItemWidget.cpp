#include "musicListItemWidget.h"

#include <QFileInfo>
#include <QLabel>
#include <QHBoxLayout>

#include <musics/musicInfo.h>

MusicListItemWidget::MusicListItemWidget( QWidget *parent, const QString &file_path, const QString &music_name, const QString &singer_name, qint64 duration_ms ) : BaseWidget( parent ),
	filePath( file_path ), musicName( music_name ), singerName( singer_name ), duration_ms( duration_ms ) {

	musicNameItem = new QLabel( music_name, this );
	musicSingerItem = new QLabel( singer_name, this );

	QDateTime dt = QDateTime::fromMSecsSinceEpoch( duration_ms );
	QString formatTime = dt.toString( "hh:mm:ss" );
	musicPlayerTimeItem = new QLabel( formatTime, this );

	auto mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( musicNameItem );
	mainLayout->addWidget( musicSingerItem );
	mainLayout->addWidget( musicPlayerTimeItem );
}
