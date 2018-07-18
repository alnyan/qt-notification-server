#ifndef NOTIFICATIONSERVER_H
#define NOTIFICATIONSERVER_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QList>
#include "notificationmessage.h"
#include "notificationdbusservice.h"

class NotificationServer : public QObject {
    Q_OBJECT
public:
    explicit NotificationServer(QObject *parent = nullptr);

    void showNotification(const QString &title, const QString &desc, int dur, const QString &icon = "");

public slots:
    void onNotificationServerStarting(void);
    void onNotificationExpired(NotificationMessage *msg);

protected:
    int getNextNotificationY(void);

private:

    NotificationMessage *m_highestMessage;
    int m_notificationTopHeight;
    QTimer m_notificationTimer;
    QList<NotificationMessage *> m_messages;
    NotificationDBusService *m_notificationServiceObject;
    int c;
};

#endif // NOTIFICATIONSERVER_H
