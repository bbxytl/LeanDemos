#ifndef FORMTEST_H
#define FORMTEST_H

#include <QMainWindow>
#include "ahead.h"

class FormTest : public QMainWindow
{
    Q_OBJECT
public:
    explicit FormTest(QWidget *parent = 0);
    ~FormTest();

    void Test();

signals:

public slots:

private:
    QAxWidget * axw;

};

#endif // FORMTEST_H
