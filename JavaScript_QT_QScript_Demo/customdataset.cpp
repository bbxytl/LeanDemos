#include "customdataset.h"


CustomDataSet::CustomDataSet(QObject * parent) : NCReportDataSource( parent )
{
    setDataSourceType(Custom);
    setLocationType(Static);
    recno() =0;
}

CustomDataSet::~ CustomDataSet()
{
    m_data.clear();
}

bool CustomDataSet::open()
{
    if ( m_data.isEmpty() ) {
        error()->setError(QString("No data in CustomDataSet datasource") );
        return false;
    }
    recno() =0;
    setOpened(true);
    return true;
}

bool CustomDataSet::close()
{
    recno() =0;
    setOpened(false);
    return true;
}

bool CustomDataSet::next()
{
    return true;
    recno()++;

    if ( recno() >= m_data.count() ) {
        recno()--;
        flagEnd() = true;
        return false;
    }
    flagBegin() = false;
    return true;
}

int CustomDataSet::size() const
{
    return m_data.count();
}

bool CustomDataSet::previous()
{
    if ( recno() <= 0 ) {
        recno() = 0;
        flagBegin() = true;
        return false;
    } else {
        recno()--;
    }
    return true;
}

bool CustomDataSet::first()
{
    recno()=0;
    return true;
}

bool CustomDataSet::last()
{
    recno() = m_data.count()-1;
    return true;
}

QVariant CustomDataSet::value(const QString & column, bool* ok, int i ) const
{
    int col = columnIndexByName(column);
    if (col<0) {
        *ok = false;
        return QVariant();
    }
    return value( col, ok, i );
}

QVariant CustomDataSet::value( int column, bool*, int ) const
{
    QVariant v;
    if(column<m_data.at(recno()).size())
        v=m_data.at(recno()).at(column);
    return v;
}

bool CustomDataSet::isValid() const
{
    return true;
}

bool CustomDataSet::read(NCReportXMLReader *)
{
    return true;
}

bool CustomDataSet::write(NCReportXMLWriter *)
{
    return true;
}

void CustomDataSet::evaluate(NCReportEvaluator *)
{
}

void CustomDataSet::addData(const QList<DATA_2> &datas)
{
    foreach (DATA_2 da, datas) {
        m_data.append( da );
    }

}

void CustomDataSet::insertData(const QList<QVariant> &data, const int pos)
{
    if(pos!=-1 && pos<m_data.size())
        m_data.insert(pos,data);
    else
        m_data.append(data);
}

void CustomDataSet::insertCol(const QString &columnName, const int pos)
{
    if(pos!=-1 && pos<m_colName.size())
        m_colName.insert(pos,columnName);
    else
        m_colName.append(columnName);
}

void CustomDataSet::addCols(const QStringList &cols)
{
    foreach (QString columnName, cols) {
        m_colName.append(columnName);
    }
}

bool CustomDataSet::hasNext()
{
    return (recno()<m_data.count()-1);
}

bool CustomDataSet::seek( int index )
{
    bool ok=true;
    if ( index == -1 )
        recno() =0;
    else if ( index < m_data.count())
        recno() = index;
    else
    {
        recno() = m_data.count()-1;
        ok=false;
    }

    return ok;
}

int CustomDataSet::columnIndexByName(const QString &columnname) const
{
    for (int i=0; i<columnCount(); i++) {
        if (columnname==columnName(i))
            return i;
    }

    return -1;
}

int CustomDataSet::columnCount() const
{
    return m_colName.size();
}

QString CustomDataSet::columnName(int column) const
{
    if(column<m_colName.size())
        return m_colName.at(column);

    return QString();
}
