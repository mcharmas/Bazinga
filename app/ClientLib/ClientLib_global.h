#ifndef CLIENTLIB_GLOBAL_H
#define CLIENTLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CLIENTLIB_LIBRARY)
#  define CLIENTLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CLIENTLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#define B_SOURCE_DRIVER 0;
#define B_SOURCE_APP 1;
#define B_SOURCE_SERVER 2;

#define B_TYPE_SREQ 0;
#define B_TYPE_SACK 1;
#define B_TYPE_SDEN 2;
#define B_TYPE_CHECK 3;
#define B_TYPE_CONFIRM 4;
#define B_TYPE_UPDATE 5;
#define B_TYPE_CLOSE 6;
#define B_TYPE_OBJECT 7;
#define B_TYPE_OTHER 8;
#define B_TYPE_ERROR 9;

#endif // CLIENTLIB_GLOBAL_H
