#ifndef NOTIFICATIONMESSAGE_H
#define NOTIFICATIONMESSAGE_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class NotificationMessage;
}

class NotificationMessage : public QDialog {
    Q_OBJECT

public:
    explicit NotificationMessage(const QString &title, const QString &desc, QWidget *parent = 0);
    ~NotificationMessage();

    void start(int timeout);
    void setIcon(const QString &icon);

protected slots:
    void onTimerExpired(void);

protected:
    void mousePressEvent(QMouseEvent *ev);

signals:
    void notificationExpired(NotificationMessage *);
    void notificationClicked(NotificationMessage *);

private:
    Ui::NotificationMessage *ui;
};

#endif // NOTIFICATIONMESSAGE_H
