#ifndef PLAYERTOOLSWIDGETTRANSLATE_H_H_HEAD__FILE__
#define PLAYERTOOLSWIDGETTRANSLATE_H_H_HEAD__FILE__
#include "iTranslate.h"

class PlayerToolsWidgetTranslate : public ITranslate {
	/// @brief 上一曲
	QString thePreviousSong;
	/// @brief 播放控制
	QString controlPlay;
	/// @brief 暂停播放
	QString controlPausa;
	/// @brief 下一曲
	QString theNextSong;
	/// @brief 当前播放列表
	QString currentPlayList;
	/// @brief 播放时间分隔
	QString playSongDateTimeSpace;

public:
	bool init( ) override;

public:
	virtual const QString & getThePreviousSong( ) const;

	virtual const QString & getControlPlay( ) const;

	virtual const QString & getControlPausa( ) const;

	virtual const QString & getTheNextSong( ) const;

	virtual const QString & getCurrentPlayList( ) const;

	virtual const QString & getPlaySongDateTimeSpace( ) const;
};

#endif // PLAYERTOOLSWIDGETTRANSLATE_H_H_HEAD__FILE__
