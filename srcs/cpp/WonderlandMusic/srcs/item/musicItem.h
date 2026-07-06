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
		bool equFilePath;
		QString absFilePath;
		QString musicFilePath;
		QString musicName;
		QString musicSinger;
		qint64 duration;
		QString formatStringDuration;

	protected:
		Info( const QJsonObject &music_json_object );

		Info( const QMediaPlayer &media_player );

		virtual bool isEquFilePath( ) const;

		virtual const QString & getAbsFilePath( ) const;

		virtual const QString & getMusicFilePath( ) const;

		virtual const QString & getMusicName( ) const;

		virtual const QString & getMusicSinger( ) const;

		virtual qint64 getDuration( ) const;

		virtual const QString & getFormatStringDuration( ) const;
	};

	MusicInfoItemWidget *musicInfoItemWidget;
	Info musicInfo;
	/* 只能被友元创建与释放 */
protected:
	~MusicItem( ) override;

	MusicItem( const QMediaPlayer &media_player );

	MusicItem( const QJsonObject &music_json_object );

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
};

#endif // MUSICITEM_H_H_HEAD__FILE__
