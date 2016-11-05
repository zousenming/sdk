#ifndef _libct_auto_obj_
#define _libct_auto_obj_

namespace libct{

// typename T
// addref()/release()

template <typename T>
class auto_obj
{
public:
	explicit auto_obj(T* obj=0):m_obj(obj){}

	~auto_obj()
	{
		clear();
	}

	void clear()
	{
		if(m_obj)
			m_obj->release();
		m_obj = 0;
	}

	bool valid() const	
	{
		return !!m_obj;
	}

	void attach(T* obj)
	{
		clear();
		m_obj = obj;
	}

	T* detach()
	{
		T* obj = m_obj;
		m_obj = 0;
		return obj;
	}

	T* get()
	{
		return m_obj;
	}

public:
	operator T*&(){ return m_obj; }

	T* operator->() { return m_obj; }
	const T* operator->() const { return m_obj; }

public:
	auto_obj(const auto_obj<T>& o)
	{
		m_obj = o.m_obj;
		m_obj->addref();
	}

	auto_obj& operator= (const auto_obj<T>& o)
	{
		attach(o.m_obj);
		m_obj->addref();
		return *this;
	}

private:
	T* m_obj;
};

} // namespace

#endif /* !_libct_auto_obj_ */
