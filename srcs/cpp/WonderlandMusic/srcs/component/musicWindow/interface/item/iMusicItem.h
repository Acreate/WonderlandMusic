#ifndef IMUSICITEM_H_H_HEAD__FILE__
#define IMUSICITEM_H_H_HEAD__FILE__
#include "../musicCentreWidgetChild/iMusicCentreWidgetChild.h"

class IMusicFavoriteItem;
class IMusicItemWidget;
class QImage;
class QString;

class IMusicItem : public IMusicCentreWidgetChild {
protected:
	~IMusicItem( ) override;

public:
	virtual bool setMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) = 0;
	IMusicItem( );
	virtual void setIdCode( const size_t id_code ) = 0;
	virtual void setName( const QString &name ) = 0;
	virtual void setSinger( const QString &singer ) = 0;
	virtual void setAbsoluteFilePath( const QString &absolute_file_path ) = 0;
	virtual void setElapsedTime( const qint64 elapsed_time ) = 0;
	virtual size_t getIdCode( ) const = 0;
	virtual const QString & getName( ) const = 0;
	virtual const QString & getSinger( ) const = 0;
	virtual const QString & getFilePath( ) const = 0;
	virtual const QString & getAbsoluteFilePath( ) const = 0;
	virtual const QString & getElapsedTimeString( ) const = 0;
	virtual const qint64 & getElapsedTime( ) const = 0;
	virtual IMusicItemWidget * getMusicItemWidget( ) const = 0;
	virtual IMusicFavoriteItem * getMusicFavoriteItem( ) const = 0;
	virtual const QString & getFileBaseName( ) const = 0;
};

#endif // IMUSICITEM_H_H_HEAD__FILE__
