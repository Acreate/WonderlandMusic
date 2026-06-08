#include "bseeApplication.h"
BseeApplication::BseeApplication( int &argc, char **const argv, const int i ) : QApplication( argc, argv, i ) { }
BseeApplication::BseeApplication( int &argc, char **const argv ) : BseeApplication( argc, argv, ApplicationFlags ) {
}
