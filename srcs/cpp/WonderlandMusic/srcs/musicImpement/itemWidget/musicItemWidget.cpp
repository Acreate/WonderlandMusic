#include "musicItemWidget.h"

#include <QLabel>
#include <QPainter>
#include <qevent.h>

#include <component/musicWindow/interface/info/iMusicItemWidthInfo.h>
#include <component/musicWindow/interface/item/iMusicItem.h>
#include <component/musicWindow/interface/widget/iMusicListWidget.h>
#include <component/musicWindow/interface/widget/iMusicTitleWidget.h>

#include <head/result_message_out.h>

#include "../../component/musicWindow/interface/widget/iMusicCentreWidget.h"
MusicItemWidget::MusicItemWidget( ) {
	appendTypeInfo( this );
	hide( );
	idLabel = new QLabel( this );
	nameLabel = new QLabel( this );
	singerLabel = new QLabel( this );
	elapsedTimeLabel = new QLabel( this );
}
MusicItemWidget::~MusicItemWidget( ) {
	delete idLabel;
	delete nameLabel;
	delete singerLabel;
	delete elapsedTimeLabel;
}
bool MusicItemWidget::setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return true;
}
IMusicCentreWidget * MusicItemWidget::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
bool MusicItemWidget::updateLayout( ) {
	if( musicCentreWidget == nullptr )
		return false;
	auto musicTitleWidget = musicCentreWidget->getMusicTitleWidget( );
	if( musicTitleWidget == nullptr )
		return false;
	auto iMusicItemWidthInfo = musicTitleWidget->getIMusicItemWidthInfo( );
	if( iMusicItemWidthInfo == nullptr )
		return false;
	size_t idCode = musicItem->getIdCode( );
	QString name = musicItem->getName( );
	QString singer = musicItem->getSinger( );
	QString elapsedTimeString = musicItem->getElapsedTimeString( );
	idLabel->setText( name );
	nameLabel->setText( name );
	singerLabel->setText( name );
	elapsedTimeLabel->setText( name );

	const int calculateMinHeight = iMusicItemWidthInfo->getSuggestHeight( );

	const int separatorWidth = iMusicItemWidthInfo->getSeparatorWidth( );
	int intervalWidth = iMusicItemWidthInfo->getIntervalWidth( ) + 0 + separatorWidth;
	QString text = QString::number( idCode );
	int musicCodeWidth = iMusicItemWidthInfo->getMusicCodeWidth( );
	QRect codeRect = QRect( intervalWidth, 0, musicCodeWidth, calculateMinHeight );
	idLabel->setGeometry( codeRect );

	intervalWidth = intervalWidth + musicCodeWidth + separatorWidth;
	int musicNameWidth = iMusicItemWidthInfo->getMusicNameWidth( );
	QRect nameRect( intervalWidth, 0, musicNameWidth, calculateMinHeight );
	elapsedTimeLabel->setGeometry( nameRect );

	intervalWidth = intervalWidth + musicNameWidth + separatorWidth;
	int musicSingerNameWidth = iMusicItemWidthInfo->getMusicSingerNameWidth( );
	QRect singerRect( intervalWidth, 0, musicSingerNameWidth, calculateMinHeight );
	elapsedTimeLabel->setGeometry( singerRect );

	intervalWidth = intervalWidth + musicSingerNameWidth + separatorWidth;
	int musicDurationTimeWidth = iMusicItemWidthInfo->getMusicDurationTimeWidth( );
	QRect elapsedTimeLabelRect( intervalWidth, 0, musicDurationTimeWidth, calculateMinHeight );
	elapsedTimeLabel->setGeometry( elapsedTimeLabelRect );
	repaint( );
	return true;
}
bool MusicItemWidget::setMusicListWidget( IMusicListWidget *music_list_widget ) {
	setParent( music_list_widget->toWidget( ) );
	return true;
}
bool MusicItemWidget::bindMusicItem( IMusicItem *music_item ) {
	musicItem = music_item;
	return true;
}
void MusicItemWidget::paintEvent( QPaintEvent *event ) {
	if( musicCentreWidget == nullptr )
		return;
	auto musicTitleWidget = musicCentreWidget->getMusicTitleWidget( );
	if( musicTitleWidget == nullptr )
		return;
	auto iMusicItemWidthInfo = musicTitleWidget->getIMusicItemWidthInfo( );
	if( iMusicItemWidthInfo == nullptr )
		return;

	QPainter painter( this );
	painter.setClipRect( event->rect( ) );
	int height = this->height( );
	const int separatorWidth = iMusicItemWidthInfo->getSeparatorWidth( );
	int intervalWidth = iMusicItemWidthInfo->getIntervalWidth( );
	QColor fillSeparatorColor( 255, 255, 255, 255 );
	QRect fillRect = QRect( intervalWidth, 0, separatorWidth, height );
	painter.fillRect( fillRect, fillSeparatorColor );

	intervalWidth = intervalWidth + separatorWidth;
	int musicCodeWidth = iMusicItemWidthInfo->getMusicCodeWidth( );

	intervalWidth = intervalWidth + musicCodeWidth;
	fillRect = QRect( intervalWidth, 0, separatorWidth, height );
	painter.fillRect( fillRect, fillSeparatorColor );

	intervalWidth = intervalWidth + separatorWidth;
	int musicNameWidth = iMusicItemWidthInfo->getMusicNameWidth( );

	intervalWidth = intervalWidth + musicNameWidth;
	fillRect = QRect( intervalWidth, 0, separatorWidth, height );
	painter.fillRect( fillRect, fillSeparatorColor );

	intervalWidth = intervalWidth + separatorWidth;
	int musicSingerNameWidth = iMusicItemWidthInfo->getMusicSingerNameWidth( );

	intervalWidth = intervalWidth + musicSingerNameWidth;
	fillRect = QRect( intervalWidth, 0, separatorWidth, height );
	painter.fillRect( fillRect, fillSeparatorColor );

	intervalWidth = intervalWidth + separatorWidth;
	int musicDurationTimeWidth = iMusicItemWidthInfo->getMusicDurationTimeWidth( );

	intervalWidth = intervalWidth + musicDurationTimeWidth;
	fillRect = QRect( intervalWidth, 0, separatorWidth, height );
	painter.fillRect( fillRect, fillSeparatorColor );
}
IMusicItem * MusicItemWidget::getBindMusicItem( ) const {
	return musicItem;
}
