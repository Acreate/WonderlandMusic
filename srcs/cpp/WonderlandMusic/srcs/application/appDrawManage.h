#ifndef APPDRAWMANAGE_H_H_HEAD__FILE__
#define APPDRAWMANAGE_H_H_HEAD__FILE__

#include "../interface/iAppCore.h"

class AppRenderImage;

class AppDrawManage : public IAppCore {
protected:
	/// @brief 渲染对象
	AppRenderImage *appRenderImage = nullptr;

public:
	~AppDrawManage( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool init( ) override;

	virtual AppRenderImage * getAppRenderImage( ) const;
};

#endif // APPDRAWMANAGE_H_H_HEAD__FILE__
