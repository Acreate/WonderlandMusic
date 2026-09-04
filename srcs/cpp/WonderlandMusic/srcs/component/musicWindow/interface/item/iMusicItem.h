#ifndef IMUSICITEM_H_H_HEAD__FILE__
#define IMUSICITEM_H_H_HEAD__FILE__
#include "../musicCentreWidgetChild/iMusicCentreWidgetChild.h"

class IMusicItemWidget;
class QImage;
class QString;

class IMusicItem : public IMusicCentreWidgetChild {
	friend class IMusicFavoriteItem;

protected:
	static bool binMusicItemWidget( IMusicItemWidget *bind_target, IMusicItem *bind_source );
	virtual bool setMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) = 0;
	~IMusicItem( ) override {
	}

public:
	IMusicItem( );
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
