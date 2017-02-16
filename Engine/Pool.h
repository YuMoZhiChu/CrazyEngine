#pragma once

#include <vector>

namespace Engine {

	template <class Object>
	class Pool;

	template <class Object>
	class PoolObject {
		Object* Element;
		PoolObject* NextElement = nullptr;
		bool state = true;
	public:
		Object* getElement() {
			return Element;
		}

		void draw() {
			Object->draw();
		}

		friend class Pool<Object>;
	};

	template <class Object>
	class Pool {
		std::vector<PoolObject<Object>*> m_Elements;
		PoolObject<Object>* m_NextFreeElement;
		PoolObject<Object>* m_PrevFreeElement;

	public:
		Pool();
		Pool(int size);

		void addElement(Object* newObject);

		~Pool() {
			for each (auto it in m_Elements) {
				delete it;
			}
		}

		PoolObject<Object>* getElement();
		void returnElement(PoolObject<Object>* element);

		std::vector<PoolObject<Object>*>& getElements() {
			return m_Elements;
		}
	};


	template <class Object>
	Pool<Object>::Pool():
		m_NextFreeElement(nullptr),
		m_PrevFreeElement(nullptr)
	{}

	template <class Object>
	Pool<Object>::Pool(int size) : m_PrevFreeElement(nullptr)
	{
		if (size > 0) {
			PoolObject<Object>* newElement = new PoolObject<Object>;
			m_Elements.push_back(newElement);

			for (int i = 1; i < size; i++) {
				PoolObject<Object>* newElement = new PoolObject<Object>;
				m_Elements.push_back(newElement);
				m_Elements[i - 1]->NextElement = m_Elements[i];
			}
		}
		m_NextFreeElement = m_Elements[0];
	};


	template <class Object>
	void Pool<Object>::addElement(Object* newObject) {
		PoolObject<Object>* newElement = new PoolObject<Object>;
		newElement->Element = newObject;
		m_Elements.push_back(newElement);
		if (m_NextFreeElement != nullptr) {
			m_PrevFreeElement = m_NextFreeElement;
			m_NextFreeElement = newElement;
			m_PrevFreeElement->NextElement = m_NextFreeElement;
		}
		else {
			m_NextFreeElement = newElement;
		}
	}


	template <class Object>
	PoolObject<Object>* Pool<Object>::getElement() {
		m_PrevFreeElement = m_NextFreeElement;
		m_PrevFreeElement->state = false;
		m_NextFreeElement = m_NextFreeElement.NextElement;
		return m_PrevFreeElement;
	};

	template <class Object>
	void Pool<Object>::returnElement(PoolObject<Object>* element) {
		m_PrevFreeElement = m_NextFreeElement;
		m_NextFreeElement = element;
		m_NextFreeElement.NextElement = m_PrevFreeElement;
		m_NextFreeElement->state = true;
	};

}



	

	
	
	