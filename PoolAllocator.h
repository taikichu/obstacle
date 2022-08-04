#pragma once

#include <algorithm>
#include <cassert>

// class Tを最大MAXSIZE個確保可能なPoolAllocatorを実装してください
//配列ではだめ?
template<class T, size_t MAXSIZE>
class PoolAllocator
{
public:
	// コンストラクタ
	PoolAllocator() {
		// TODO: 必要に応じて実装してください
		m_buffer = new Element[MAXSIZE];
		for (size_t i = 0; i < MAXSIZE; ++i)
		{
			if (i == MAXSIZE - 1)
			{
				m_buffer[i].next = nullptr;
			}
			else
			{
				m_buffer[i].next = m_buffer + i + 1;
			}
		}
		m_free = m_buffer;
		m_allocCount = 0;
	}

	// デストラクタ
	~PoolAllocator() {
		// TODO: 必要に応じて実装してください
		//割り当て済みの状態で破棄されたら破壊される。
		//エラー
		assert(m_allocCount == 0);

		delete[] m_buffer;
	}
	// 確保できない場合はnullptrを返す事。
	T* Alloc() {
		// TODO: 実装してください
		if (m_free == nullptr)return nullptr;
		Element* next = m_free->next;
		//PlacementNewでコンストラクタを呼び出す
		T* t = new(m_free->buf) T;
		m_free = next;
		return t;
	}

	// Free(nullptr)で誤動作しないようにする事。
	void Free(T* addr) {
		if (!addr)return;

		//デストラクタ呼び出し
		addr->~T();
		//解放
		Element* next = m_free;
		m_free = reinterpret_cast<Element*>(addr);
		m_free->next = next;
	}

private:
	// TODO: 実装してください
	struct Element
	{
		union
		{
			char buf[sizeof(T)];
			Element* next;
		};
	};
	Element* m_buffer;
	Element* m_free;

	unsigned int m_allocCount;
};
