#ifndef MUSICITEM_H_H_HEAD__FILE__
#define MUSICITEM_H_H_HEAD__FILE__
#include "../interface/iAppJsonData.h"
class MusicInfoItemWidget;
class QMediaPlayer;

class MusicItem : public QObject, public IAppJsonData {
	Q_OBJECT;
	friend class AppMusicManage;

protected:
	/// @brief 音频信息数据，内部类，保护不被友元访问
	class Info : public IAppJsonData {
	public:
		~Info( ) override;
		bool getJsonData( QJsonObject &get_json_object ) const override;
		bool setJsonData( const QJsonObject &set_json_object ) override;

	private:
		// 允许上层类访问
		friend class MusicItem;
		MusicItem *musicItem;
		bool equFilePath;
		QString absFilePath;
		QString musicFilePath;
		QString musicName;
		QString musicSinger;
		qint64 duration;
		QString formatStringDuration;
		/// @brief 音频项，该项不由 class Info 创建，而由 class MusicItem 创建并赋予
		MusicInfoItemWidget *musicInfoItemWidget = nullptr;
		QObject *deleteErrorObj;
		virtual void setMusicInfoItemWidget( MusicInfoItemWidget *music_info_item_widget );

	protected:
		Info( const QMediaPlayer &media_player, MusicItem *music_item );
		Info( MusicItem *music_item );
		virtual bool isEquFilePath( ) const;
		virtual const QString & getAbsFilePath( ) const;
		virtual const QString & getMusicFilePath( ) const;
		virtual const QString & getMusicName( ) const;
		virtual const QString & getMusicSinger( ) const;
		virtual qint64 getDuration( ) const;
		virtual const QString & getFormatStringDuration( ) const;
		virtual MusicInfoItemWidget * getMusicInfoItemWidget( ) const;
		virtual MusicItem * getMusicItem( ) const;
	};

	Info *musicInfo;
	/* 只能被友元创建与释放 */
protected:
	~MusicItem( ) override;
	MusicItem( const QMediaPlayer &media_player );
	MusicItem( const QJsonObject &music_json_object );

public:
	static bool getJsonDataVector( QJsonObject &get_json_object, const std::vector< MusicItem * > &conver_vector );
	static bool setJsonDataVector( std::vector< MusicItem * > &result_vector, const QJsonObject &set_json_object );

public:
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	//MusicItem( const QString &music_file_path, const QString &music_name, const QString &music_singer, qint64 duration );
	virtual bool isMusicFile( const QString &music_file_path );
	virtual bool isMusicFile( const MusicItem &music_file_path );
	virtual const QString & getAbsFilePath( ) const;
	virtual const QString & getMusicFilePath( ) const;
	virtual const QString & getMusicName( ) const;
	virtual const QString & getMusicSinger( ) const;
	virtual qint64 getDuration( ) const;
	virtual const QString & getFormatStringDuration( ) const;
	virtual MusicInfoItemWidget * getMusicInfoItemWidget( ) const;
Q_SIGNALS:
	void signal_free( MusicItem *favorite_item );
};
#endif // MUSICITEM_H_H_HEAD__FILE__
