#ifndef EDITCOORDINATOR_H
#define EDITCOORDINATOR_H

#include <QObject>

class EditCoordinator : public QObject
{
    Q_OBJECT
public:
    explicit EditCoordinator(QObject *parent = 0);

signals:

public slots:
    void keyDown(){

    }
};

#endif // EDITCOORDINATOR_H
