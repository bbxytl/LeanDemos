#ifndef AHEAD_H
#define AHEAD_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QVariantList>

#include <QFile>
#include <QHash>
#include <QTextStream>

#include <QScriptEngine>
#include <QScriptValue>
#include <QScriptValueList>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>


#include "ncreport.h"
#include "ncreportoutput.h"
#include "ncreportpreviewoutput.h"
#include "ncreportpreviewwindow.h"

#include "ncreportdef.h"
#include "ncreportdatasource.h"
#include <QtCore/private/qfsfileengine_p.h>


// 向JS引擎里注册类---模板
template <typename Tp>
QScriptValue qScriptValueFromQObject(QScriptEngine *engine, Tp const &qobject)
{
   return engine->newQObject(qobject);
}

template <typename Tp>
void qScriptValueToQObject(const QScriptValue &value, Tp &qobject)
{ qobject = qobject_cast<Tp>(value.toQObject());
}

template <typename Tp>
int qScriptRegisterQObjectMetaType(
   QScriptEngine *engine,
   const QScriptValue &prototype = QScriptValue()
   , Tp = 0
   )
{
   return qScriptRegisterMetaType<Tp>(engine, qScriptValueFromQObject,
                                      qScriptValueToQObject, prototype);
}


#endif // AHEAD_H
