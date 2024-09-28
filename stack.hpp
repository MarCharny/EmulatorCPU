#pragma once

#include <cstdlib>
#include <new>
#include <algorithm>

namespace stack
{
	template<typename tData>
	class Stack
	{
		tData* data_;
		size_t capacity_;
		size_t size_;

		void incrementSize()
		{
			if (size_ + 1 > capacity_)
			{
				capacity_ *= 2;
				tData* tmp = new tData[capacity_];
				for (size_t i = 0; i < size_; i++)
				{
					tmp[i] = std::move(data_[i]);
				}
				data_ = std::move(tmp);
			}
			size_++;
		}

		void isMoved() const
		{
			if (data_ == nullptr)
			{
				throw std::runtime_error("Stack has been moved");
			}
		}

	public:
		Stack() : data_(new tData[1]), capacity_(1), size_(0) {}

		Stack(const Stack& other) : data_(nullptr)
		{
			*this = other;
		}

		Stack(Stack&& other) : data_(nullptr)
		{
			*this = std::move(other);
		}

		~Stack() { delete[] data_; }

		Stack& operator=(const Stack& other)
		{
			size_ = other.size_;
			capacity_ = size_ >= 1 ? size_ : 1;

			delete[] data_;
			data_ = new tData[capacity_];
			for (size_t i = 0; i < size_; i++)
			{
				data_[i] = other.data_[i];
			}

			return *this;
		}

		Stack& operator=(Stack&& other)
		{
			delete[] data_;
			data_ = other.data_;
			size_ = other.size_;
			capacity_ = other.capacity_;

			other.data_ = nullptr;
			other.size_ = 0;
			other.capacity_ = 0;

			return *this;
		}

		tData& push(const tData& val)
		{
			isMoved();
			incrementSize();
			return data_[size_ - 1] = val;
		}

		tData& push(tData&& val)
		{
			isMoved();
			incrementSize();
			return data_[size_ - 1] = std::move(val);
		}

		tData pop()
		{
			isMoved();
			if (empty())
			{
				throw std::runtime_error("Stack is empty, unable to pop");
			}
			size_--;
			return data_[size_];
		}

		tData top() const
		{
			isMoved();
			if (empty())
			{
				throw std::runtime_error("Stack is empty, unable to return top");
			}
			return data_[size_ - 1];
		}

		bool empty() const
		{
			isMoved();
			return size_ == 0;
		}

		size_t size()
		{
			isMoved();
			return size_;
		}

		//debug
		std::string print()
		{
			std::string str;
			for (int i = 0; i < size_; i++)
			{
				str += " " + std::to_string(data_[i]);
			}
			return str;
		}
	};
}