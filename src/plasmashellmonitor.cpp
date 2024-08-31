
#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QTimer>
#include <QProcess>
#include <QDebug>

class PlasmashellMonitor : public QObject {
    Q_OBJECT

public:
    PlasmashellMonitor() : plasmashellDetected(false) {
        // Set up a timer to check periodically
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &PlasmashellMonitor::checkPlasmashell);
        timer->start(30000); // Check every 30 seconds
    }

public slots:
    void checkPlasmashell() {
        // Try to ping plasmashell via D-Bus
        QDBusInterface iface("org.kde.plasmashell", "/PlasmaShell", "", QDBusConnection::sessionBus());
        if (iface.isValid()) {
            if (!plasmashellDetected) {
                qDebug() << "Plasmashell has been detected running for the first time.";
                plasmashellDetected = true;
            } else {
                qDebug() << "Plasmashell is still running.";
            }
        } else {
            if (plasmashellDetected) {
                qDebug() << "Plasmashell was running but now it's not. Restarting...";
                QProcess::startDetached("kstart5 plasmashell");
            } else {
                qDebug() << "Plasmashell has not been detected running yet.";
            }
        }
    }

private:
    bool plasmashellDetected;
};

