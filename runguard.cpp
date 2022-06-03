#include "runguard.h"
#include <QDebug>
namespace
{

QString generateKeyHash( const QString& key, const QString& salt )
{
    QByteArray data;

    data.append( key.toUtf8() );
    data.append( salt.toUtf8() );
    data = QCryptographicHash::hash( data, QCryptographicHash::Sha1 ).toHex();

    return data;
}

}


RunGuard::RunGuard(const QString &key)
    : key( key )
    , memLockKey( generateKeyHash( key, "_memLockKey" ) )
    , sharedmemKey( generateKeyHash( key, "_sharedmemKey" ) )
    , sharedMem( sharedmemKey )
    , memLock( memLockKey, 1 )

{
    memLock.acquire();
      {
          QSharedMemory fix( sharedmemKey );
          bool r=fix.attach();
          bool z=sharedMem.attach();
          qDebug()<<"attached in constructro="<<r;
          qDebug()<<"attached in constructro="<<z;
      }
    memLock.release();
}

RunGuard::~RunGuard()
{
    release();
}

bool RunGuard::isAnotherRunning()
{
    if ( sharedMem.isAttached() )//always false
    {
        qDebug()<<"++++++++++++++="<<true;
        return false;
    }

    //sharedMem.isAttached() == false
    memLock.acquire();
    const bool isRunning = sharedMem.attach();
      qDebug()<<"attached in isAnotherRunning="<<isRunning;
    if ( isRunning )
    {

        bool z=sharedMem.detach();
         qDebug()<<"detach in isAnotherRunning="<<z;
    }
    else
        qDebug()<<"error= "<<sharedMem.errorString();
    memLock.release();
    qDebug()<<"isRunning="<<isRunning;
    return isRunning;
}

bool RunGuard::tryToRun()
{
    if ( isAnotherRunning() )   // Extra check
        return false;

    memLock.acquire();
    //creat do auto attach
    const bool result = sharedMem.create( sizeof( quint64 ) );
    memLock.release();
    if ( !result )
    {
        release();
        return false;
    }

    return true;
}

void RunGuard::release()
{
    memLock.acquire();
    if ( sharedMem.isAttached() )
        sharedMem.detach();
    memLock.release();
}
