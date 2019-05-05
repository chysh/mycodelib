#include<pthread.h>

/*****************************************************************************
 函 数 名  : CreateTask
 功能描述  : 创建线程/任务
 输入参数  : const char *name    线程名称
            int Pri      		    优先级
            int StackSize       堆栈大小
            void* pEntryFunc    入口函数
            void* pArg          参数指针
 输出参数  : 无
 返 回 值  : 成功返回线程ID,失败返回-1
*****************************************************************************/

int CreateTask(const char *name, int Pri, int StackSize, void* pEntryFunc, int Arg)
{
	  pthread_attr_t attr;//线程属性
	  struct sched_param param;//调度参数，主要是优先级
	  pthread_t  threadid;//线程ID
	  int rtn = 0;//创建线程结果
	  static int TotalStackSize = 0;
	  TotalStackSize+=StackSize;
	  assert(NULL != pEntryFunc);
	  errno = 0;
		
    //将线程属性attr初始化为默认值
	  pthread_attr_init(&attr);
    //设置为分离线程
	  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    //设置调度方式为实时调度策略，时间片轮转
	  pthread_attr_setschedpolicy(&attr, SCHED_RR);
    //线程优先级
    param.sched_priority = Pri;
	  pthread_attr_setschedparam(&attr,&param);
    //线程堆栈大小
	  pthread_attr_setstacksize(&attr, (size_t)StackSize);
    //创建线程 "/lib/libc.so.6" i
	  rtn = pthread_create(&threadid, &attr, pEntryFunc,(void *)&Arg);
    printf("Create thread %s threadid =%d Curr StackSize = %d,TotalStackSize = %d\r\n",
        name,(int)threadid,StackSize,TotalStackSize);

    //销毁attr
	  pthread_attr_destroy(&attr);

	  if(rtn != 0)
	  {
		    printf("Erroe: %s\n", strerror(errno));
		    return -1;
	  }
	  else
	  {
		    return threadid;
	  }
}

/*****************************************************************************
 函 数 名  : TaskGetPriority
 功能描述  : 获取线程优先级
 输入参数  : int TaskHandle  //线程ID
 输出参数  : 无
*****************************************************************************/
int TaskGetPriority(int TaskHandle)
{
	  //线程属性
	  pthread_attr_t attr;
	  //调度参数，主要是优先级
	  struct sched_param param;

    //将线程属性attr初始化为默认值
	  pthread_attr_init(&attr);

    pthread_getattr_np(TaskHandle,&attr);
    //当前线程调度属性
	  pthread_attr_getschedparam(&attr,&param);
    //销毁attr
	  pthread_attr_destroy(&attr);

	  return param.sched_priority;
}
