# Banking-Data-Management-System
This project puts into practice a hashmap-based bank account information management system. The system employs diverse collision resolution techniques to effectively store and retrieve account information.

## Introduction

The project models a situation in which a bank keeps a database with millions of customer accounts. The system uses a hashmap to map account identifiers (IFSC code and account number) to the corresponding account information in order to facilitate efficient data access and retrieval.

## Hashmap Implementation

A custom `BankData` class is used to implement the hashmap. The class provides methods for opening, changing, and accessing bank accounts. It also employs various collision resolution techniques to manage scenarios in which many accounts map to the same hash index.

## Colission Resolution Techniques

There are four collision resolution strategies used in the project:

1. **Chaining** To keep accounts with the same hash code, this technique builds linked lists at each hash table index.
2. **Linear Probing** This method linearly searches(probes) successive hash table slots until it locates an empty slot.
3. **Quadratic Probing** To be more fairly distributed collisions, this technique uses a quadratic function to probe adjacent hash table slots.
4. **Cubic Probing** To disperse collisions even more, this method uses a cubic function to explore subsequent hash table slots.

### The unique ID for a bank account will be :
    <#11 digit IFSC Code>_<10 digit account number>

### Here, we have made the size of hash table to 100000, which means data of unique 10000 accounts can be stored in this hash table.

# Functions Descriptions

| Function                              | Description                                                                                                           |
| ------------------------------------- | --------------------------------------------------------------------------------------------------------------------- |
| `createAccount(string id, int count)` | Creates a new account with the given `id` and initial `count` value. The `id` uniquely identifies the account.        |
| `getTopK(int k)`                      | Retrieves the top `k` balances values from the database. Returns a vector containing at most `k` balances values.    |
| `getBalance(string id)`               | Returns the current balance of the account identified by the provided `id`. In case the `id` is not present, return -1. |
| `addTransaction(string id, int count)`| Adds a transaction of `count` value to the account specified by the `id`. If the account is not present, create a new one and then add this transaction. Transactions can be positive or negative. |
| `doesExist(string id)`                 | Checks if an account with the given `id` exists in the database. Returns true if the account exists, and false otherwise. |
| `databaseSize()`                       | Returns the total number of accounts currently stored in the database.                                                 |
| `hash(string id)`                      | Computes the hash value for the given `id`. Use this hash function only in your strategies.                           |
| `delete(string id)`                    | Deletes the key stored in the database. Returns true after deletion. If the key was not present, returns false.         |

## Let's Goo and start run this code
If you want to run this project then you will need to follow these three steps

1. Clone the project repository.

2. Compile the project using a C++ compiler.

3. Execute the compiled program.

## It contains following Files : 

1. **`BaseClass.h`** -> 
2. **`Chaining.h`**
3. **`Chaining.cpp`**
4. **`LinearProbing.h`**
5. **`LinearProbing.cpp`**
6. **`QuadraticProbing.h`**
7. **`QuadraticProbing.cpp`**
8. **`CubicProbing.h`**
9. **`CubicProbing.cpp`**











