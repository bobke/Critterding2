#ifndef BE_WORKER_POOL_H_INCLUDED
#define BE_WORKER_POOL_H_INCLUDED

#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include "threadpool.hpp"

	class BeWorkerPool
	{
		public:
			BeWorkerPool(const size_t workerCount);

			template<typename T>
			boost::shared_future<T> schedule(boost::function<T (void)> const& fn)
			{
				if(m_pool)
				{
					boost::shared_ptr<boost::packaged_task<T> > task(new boost::packaged_task<T>(fn));
					boost::shared_future<T> res(task->get_future());
					m_pool->schedule(boost::bind(&boost::packaged_task<T>::operator(), task));
					return res;
				}
				else
				{
					boost::promise<T> promise;
					promise.set_value(fn());
					return promise.get_future();
				}
			}

			~BeWorkerPool() {};

			boost::shared_ptr<boost::threadpool::pool> m_pool;
	};

#endif 
