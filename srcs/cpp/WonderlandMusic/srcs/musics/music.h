#ifndef MUSIC_H_H_HEAD__FILE__
#define MUSIC_H_H_HEAD__FILE__
#include <qobject.h>

/// @brief 音乐类
class Music : public QObject {
	Q_OBJECT;
private:
	QString musicPath;
public:
	Music( const QString &music_path, QObject *const parent = nullptr );
};

#endif // MUSIC_H_H_HEAD__FILE__
