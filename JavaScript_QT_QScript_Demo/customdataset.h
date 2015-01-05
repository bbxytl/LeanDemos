#ifndef CUSTOMDATASET_H
#define CUSTOMDATASET_H

#include "ahead.h"

typedef QList<QVariant> DATA_2;

class CustomDataSet : public NCReportDataSource
{
    Q_OBJECT
public:
    CustomDataSet( QObject *parent=0 );
    ~CustomDataSet();

    void addData(const QList<DATA_2> &datas );   //add the datas to DataSource
    void addCols(const QStringList &cols);     //add the cols to DataSource

    void insertData(const QList<QVariant> &data,const int pos=-1);   //add one data
    void insertCol(const QString &columnName,const int pos=-1);      //add one col

    bool open();
    bool close();
    bool first();
    bool last();
    bool next();
    bool previous();
    bool hasNext();
    int size() const;
    QVariant value( const QString&, bool*, int ) const;
    QVariant value( int, bool*, int ) const;
    bool read( NCReportXMLReader* );
    bool write( NCReportXMLWriter* );
    void evaluate( NCReportEvaluator* );
    bool seek( int index );
    bool isValid() const;
    int columnIndexByName(const QString& columnname) const;
    int columnCount() const;
    QString columnName(int column) const;


private:
    QList<DATA_2> m_data;        //save the all data(all Type)
    QStringList m_colName;      //save the colName of the data

};

#endif // CUSTOMDATASET_H
