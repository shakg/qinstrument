#ifndef GAUGEQT_GLOBAL_H
#define GAUGEQT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GAUGEQT_LIBRARY)
#  define GAUGEQT_EXPORT Q_DECL_EXPORT
#else
#  define GAUGEQT_EXPORT Q_DECL_IMPORT
#endif

#endif // GAUGEQT_GLOBAL_H
