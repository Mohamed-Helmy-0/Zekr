#ifndef RUNGUARD_H
#define RUNGUARD_H

#include <QObject>

#include <QSharedMemory>
#include <QSystemSemaphore>

#include <QCryptographicHash>



class RunGuard : public QObject
{
    Q_OBJECT
public:
    explicit RunGuard(const QString& key );
    ~RunGuard();

      bool isAnotherRunning();
      bool tryToRun();
      void release();

private:
    const QString key;
    const QString memLockKey;
    const QString sharedmemKey;

    QSharedMemory sharedMem;
    QSystemSemaphore memLock;

    Q_DISABLE_COPY( RunGuard )

signals:

};

#endif // RUNGUARD_H
