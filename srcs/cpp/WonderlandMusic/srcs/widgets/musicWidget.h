#ifndef MUSICWIDGET_H_H_HEAD__FILE__
#define MUSICWIDGET_H_H_HEAD__FILE__
#include <qwidget.h>

class MusicPlayerButtonScrollArea;
class MusicVectorInfoScrollArea;
class MusicPlayerScrollArea;
class AppFunctionScrollArea;
class QFileInfo;
class QDir;
class Music;
/// @brief 音乐播放组件
class MusicWidget : public QWidget {
	Q_OBJECT;
private:
	/// @brief 目录工具
	QDir *dirPtr;
	/// @brief 文件工具
	QFileInfo *fileInfo;
	/// @brief 所有音乐
	std::vector< Music * > musicsLoadPlanVector;
	/// @brief 显示软件功能
	AppFunctionScrollArea *appFunctionScrollArea;
	/// @brief 显示播放列表
	MusicPlayerScrollArea *musicPlayerScrollArea;
	/// @brief 显示音乐列表
	MusicVectorInfoScrollArea *musicVectorInfoScrollArea;
	/// @brief 显示播放功能
	MusicPlayerButtonScrollArea *musicPlayerButtonScrollArea;
public:
	/// @brief 创建音乐组件
	/// @param parent 父组件
	/// @param f 组件风格
	MusicWidget( QWidget *parent, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	~MusicWidget( ) override;
	/// @brief 根据路径加载音乐
	/// @param path 路径列表
	/// @return 成功加载的音乐列表
	void loadPathMusicFile( const std::vector< QString > &path );
	/// @brief 根据路径加载音乐
	/// @param path 路径
	/// @return 成功加载的音乐列表
	void loadPathMusicFile( const QString &path );
	/// @brief 检查文件是否支持
	/// @param file_name 音乐文件
	/// @return false 表示不支持
	bool isSupportedAudioCodecs( const QString &file_name ) const;
protected:
	void resizeEvent( QResizeEvent *event ) override;
};

#endif // MUSICWIDGET_H_H_HEAD__FILE__
