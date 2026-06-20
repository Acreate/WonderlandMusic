#ifndef PLAYERLISTTOOLWIDGETJSONKEY_H_H_HEAD__FILE__
#define PLAYERLISTTOOLWIDGETJSONKEY_H_H_HEAD__FILE__
#include "iJsonKey.h"

class PlayerListToolWidgetJsonKey : public IJsonKey {
	/// @brief 上一曲图标
	QString thePreviousSongIconPath;
	/// @brief 播放图标
	QString controlPlayIconPath;
	/// @brief 暂停图标
	QString controlPauseIconPath;
	/// @brief 下一曲图标
	QString theNextSongIconPath;

	/// @brief 当前播放列表
	QString currentSongPlayListIconPath;

public:
	bool init( ) override;

	virtual const QString & getThePreviousSongIconPath( ) const;

	virtual const QString & getControlPlayIconPath( ) const;

	virtual const QString & getControlPauseIconPath( ) const;

	virtual const QString & getTheNextSongIconPath( ) const;

	virtual const QString & getCurrentSongPlayListIconPath( ) const;
};

#endif // PLAYERLISTTOOLWIDGETJSONKEY_H_H_HEAD__FILE__
