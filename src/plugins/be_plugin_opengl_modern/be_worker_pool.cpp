#include "be_worker_pool.h"

	BeWorkerPool::BeWorkerPool(const size_t workerCount)	//when workerCount is 0
	{
		if(workerCount>0)
		{
			m_pool = boost::shared_ptr<boost::threadpool::pool>( new boost::threadpool::pool(workerCount) );
		}
	}
