#ifndef MUSICITEMWIDTHINFO_H_H_HEAD__FILE__
#define MUSICITEMWIDTHINFO_H_H_HEAD__FILE__
#include "../component/musicWindow/interface/info/iMusicItemWidthInfo.h"

class MusicItemWidthInfo : public IMusicItemWidthInfo {
protected:
	int suggestHeight;
	int clickWidth;
	int intervalWidth;
	int separatorWidth;
	int musicCodeWidth;
	int musicNameWidth;
	int musicSingerNameWidth;
	int musicDurationTimeWidth;
	int minItemWidth;

public:
	MusicItemWidthInfo( );
	~MusicItemWidthInfo( ) override;
	MusicItemWidthInfo( const MusicItemWidthInfo &other );
	MusicItemWidthInfo & operator=( const MusicItemWidthInfo &other );
	virtual void setSuggestHeight( const int suggest_height );
	virtual void setClickWidth( const int click_width );
	virtual void setIntervalWidth( const int interval_width );
	virtual void setSeparatorWidth( const int separator_width );
	virtual void setMusicCodeWidth( const int music_code_width );
	virtual void setMusicNameWidth( const int music_name_width );
	virtual void setMusicSingerNameWidth( const int music_singer_name_width );
	virtual void setMusicDurationTimeWidth( const int music_duration_time_width );
	virtual void setMinItemWidth( const int min_item_width );

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
