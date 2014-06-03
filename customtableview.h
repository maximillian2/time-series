#ifndef CUSTOMTABLEVIEW_H
#define CUSTOMTABLEVIEW_H

#include <QTableView>
#include "seriesReader.h"

class CustomTableView : public QTableView, public SeriesReader
{
    Q_OBJECT
public:
    explicit CustomTableView(QObject *parent = 0);

signals:

public slots:

};

#endif // CUSTOMTABLEVIEW_H
