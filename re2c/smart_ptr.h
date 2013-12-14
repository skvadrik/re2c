#ifndef SMART_PTR_HPP_INCLUDE_GUARD
#define SMART_PTR_HPP_INCLUDE_GUARD

namespace re2c 
{

	template <class T>
	class smart_ptr 
	{
	private:
		T* ptr;
		long* count;   // shared number of owners

	public:
		explicit smart_ptr (T* p=0)
			: ptr(p), count(new long(1)) {}

		smart_ptr (const smart_ptr<T>& p) throw()
			: ptr(p.ptr), count(p.count) 
		{
			++*count;
		}

		~smart_ptr ()
		{
			dispose();
		}

		smart_ptr<T>& operator= (const smart_ptr<T>& p)
		{
			if (this != &p) 
			{
					dispose();
					ptr = p.ptr;
					count = p.count;
					++*count;
			}
			return *this;
		}

		T& operator*() const
		{
			return *ptr;
		}

		T* operator->() const
		{
			return ptr;
		}

	private:
		void dispose()
		{
			if (--*count == 0) 
			{
					delete count;
					delete ptr;
			}
		}
	};

	template <typename T>
	smart_ptr<T> make_smart_ptr(T* p)
	{
		return smart_ptr<T>(p);
	}
}

#endif
