#ifndef IAPPRENDERBUFF_H_H_HEAD__FILE__
#define IAPPRENDERBUFF_H_H_HEAD__FILE__

class QImage;

class IAppRenderBuff {
protected:
	QImage *renderBuff = nullptr;
	virtual ~IAppRenderBuff( );
public:
	IAppRenderBuff( );

	virtual const QImage * getRenderBuff( ) const;

	virtual bool renderToBuff( ) = 0;
};
#endif // IAPPRENDERBUFF_H_H_HEAD__FILE__
