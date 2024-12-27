#include "Chaining.h"

void Chaining::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    Account a;
    a.balance = count;
    a.id = id;
    int hv = hash(id);
    if (hv > size_of_database){
        bankStorage2d.resize(100001);
    }
    bankStorage2d[hv].push_back(a);
    size_of_database++;
    balances.push_back(0);
    int ite = balances.size() - 2;
    while(ite >= 0){
        if(balances[ite] > count){
            balances[ite+1] = balances[ite];
        }
        else if(balances[ite] <= count){
            balances[ite+1] = count;
            break;
        }
        ite--;
    }
    if(ite == -1){
        balances[0] = count;
    }
    
}

std::vector<int> Chaining::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    std::vector<int> ans;
    int i = 0;
    int n = balances.size() - 1;
    while(i < k){
        ans.push_back(balances[n-i]);
        i++;
    }
    return ans; // 
}

int Chaining::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int hv = hash(id);
    int size_of_chain = bankStorage2d[hv].size();
    for (int i = 0; i < size_of_chain; i++)
    {
        if( bankStorage2d[hv][i].id == id){
            return bankStorage2d[hv][i].balance;
        }
    }
    
    return -1; // 
}

void Chaining::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int hv = hash(id);
    int size_of_chain = bankStorage2d[hv].size();
    for (int i = 0; i < size_of_chain; i++)
    {
        if(bankStorage2d[hv][i].id == id){
            int bal = bankStorage2d[hv][i].balance;
            bankStorage2d[hv][i].balance = bal + count;
            int comp = bal+count;

            int start = 0;
            int end = balances.size() - 1;
            int mid;
            while(start <= end){
                mid = (start + end)/2;
                if(balances[mid] == bal){
                    break;
                }
                else if(balances[mid] > bal){
                    end = mid - 1;
                }
                else{
                    start = mid + 1;
                }
            }
            if(count<0){
                while(mid >= 1){
                    if(balances[mid - 1] > comp){
                        balances[mid] = balances[mid - 1];
                        mid--;
                    }
                    else if(balances[mid-1] <= comp){
                        balances[mid] = comp;
                        break;
                    }
                }
                if(mid == 0){
                    balances[0] = comp;
                }
            }
            else if(count>0){
                int n = balances.size();
                while(mid < n-1){
                    if(balances[mid + 1] < comp){
                        balances[mid] = balances[mid + 1];
                        mid++;
                    }
                    else if(balances[mid+1] >= comp){
                        balances[mid] = comp;
                        break;
                    }
                }
            if(mid == n-1){
                balances[n-1] = comp;
            }  
            }
            return;
        }
    }
    
    createAccount(id,count);

    

}

bool Chaining::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int hv = hash(id);
    int size_of_chain = bankStorage2d[hv].size();
    for (int i = 0; i < size_of_chain; i++)
    {
        if(bankStorage2d[hv][i].id == id){
            return true;
        }
    }
    return false; // 
}

bool Chaining::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int hv = hash(id);
    int bal_to_del;
    int size_of_chain = bankStorage2d[hv].size();
    for (int i = 0; i < size_of_chain; i++)
    {
        if(bankStorage2d[hv][i].id == id){
            bal_to_del = bankStorage2d[hv][i].balance;
            // if account exist then for deletion id will be change to -1
            bankStorage2d[hv].erase(bankStorage2d[hv].begin()+i);
            size_of_database -= 1;

            // binary search for bal_to_del
            int start = 0;
            int end = balances.size();
            int mid = 0;
            while(start <= end){
                mid = (start + end)/2;
                if(balances[mid] == bal_to_del){
                    break;
                }
                else if(balances[mid] > bal_to_del){
                    end = mid - 1;
                }
                else{
                    start = mid + 1;
                }
            }
            balances.erase(balances.begin()+mid);
            return true;
        }
    }

    return false; // 
}
int Chaining::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return size_of_database; // 
}

int Chaining::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int M = 100001;
    int hv = 0, fac = 1;
    int multi = 256;
    for (int i = 0; i < id.length(); i++) {
        if(i % 4 == 0){
           fac = 1; 
        }
        else{
            fac = fac*multi;
        }
        hv += id[i] * fac;
    }
    return abs(hv % M);
}
