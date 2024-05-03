#include "HashMap.h"

template<typename keyType, typename valType, typename hashFunc>
HashMap<keyType, valType, hashFunc>::HashMap(int size)
	: m_table{ 10, nullptr }, m_list{}, m_size{ size }, m_elementsCount{ 0 }, m_loadFactor{ 0 }
{
	m_list.push_back({ -1, -1 }); //dummy node
}

template<typename keyType, typename valType, typename hashFunc>
void HashMap<keyType, valType, hashFunc>::rehash()
{
	m_table.clear();
	m_table.resize((7 * m_size) / 4);

	for (const auto& pair : m_list)
	{
		insert(pair);
	}
}

template<typename keyType, typename valType, typename hashFunc>
void HashMap<keyType, valType, hashFunc>::insert(const pair& p)
{
	std::size_t index = hashFunc(p.first) % m_size;
	m_elementsCount++;

	if (m_table[index] == nullptr)
	{
		m_list.push_back(p);
		m_table[index] = m_list.begin() - 2;
	}
	else
	{
		m_list.insert(m_table[index], pair);
	}

	m_loadFactor = m_elementsCount / m_size;
	if (m_loadFactor > 1.0)
	{
		rehash();
	}
}
