#ifndef PLATFORM_H
#define PLATFORM_H 1
#include "definition.h"
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

#endif