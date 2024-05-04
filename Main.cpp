#include "HashMap.h"
#include <iostream>
#include <fstream>

void printMenu()
{
	std::cout << "Menu:\n";
	std::cout << "1. Insert\t\t2. Find\t\t3. Erase\n";
	std::cout << "4. Print Buckets\t5. printMenu\t6. Exit\n";
}

template<typename keyType, typename valType, typename hashFunc>
void readMap(HashMap<keyType, valType, hashFunc>& map, const std::string& fileName)
{
	std::ifstream fin(fileName);
	if (!fin.is_open())
	{
		std::cerr << "Error opening the file\n";
		return;
	}
	keyType key;
	valType val;
	while (fin >> key >> val)
	{
		map.insert({ key, val });
	}
}

struct Hash
{
	const uint64_t hashKey(uint64_t k) const {
		// MurmurHash64A
		const uint64_t m = 0xc6a4a7935bd1e995;
		const int r = 47;
		uint64_t h = 0x8445d61a4e774912 ^ (8 * m);
		k *= m;
		k ^= k >> r;
		k *= m;
		h ^= k;
		h *= m;
		h ^= h >> r;
		h *= m;
		h ^= h >> r;
		return h;
	}

	size_t operator()(uint64_t key) const
	{
		return hashKey(key);
	}
};

int main()
{
	std::string fileName("hashMapInput.txt");
	HashMap<int, int, Hash> map;
	readMap(map, fileName);

	printMenu();
	int choice;
	do {
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
		{
			std::cout << "Element to be inserted (key, value): ";
			int key, val;
			std::cin >> key >> val;
			map.insert({ key, val });
			break;
		}
		case 2:
		{
			std::cout << "Key to be found: ";
			int key;
			std::cin >> key;
			map.find(key) ? std::cout << "found the key\n" : std::cout << "the key doesn't exit\n";
			break;
		}
		case 3:
		{
			std::cout << "Key to be erased: ";
			int key;
			std::cin >> key;
			map.erase(key);
			break;
		}
		case 4:
		{
			map.printBuckets();
			break;
		}
		case 5:
		{
			printMenu();
			break;
		}
		case 6:
		{
			std::cout << "Exiting...\n";
			break;
		}
		default:
		{
			std::cout << "Invalid choice. Please try again.\n";
			break;
		}
		}

	} while (choice != 6);

	return 0;
}