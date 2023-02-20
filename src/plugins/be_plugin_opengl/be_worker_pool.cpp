#include "be_worker_pool.h"

	BeWorkerPool::BeWorkerPool(const size_t workerCount)	//when workerCount is 0
	{
		if(workerCount>0)
		{
			m_pool=boost::shared_ptr<boost::threadpool::pool>( new boost::threadpool::pool(workerCount) );
		}
	}

// 	template<typename T>
// 	boost::shared_future<T> schedule(boost::function<T (void)> const& fn)
// 	{
// 		if(m_pool)
// 		{
// 			boost::shared_ptr<boost::packaged_task<T> > task(new boost::packaged_task<T>(fn));
// 			boost::shared_future<T> res(task->get_future());
// 			m_pool->schedule(boost::bind(&boost::packaged_task<T>::operator(), task));
// 			return res;
// 		}
// 		else
// 		{
// 			boost::promise<T> promise;
// 			promise.set_value(fn());
// 			return promise.get_future();
// 		}
// 	}
	
