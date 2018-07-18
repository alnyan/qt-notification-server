#ifndef NOTIFICATIONDBUSSERVICE_H
#define NOTIFICATIONDBUSSERVICE_H
#include <QStringList>
#include <QDBusArgument>

#include <QObject>

class NotificationDBusService : public QObject {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.Notifications")
public:
    explicit NotificationDBusService(QObject *parent = nullptr);

    Q_INVOKABLE QStringList GetCapabilities(void);
    Q_INVOKABLE uint32_t Notify(const QString &appName,
                                uint replacesId,
                                const QString &appIcon,
                                const QString &summary,
                                const QString &body,
                                const QStringList &actions,
                                const QVariantMap &hints,
                                int expireTimeout);
    Q_INVOKABLE void CloseNotification(uint32_t id);
    Q_INVOKABLE void GetServerInformation(QString &name, QString &vendor, QString &version, QString &specVersion);
signals:

public slots:

};

#endif // NOTIFICATIONDBUSSERVICE_H
