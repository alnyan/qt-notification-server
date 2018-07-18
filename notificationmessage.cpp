#include "notificationmessage.h"
#include "ui_notificationmessage.h"

NotificationMessage::NotificationMessage(const QString &title, const QString &desc, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NotificationMessage) {
    ui->setupUi(this);

    ui->notificationTitle->setText(title);
    ui->notificationDescription->setText(desc);
}

void NotificationMessage::onTimerExpired(void) {
    emit notificationExpired(this);
}

void NotificationMessage::start(int timeout) {
    QTimer::singleShot(timeout, this, SLOT(onTimerExpired()));
}

NotificationMessage::~NotificationMessage() {
    delete ui;
}

void NotificationMessage::mousePressEvent(QMouseEvent *ev) {
    emit notificationClicked(this);
}

void NotificationMessage::setIcon(const QString &icon) {
    if (icon.isEmpty()) {
        ui->notificationIcon->setMinimumSize(0, 0);
        ui->notificationIcon->setText("");
    } else {
        QPixmap i(icon);
        i = i.scaled(72, 72, Qt::KeepAspectRatio);
        ui->notificationIcon->setPixmap(i);
    }
}
