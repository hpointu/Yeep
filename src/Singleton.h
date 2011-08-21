#ifndef SINGLETON_H
#define SINGLETON_H

/**
  Un template à utiliser pour standardiser nos classes singleton
*/

template <typename T> class Singleton
{
protected:
	Singleton () { }
	~Singleton () { }

public:
	static T *getInstance ()
	{
		if (0 == _singleton)
		{
			_singleton = new T;
		}
		return (static_cast<T*> (_singleton));
	}
	static void kill ()
	{
		if (0 != _singleton)
		{
			delete _singleton;
			_singleton = 0;
		}
	}

private:
	static T *_singleton;
};

template <typename T> T *Singleton<T>::_singleton = 0;


#endif
