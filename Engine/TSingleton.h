#pragma once

/*
http://scottbilas.com/publications/gem-singleton/
*/

template <class T> class TSingleton 
{
    static T* m_istance;

public:

    TSingleton() {
        if (m_istance == nullptr) {
            //m_istance = new T;
            //If the class T inherit TSingleton
            m_istance = static_cast <T*> (this);
        }
    }

    ~TSingleton() {
        if (m_istance != nullptr) {
            //delete m_istance; //this doesn't work 
            m_istance = 0;
        }
    }

    static T* GetSingleton()
    {
        if (m_istance != nullptr) {
            return m_istance;
        }
        else {
            nullptr;
        }
    }
};

template <typename T> 
T* TSingleton <T>::m_istance = 0;