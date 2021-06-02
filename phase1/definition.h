#ifndef DEFINITION_H
#define DEFINITION_H 2

#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream> //convert num in string to int
#include <vector>

/*-------------------------------------------------------*/

using std::cin;
using std::cout;
using std::endl;
using std::setfill;
using std::setw;
using std::string;
using std::stringstream;
using std::vector;
/*-----------------------------------------------------*/

#define SELLER 1
#define CONSUMER 2

#define FOOD 11
#define CLOTH 12
#define BOOK 13

#define CART_SIZE 20
#define CHOISE_COUNT 12
#define MAX_PRODUCT 1000 // max product count for each seller
#define MAX_SELLER_COUNT 200
#define MAX_CONSUMER_COUNT 2000
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
  virtual string GetPswd() { return this->password; }
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

  bool operator<(const account &str) const { return (id < str.id); }
  bool operator==(const unsigned short &fid) { return (id == fid); }

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
  using account::operator<;
  vector<class product>::iterator fst_book, fst_clth, fst_fod;
};

class consumer : public account {
public:
  consumer(string name_ = NULL, string password_ = NULL, float balance_ = 0,
           unsigned int id_ = 0)
      : account(name_, password_, balance_, id_){};
  int GetUserType() { return CONSUMER; }
  using account::operator<;
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
  virtual seller *GetSellerAccount() { return seller_act; }
  virtual void SetSellerAccount(seller *sact) { seller_act = sact; }
  virtual int GetProductType() = 0;
  virtual unsigned int GetId() { return id; };
  virtual unsigned int GetSellerId() { return seller_id; };

  bool operator<(const product &str) const {
    if (seller_id < str.seller_id)
      return (seller_id < str.seller_id);
    else
      return (id < str.id);
  }
  bool operator==(const unsigned short &fid) { return (id == fid); }

private:
  string Descrip;

  float Price;
  int Stock;
  unsigned int seller_id;
  unsigned int id;

  seller *seller_act;
};

class food : public product {
public:
  food(string Descrip_ = NULL, float Price_ = 0, int Stock_ = 0,
       unsigned int id_ = 0, unsigned int seller_id_ = 0)
      : product(Descrip_, Price_, Stock_, id_, seller_id_), type(FOOD){};
  int GetProductType() { return type; }
  using product::operator<;

private:
  int type;
};
class cloth : public product {
public:
  cloth(string Descrip_ = NULL, float Price_ = 0, int Stock_ = 0,
        unsigned int id_ = 0, unsigned int seller_id_ = 0)
      : product(Descrip_, Price_, Stock_, id_, seller_id_), type(CLOTH){};
  int GetProductType() { return type; }
  using product::operator<;

private:
  int type;
};
class book : public product {
public:
  book(string Descrip_ = NULL, float Price_ = 0, int Stock_ = 0,
       unsigned int id_ = 0, unsigned int seller_id_ = 0)
      : product(Descrip_, Price_, Stock_, id_, seller_id_), type(BOOK){};
  int GetProductType() { return type; }
  using product::operator<;

private:
  int type;
};
class Platform {
public:
  void init_load_file(); // load in user and product
  void login_signin();
  void print_all_pdt(int type); // print all_product in type
  void print_all_act(int type); // print all_seller or all_counsumer
  int Get_option();
  void write_back_file();
  void process_choice(int choice);
  void search_product();
  void create_new_act();
  unsigned int genrate_account_id(int type);
  void login();
  void change_password();
  void top_up();
  void purchase_pdt();
  void add_pdt();
  unsigned int genrate_pdt_id(int type);
  void del_pdt();
  void edt_pdt();
  void search_my_pdt(int type, unsigned int id,
                     vector<product>::iterator &cur_pdt, seller *cur);

private:
  vector<seller> all_seller;
  vector<consumer> all_consumer;
  account *cur_account;
  int account_type; //-1 signed out. 1 seller  2 consumer

  vector<book> all_book;
  vector<cloth> all_cloth;
  vector<food> all_food;
};

#endif