#ifndef APPLICATIONINSTANCE_H_H_HEAD__FILE__
#define APPLICATIONINSTANCE_H_H_HEAD__FILE__

#include <QApplication>
#include <macro/eventMacroDefine.h>
class ControlMusicListMenu;
class ControlCollectionMenu;
class QMenu;
class Render;
class ApplicationEvenTrigger;
class QFileInfo;
class QDir;
class MainWindow;
class QJsonObject;
class ApplicationInstance : public QApplication {
	Q_OBJECT;
private:
	static ApplicationInstance *current;
public:
	static ApplicationInstance * getApplicationInstance( );
private:
	void initVar( );
	void initJson( );
	void initTranslation( );
	void initRender( );
	void initApplicationEvenTrigger( );
	void initMainWindow( );
	void initTriggerEvent( );
	void sendAppEvent( );
	void saveJsonDataToAppSettingFile( ) const;
public:
	ApplicationInstance( int &argc, char **const argv, const int i = ApplicationFlags );
	~ApplicationInstance( ) override;
	bool notify( QObject *object, QEvent *event ) override;
protected:
	bool event( QEvent * ) override;
private:
	class Translate {
		friend class ApplicationInstance;
		/// @brief 创建目录错误
		QString createDirError;
		/// @brief 打开文件错误
		QString openFileError;
		/// @brief 打开语言文件失败
		QString loadQTranslatorFile;
		/// @brief 加载语言文件打软件失败
		QString loadQTranslatorApp;
	public:
		Translate( );
	} *translate;
	class JSonKey {
		friend class ApplicationInstance;
		/// @brief 语言文件关键字
		QString app_QTranslator_path_key;
		/// @brief 主窗口横向关键字
		QString main_window_x_key;
		/// @brief 主窗口纵向关键字
		QString main_window_y_key;
		/// @brief 主窗口宽度关键字
		QString main_window_h_key;
		/// @brief 主窗口高度关键字
		QString main_window_w_key;
		/// @brief 软件音乐信息保存路径
		QString app_music_info_file_path;
		/// @brief 播放列表的收藏宽度
		QString app_music_collection_main_widget_width;
	public:
		JSonKey( );
	} jsonKey;
private:
	/// @brief 语言
	QTranslator *qTranslator;
	/// @brief 主要先显示的窗口
	MainWindow *mainWindowPtr;
	/// @brief 是否第一次显示
	bool firstShow;
	/// @brief 软件配置
	QJsonObject *appSetting;
	/// @brief 软件配置路径
	QString appSettingPath;
	/// @brief 目录工具
	QDir *qDirTool;
	/// @brief 路径工具
	QFileInfo *fileInfoTool;
	/// @brief 软件启动时间
	QDateTime *appStartRunTime;
	Render *render;
	ApplicationEvenTrigger *applicationEvenTrigger;
	/// @brief 收藏夹菜单
	ControlCollectionMenu *controlCollectionMenu;
	/// @brief 音乐菜单
	ControlMusicListMenu *controlMusicListMenu;
public:
	/// @brief 获取配置的主要窗口
	/// @return 主要窗口
	virtual MainWindow * getMainWindowPtr( ) const { return mainWindowPtr; }
	/// @brief 设置主要窗口，未配置该项时，窗口已经显示，则不会调用 firstMainWindowShow
	/// @param main_window_ptr 配置的主要窗口
	virtual void setMainWindowPtr( MainWindow *main_window_ptr );
	virtual const QDateTime & getAppStartRunDataTime( ) const {
		return *appStartRunTime;
	}
	virtual Render * getRender( ) const { return render; }
	virtual ApplicationEvenTrigger * getApplicationEvenTrigger( ) const { return applicationEvenTrigger; }
private:
	/// @brief 第一次显示主要窗口时调用该函数
	/// @param first_show_main_window 调用的主要窗口
	void firstMainWindowShow( MainWindow *first_show_main_window );
};

class Event_Default_Event_Info_Type_Name( ApplicationInstance ) {
public:
	enum class EventType {
		None,
		Load_Music_Info_Path_Text,
		Move_Global_Mouse_Pos,
		Press_Global_Mouse_Pos,
		Release_Global_Mouse_Pos,
		Update_Music_Widget_Width,
		Init_Music_Widget_Width
	};
protected:
	EventType eventType;
	QString loadMusicInfoPath;
	int newMusicWidgetWidth;
public:
	virtual ~ApplicationInstanceEventInfo( ) = default;
	ApplicationInstanceEventInfo( const EventType event_type )
		: eventType( event_type ) { }
	ApplicationInstanceEventInfo( )
		: eventType( EventType::None ) { }
	ApplicationInstanceEventInfo( const EventType event_type, const QString &load_music_info_path )
		: eventType( event_type ),
		loadMusicInfoPath( load_music_info_path ) { }
	ApplicationInstanceEventInfo( const EventType event_type, const int new_music_widget_width )
		: eventType( event_type ),
		newMusicWidgetWidth( new_music_widget_width ) { }
	virtual EventType getEventType( ) const { return eventType; }
	virtual const QString & getLoadMusicInofPath( ) const {
		return loadMusicInfoPath;
	}
	virtual int getNewMusicWidgetWidth( ) const { return newMusicWidgetWidth; }
};
#endif // APPLICATIONINSTANCE_H_H_HEAD__FILE__
