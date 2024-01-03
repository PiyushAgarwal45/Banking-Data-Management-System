#include "CubicProbing.h"

void CubicProbing::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    if(bankStorage1d.size() == 0){
        for (int i = 0; i < 100001; i++)
        {
            Account a;
            a.id = "";
            a.balance = 0;
            bankStorage1d.push_back(a);
            /* code */
        }
    }
    int probe = 1;
    int hv = hash(id);
    while (bankStorage1d[hv].id != "" && bankStorage1d[hv].id != "-1"){
        hv = (hv + (probe*probe*probe))%100001;
        probe++;
    }
    bankStorage1d[hv].id = id;
    bankStorage1d[hv].balance = count;
    database_size++;

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

std::vector<int> CubicProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    std::vector<int> ans;
    int i = 0;
    int n = balances.size() - 1;
    while(i < k){
        ans.push_back(balances[n-i]);
        i++;
    }
    return ans; // Placeholder return value
}

int CubicProbing::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int hv = hash(id);
    int probe = 1;
    while(bankStorage1d[hv].id != ""){
        if(bankStorage1d[hv].id == id){
            return bankStorage1d[hv].balance;
        }
        hv = (hv + (probe*probe*probe))%100001;
        probe++;
    }
    return -1; // Placeholder return value
}

void CubicProbing::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int hv = hash(id);
    int probe = 1;
    while(bankStorage1d[hv].id != ""){
        if(bankStorage1d[hv].id == id){
            int bal = bankStorage1d[hv].balance;
            bankStorage1d[hv].balance = bal + count;
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
        hv = (hv + (probe*probe*probe))%100001;
        probe++;
    }
    createAccount(id,count);
}

bool CubicProbing::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int hv = hash(id);
    int probe = 1;
    while(bankStorage1d[hv].id != ""){
        if(bankStorage1d[hv].id == id){
            return true;
        }
        hv = (hv + (probe*probe*probe))%100001;
        probe++;
    }
    return false; // Placeholder return value
}

bool CubicProbing::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int hv = hash(id);
    int probe = 1;
    while (bankStorage1d[hv].id != "")
    {
        if(bankStorage1d[hv].id == id){
            int bal_to_del = bankStorage1d[hv].balance;
            bankStorage1d[hv].id = "-1"; 
            database_size--;

            // binary search for bal_to_del
            int start = 0;
            int end = balances.size() - 1;
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
        hv = (hv + probe*probe*probe)%100001;
        probe++;
    }
    return false; // Placeholder return value
}
int CubicProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return database_size; // Placeholder return value
}

int CubicProbing::hash(std::string id) {
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

    // Placeholder return value
}
