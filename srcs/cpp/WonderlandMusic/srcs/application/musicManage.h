#ifndef MUSICMANAGE_H_H_HEAD__FILE__
#define MUSICMANAGE_H_H_HEAD__FILE__
#include "appCore.h"

class MusicDecoder;

class MusicManage : public AppCore {
protected:
	/// @brief 音频解码实例
	MusicDecoder *musicDecoder = nullptr;

public:
	~MusicManage( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool init( ) override;

	virtual MusicDecoder * getMusicDecoder( ) const;
};

#endif // MUSICMANAGE_H_H_HEAD__FILE__
