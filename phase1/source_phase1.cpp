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
using std::setfill;
using std::setw;
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

#define FORMAT_NAME_WID 25
#define FORMAT_PRICE_WID 12
#define FORMAT_BAR_FRONT 40
#define FORMAT_BAR_RARE 25
/*-----------------------------------------------------*/
class account {
public:
  account(string name_ = NULL, string password_ = NULL, float balance_ = 0,
          unsigned int id_ = 0)
      : name(name_), password(password_), balance(balance_), id(id_){};
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
  virtual unsigned int Getid() { return id; }

private:
  string name;
  string password;
  float balance;
  unsigned int id;
};
/*
    account format in file: type_code name password balance id
    product format in file: type description price stock id seller_id
*/
class seller : public account {
public:
  seller(string name_ = NULL, string password_ = NULL, float balance_ = 0,
         unsigned int id_ = 0)
      : account(name_, password_, balance_, id_){};
  int GetUserType() { return SELLER; }
  class product *_product; // pointer to product
};

class consumer : public account {
public:
  consumer(string name_ = NULL, string password_ = NULL, float balance_ = 0,
           unsigned int id_ = 0)
      : account(name_, password_, balance_, id_){};
  int GetUserType() { return CONSUMER; }
  //   cart_product * cart
};

class product {
public:
  product(string Descrip_ = NULL, float Price_ = 0, int Stock_ = 0,
          unsigned int id_ = 0, unsigned int seller_id_ = 0)
      : Descrip(Descrip_), Price(Price_), Stock(Stock_), seller_id(seller_id_),
        id(id_){};
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
  virtual unsigned int GetId() { return id; };
  virtual unsigned int GetSellerId() { return seller_id; };

private:
  string Descrip;

  float Price;
  int Stock;
  unsigned int seller_id;
  unsigned int id;
};

class food : public product {
public:
  food(string Descrip_ = NULL, float Price_ = 0, int Stock_ = 0,
       unsigned int id_ = 0, unsigned int seller_id_ = 0)
      : product(Descrip_, Price_, Stock_, id_, seller_id_), type(FOOD){};
  int GetProductType() { return type; }

private:
  int type;
};
class cloth : public product {
public:
  cloth(string Descrip_ = NULL, float Price_ = 0, int Stock_ = 0,
        unsigned int id_ = 0, unsigned int seller_id_ = 0)
      : product(Descrip_, Price_, Stock_, id_, seller_id_), type(CLOTH){};
  int GetProductType() { return type; }

private:
  int type;
};
class book : public product {
public:
  book(string Descrip_ = NULL, float Price_ = 0, int Stock_ = 0,
       unsigned int id_ = 0, unsigned int seller_id_ = 0)
      : product(Descrip_, Price_, Stock_, id_, seller_id_), type(BOOK){};
  int GetProductType() { return type; }

private:
  int type;
};
class Platform {
public:
  void init_load_file(); // load in user and product
  void login_signin();
  void print_all_pdt(int type); // print all_product in type
  void print_all_act(int type); // print all_seller or all_counsumer
  void show_option();
  void write_back_file();

private:
  vector<seller> all_seller;
  vector<consumer> all_consumer;
  account *cur_account;

  vector<book> all_book;
  vector<cloth> all_cloth;
  vector<food> all_food;
};
/*-------------------------------------------------------*/

/*-----------------------------------------------------*/

int main() {
  Platform platform;

  platform.init_load_file();

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
  unsigned int id;
  int type;

  fin.open("account.txt");
  if (!fin.is_open())
    cout << "FAIL TO OPEN account.txt" << std::endl;
  else {
    while (fin.peek() != EOF) {
      fin >> type >> name >> password >> balance >> id;
      print_all_act(SELLER);
      print_all_act(CONSUMER);
      if (type == SELLER) {
        seller sler(name, password, balance, id);
        all_seller.push_back(sler);
      }
      if (type == CONSUMER) {
        consumer csmr(name, password, balance, id);
        all_consumer.push_back(csmr);
      }
    }
  }
  fin.close();
  fin.open("product.txt");
  string descrip, s_sler;
  int stock;
  float price;
  unsigned int seller_id;
  /*
      account format in file: type_code name password balance id
      product format in file: type description price stock id seller_id
  */
  if (!fin.is_open())
    cout << "FAIL TO OPEN account.txt" << std::endl;
  else {
    while (!fin.eof()) {
      fin >> type >> descrip >> price >> stock >> id >> seller_id;
      if (type == FOOD) {
        food fod(descrip, price, stock, id, seller_id);
        all_food.push_back(fod);
      }
      if (type == CLOTH) {
        cloth clt(descrip, price, stock, id, seller_id);
        all_cloth.push_back(clt);
      }
      if (type == BOOK) {
        book bok(descrip, price, stock, id, seller_id);
        all_book.push_back(bok);
      }
    }
  }
  print_all_act(SELLER);
  print_all_act(CONSUMER);
  print_all_pdt(FOOD);
  print_all_pdt(CLOTH);
  print_all_pdt(BOOK);
}

void Platform ::print_all_act(int type) {

  switch (type) {
  case SELLER:
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING ALL SELLER"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');

    cout << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID)
         << "BALANCE" << setw(FORMAT_PRICE_WID) << "ID" << endl;
    for (int i = 0; i < all_seller.size(); i++) {
      cout << setw(FORMAT_NAME_WID) << all_seller[i].GetName()
           << setw(FORMAT_PRICE_WID) << all_seller[i].GetBalence()
           << setw(FORMAT_PRICE_WID) << all_seller[i].Getid() << endl;
    }
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINTING"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');
    break;

  case CONSUMER:
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING ALL CONSUMER"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');

    cout << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID)
         << "BALANCE" << setw(FORMAT_PRICE_WID) << "ID" << endl;
    for (int i = 0; i < all_consumer.size(); i++) {
      cout << setw(FORMAT_NAME_WID) << all_consumer[i].GetName()
           << setw(FORMAT_PRICE_WID) << all_consumer[i].GetBalence()
           << setw(FORMAT_PRICE_WID) << all_consumer[i].Getid() << endl;
    }
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINTING"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');

    break;
  }
}

void Platform ::print_all_pdt(int type) {
  switch (type) {
  case BOOK:
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING ALL BOOKS"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');

    cout << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID) << "Price"
         << setw(FORMAT_PRICE_WID) << "ID" << setw(FORMAT_PRICE_WID)
         << "SELLER_ID" << endl;
    for (int i = 0; i < all_book.size(); i++) {
      cout << setw(FORMAT_NAME_WID) << all_book[i].GetDscrip()
           << setw(FORMAT_PRICE_WID) << all_book[i].GetPrice()
           << setw(FORMAT_PRICE_WID) << all_book[i].GetId()
           << setw(FORMAT_PRICE_WID) << all_book[i].GetSellerId() << endl;
    }
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINTING"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');

    break;
  case CLOTH:
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING ALL CLOTHES"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');

    cout << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID) << "Price"
         << setw(FORMAT_PRICE_WID) << "ID" << setw(FORMAT_PRICE_WID)
         << "SELLER_ID" << endl;
    for (int i = 0; i < all_cloth.size(); i++) {
      cout << setw(FORMAT_NAME_WID) << all_cloth[i].GetDscrip()
           << setw(FORMAT_PRICE_WID) << all_cloth[i].GetPrice()
           << setw(FORMAT_PRICE_WID) << all_cloth[i].GetId()
           << setw(FORMAT_PRICE_WID) << all_cloth[i].GetSellerId() << endl;
    }
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINTING"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');
    break;
  case FOOD:
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING ALL FOOD"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');

    cout << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID) << "Price"
         << setw(FORMAT_PRICE_WID) << "ID" << setw(FORMAT_PRICE_WID)
         << "SELLER_ID" << endl;
    for (int i = 0; i < all_food.size(); i++) {
      cout << setw(FORMAT_NAME_WID) << all_food[i].GetDscrip()
           << setw(FORMAT_PRICE_WID) << all_food[i].GetPrice()
           << setw(FORMAT_PRICE_WID) << all_food[i].GetId()
           << setw(FORMAT_PRICE_WID) << all_food[i].GetSellerId() << endl;
    }
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINTING"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');
    break;
  }
}
