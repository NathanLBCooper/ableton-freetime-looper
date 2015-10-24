#pragma once

#include <queue>
#include <string>
#include <memory>
#include <mutex>
#include <condition_variable>

namespace AbletonProject
{
	template<typename T>
	class ConcurrentQueue
	{
	private:
		std::queue<T> _queue;
		std::mutex _mutex;

	public:
		ConcurrentQueue()
			: _queue(),
			_mutex()
		{
		}

		virtual ~ConcurrentQueue() = default;

		bool empty() const
		{
			return _queue.empty();
		}

		std::size_t size() const
		{
			return _queue.size();
		}

		void enqueue(T item)
		{
			std::lock_guard<std::mutex> lock(_mutex);
			_queue.push(item);
		}

		bool tryDequeue(T& item)
		{
			std::lock_guard<std::mutex> lock(_mutex);

			if (_queue.empty()) return false;

			item = _queue.back();
			_queue.pop();
			return true;
		}
	};
}