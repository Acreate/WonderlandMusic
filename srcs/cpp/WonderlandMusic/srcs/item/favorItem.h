#ifndef FAVORITEM_H_H_HEAD__FILE__
#define FAVORITEM_H_H_HEAD__FILE__
#include <QString>

class MusicItem;

class FavorItem {
protected:
	QString name;
	std::vector< MusicItem * > musicItemvVector;

public:
	FavorItem( const QString &name, const std::vector< MusicItem * > &music_itemv_vector );

	FavorItem( const QString &name );

	virtual ~FavorItem( );

	virtual const QString & getName( ) const;

	virtual const std::vector< MusicItem * > & getMusicItemvVector( ) const;

	virtual bool appendMusicItem( MusicItem *music_item );

	virtual std::vector< MusicItem * > findMusicName( const QString &find_name ) const;

	virtual std::vector< MusicItem * > findMusicFilePath( const QString &find_file_path ) const;

	virtual std::vector< MusicItem * > findMusicMusicSinger( const QString &music_singer ) const;
};

#endif // FAVORITEM_H_H_HEAD__FILE__
