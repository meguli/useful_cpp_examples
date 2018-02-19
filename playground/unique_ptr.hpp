/* 
	Most of this code is taken from the book of Arthur O'Dwyer
	and it was MIT licensed.
*/

#ifndef CHOPS_UNIQUE_PTR
#define CHOPS_UNIQUE_PTR

#include <utility>

namespace chops{

/* 
	A T* wrapper that acts as a unique owner of the T*. This class is
	not copyable and ownership can only be released, in which case caller
	can the the ownership, or it could be reset with another T*, deleting
	the old T*. Destructor calls reset with nullptr so this is a scoped ptr. 
*/
template<typename T>
class unique_ptr {
	
	T *m_ptr = nullptr; // default constructed will point to a nullptr

	public:
		constexpr unique_ptr() noexcept = default;
		constexpr unique_ptr(T *p) noexcept : m_ptr(p) {}
		
		unique_ptr(unique_ptr&& rhs) noexcept {
			this->reset(rhs.release());
		}
		
		unique_ptr& operator=(unique_ptr&& rhs) noexcept {
			this->reset(rhs.release());
			return *this;
		} 
		
		~unique_ptr() {
			reset();
		}

		/* 
			Notice that we can change the object pointed to by T*
			and we can release and reset the pointed object but
			in no way we can share the pointer. Then does this get()
			defies the purpose of unique_ptr? Yes and no! It should be
			used scarcely but anytime you need to pass the contents
			of your unique_ptr to a C-style pointer expecting func,
			you need to do this dirty thing.
		*/
		T* get() const noexcept { return m_ptr; }

		// So that we can use this bool conversion for things like
		// if, while etc. checks
		operator bool() const noexcept { return bool(get()); }

		// These makes our unique_ptr acts like normal T*
		T& operator*() const noexcept { return *get(); }
		T* operator->() const noexcept { return get(); }
		
		/* 
			reset makes this uniqe_ptr to point to another
			T*, deleting the old one of course
		*/
		void reset(T *p = nullptr) noexcept {
			T *old_p = std::exchange(m_ptr, p);
			delete old_p;
		}

		/* 
			release makes this unique_ptr point to nullptr and
			also returns the previous T*, so that callee can
			take the ownership
		*/
		T* release() noexcept {
			return std::exchange(m_ptr, nullptr);
		}	
};

/*
	A variadic template given as helper so that we could minimize
	the call of new and delete in our code
*/
template<typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args)
{
	return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

// namespace chops ends
}
#endif
