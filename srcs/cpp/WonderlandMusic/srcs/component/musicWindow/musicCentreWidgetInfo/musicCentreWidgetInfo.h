#ifndef MUSICCENTREWIDGETINFO_H_H_HEAD__FILE__
#define MUSICCENTREWIDGETINFO_H_H_HEAD__FILE__

#include <interface/iAppDiskJsonData.h>

class MusicCentreWidgetInfo : public IAppDiskJsonData {
	friend class MusicCentreWidget;
	int favoriteWidgetWidth;
	int toolWidgetWidth;
	int titleWidgetWidth;

public:
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;

	bool readJsonData( ) override;
	bool writeJsonData( ) override;

	virtual int getFavoriteWidgetWidth( ) const;
	virtual int getToolWidgetWidth( ) const;
	virtual int getTitleWidgetWidth( ) const;
};

#endif // MUSICCENTREWIDGETINFO_H_H_HEAD__FILE__
