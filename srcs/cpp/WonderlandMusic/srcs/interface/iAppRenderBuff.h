#ifndef IAPPRENDERBUFF_H_H_HEAD__FILE__
#define IAPPRENDERBUFF_H_H_HEAD__FILE__

class QImage;

class IAppRenderBuff {
protected:
	QImage *renderBuff = nullptr;

public:
	IAppRenderBuff( );

	virtual ~IAppRenderBuff( );

	virtual const QImage * getRenderBuff( ) const;

	virtual bool renderToBuff( ) = 0;
};
#endif // IAPPRENDERBUFF_H_H_HEAD__FILE__
