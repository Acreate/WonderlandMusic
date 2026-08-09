#ifndef ITEMWIDTHINFO_H_H_HEAD__FILE__
#define ITEMWIDTHINFO_H_H_HEAD__FILE__

#include <interface/iAppJsonData.h>

class ItemWidthInfo : public IAppJsonData {
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

protected:
	virtual void getItemWidthInfo( int &result_interval_width, int &result_separator_width, int &result_music_code_width, int &result_music_name_width, int &result_music_singer_name_width, int &result_music_duration_time_width ) const;
	virtual void setItemWidthInfo( int interval_width, int separator_width, int music_code_width, int music_name_width, int music_singer_name_width, int music_duration_time_width );

public:
	ItemWidthInfo( );
	ItemWidthInfo( int suggest_height, int interval_width, int separator_width, int music_code_width, int music_name_width, int music_singer_name_width, int music_duration_time_width, int min_item_width );
	~ItemWidthInfo( ) override;
	virtual int getSuggestHeight( ) const;
	virtual int getClickWidth( ) const;
	virtual int getCalculateMinWidth( ) const;
	virtual int getIntervalWidth( ) const;
	virtual int getSeparatorWidth( ) const;
	virtual int getMusicCodeWidth( ) const;
	virtual int getMusicNameWidth( ) const;
	virtual int getMusicSingerNameWidth( ) const;
	virtual int getMusicDurationTimeWidth( ) const;
	virtual int getMinItemWidth( ) const;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
};

#endif // ITEMWIDTHINFO_H_H_HEAD__FILE__
