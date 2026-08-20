#ifndef FONTTOOLS_H_H_HEAD__FILE__
#define FONTTOOLS_H_H_HEAD__FILE__

class QFontMetrics;
class QFont;

namespace FontTools {
	bool getFontHeight( int &result_height, const QFont &font );
	bool getFontHeight( int &result_height, const QFontMetrics &font_metrics );
	bool getFontHeight( int &result_height );
}

#endif // FONTTOOLS_H_H_HEAD__FILE__
