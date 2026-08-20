#ifndef MUSICITEMWIDTHINFO_H_H_HEAD__FILE__
#define MUSICITEMWIDTHINFO_H_H_HEAD__FILE__
#include "../component/musicWindow/interface/info/iMusicItemWidthInfo.h"

class MusicItemWidthInfo : public IMusicItemWidthInfo{
public:
	MusicItemWidthInfo( );
	~MusicItemWidthInfo( ) override;

protected:
	bool setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) override;

public:
	int getSuggestHeight( ) const override;
	int getClickWidth( ) const override;
	int getCalculateMinWidth( ) const override;
	int getIntervalWidth( ) const override;
	int getSeparatorWidth( ) const override;
	int getMusicCodeWidth( ) const override;
	int getMusicNameWidth( ) const override;
	int getMusicSingerNameWidth( ) const override;
	int getMusicDurationTimeWidth( ) const override;
	int getMinItemWidth( ) const override;
	bool setIMusicItemWidthInfo( const IMusicItemWidthInfo &music_item_width_info ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	bool updateInfo( ) override;
	IMusicTitleWidget * setMusicTitleWidget( IMusicTitleWidget *music_title_widget ) override;
	IMusicTitleWidget * getMusicTitleWidget( ) override;
};

#endif // MUSICITEMWIDTHINFO_H_H_HEAD__FILE__
