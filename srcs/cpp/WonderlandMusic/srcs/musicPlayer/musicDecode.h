#ifndef MUSICDECODE_H_H_HEAD__FILE__
#define MUSICDECODE_H_H_HEAD__FILE__
#include <QObject>
#include <QAudioBuffer>

class QAudioFormat;
class QString;
class QUrl;
class QAudioDecoder;

class MusicDecode : public QObject {
	Q_OBJECT;

public:
	enum class Error {
		NoError,
		ResourceError,
		FormatError,
		AccessDeniedError,
		NotSupportedError
	};

protected:
	QAudioDecoder *audioDecoder = nullptr;
	QUrl *loadUrl = nullptr;
	std::vector< QAudioBuffer > audioBufferVector;

protected:
	virtual void deleteResource( );

public:
	~MusicDecode( ) override;

	MusicDecode( );

	virtual bool init( );

	virtual bool setSource( const QUrl &url );

	virtual bool setSource( const QString &file_path );

	virtual bool start( );

	virtual bool stop( );

	virtual bool isDecoding( );

	virtual const QUrl * getLoadUrl( ) const;

Q_SIGNALS:
	void finished_Signal( const std::vector< QAudioBuffer > &audio_buffer_vector );

	void error_Signal( Error error, const QString &error_msg );
};

#endif // MUSICDECODE_H_H_HEAD__FILE__
