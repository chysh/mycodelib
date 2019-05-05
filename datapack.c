/*数据流复制*/
VOID MemCopy_r(VOID *pdesn, VOID *psrc, BWORD len)
{
	memcpy((void *)pdesn, (const void *)psrc, (size_t)len);
		/*prototype:
			void	*memcpy(
					void			*destination,	"destination of copy"
					const void	*source,		"source of copy"
					size_t		size);		"size of memory to copy"
		*/
	return;
}

/*数据流搬移*/
VOID MemMove_r(VOID *pdesn, VOID *psrc, BWORD len)
{
	memmove((void *)pdesn, (const void *)psrc, (size_t)len);
		/*prototype:
			void	*memmove(
					void			*destination,	"destination of copy"
					const void	*source,		"source of copy"
					size_t		size);		"size of memory to copy"
		*/

	return;
}

/*数据流设置*/
VOID MemSet_r(VOID *pdesn, CHAR num, BWORD len)
{
	memset((void *)pdesn, (int)num, (size_t)len);
		/*prototype:
			void	*memset(
					void		*m,		"block of memory"
					int		c,		"character to store"
					size_t	size);	"size of memory"
		*/

	return;
}

/*数据流比较*/
unsigned char MemComp_r(VOID *pdesn, VOID *psrc, BWORD len)
{
	int Result;

	Result=memcmp((const void *)pdesn, (const void *)psrc, (size_t)len);
		/*prototype:
			int	memcmp(
					const void	*s1,		"array 1"
					const void	*s2,		"array 2"
					size_t		n);		"size of memory to compare"
		*/
	return Result;
}
