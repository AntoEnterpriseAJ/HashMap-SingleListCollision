#include <vector>
#include <list>
#include <iostream>

template <typename keyType, typename valType, typename hashFunc = std::hash<keyType>>
class HashMap
{
public:
	using pair = std::pair<keyType, valType>;
	using iterator = typename std::list<pair>::iterator;
	using startPointer = std::pair<iterator, bool>;
	using bucket = std::pair<startPointer, int>;

	HashMap(int size = 10);

	iterator begin() { return std::next(m_list.begin()); }
	iterator end() { return m_list.end(); }

	void insert(const pair& p);
	bool find(const keyType& key) const;
	void erase(const keyType& key);
	void printBuckets() const;
	valType& operator[](keyType key);

private:
	static constexpr double resizeFactor = 7.0 / 4;

	std::vector<bucket> m_table;
	std::list<pair> m_list;
	int m_elementsCount;
	int m_size;
	double m_loadFactor;

	void rehash();
};

template<typename keyType, typename valType, typename hashFunc>
valType& HashMap<keyType, valType, hashFunc>::operator[](keyType key)
{
	std::size_t index = hashFunc()(key) % m_size;
	const bucket& bucketToSearch = m_table[index];
	int bucketLength = m_table[index].second;

	if (bucketToSearch.first.second == false) //create a bucket
	{
		insert({ key, {} });
		const bucket& bucketToinsert = m_table[hashFunc()(key) % m_size];
		return std::next(bucketToinsert.first.first)->second;
	}

	auto it = bucketToSearch.first.first; // element before
	it++;

	bool found = false;
	while (bucketLength--)
	{
		if (it->first == key)
		{
			found = true;
			break;
		}
		it++;
	}

	if (!found)
	{
		insert({ key, {} });
		return std::next(bucketToSearch.first.first, 1)->second;
	}
	return it->second;
}


template<typename keyType, typename valType, typename hashFunc>
void HashMap<keyType, valType, hashFunc>::printBuckets() const
{
	int i = 0;
	for (const auto& bucket : m_table)
	{
		if (bucket.first.second)
		{
			int length = bucket.second;
			auto firstIt = bucket.first.first;
			std::cout << "bucket" << i++ << ":";
			while (length--)
			{
				firstIt++;
				std::cout << "(" << firstIt->first << ", " << firstIt->second << ") ";
			}
			std::cout << '\n';
		}
	}
	std::cout << '\n';
}

template<typename keyType, typename valType, typename hashFunc>
HashMap<keyType, valType, hashFunc>::HashMap(int size)
	: m_table{ static_cast<size_t>(size), { { {}, false}, 0} }, m_list{}, m_size{ size }, m_elementsCount{ 0 }, m_loadFactor{ 0 }
{
	m_list.push_back({ -1, -1 }); //dummy node
}

template<typename keyType, typename valType, typename hashFunc>
void HashMap<keyType, valType, hashFunc>::rehash()
{
	std::list<pair> temp{ m_list };
	m_list.clear(), m_list.push_back({ -1, -1 }); //dummy node
	m_table.clear(), m_size = m_size * resizeFactor, m_elementsCount = 0; // ?
	m_table.resize(m_size, { { {}, false}, 0 });
	m_loadFactor = static_cast<double>(m_elementsCount) / m_size;

	for (auto it = std::next(temp.begin()); it != temp.end(); ++it)
	{
		insert(*it);
	}
}

template<typename keyType, typename valType, typename hashFunc>
void HashMap<keyType, valType, hashFunc>::insert(const pair& p)
{
	std::size_t index = hashFunc()(p.first) % m_size;

	if (!m_table[index].first.second)
	{
		m_table[index] = { {std::prev(m_list.end()), true}, 1 };
		m_list.push_back(p);
		m_elementsCount++;
	}
	else
	{
		int bucketLength = m_table[index].second;
		auto it = m_table[index].first.first; // element before;
		it++;

		//check if it is already inserted
		while (bucketLength--)
		{
			if (it->first == p.first)
			{
				it->second = p.second;
				return;
			}
		}

		m_elementsCount++;
		auto pos = m_table[index].first.first;
		m_list.insert(++pos, p);
		m_table[index].second++;
	}

	m_loadFactor = static_cast<double>(m_elementsCount) / m_size;
	if (m_loadFactor > 1.0)
	{
		rehash();
	}
}

template<typename keyType, typename valType, typename hashFunc>
bool HashMap<keyType, valType, hashFunc>::find(const keyType& key) const
{
	std::size_t index = hashFunc()(key) % m_size;
	const bucket& bucketToSearch = m_table[index];
	int bucketLength = m_table[index].second;

	if (bucketToSearch.first.second == false) return false;

	auto it = bucketToSearch.first.first; // element before
	it++;

	while (bucketLength--)
	{
		if (it->first == key) return true;
		it++;
	}

	return false;
}

template<typename keyType, typename valType, typename hashFunc>
void HashMap<keyType, valType, hashFunc>::erase(const keyType& key)
{
	std::size_t index = hashFunc()(key) % m_size;
	int bucketLength = m_table[index].second;


	if (m_table[index].first.second == false) return;

	auto elementIt = m_table[index].first.first; // element before the bucket
	elementIt++;

	//search the element
	int pos = 0;
	while (pos < bucketLength)
	{
		if (elementIt->first == key)
		{
			m_elementsCount--, m_loadFactor = static_cast<double>(m_elementsCount) / m_size;

			//element we want to delete could be the start of another bucket
			if (pos == bucketLength - 1)
			{
				if (std::next(elementIt, 1) != m_list.end())
				{
					m_table[hashFunc()(std::next(elementIt, 1)->first) % m_size].first.first = std::next(elementIt, -1);
				}
			}
			m_list.erase(elementIt);

			if (bucketLength == 1)
			{
				m_table[index].first.second = false; //delete iterator to the start of the bucket
			}

			m_table[index].second--;
			return;
		}
		pos++;
		elementIt++;
	}
}