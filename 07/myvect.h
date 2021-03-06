#include <iostream>
#include <limits>
#include <iterator>

template <class T>
class Allocator
{
public:
	using value_type = T;
	using pointer = T*;
	using size_type = size_t;

	pointer allocate(size_type count)
	{
		return static_cast<pointer>(operator new(sizeof(value_type) * count));
	}

	void deallocate(pointer ptr)
	{
		operator delete(ptr);
	}

	size_t max_size() const noexcept
	{
		return std::numeric_limits<size_type>::max();
	}

	template<class... Args >
	void construct(pointer p, Args&&... args )
	{
		new ((void*)p) value_type (std::forward<Args>(args)...);
	}

	void destroy(pointer p)
	{
		p -> ~value_type();
	}

};

template <class T>
class Iterator:public std::iterator<std::random_access_iterator_tag, T>
{
	T* ptr_;
public:
	using reference = T&;

	explicit Iterator(T* ptr) : ptr_(ptr) {};

	bool operator==(const Iterator<T>& other) const
	{
		return ptr_ == other.ptr_;
	}

	bool operator!=(const Iterator<T>& other) const
        {
                return !(*this == other);
        }
        
        reference operator*() const
        {
                return *ptr_;
        }
        
        Iterator& operator[](int n)
        {
                return ptr_[n];
        }
        
        Iterator& operator++()
        {
                ++ptr_;
                return *this;
        }
        
        Iterator& operator--()
        {
                --ptr_;
                return *this;
        }
        
};


template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
	using iterator = Iterator<T>;
	using value_type = T;
        using pointer = T*;
        using size_type = size_t;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using reference = T&;
private:
        Alloc alloc_;
        pointer data_;
        size_type capacity_;
        size_type size_;

public:
	Vector()
	{
		data_ = nullptr;
		capacity_ = 0;
		size_ = 0;
	}

	explicit Vector(size_type count)
	{
		data_ = alloc_.allocate(count);
		size_ = count;
		capacity_ = count;
		for (size_type i = 0; i < size_; i++)
		{
			alloc_.construct(data_ + i);
		}
	}

	size_type size() const
	{
		return size_;
	}

	bool empty() const
	{
		return size_ == 0;
	}

	size_type capacity()
	{
		return capacity_;
	}

	iterator begin() const
	{
		return iterator(data_);
	}

	reverse_iterator rend() const
	{
		return reverse_iterator(this -> begin());
	}

	iterator end() const
	{
		return iterator(data_ + size_);
	}

	reverse_iterator rbegin() const
	{
		return reverse_iterator(this -> end());
	}

	void reserve(size_type n)
	{
		if (n >= capacity_)
		{
			pointer extra = alloc_.allocate(n);
			for (size_type i = 0; i < size_; i++)
			{
				alloc_.construct(extra + i, std::forward<T>(*(data_ + i)));
				alloc_.destroy(data_ + i);
			}

			alloc_.deallocate(data_);
			data_ = extra;
			capacity_ = n;
		}
	}

	void resize(size_type n)
	{
		if (size_ <= n)
		{
			reserve(n);
			for (size_type i = size_; i < n; i++)
				alloc_.construct(data_ + i);
			size_ = n;
		}else{
			for (size_type i = n; i < size_; i++)
				alloc_.destroy(data_ + i);
			size_ = n;
		}
	}

	reference operator[](size_type i)
	{
		if (i >= size_)
			throw std::out_of_range("");
		return data_[i];
	}

	void push_back(const value_type& val)
	{
		if (size_ == capacity_)
			reserve(capacity_ * 2);
		alloc_.construct(data_ + size_, val);
		size_ += 1; 
	}

	void push_back(value_type&& val)
	{
		if (size_ == capacity_)
			reserve(capacity_ * 2);
		alloc_.construct(data_ + size_, std::move(val));
		size_ += 1; 
	}

	void pop_back()
	{
		if (size_ != 0)
		{
			alloc_.destroy(data_ + size_);
			size_--;
		}
	}

	void clear()
	{
		resize(0);
	}
};
