#ifndef MUSICITEMWIDTHINFO_H_H_HEAD__FILE__
#define MUSICITEMWIDTHINFO_H_H_HEAD__FILE__
#include <component/musicWindow/interface/info/iMusicItemWidthInfo.h>

class MusicItemWidthInfo : public IMusicItemWidthInfo {
private:
	int suggestHeight;
	int clickWidth;
	int intervalWidth;
	int separatorWidth;
	int musicCodeWidth;
	int musicNameWidth;
	int musicSingerNameWidth;
	int musicDurationTimeWidth;
	int minItemWidth;
	IMusicTitleWidget *musicTitleWidget = nullptr;
	MusicCentreWidget *musicCentreWidget = nullptr;

protected:
	void setClickWidth( const int click_width ) override;
	void setIntervalWidth( const int interval_width ) override;
	void setMinItemWidth( const int min_item_width ) override;
	void setMusicCodeWidth( const int music_code_width ) override;
	void setMusicDurationTimeWidth( const int music_duration_time_width ) override;
	void setMusicNameWidth( const int music_name_width ) override;
	void setMusicSingerNameWidth( const int music_singer_name_width ) override;
	void setSeparatorWidth( const int separator_width ) override;
	void setSuggestHeight( const int suggest_height ) override;

public:
	MusicItemWidthInfo( );
	~MusicItemWidthInfo( ) override;
	MusicItemWidthInfo( const MusicItemWidthInfo &other );
	MusicItemWidthInfo & operator=( const MusicItemWidthInfo &other );

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
	bool initInfo( ) override;
	IMusicTitleWidget * setMusicTitleWidget( IMusicTitleWidget *music_title_widget ) override;
	IMusicTitleWidget * getMusicTitleWidget( ) override;
	bool synchronization( ) override;
	MusicCentreWidget * getMusicCentreWidget( ) const override;
	bool isSuggestHeight( const int *width_var_ptr ) const override;
	bool isClickWidth( const int *width_var_ptr ) const override;
	bool isIntervalWidth( const int *width_var_ptr ) const override;
	bool isSeparatorWidth( const int *width_var_ptr ) const override;
	bool isMusicCodeWidth( const int *width_var_ptr ) const override;
	bool isMusicNameWidth( const int *width_var_ptr ) const override;
	bool isMusicSingerNameWidth( const int *width_var_ptr ) const override;
	bool isMusicDurationTimeWidth( const int *width_var_ptr ) const override;
	bool getPosItemWidthPtr( const int *&result_width_var_ptr, int &result_index, int x ) const override;
};

#endif // MUSICITEMWIDTHINFO_H_H_HEAD__FILE__
