#ifndef APPDRAWMANAGE_H_H_HEAD__FILE__
#define APPDRAWMANAGE_H_H_HEAD__FILE__
#include "appCore.h"

class RenderImage;

class AppDrawManage : public AppCore {
protected:
	/// @brief 渲染对象
	RenderImage *renderImage = nullptr;

public:
	~AppDrawManage( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool init( ) override;

	virtual RenderImage * getRenderImage( ) const;
};

#endif // APPDRAWMANAGE_H_H_HEAD__FILE__
