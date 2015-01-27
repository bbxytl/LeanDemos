#ifndef CustomDataSet_H
#define CustomDataSet_H

#include "ahead.h"

class CustomDataSet : public NCReportDataSource
{
    Q_OBJECT
public:
    CustomDataSet( QObject *parent=0 );
    ~CustomDataSet();

    void addData(const QList<QVariantList> &datas );   //add the datas to DataSource
    void addCols(const QStringList &cols);     //add the cols to DataSource

    void insertData(const QVariantList &data,const int pos=-1);   //add one data
    void insertCol(const QString &columnName,const int pos=-1);      //add one col

    QVariant getData(const int row, const int col);
    bool modifyData(const int row, const int col, const QVariant &data=QVariant());
    bool modifyCol(const int col, const QString &data);
    bool modifyCol(const QString &colNameOld, const QString &colNameNew);

    QVariantList removeData(const int pos=-1);   //remove one data

    QList<QVariantList> * getCustomData();
    void clear();

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
    int rowCount() const;
    QString columnName(int column) const;


private:
    QList<QVariantList> m_lsVar;        //save the all data(all Type)
    QStringList m_colName;      //save the colName of the data

};

#endif // CustomDataSet_H
