#include "musicInfoItemWidget.h"

#include <QJsonObject>
#include <QMediaMetaData>
#include <QPainter>

#include "../application/appDataJsonKey.h"
#include "../application/appDataManage.h"
#include "../application/appDrawManage.h"
#include "../application/appInstance.h"
#include "../application/appRenderImage.h"
#include "../application/jsonKey/musicInfoItemWidgetJsonKey.h"
#include "../application/translate/musicInfoItemTranslate.h"

#include "../dateTimeFormat/dateTimeFormat.h"

#include "../tools/pathTools.h"

#include "../window/playerWindow.h"

void MusicInfoItemWidget::setItemWidth( int brfore, int after, int split, int index, int name, int singer, int duation ) {
	widgetBeforeWidth = brfore;
	widgetAfterWidth = after;
	splitWidth = split;
	indexWidth = index;
	musicNameWidth = name;
	musicSingerWidth = singer;
	musicDurationWidth = duation;
}

int MusicInfoItemWidget::getWidgetBeforeWidth( ) const {
	return widgetBeforeWidth;
}

int MusicInfoItemWidget::getWidgetAfterWidth( ) const {
	return widgetAfterWidth;
}

int MusicInfoItemWidget::getSplitWidth( ) const {
	return splitWidth;
}

int MusicInfoItemWidget::getIndexWidth( ) const {
	return indexWidth;
}

int MusicInfoItemWidget::getMusicNameWidth( ) const {
	return musicNameWidth;
}

int MusicInfoItemWidget::getMusicSingerWidth( ) const {
	return musicSingerWidth;
}

int MusicInfoItemWidget::getMusicDurationWidth( ) const {
	return musicDurationWidth;
}

MusicInfoItemWidget::MusicInfoItemWidget( ) : MusicInfoItemWidget( nullptr ) {
}

MusicInfoItemWidget::MusicInfoItemWidget( QWidget *parent ) :
	QWidget( parent ) {
	hide( );
	index = 0;
	splitWidth = musicNameWidth = musicSingerWidth = musicDurationWidth = 4;
	// 开启鼠标穿透
	setAttribute( Qt::WA_TransparentForMouseEvents, true );
}

bool MusicInfoItemWidget::renderToBuff( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto appDrawManage = appInstance->getAppDrawManage( );
	auto renderImage = appDrawManage->getAppRenderImage( );
	auto font = renderImage->getFont( );

	int offsetSplitX = splitWidth / 2;

	auto currentHeight = height( );
	auto currentWidh = width( );
	*renderBuff = QImage( currentWidh, currentHeight, QImage::Format_RGBA8888 );

	QPainter painter;
	painter.begin( renderBuff );
	auto pen = painter.pen( );
	pen.setWidth( splitWidth );
	painter.setPen( pen );
	painter.setFont( *font );

	int drawOffsetX = offsetSplitX + widgetBeforeWidth;
	QRect drawRect;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentHeight );
	drawOffsetX += offsetSplitX;
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( indexWidth, currentHeight ) );
	painter.drawText( drawRect, formatStringIndex );
	drawOffsetX += indexWidth + offsetSplitX;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentHeight );
	drawOffsetX += offsetSplitX;
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( musicNameWidth, currentHeight ) );
	painter.drawText( drawRect, musicName );
	drawOffsetX += musicNameWidth + offsetSplitX;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentHeight );
	drawOffsetX += offsetSplitX;
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( musicSingerWidth, currentHeight ) );
	painter.drawText( drawRect, musicSinger );
	drawOffsetX += musicSingerWidth + offsetSplitX;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentHeight );
	drawOffsetX += offsetSplitX;
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( musicDurationWidth, currentHeight ) );
	painter.drawText( drawRect, formatStringDuration );
	drawOffsetX += musicDurationWidth + offsetSplitX;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentHeight );

	painter.end( );
	return true;
}

bool MusicInfoItemWidget::getJsonData( QJsonObject &get_json_object ) const {
	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getAppDataManage( )->getAppDataJsonKey( );
	auto musicInfoItemJsonKey = jsonFileKey->getMusicInfoItemWidget( );
	get_json_object.insert( musicInfoItemJsonKey->getMusicInfoFile( ), musicFilePath );
	get_json_object.insert( musicInfoItemJsonKey->getMusicInfoName( ), musicName );
	get_json_object.insert( musicInfoItemJsonKey->getMusicInfoSinger( ), musicSinger );
	get_json_object.insert( musicInfoItemJsonKey->getMusicInfoDuration( ), duration );
	return true;
}

bool MusicInfoItemWidget::setJsonData( const QJsonObject &set_json_object ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getAppDataManage( )->getAppDataJsonKey( );

	auto musicInfoItemJsonKey = jsonFileKey->getMusicInfoItemWidget( );
	auto end = set_json_object.end( );
	auto find = set_json_object.find( musicInfoItemJsonKey->getMusicInfoFile( ) );
	if( end == find )
		return false;
	musicFilePath = PathTools::getAutoShortenPathName( find.value( ).toString( ) );
	find = set_json_object.find( musicInfoItemJsonKey->getMusicInfoName( ) );
	if( end == find )
		return false;
	musicName = find.value( ).toString( );
	find = set_json_object.find( musicInfoItemJsonKey->getMusicInfoSinger( ) );
	if( end == find )
		return false;
	musicSinger = find.value( ).toString( );
	find = set_json_object.find( musicInfoItemJsonKey->getMusicInfoDuration( ) );
	if( end == find )
		return false;
	duration = find.value( ).toInteger( );
	formatStringDuration = DateTimeFormat::millsecondToHourMinSecFrom( duration );

	QFileInfo info( musicFilePath );
	absFilePath = info.absoluteFilePath( );
	equFilePath = absFilePath == musicFilePath;
	renderToBuff( );
	return true;
}

void MusicInfoItemWidget::paintEvent( QPaintEvent *event ) {
	QPainter painter( this );
	painter.drawImage( 0, 0, *renderBuff );
}

bool MusicInfoItemWidget::init( const QString &music_file_path, const QString &music_name, const QString &music_singer, qint64 duration_ms ) {
	QFileInfo info( music_file_path );
	musicFilePath = PathTools::getAutoShortenPathName( music_file_path );
	absFilePath = info.absoluteFilePath( );
	musicName = music_name;
	musicSinger = music_singer;
	this->duration = duration_ms;
	this->formatStringDuration = DateTimeFormat::millsecondToHourMinSecFrom( duration_ms );
	equFilePath = absFilePath == musicFilePath;
	renderToBuff( );
	return true;
}

bool MusicInfoItemWidget::init( const QString &file_path, const QMediaMetaData &mediaMetaData ) {
	if( mediaMetaData.isEmpty( ) )
		return false;

	musicSinger = mediaMetaData.stringValue( QMediaMetaData::ContributingArtist );
	if( musicSinger.isEmpty( ) )
		musicSinger = mediaMetaData.stringValue( QMediaMetaData::AlbumArtist );
	if( musicSinger.isEmpty( ) )
		musicSinger = mediaMetaData.stringValue( QMediaMetaData::Author );
	if( musicSinger.isEmpty( ) ) {
		auto appInstance = AppInstance::getAppInstance( );
		auto appDataManage = appInstance->getAppDataManage( );
		auto appTranslate = appDataManage->getTranslate( );
		auto musicInfoItemTranslate = appTranslate->getMusicInfoItem( );
		musicSinger = musicInfoItemTranslate->getMusichumanBeingNameNone( );// 使用匿名
	}
	duration = mediaMetaData.value( QMediaMetaData::Duration ).toLongLong( );
	formatStringDuration = DateTimeFormat::millsecondToHourMinSecFrom( duration );
	musicFilePath = PathTools::getAutoShortenPathName( file_path );
	musicName = mediaMetaData.stringValue( QMediaMetaData::Title );
	if( musicName.isEmpty( ) ) {
		QFileInfo info( musicFilePath );
		musicName = info.baseName( );
	}
	QFileInfo info( file_path );
	absFilePath = info.absoluteFilePath( );
	equFilePath = absFilePath == musicFilePath;
	renderToBuff( );
	return true;
}

bool MusicInfoItemWidget::isFile( const QString &comp_file ) const {
	if( equFilePath == false )
		return musicFilePath == comp_file || absFilePath == comp_file;
	return musicFilePath == comp_file;
}

bool MusicInfoItemWidget::isFile( const MusicInfoItemWidget *comp_file ) const {
	if( comp_file == this )
		return true;
	this->isFile( comp_file->absFilePath );
	return false;
}

const QString & MusicInfoItemWidget::getMusicFilePath( ) const {
	return musicFilePath;
}

const QString & MusicInfoItemWidget::getMusicName( ) const {
	return musicName;
}

const QString & MusicInfoItemWidget::getMusicSinger( ) const {
	return musicSinger;
}

qint64 MusicInfoItemWidget::getDuration( ) const {
	return duration;
}

const QString & MusicInfoItemWidget::getFormatStringDuration( ) const {
	return formatStringDuration;
}

size_t MusicInfoItemWidget::getIndex( ) const {
	return index;
}

void MusicInfoItemWidget::setIndex( const size_t index ) {
	this->index = index;
	formatStringIndex = QString( "%1" ).arg( index, 4, 10, '0' );
}

const QString & MusicInfoItemWidget::getFormatStringIndex( ) const {
	return formatStringIndex;
}
