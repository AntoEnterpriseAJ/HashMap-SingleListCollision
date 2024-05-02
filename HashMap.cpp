#include "HashMap.h"

template<typename keyType, typename valType, typename hashFunc>
HashMap<keyType, valType, hashFunc>::HashMap(int size)
	: m_pos{ size, nullptr }, m_list{}, m_elementsCount{0}, m_size{size}, m_loadFactor{0}
{}


