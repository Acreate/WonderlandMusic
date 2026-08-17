#ifndef IITEMWIDTHINFO_H_H_HEAD__FILE__
#define IITEMWIDTHINFO_H_H_HEAD__FILE__

class IItemWidthInfo {
public:
	virtual ~IItemWidthInfo() = default;
	virtual int getSuggestHeight( ) const;
	virtual int getClickWidth( ) const;
	virtual int getCalculateMinWidth( ) const;
	virtual int getIntervalWidth( ) const;
	virtual int getSeparatorWidth( ) const;
	virtual int getMusicCodeWidth( ) const;
	virtual int getMusicNameWidth( ) const;
	virtual int getMusicSingerNameWidth( ) const;
	virtual int getMusicDurationTimeWidth( ) const;
	virtual int getMinItemWidth( ) const;
};

#endif // IITEMWIDTHINFO_H_H_HEAD__FILE__
