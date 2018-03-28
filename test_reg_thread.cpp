#include <stdio.h>
#include <string.h>
#include "gtest/gtest.h"
#include "TestForReliability.h"
#include <string>
#include <cstring>

TEST(TEST_RELIABILITY, reg)
{
	UserAgent::setIpAddress( "10.1.77.85");
    UserAgent::setPort(6111);
    
    EXPECT_TRUE(UserAgent::initialize(true)); //initialize

    TestForCall ua; 

    EXPECT_TRUE(ua.start()); //启动UserAgent
	
    char id[40]; // 010001000101000001
    char issue[] = "01";  // 01
    char devID[] = "000001";
    
    /*
    char zone[8];   // 0001
    char build[4];  // 0001
    char unit[4];   //01
    */
    while (1)
    {
    for (int i=1; i <= 2; i++)
    {
        //sprintf(zone, "%04d", i);
        for (int j=1; j<=20; j++)
        {
            //sprintf(build, "%4d", j);
            for (int k=1; k<=10; k++)
            {
                
                //sprintf(unit, "%02d", k);
                sprintf(id, "%s%04d%04d%02d%s", issue, i, j, k, devID);
                printf(">>> Register id: %s\n", id);
                ua.setUsername(id);
                ua.setRegistrar("10.1.77.235");
                int addAuth;
                addAuth = ua.addAuthenticationInfo(ua.getUsername(), ua.getUsername(),NULL);
                EXPECT_EQ(0, addAuth);
                
                EXPECT_TRUE(ua.registerToProxy(ua.getRegistrar(), 1800));// 注册到服务器

                sleep(1);
             
                EXPECT_STREQ(ua.callFlag, "onRegistrationSuccess");
            }
        }
    }
    sleep(10);
    }
    
    ua.stop(); 
    UserAgent::quit();
}


