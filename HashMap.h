#pragma once
#include <vector>
#include <list>
#include <unordered_map>


template <typename keyType, typename valType, typename hashFunc = std::hash<keyType>>
class HashMap
{
	uning pair = std::pair<keyType, valType>;

	std::vector<std::list<pair>::iterator> m_pos;
	std::list<pair> m_list;
	int m_elementsCount;
	int m_size;
	double m_loadFactor;
public:
	HashMap(int size = 10);
	void insert(pair p);
	bool find(const keyType& key);
	void erase(const keyType& key);
};