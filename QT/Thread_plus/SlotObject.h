#ifndef SLOTOBJECT_H
#define SLOTOBJECT_H

#include <QObject>

class SlotObject : public QObject
{
    Q_OBJECT
public:
    explicit SlotObject(QObject *parent = 0);

signals:

public slots:
};

#endif // SLOTOBJECT_H