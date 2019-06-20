#ifndef SINGLETON_H
#define SINGLETON_H

///////////////////////////////////////////////////////////////////////////////
// Singleton implementation

template <class T>
class Singleton
{
public:
        static  T*   GetInstance();
        static  bool HasInstance();
        static  void FreeInstance();
        virtual void Init() {};

protected:
        Singleton();
        virtual ~Singleton();

private:
        static T* s_instance;
};

//////////////////////////////////////////////////////////////////////////

template <class T>
T* Singleton<T>::s_instance = nullptr;

//////////////////////////////////////////////////////////////////////////

template <class T>
T* Singleton<T>::GetInstance()
{
        // doesn't create the instance automatically
        if (s_instance == nullptr)
        {
                s_instance = new T();
        }

        return s_instance;
}

//////////////////////////////////////////////////////////////////////////

template <class T>
bool Singleton<T>::HasInstance()
{
        return s_instance != nullptr;
}

//////////////////////////////////////////////////////////////////////////

template <class T>
void Singleton<T>::FreeInstance()
{
        delete s_instance;
        s_instance = nullptr;
}

//////////////////////////////////////////////////////////////////////////

template <class T>
Singleton<T>::Singleton()
{
        if (s_instance == nullptr)
        {
                s_instance = dynamic_cast<T*>(this);
        }
}

//////////////////////////////////////////////////////////////////////////

template <class T>
Singleton<T>::~Singleton()
{
        s_instance = nullptr;
}

//
///////////////////////////////////////////////////////////////////////////////

#endif // SINGLETON_H
