#pragma once
#include <vector>
#include <list>
#include <unordered_map>


template <typename keyType, typename valType, typename hashFunc = std::hash<keyType>>
class HashMap
{
	using pair = std::pair<keyType, valType>;
	using listPointer = std::list<pair>::iterator;

	std::vector<listPointer> m_table;
	std::list<pair> m_list;
	int m_elementsCount;
	int m_size;
	double m_loadFactor;

	void rehash();
public:
	HashMap(int size = 10);

	void insert(const pair& p);
	bool find(const keyType& key);
	void erase(const keyType& key);
};