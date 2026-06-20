#ifndef PLAYERWIDGETTRANSLATE_H_H_HEAD__FILE__
#define PLAYERWIDGETTRANSLATE_H_H_HEAD__FILE__
#include "iTranslate.h"

class PlayerWidgetTranslate : public ITranslate {
	QString playMusic;
	QString stopMusic;
	QString pauseMusic;
	QString playListWidget;

public:
	bool init( ) override;

	virtual const QString & getPlayMusic( ) const;

	virtual const QString & getStopMusic( ) const;

	virtual const QString & getPauseMusic( ) const;

	virtual const QString & getPlayListWidget( ) const;
};
#endif // PLAYERWIDGETTRANSLATE_H_H_HEAD__FILE__
