#ifndef LINEARPROBING_H
#define LINEARPROBING_H

#include "BaseClass.h"
#include <iostream>

class LinearProbing : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    // Other data members and functions specific to Linear Probing
    int database_size = 0;
    std::vector<int> balances;
};

#endif // LINEARPROBING_H
