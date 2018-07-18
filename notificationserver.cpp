#include "notificationserver.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QDBusMetaType>
#include <QDBusConnectionInterface>

NotificationServer::NotificationServer(QObject *parent) : QObject(parent) {
    m_notificationTopHeight = 0;
    m_highestMessage = nullptr;
    m_notificationServiceObject = new NotificationDBusService(this);
    QDBusConnection dbus = QDBusConnection::sessionBus();

    if (!dbus.registerObject("/org/freedesktop/Notifications", m_notificationServiceObject, QDBusConnection::ExportAllInvokables)) {
        qDebug() << "Failed to register DBus object";
    }

    if (!dbus.registerService("org.freedesktop.Notifications")) {
        qDebug() << "Failed to register service";
    }

    c = 0;
}

void NotificationServer::onNotificationExpired(NotificationMessage *msg) {
    if (msg == m_highestMessage) {
        m_highestMessage = nullptr;

        for (const auto &m: m_messages) {
            if (!m_highestMessage || (m->height() > m_highestMessage->height())) {
                m_highestMessage = m;
            }
        }

        if (m_highestMessage) {
            m_notificationTopHeight = m_highestMessage->y() + m_highestMessage->height();
        } else {
            m_notificationTopHeight = 0;
        }
    }

    m_messages.removeAll(msg);
    delete msg;

    if (m_messages.empty()) {
        m_notificationTopHeight = 0;
        m_highestMessage = nullptr;
    }
}

void NotificationServer::showNotification(const QString &title, const QString &desc, int dur, const QString &icon) {
    // Get display geometry
    QRect displayGeometry = QApplication::desktop()->screenGeometry();

    // Create notification message
    NotificationMessage *msg = new NotificationMessage(title, desc);

    m_highestMessage = msg;

    m_messages.append(msg);

    msg->setGeometry(displayGeometry.width() - msg->width(), 24 + m_notificationTopHeight, msg->width(), msg->height());
    msg->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_notificationTopHeight += msg->height() + 2;
    msg->setAttribute(Qt::WA_ShowWithoutActivating, true);
    msg->setIcon(icon);
    msg->show();

    // Make sure we remove the notification when it times out
    QObject::connect(msg, SIGNAL(notificationExpired(NotificationMessage*)), this, SLOT(onNotificationExpired(NotificationMessage*)));

    // Start notification expiration timer
    msg->start(dur);
}

void NotificationServer::onNotificationServerStarting(void) {

}
