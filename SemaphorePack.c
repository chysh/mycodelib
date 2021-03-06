/*****************************************************************************
 函 数 名  : SemaphoreCreate
 功能描述  : 创建信号量
 参数      :sem_t *pSem  信号量
 返 回 值  : 成功返回0,失败返回-1
*****************************************************************************/
int SemaphoreCreate(sem_t *pSem)
{
	assert(NULL != pSem);

	OsPackResetErrno_r();

	if(sem_init(pSem,0,0)==0)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

/*****************************************************************************
 函 数 名  : SemaphorePost
 功能描述  : 释放信号量
 参    数  : sem_t *pSem 信号量
 返 回 值  : 成功返回0,失败返回-1
*****************************************************************************/
int SemaphorePost(sem_t *pSem)
{
	assert(NULL != pSem);
	if(0 == sem_post(pSem))
	{
		return 0;
	}
	else
	{
		return -1;
	}
}
