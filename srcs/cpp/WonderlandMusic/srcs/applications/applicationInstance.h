#ifndef APPLICATIONINSTANCE_H_H_HEAD__FILE__
#define APPLICATIONINSTANCE_H_H_HEAD__FILE__

#include <qjsonobject.h>
#include <qjsonparseerror.h>

#include <macro/eventMacroDefine.h>

#include "../base/bseeApplication/bseeApplication.h"

class MusicInfo;
class MusicListWidget;
class MusicCollectionWidget;
class MusicListSubMenu;
class MusicListTopMenu;
class MusicCollectionSubMenu;
class MusicCollectionTopMenu;
class QMenu;
class Render;
class ApplicationEvenTrigger;
class QFileInfo;
class QDir;
class MainWindow;
class QJsonObject;
class ApplicationInstance : public BseeApplication {
	Q_OBJECT;
private:
	static ApplicationInstance *current;
public:
	static ApplicationInstance * getApplicationInstance( );
public:
	enum class PathType {
		Music_Info
	};
	static QString formatMusicInfoPath( const QString &root_path, PathType path_type );
	static QString formatAppInfoPath( const QString &root_path );
	static QString formatTranslationPath( const QString &root_path, const QString &language = "" );
private:
	void initVar( );
	void initSupportAudioDecoderFileNameSuffix( );
	void initJson( );
	void initTranslation( );
	void initRender( );
	void initApplicationEvenTrigger( );
	void initMainWindow( );
	void initTriggerEvent( );
	void sendAppEvent( );
	void saveJsonDataToAppSettingFile( ) const;
	void saveJsonDataToAppSettingFile( const QJsonObject &write_json, const QString &wirte_file_path ) const;
	size_t readFileToJson( QJsonObject &result_json_obj, QJsonParseError &result_json_error, const QString &json_file_path );
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
		/// @brief 音频文件选择路径的起始地址
		QString music_select_file_path_start_path;
		/// @brief 音频目录选择路径的起始地址
		QString music_select_dir_path_start_path;
		/// @brief 播放列表顶部标题大小信息
		QString music_play_top_size_info;
		/// @brief 播放列表的音乐信息
		QString music_play_list_music_info;
	public:
		JSonKey( );
	} jsonKey;
protected:
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
	/// @brief app 事件
	ApplicationEvenTrigger *applicationEvenTrigger;
	/// @brief 总收藏夹菜单
	MusicCollectionTopMenu *musicCollectionTopMenu;
	/// @brief 子收藏夹菜单
	MusicCollectionSubMenu *musicCollectionSubMenu;
	/// @brief 总音乐列表菜单
	MusicListTopMenu *musicListTopMenu;
	/// @brief 子音乐列表菜单
	MusicListSubMenu *musicListSubMenu;
	/// @brief 支持音频文件的后缀名称
	QStringList supportAudioDecoderFileNameSuffix;
	/// @brief 是否退出状态
	bool isQuit;
public:
	/// @brief 获取配置的主要窗口
	/// @return 主要窗口
	virtual MainWindow * getMainWindowPtr( ) const { return mainWindowPtr; }
	virtual bool getQuitStatus( ) const { return isQuit; }
	/// @brief 设置主要窗口，未配置该项时，窗口已经显示，则不会调用 firstMainWindowShow
	/// @param main_window_ptr 配置的主要窗口
	virtual void setMainWindowPtr( MainWindow *main_window_ptr );
	virtual const QDateTime & getAppStartRunDataTime( ) const {
		return *appStartRunTime;
	}
	virtual Render * getRender( ) const { return render; }
	virtual ApplicationEvenTrigger * getApplicationEvenTrigger( ) const { return applicationEvenTrigger; }
	/// @brief 检查文件后缀是否支持解码
	/// @param music_file_path 文件路径
	/// @return false 表示不支持
	virtual bool musicFileNmaeSupperDecoder( const QString &music_file_path ) const;
private:
	/// @brief 第一次显示主要窗口时调用该函数
	/// @param first_show_main_window 调用的主要窗口
	void firstMainWindowShow( MainWindow *first_show_main_window );
};

class Event_Define_Event_Info_Type_Name( ApplicationInstance ) {
	friend class ApplicationInstance;
public:
	enum class EventType {
		Init_Music_Info_Path,
		Mouse_Leave_Pos,
		Mouse_Enter_Pos,
		Move_Global_Mouse_Pos,
		Press_Global_Mouse_Pos,
		Release_Global_Mouse_Pos,
		Press_Global_Key,
		Release_Global_Key,
		Update_Music_Widget_Width,
		Init_Music_Widget_Width,
		Init_Music_Player_Top_Width,
		Pop_Music_Collection_Top_Menu,
		Pop_Music_Collection_Sub_Menu,
		Pop_Music_List_Top_Menu,
		Pop_Music_List_Sub_Menu,
		Create_Music_Collection_Item,
		Collection_Top_Menu_Select_Over_Music_File_Path,
		Collection_Top_Menu_Select_Over_Music_Dir_Path,
		Collection_Sub_Menu_Select_Over_Music_File_Path,
		Collection_Sub_Menu_Select_Over_Music_Dir_Path,
		List_Top_Menu_Select_Over_Music_File_Path,
		List_Top_Menu_Select_Over_Music_Dir_Path,
		List_Sub_Menu_Select_Over_Music_File_Path,
		List_Sub_Menu_Select_Over_Music_Dir_Path,
	};
protected:
	EventType eventType;
	int newMusicWidgetWidth;
	QStringList inputStringList;
	QJsonObject *jsonObject;
	QString inputString;
	QObject *supervisorObject = nullptr;
private:
	ApplicationInstanceEventInfo( );
public:
	virtual ~ApplicationInstanceEventInfo( );

	/// @brief 上层对象，经过 ApplicationInstanceEventInfo 对象处理前的消息对象指针
	/// @return 对象处理前的消息对象指针
	virtual QObject * getSupervisorObject( ) const { return supervisorObject; }
	virtual EventType getEventType( ) const { return eventType; }
	virtual int getNewMusicWidgetWidth( ) const { return newMusicWidgetWidth; }
	virtual const QStringList & getInputStringList( ) const { return inputStringList; }
	virtual const QJsonObject & getJsonObject( ) const;
	virtual const QString & getInputString( ) const { return inputString; }
};
#endif // APPLICATIONINSTANCE_H_H_HEAD__FILE__
