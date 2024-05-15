# HashMap Implementation using a single list for colission handling

This repository contains a C++ implementation of a hash map utilizing a single list for handling colissions. In this implementation, a single large linked list is used to store all elements, and a vector of pointers to the node before the start of each bucket is employed for quick access.

![hashmap](https://github.com/AntoEnterpriseAJ/HashMap-SingleListCollision/assets/152036671/7b2e9f38-66f7-4148-a63a-92787eb00d02)

## Features

- **Template-based**: The hash map is implemented as a template class, allowing for flexibility in the types of keys and values it can store.
- **Hashing Function**: The implementation includes a customizable hashing function. By default, it utilizes `std::hash`, but users can also provide their own hashing function.
- **Dynamic Resizing**: The hash map automatically resizes itself when the load factor exceeds a certain threshold, ensuring efficient performance even with changing numbers of elements.
- **Basic Operations**: Supports standard operations like insertion, search, and deletion of key-value pairs. Additionally, it provides iterators for traversal.

## Usage

To use this hash map implementation, follow these steps:

1. **Include the Header**: Include the `HashMap.h` header file in your C++ project.
2. **Instantiate the HashMap**: Create an instance of the `HashMap` class with appropriate template arguments.
3. **Perform Operations**: Use the provided methods (`insert`, `find`, `erase`, etc.) to manipulate the hash map.

Example:

```cpp
#include "HashMap.h"

int main() {
    // Instantiate a HashMap with integer keys and values
    HashMap<int, int> map;

    // Insert key-value pairs
    map.insert({1, 10});
    map.insert({2, 20});

    // Find a key
    if(map.find(1))
        std::cout << "Key 1 found!\n";

    // Erase a key
    map.erase(2);

    return 0;
}
```

## Customization

- **Hashing Function**: Users can provide their own hashing function by specifying it as a template argument when instantiating the `HashMap` class.
- **Load Factor Threshold**: The resizing behavior can be adjusted by modifying the `resizeFactor` constant in the `HashMap` class.

## File Structure

- `HashMap.h`: Contains the implementation of the `HashMap` class.
- `main.cpp`: Example usage of the hash map implementation, including a menu-based interface for interaction.
- `hashMapInput.txt`: Sample input file containing key-value pairs to initialize the hash map.

## Contributing

This project was created for study purposes. Contributions are welcome but not actively sought.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE.md) file for details.
