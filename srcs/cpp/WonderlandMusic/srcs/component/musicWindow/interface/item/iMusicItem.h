#ifndef IMUSICITEM_H_H_HEAD__FILE__
#define IMUSICITEM_H_H_HEAD__FILE__
#include "../musicCentreWidgetChild/iMusicCentreWidgetChild.h"

class QImage;
class QString;

class IMusicItem : public IMusicCentreWidgetChild {
	friend class AppRenderImage;

protected:
	virtual bool setDrawBuff( QImage &image ) = 0;

public:
	IMusicItem( );
	virtual bool isLoadedOver( ) = 0;
	virtual bool getIdCode( size_t &result_id_code ) const = 0;
	virtual bool getName( QString &result_name ) const = 0;
	virtual bool getSinger( QString &result_singer ) const = 0;
	virtual bool getFilePath( QString &result_file_path ) const = 0;
	virtual bool getElapsedTime( size_t &result_elapsed_time ) const = 0;
	virtual bool getElapsedTimeString( QString &result_elapsed_time_string ) const = 0;
	virtual bool getDrawBuff( QImage &result_buff ) const = 0;
};

#endif // IMUSICITEM_H_H_HEAD__FILE__
