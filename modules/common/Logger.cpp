//
// Created by yz on 18-8-26.
//

#include "Logger.h"

Logger g_Logger;

Logger::Logger() {
  nsp_google::InitGoogleLogging("test");
  nsp_google::SetStderrLogging(google::GLOG_INFO);
}

Logger::~Logger() {
  /* FIXME 由于Logger被定义为全局变量, 将在程序的main函数执行前构造, 在main结束后析构, \
   * 这导致 nsp_google::ShutdownGoogleLogging() 执行报错, 原因应该是资源释放的出错 */
//  nsp_google::ShutdownGoogleLogging();
}