#include "notificationdbusservice.h"
#include <QDebug>
#include "notificationserver.h"

NotificationDBusService::NotificationDBusService(QObject *parent) : QObject(parent) {

}

QStringList NotificationDBusService::GetCapabilities() {
    return {
        "icon-static"
    };
}

uint32_t NotificationDBusService::Notify(const QString &appName,
                                         uint replacesId,
                                         const QString &appIcon,
                                         const QString &summary,
                                         const QString &body,
                                         const QStringList &actions,
                                         const QVariantMap &hints,
                                         int expireTimeout) {
    NotificationServer *serv = (NotificationServer *) parent();

    if (expireTimeout <= 1000) {
        expireTimeout = 5000;
    }

    if (serv) {
        serv->showNotification(summary, body, expireTimeout, appIcon);
    }
    return 0;
}

void NotificationDBusService::CloseNotification(uint32_t id) {

}

void NotificationDBusService::GetServerInformation(QString &name, QString &vendor, QString &version, QString &specVersion) {
    name = "notify-server";
    vendor = "alnyan";
    version = "1.0";
    specVersion = "";
}
