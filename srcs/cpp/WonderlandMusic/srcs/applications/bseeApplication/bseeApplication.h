#ifndef BSEEAPPLICATION_H_H_HEAD__FILE__
#define BSEEAPPLICATION_H_H_HEAD__FILE__

#include <QApplication>
class BseeApplication : public QApplication {
	Q_OBJECT;
public:
	BseeApplication( int &argc, char **const argv, const int i = ApplicationFlags )
		: QApplication( argc, argv, i ) { }
};

#endif // BSEEAPPLICATION_H_H_HEAD__FILE__
