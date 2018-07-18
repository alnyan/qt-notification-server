#include <QApplication>
#include <QTimer>
#include <QDebug>
#include "notificationserver.h"

int main(int argc, char **argv) {
    QApplication a(argc, argv);
    NotificationServer ns(&a);
    QTimer timer;
    timer.singleShot(0, &ns, SLOT(onNotificationServerStarting()));
    return a.exec();
}
