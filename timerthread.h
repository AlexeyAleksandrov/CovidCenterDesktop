#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

#include <QMessageBox>
#include <QTimer>
#include <QThread>

class TimerThread : public QThread
{
    Q_OBJECT
public:
    explicit TimerThread(QObject *parent = nullptr);

signals:
    void timeout();

protected:
    void run() override;
};
#endif // TIMERTHREAD_H
