#ifndef PLASMASHELLMONITOR_H
#define PLASMASHELLMONITOR_H

#include <QObject>
#include <QDBusInterface>
#include <QTimer>
#include <QProcess>
#include <QDebug>

class PlasmashellMonitor : public QObject {
    Q_OBJECT

public:
    explicit PlasmashellMonitor(QObject *parent = nullptr);

public slots:
    void checkPlasmashell();

private:
    bool plasmashellDetected;
};

#endif // PLASMASHELLMONITOR_H
