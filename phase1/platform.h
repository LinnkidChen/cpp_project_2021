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

  account_type = -1;

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
        for (int i = 0; i < all_seller.size(); i++) {
          if (all_seller[i].Getid() == seller_id) {
            fod.SetSellerAccount(&all_seller[i]);
            break;
          }
        }
        all_food.push_back(fod);
      }
      if (type == CLOTH) {
        cloth clt(descrip, price, stock, id, seller_id);
        for (int i = 0; i < all_seller.size(); i++) {
          if (all_seller[i].Getid() == seller_id) {
            clt.SetSellerAccount(&all_seller[i]);
            break;
          }
        }
        all_cloth.push_back(clt);
      }
      if (type == BOOK) {
        book bok(descrip, price, stock, id, seller_id);
        for (int i = 0; i < all_seller.size(); i++) {
          if (all_seller[i].Getid() == seller_id) {
            bok.SetSellerAccount(&all_seller[i]);
            break;
          }
        }
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
/*
      account format in file: type_code name password balance id
      product format in file: type description price stock id seller_id
  */
void Platform::write_back_file() {
  std::ofstream fout;
  fout.open("account.txt");

  std::sort(all_seller.begin(), all_seller.end());
  std::sort(all_consumer.begin(), all_consumer.end());
  std::sort(all_food.begin(), all_food.end());
  std::sort(all_cloth.begin(), all_cloth.end());
  std::sort(all_book.begin(), all_book.end());
  if (!fout.is_open()) {
    cout << "unable to open account.txt";
  } else {
    for (int i = 0; i < all_seller.size(); i++)
      fout << all_seller[i].GetUserType() << " " << all_seller[i].GetName()
           << " " << all_seller[i].GetPswd() << " "
           << all_seller[i].GetBalence() << " " << all_seller[i].Getid()
           << endl;

    for (int i = 0; i < all_consumer.size(); i++)
      fout << all_consumer[i].GetUserType() << " " << all_consumer[i].GetName()
           << " " << all_consumer[i].GetPswd() << " "
           << all_consumer[i].GetBalence() << " " << all_consumer[i].Getid()
           << endl;
  }
  fout.close();
  fout.open("test.txt");
  if (!fout.is_open()) {
    cout << "unable to open product.txt";
  } else {
    for (int i = 0; i < all_food.size(); i++) {
      fout << all_food[i].GetProductType() << " " << all_food[i].GetDscrip()
           << " " << all_food[i].GetPrice() << " " << all_food[i].GetStock()
           << " " << all_food[i].GetId() << " " << all_food[i].GetSellerId()
           << endl;
    }
    for (int i = 0; i < all_cloth.size(); i++) {
      fout << all_cloth[i].GetProductType() << " " << all_cloth[i].GetDscrip()
           << " " << all_cloth[i].GetPrice() << " " << all_cloth[i].GetStock()
           << " " << all_cloth[i].GetId() << " " << all_cloth[i].GetSellerId()
           << endl;
      for (int i = 0; i < all_book.size(); i++) {
        fout << all_book[i].GetProductType() << " " << all_book[i].GetDscrip()
             << " " << all_book[i].GetPrice() << " " << all_book[i].GetStock()
             << " " << all_book[i].GetId() << " " << all_book[i].GetSellerId()
             << endl;
      }
    }
  }
}
/*
    1. show all product   --all
    2. search product  --all
    3. sign in         -- -1
    4. log in           -- -1
    5. change password               --seller / consmer
    6. show balance  --seller/con
    7.  log out    --seller/con
    8.top up           ---con
    9.buy product          --con
    10.add product--seller
    11. delete product -->changd descrip/ change stock/ change price
    12.  edit product--seller

*/
int Platform::Get_option() {
  int i = 1;
  int choice;
  account_type = SELLER;
  cout << i << ". show all product" << endl; // 1
  i++;
  cout << i << ". search product " << endl; // 2
  i++;
  if (account_type == -1) {           // not signed in{
    cout << i << ". sign in" << endl; // 3
    i++;
    cout << i << ". log in" << endl; // 4
    i++;
  } else {                                    // signed in
    cout << i << ". change password" << endl; // 3
    i++;
    cout << i << ". show balance" << endl; // 4
    i++;
    cout << i << ". log out" << endl; // 5
    i++;
  }

  if (account_type == CONSUMER) {
    cout << i << ".  top up" << endl; // 6
    i++;
    cout << i << ". buy product" << endl; // 7
  }
  if (account_type == SELLER) {
    cout << i << ". add product" << endl; // 6
    i++;
    cout << i << ". delete product" << endl; // 7
    i++;
    cout << i << ". edit product" << endl; // 8
    i++;
  }
  cout << "q.quiting\n";
  cout << "\n"
       << "Please enter your choice number" << endl;
  if (cin.peek() == 'q') {
    cout << "exiting program\n";
    exit(1);
  }
  cin >> choice;

  if (choice < 3)
    return choice;
  if (choice < 5 && account_type == -1)
    return choice;
  choice += 2;
  if (choice < 8 && account_type)
    return choice;
  if (choice < 10 && account_type == CONSUMER) {
    return choice;
  }
  choice += 2;
  if (choice < 13 && account_type == SELLER)
    return choice;

  return -1;
}
#endif