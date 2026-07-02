#ifndef ITRANSLATE_H_H_HEAD__FILE__
#define ITRANSLATE_H_H_HEAD__FILE__

#include "../appCore.h"
#include <QString>
#include <QObject>

class ITranslate : public AppCore {
protected:
	bool deleteResource( ) override;
};

#endif // ITRANSLATE_H_H_HEAD__FILE__
