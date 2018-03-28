
#include <stdio.h>
#include "TestForReliability.h"
#include <assert.h>
#include <string.h>
#include "RegistrationProcessor.h"
#include <unistd.h>

TestForCall::TestForCall()
                        :m_pthreadStruc05(0),
                        m_pthreadStruc04(0),
                        m_pthreadStruc03(0),
                        //m_pthreadStruc02(0),
                        //m_pthreadStruc01(0),
                        m_beginTime(),
                        m_registrar(),
						callFlag(),
						isTerminated(false)
{
    pthread_create(&m_pthreadStruc05, NULL, ThreadReg05, this);
    pthread_create(&m_pthreadStruc04, NULL, ThreadReg04, this);
    pthread_create(&m_pthreadStruc03, NULL, ThreadReg03, this);
    //pthread_create(&m_pthreadStruc02, NULL, ThreadReg02, this);
    //pthread_create(&m_pthreadStruc01, NULL, ThreadReg01, this);
}

TestForCall::~TestForCall()
{
     pthread_cancel( m_pthreadStruc05);
     pthread_cancel( m_pthreadStruc04);
     pthread_cancel( m_pthreadStruc03);
     //pthread_cancel( m_pthreadStruc02);
     //pthread_cancel( m_pthreadStruc01);
}


void * 
TestForCall::timeThreadProc(void* data)
{
    TestForCall * ua = static_cast<TestForCall *> (data);
    assert (ua != NULL);
    
    //ua->setRegistrar("10.1.77.222");
    
    while (1)
    {
        time_t now;
        time( &now);
        double timeResult = difftime( now, *(ua->getBeginTime()));
        /*if (timeResult >=10)
        {
            ua->unregisterToProxy();
            
            //if (ua->registrationProcessor().isRegistrationSuccessful())
                // ua->unregisterToProxy();

            ua->registerToProxy( ua->getRegistrar());
            break;
        }
        
        if (timeResult >= 120)
        {
            printf( "*** In timeThreadProc, time out ***\n");
            ua->terminate( 0);
            break;
        }*/

        usleep(10);
    }
}

void
TestForCall::onCallProxyFailed( int linuNumber, const char * remoteUsername, const char * remoteHost)
{
    printf( "*** In TestForCall::onCallProxyFailed, remoteUsername is %s ***\n", remoteUsername);
    memset(callFlag, 0, 1024);
	strcpy(callFlag, "onCallProxyFailed");
}

void
TestForCall::onTerminated( int lineNumber, const char * remoteUsername, const char * remoteHost)
{
    printf( "*** In TestForCall::onTerminated, remoteHost is %s ***\n", remoteHost);
	isTerminated = true;
}

void 
TestForCall::onPeerRinging( int lineNumber, const char * remoteUsername, const char * remoteHost)
{
    printf( "*** In TestForCall::onPeerRinging, remoteHost is %s ***\n", remoteHost);
    memset(callFlag, 0, 1024);
    strcpy(callFlag, "onPeerRinging");
}

void 
TestForCall::onPeerBusy( int lineNumber, const char * remoteUsername, const char * remoteHost)
{
    printf( "*** In TestForCall::onPeerBusy, remoteUsername is %s ***\n", remoteUsername);
    memset(callFlag, 0, 1024);
    strcpy(callFlag, "onPeerBusy");
}

void
TestForCall::onStartMedia( int lineNumber, const char * remoteHost,
                         int remoteVideoPort, int remoteAudioPort, bool bSelfDialled)
{
    printf( "*** In TestForCall::onStartMedia, remoteHost is: %s ***\n", remoteHost);
    if (bSelfDialled)
        printf( "*** In TestForCall::onStartMedia, self call ***\n");
    else
        printf( "*** In TestForCall::onStartMedia, remote call ***\n");
    memset(callFlag, 0, 1024);
    strcpy(callFlag, "onStartMedia");
}

void
TestForCall::onStopMedia( int lineNumber)
{
    printf( "*** In TestForCall::onStopMedia ***\n");
    memset(callFlag, 0, 1024);
    strcpy(callFlag, "onStopMedia");
}

void
TestForCall::onConfirmed( int lineNumber, const char * remoteUsername, const char * remoteHost)
{
    printf( "*** In TestForCall::onConfirmed, remoteHost is %s ***\n", remoteHost);
    memset(callFlag, 0, 1024);
    strcpy(callFlag, "onConfirmed");
}

void
TestForCall::onRegistrationSuccess()
{
    printf( "*** In TestForCall::onRegistrationSuccess ***\n");
    memset(callFlag, 0, 1024);
    strcpy(callFlag, "onRegistrationSuccess");
}

void
TestForCall::onRegistrationFailure()
{
    printf( "*** In TestForCall::onRegistrationFailure ***\n");
    memset(callFlag, 0, 1024);
    strcpy(callFlag, "onRegistrationFailure");
}

void *
TestForCall::ThreadReg01( void * data)
{
    TestForCall * ua = static_cast<TestForCall *>( data);

    assert( ua != NULL);

    sleep(5);
    char id[40]; // 010001000101000001
    char issue[] = "01";  // 01
    char devID[] = "000001";
    int issue_loc = 1;
    while (1)
    {
        for (int j=1; j<=20; j++)
        {
            for (int k=1; k<=10; k++)
            {
                sprintf(id, "%s%04d%04d%02d%s", issue, issue_loc, j, k, devID);
                printf(">>> Register id: %s", id);
                ua->setUsername(id);
                ua->setRegistrar("10.1.77.235");
                int addAuth;
                addAuth = ua->addAuthenticationInfo(ua->getUsername(), ua->getUsername(),NULL);
                
                ua->registerToProxy(ua->getRegistrar(), 1800);// 注册到服务器

                sleep(1);
            }
        }
        sleep(10);
    }
    return NULL;
}

void *
TestForCall::ThreadReg02( void * data)
{
    TestForCall * ua = static_cast<TestForCall *>( data);

    assert( ua != NULL);

    sleep(5);
    char id[40]; // 010001000101000001
    char issue[] = "01";  // 01
    char devID[] = "000001";
    int issue_loc = 2;
    while (1)
    {
        for (int j=1; j<=20; j++)
        {
            for (int k=1; k<=10; k++)
            {
                sprintf(id, "%s%04d%04d%02d%s", issue, issue_loc, j, k, devID);
                printf(">>> Register id: %s", id);
                ua->setUsername(id);
                ua->setRegistrar("10.1.77.235");
                int addAuth;
                addAuth = ua->addAuthenticationInfo(ua->getUsername(), ua->getUsername(),NULL);
                
                ua->registerToProxy(ua->getRegistrar(), 1800);// 注册到服务器

                sleep(1);
            }
        }
        sleep(10);
    }
    return NULL;
}

void *
TestForCall::ThreadReg03( void * data)
{
    TestForCall * ua = static_cast<TestForCall *>( data);

    assert( ua != NULL);

    sleep(5);
    char id[40]; // 010001000101000001
    char issue[] = "01";  // 01
    char devID[] = "000001";
    int issue_loc = 3;
    while (1)
    {
        for (int j=1; j<=20; j++)
        {
            for (int k=1; k<=10; k++)
            {
                sprintf(id, "%s%04d%04d%02d%s", issue, issue_loc, j, k, devID);
                printf(">>> Register id: %s", id);
                ua->setUsername(id);
                ua->setRegistrar("10.1.77.235");
                int addAuth;
                addAuth = ua->addAuthenticationInfo(ua->getUsername(), ua->getUsername(),NULL);
                
                ua->registerToProxy(ua->getRegistrar(), 1800);// 注册到服务器

                sleep(1);
            }
        }
        sleep(10);
    }
    return NULL;
}

void *
TestForCall::ThreadReg04( void * data)
{
    TestForCall * ua = static_cast<TestForCall *>( data);

    assert( ua != NULL);

    sleep(5);
    char id[40]; // 010001000101000001
    char issue[] = "01";  // 01
    char devID[] = "000001";
    int issue_loc = 4;
    while (1)
    {
        for (int j=1; j<=20; j++)
        {
            for (int k=1; k<=10; k++)
            {
                sprintf(id, "%s%04d%04d%02d%s", issue, issue_loc, j, k, devID);
                printf(">>> Register id: %s", id);
                ua->setUsername(id);
                ua->setRegistrar("10.1.77.235");
                int addAuth;
                addAuth = ua->addAuthenticationInfo(ua->getUsername(), ua->getUsername(),NULL);
                
                ua->registerToProxy(ua->getRegistrar(), 1800);// 注册到服务器

                sleep(1);
            }
        }
        sleep(10);
    }
    return NULL;
}

void *
TestForCall::ThreadReg05( void * data)
{
    TestForCall * ua = static_cast<TestForCall *>( data);

    assert( ua != NULL);
    sleep(5);

    char id[40]; // 010001000101000001
    char issue[] = "01";  // 01
    char devID[] = "000001";
    int issue_loc = 5;
    while (1)
    {
        for (int j=1; j<=20; j++)
        {
            for (int k=1; k<=10; k++)
            {
                sprintf(id, "%s%04d%04d%02d%s", issue, issue_loc, j, k, devID);
                printf(">>> Register id: %s", id);
                ua->setUsername(id);
                ua->setRegistrar("10.1.77.235");
                int addAuth;
                addAuth = ua->addAuthenticationInfo(ua->getUsername(), ua->getUsername(),NULL);
                
                ua->registerToProxy(ua->getRegistrar(), 1800);// 注册到服务器

                sleep(1);
            }
        }
        sleep(10);
    }
    return NULL;
}
