#ifndef APPRENDERBUFF_H_H_HEAD__FILE__
#define APPRENDERBUFF_H_H_HEAD__FILE__

class QImage;

class AppRenderBuff {
protected:
	QImage *renderBuff = nullptr;

public:
	AppRenderBuff( );

	virtual ~AppRenderBuff( );

	virtual const QImage * getRenderBuff( ) const;

	virtual bool renderToBuff( ) = 0;
};

#endif // APPRENDERBUFF_H_H_HEAD__FILE__
