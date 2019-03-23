#include "Logger.h"
#include "threads.h"
#include "discoverythread.h"
#include "onvif/discoveryobj.h"
#include "soap/wsddapi.h"

DiscoveryThread::DiscoveryThread() {

}

int DiscoveryThread::start() {
  THREAD_TYPE thread1ID;
  const string inputStr = "my name is zoobi!";
  
  //创建线程，输入参数为对象inputStr的地址;
  if (0 != THREAD_CREATE(&thread1ID, DiscoveryThread::run, (void *) &inputStr)) {
    LOG(INFO) << "pthread_create failed! err:" << errno;
    return -1;
  }
  
  //等待线程ID为thread1ID的非分离线程退出，并获取线程的返回值thread1Ret;
  //该函数成功应该返回0;如果返回 EDEADLK,表示线程内部右死锁;返回EINVAL，则线程是分离线程,
  //分离线程不用调用pthread_join，系统会自动回收线程资源;返回EINVAL，重复调用pthread_join等待
  //同一线程退出;返回ESRCH，则线程ID是非法的;
  int ret = THREAD_JOIN(thread1ID);
  if (0 != ret) {
    LOG(INFO) << "pthread_join failed!, the ret:" << ret;
  } else {
    LOG(INFO) << "The task return";
  }
  
  return ret;
}

void *DiscoveryThread::run(void *arg) {
  struct soap *serv = soap_new1(SOAP_IO_UDP);
  serv->bind_flags = SO_REUSEADDR;
  if (!soap_valid_socket(soap_bind(serv, NULL, HOST_PORT, 1000))) {
    soap_print_fault(serv, stderr);
    exit(1);
  }
  ip_mreq mcast;
  mcast.imr_multiaddr.s_addr = inet_addr(HOST_IP);
  mcast.imr_interface.s_addr = htonl(INADDR_ANY);
  //if (setsockopt(serv->master, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mcast, sizeof(mcast))<0)
  if (setsockopt(serv->master, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *) &mcast, sizeof(mcast)) < 0) {
    LOG(INFO) << "group membership failed:" << strerror(errno);
    exit(1);
  }
  
  // sendHello();
  // DiscoveryObj::sendHello();
  // mainloop(serv);
  
  //signal(SIGINT, &sighandler);
//    while (!stop)
  while (true) {
    LOG(INFO) << "inside while";
    //mainloop(serv);
    soap_wsdd_listen(serv, -1000000);
  }

//    sendBye();
//    mainloop(serv);
  //
}
