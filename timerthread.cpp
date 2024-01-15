#include "timerthread.h"


TimerThread::TimerThread(QObject *parent) : QThread(parent) {}

void TimerThread::run()
{
    QTimer timer;
    connect(&timer, &QTimer::timeout, this, &TimerThread::timeout);
    timer.start(1000);
    exec(); // Выполняем цикл обработки событий для этого потока
}
