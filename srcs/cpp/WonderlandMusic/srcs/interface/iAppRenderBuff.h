#ifndef IAPPRENDERBUFF_H_H_HEAD__FILE__
#define IAPPRENDERBUFF_H_H_HEAD__FILE__

class QImage;

class IAppRenderBuff {
private:
	QImage *renderBuff = nullptr;

protected:
	virtual ~IAppRenderBuff( );

public:
	IAppRenderBuff( );

	virtual QImage * getRenderBuff( ) const;

	virtual bool renderToBuff( ) = 0;
};
#endif // IAPPRENDERBUFF_H_H_HEAD__FILE__
