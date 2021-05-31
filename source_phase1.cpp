/* notes
1. 全部函数，变量用类封装 不要使用全局变量
*/

#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
/*-------------------------------------------------------*/

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
/*-----------------------------------------------------*/

#define SELLER 1
#define CONSUMER 2

#define FOOD 11
#define CLOTH 12
#define BOOK 13

#define CART_SIZE 20
#define MAX_PRODUCT 50 // max product count for each seller

#define HASH_MOD 200
/*-----------------------------------------------------*/
class account {
public:
  account(string name_ = NULL, string password_ = NULL, float balance_ = 0)
      : name(name_), password(password_), balance(balance_){};
  // virtual ~account();

  virtual int GetBalence() { return this->balance; };
  virtual bool SubBalance(float withdraw) {
    if (this->balance > 0) {
      this->balance -= withdraw;
      return true;
    } else
      return false;
  }
  virtual bool AddBalance(float topup) {
    if (topup >= 0) {
      this->balance += topup;
      return true;
    } else
      return false;
  }

  virtual string GetName() { return this->name; }
  virtual bool ChangeName(string new_name) {
    this->name = new_name;
    return true;
  };

  virtual int GetUserType() = 0;

  virtual bool checkPassword(string input) { return input == this->password; }
  virtual bool changePassword(string origin, string new_) {
    if (origin == this->password) {
      this->password = new_;
      return true;
    } else
      return false;
  }

private:
  string name;
  string password;
  float balance;
};
/*
    account format in file: type_code name password balance
*/
class seller : public account {
public:
  seller(string name_ = NULL, string password_ = NULL, float balance_ = 0)
      : account(name_, password_, balance_){};
  int GetUserType() { return SELLER; }
  class product *_product; // pointer to product
};

class consumer : public account {
public:
  consumer(string name_ = NULL, string password_ = NULL, float balance_ = 0)
      : account(name_, password_, balance_){};
  int GetUserType() { return CONSUMER; }
  //   cart_product * cart
};

class product {
public:
  product(string Descrip_ = NULL, float Price_ = 0, int Stock_ = 0)
      : Descrip(Descrip_), Price(Price_), Stock(Stock_){};
  virtual ~product(){};

  virtual string GetDscrip() { return Descrip; };
  virtual bool ChangeDscrip(string new_des) {
    this->Descrip = new_des;
    return true;
  };

  virtual bool ChangePrice(float new_price) {
    this->Price = new_price;
    return 1;
  };
  virtual float GetPrice() { return Price; };

  virtual bool ChangeStock(int offset) {
    if (this->Stock + offset >= 0) {
      this->Stock += offset;
      return true;
    } else
      return false;
  }
  virtual bool SetStock(int new_stock) {
    this->Stock = new_stock;
    return true;
  }
  virtual int GetStock() { return Stock; };

  virtual int GetProductType() = 0;

private:
  string Descrip;
  float Price;
  int Stock;
};

class food : public product {
public:
  food(string Descrip_ = NULL, float Price_ = 0, int Stock_ = 0)
      : product(Descrip_, Price_, Stock_), type(FOOD){};

private:
  int type;
};
class cloth : public product {
public:
  cloth(string Descrip_ = NULL, float Price_ = 0, int Stock_ = 0)
      : product(Descrip_, Price_, Stock_), type(CLOTH){};

private:
  int type;
};
class book : public product {
public:
  book(string Descrip_ = NULL, float Price_ = 0, int Stock_ = 0)
      : product(Descrip_, Price_, Stock_), type(BOOK){};

private:
  int type;
};
class Platform {
public:
  void init_load_file(); // load in user and product
  void login_signin();
  void print_all(int type); // print all_seller or all_counsumer

private:
  vector<struct seller> all_seller;
  vector<struct consumer> all_consumer;
};
/*-------------------------------------------------------*/

/*-----------------------------------------------------*/

int main() {
  Platform platform;
  platform.init_load_file();
  //   platform.login_signin();
  //   string input;
  //   while (true) {
  //     cin >> input;
  //   }
  return 0;
}

void Platform::init_load_file() {
  // loading accounts;
  std::ifstream fin;
  string name, password;
  float balance;
  int type;

  fin.open("account.txt");
  if (!fin.is_open())
    cout << "FAIL TO OPEN account.txt" << std::endl;
  else {
    while (!fin.eof()) {
      fin >> type >> name >> password >> balance;
      if (type == SELLER) {
        seller sler(name, password, balance);
        all_seller.push_back(sler);

      } else {
        consumer csmr(name, password, balance);
        all_consumer.push_back(csmr);
      }
    }
  }
  print_all(SELLER);
  print_all(CONSUMER);
}
void Platform ::print_all(int type) {
  switch (type) {
  case SELLER:
    cout << "----------PRINTING ALL SELLER------------" << endl;
    for (int i = 0; i < all_seller.size(); i++) {
      cout << all_seller[i].GetName() << all_seller[i].GetBalence() << endl;
    }
    cout << "--------------END OF PRINTING---------------" << endl;
    break;

  case CONSUMER:
    cout << "----------PRINTING ALL CONSUMER------------" << endl;
    for (int i = 0; i < all_consumer.size(); i++) {
      cout << all_consumer[i].GetName() << all_consumer[i].GetBalence() << endl;
    }
    cout << "--------------END OF PRINTING---------------" << endl;
    break;
  }
}