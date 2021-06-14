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
    while (!fin.eof()) {
      fin >> type >> name >> password >> balance >> id;
      //   print_all_act(SELLER);
      //   print_all_act(CONSUMER);
      if (type == SELLER) {
        seller sler(name, password, balance, id);
        all_seller.push_back(sler);
      }
      if (type == CONSUMER) {
        consumer csmr(name, password, balance, id);
        all_consumer.push_back(csmr);
      }
      type = -1;
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
        list<seller>::iterator it = all_seller.begin();
        for (; it != all_seller.end(); it++) {
          if (it->Getid() == seller_id) {
            fod.SetSellerAccount(&(*it));
            break;
          }
        }
        all_food.push_back(fod);
      }
      if (type == CLOTH) {
        cloth clt(descrip, price, stock, id, seller_id);
        list<seller>::iterator it = all_seller.begin();
        for (; it != all_seller.end(); it++) {
          if (it->Getid() == seller_id) {
            clt.SetSellerAccount(&(*it));
            break;
          }
        }
        all_cloth.push_back(clt);
      }
      if (type == BOOK) {
        book bok(descrip, price, stock, id, seller_id);
        list<seller>::iterator it = all_seller.begin();
        for (; it != all_seller.end(); it++) {
          if (it->Getid() == seller_id) {
            bok.SetSellerAccount(&(*it));
          }
        }
        all_book.push_back(bok);
      }
      type = -1;
    }
  }

  // cout << all_seller[0].fst_book->GetDscrip() << endl;
  //   print_all_act(SELLER);
  //   print_all_pdt(FOOD);
  //   print_all_pdt(CLOTH);
  // print_all_pdt(BOOK);
}

void Platform ::print_all_act(int type) {

  if (type == SELLER) {
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING ALL SELLER"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');

    cout << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID)
         << "BALANCE" << setw(FORMAT_PRICE_WID) << "ID" << endl;
    list<seller>::iterator it = all_seller.begin();
    for (; it != all_seller.end(); it++) {
      cout << setw(FORMAT_NAME_WID) << it->GetName() << setw(FORMAT_PRICE_WID)
           << it->GetBalence() << setw(FORMAT_PRICE_WID) << it->Getid() << endl;
    }
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINTING"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');
  }

  if (type == CONSUMER) {
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING ALL CONSUMER"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');

    cout << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID)
         << "BALANCE" << setw(FORMAT_PRICE_WID) << "ID" << endl;
    for (list<consumer>::iterator it = all_consumer.begin();
         it != all_consumer.end(); it++) {
      cout << setw(FORMAT_NAME_WID) << it->GetName() << setw(FORMAT_PRICE_WID)
           << it->GetBalence() << setw(FORMAT_PRICE_WID) << it->Getid() << endl;
    }
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINTING"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');
  }
}

void Platform ::print_all_pdt(int type) {

  if (type == BOOK) {
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING ALL BOOKS"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');

    cout << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID) << "Price"
         << setw(FORMAT_PRICE_WID) << "Stock" << setw(FORMAT_PRICE_WID) << "ID"
         << setw(FORMAT_PRICE_WID) << "SELLER_ID" << endl;
    for (list<book>::iterator it = all_book.begin(); it != all_book.end();
         it++) {
      cout << setw(FORMAT_NAME_WID) << it->GetDscrip() << setw(FORMAT_PRICE_WID)
           << it->GetPrice() << setw(FORMAT_PRICE_WID) << it->GetStock()
           << setw(FORMAT_PRICE_WID) << it->GetId() << setw(FORMAT_PRICE_WID)
           << it->GetSellerId() << endl;
    }
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINTING"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');
  }
  if (type == CLOTH) {
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING ALL CLOTHES"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');

    cout << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID) << "Price"
         << setw(FORMAT_PRICE_WID) << "Stock" << setw(FORMAT_PRICE_WID) << "ID"
         << setw(FORMAT_PRICE_WID) << "SELLER_ID" << endl;
    for (list<cloth>::iterator it = all_cloth.begin(); it != all_cloth.end();
         it++) {
      cout << setw(FORMAT_NAME_WID) << it->GetDscrip() << setw(FORMAT_PRICE_WID)
           << it->GetPrice() << setw(FORMAT_PRICE_WID) << it->GetStock()
           << setw(FORMAT_PRICE_WID) << it->GetId() << setw(FORMAT_PRICE_WID)
           << it->GetSellerId() << endl;
    }
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINTING"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');
  }
  if (type == FOOD) {
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING ALL FOOD"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');

    cout << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID) << "Price"
         << setw(FORMAT_PRICE_WID) << "Stock" << setw(FORMAT_PRICE_WID) << "ID"
         << setw(FORMAT_PRICE_WID) << "SELLER_ID" << endl;
    for (list<food>::iterator it = all_food.begin(); it != all_food.end();
         it++) {
      cout << setw(FORMAT_NAME_WID) << it->GetDscrip() << setw(FORMAT_PRICE_WID)
           << it->GetPrice() << setw(FORMAT_PRICE_WID) << it->GetStock()
           << setw(FORMAT_PRICE_WID) << it->GetId() << setw(FORMAT_PRICE_WID)
           << it->GetSellerId() << endl;
    }
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINTING"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');
  }
}
/*
      account format in file: type_code name password balance id
      product format in file: type description price stock id seller_id
  */
void Platform::write_back_file() {
  std::ofstream fout;
  fout.open("account.txt");

  //   std::sort(all_seller.begin(), all_seller.end());
  //   std::sort(all_consumer.begin(), all_consumer.end());
  //   std::sort(all_food.begin(), all_food.end());
  //   std::sort(all_cloth.begin(), all_cloth.end());
  //   std::sort(all_book.begin(), all_book.end());
  if (!fout.is_open()) {
    cout << "unable to open account.txt";
  } else {
    for (list<seller>::iterator it = all_seller.begin(); it != all_seller.end();
         it++)
      fout << it->GetUserType() << " " << it->GetName() << " " << it->GetPswd()
           << " " << it->GetBalence() << " " << it->Getid() << endl;

    for (list<consumer>::iterator it = all_consumer.begin();
         it != all_consumer.end(); it++)
      fout << it->GetUserType() << " " << it->GetName() << " " << it->GetPswd()
           << " " << it->GetBalence() << " " << it->Getid() << endl;
  }
  fout.close();
  fout.open("product.txt");
  if (!fout.is_open()) {
    cout << "unable to open product.txt";
  } else {
    for (list<food>::iterator it = all_food.begin(); it != all_food.end();
         it++) {
      fout << it->GetProductType() << " " << it->GetDscrip() << " "
           << it->GetPrice() << " " << it->GetStock() << " " << it->GetId()
           << " " << it->GetSellerId() << endl;
    }
    for (list<cloth>::iterator it = all_cloth.begin(); it != all_cloth.end();
         it++) {
      fout << it->GetProductType() << " " << it->GetDscrip() << " "
           << it->GetPrice() << " " << it->GetStock() << " " << it->GetId()
           << " " << it->GetSellerId() << endl;
      for (list<book>::iterator it = all_book.begin(); it != all_book.end();
           it++) {
        fout << it->GetProductType() << " " << it->GetDscrip() << " "
             << it->GetPrice() << " " << it->GetStock() << " " << it->GetId()
             << " " << it->GetSellerId() << endl;
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
    13. add product
    14. remove product
    15. change product num
    16.show cart
    17. generate order

*/
int Platform::Get_option() {
  int i = 1;
  int choice;
  string input;
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
    i++;
  }
  if (account_type == SELLER) {
    cout << i << ". add product" << endl; // 6
    i++;
    cout << i << ". delete product" << endl; // 7
    i++;
    cout << i << ". edit product" << endl; // 8
    i++;
  }

  if (account_type == CONSUMER) {
    cout << i << ". add product to cart" << endl; // 8
    i++;
    consumer *act;
    act = (consumer *)cur_account;
    if (!(act->cart_.is_empty())) {
      cout << i << ". remove product" << endl; // 9
      i++;
      cout << i << ". change product number" << endl; // 10
      i++;
      cout << i << ". show cart" << endl; // 11
      i++;
      cout << i << ". genrate_order" << endl; // 12
      i++;
    }
  }
  //   cout << i << ". back to option page" << endl;
  cout << "q.quiting\n";
  cout << "\n"
       << "Please enter your choice number" << endl;
  cin >> input;
  if (input[0] == 'q') {
    return -1;
  }
  stringstream degree(input);
  degree >> choice;
  cin >> choice;
  if (choice >= i)
    return 50; // skip the swithch branch
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
  if (choice < 15 && account_type == CONSUMER) {
    return choice += 3;
  }
  choice += 2;
  if (choice < 13 && account_type == SELLER)
    return choice;

  return -1;
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
  ----------cart feature--------
    13. add product cart
    14. remove product
    15. change product num
    16.show cart
    17. generate order

*/
void Platform ::process_choice(int choice) {
  consumer *curact = (consumer *)cur_account;
  switch (choice) {
  case 1: // show all product
    print_all_pdt(CLOTH);
    print_all_pdt(FOOD);
    print_all_pdt(BOOK);
    break;
  case 2:
    search_product();
    break;
  case 3:
    create_new_act();
    break;
  case 4:
    login();
    break;
  case 5:
    change_password();
    break;
  case 6:
    cout << "your balance is : " << cur_account->GetBalence() << endl;
    break;
  case 7:
    cur_account = NULL;
    account_type = -1;
    cout << "log out successfully" << endl;
    break;
  case 8:
    top_up();
    break;
  case 9:
    purchase_pdt();
    break;
  case 10:
    add_pdt();
    break;
  case 11:
    del_pdt();
    break;
  case 12:
    edt_pdt();
    break;
  case 13:
    add_pdt_to_cart();
    break;
  case 14:
    remov_pdt_cart();
    break;
  case 15:
    change_pdt_cart();
    break;
  case 16:
    curact->cart_.show_cart();
    break;
  case 17:
    check_out_cart();
    break;
  }
}

void Platform::search_product() {
  cout << "Please enter the info you want to search" << endl;
  string input;
  unsigned int id, flag;
  cin >> input;
  stringstream degree(input); // transform string to int
  degree >> id;
  flag = 0;

  if (!input.compare("FOOD")) // print all products under one catagory
    print_all_pdt(FOOD);
  else if (!input.compare("CLOTH"))
    print_all_pdt(CLOTH);
  else if (!input.compare("BOOK"))
    print_all_pdt(BOOK);
  else {
    for (list<book>::iterator it = all_book.begin(); it != all_book.end();
         it++) {
      if (it->GetDscrip().find(input) != string::npos ||
          it->GetId() == id) { // found a match
        flag++;
        cout << setw(FORMAT_NAME_WID) << it->GetDscrip()
             << setw(FORMAT_PRICE_WID) << it->GetPrice()
             << setw(FORMAT_PRICE_WID) << it->GetId() << setw(FORMAT_PRICE_WID)
             << it->GetSellerId() << endl;
      }
    }
    for (list<cloth>::iterator it = all_cloth.begin(); it != all_cloth.end();
         it++) {
      if (it->GetDscrip().find(input) != string::npos ||
          it->GetId() == id) { // found a match
        flag++;
        cout << setw(FORMAT_NAME_WID) << it->GetDscrip()
             << setw(FORMAT_PRICE_WID) << it->GetPrice()
             << setw(FORMAT_PRICE_WID) << it->GetId() << setw(FORMAT_PRICE_WID)
             << it->GetSellerId() << endl;
      }
    }
    for (list<food>::iterator it = all_food.begin(); it != all_food.end();
         it++) {

      if (it->GetDscrip().find(input) != string::npos ||
          it->GetId() == id) { // found a match
        flag++;
        cout << setw(FORMAT_NAME_WID) << it->GetDscrip()
             << setw(FORMAT_PRICE_WID) << it->GetPrice()
             << setw(FORMAT_PRICE_WID) << it->GetId() << setw(FORMAT_PRICE_WID)
             << it->GetSellerId() << endl;
      }
    }
    if (!flag)
      cout << "Cant find target product " << endl;
  }
}

void Platform ::create_new_act() {
  cout << "Creating new account" << endl;
  string username, password;
  unsigned int id;
  int type;
  cout << "Type.1 for seller,2 for consumer" << endl;
  cin >> type;
  cout << "username" << endl;
  cin >> username;
  cout << "password" << endl;
  cin >> password;

  id = genrate_account_id(type);
  if (type == CONSUMER) {
    for (list<consumer>::iterator it = all_consumer.begin();
         it != all_consumer.end(); it++) {
      if (username == it->GetName()) {
        id = 0;
        break;
      }
    }
    if (id > 0) {
      consumer csmr(username, password, 0, id);
      all_consumer.push_back(csmr);
      cout << "Create successfully!" << endl;
    } else
      cout << "Username alredy in use." << endl;
  }
  if (type == SELLER) {
    for (list<seller>::iterator it = all_seller.begin(); it != all_seller.end();
         it++) {
      if (username == it->GetName()) {
        id = 0;
        break;
      }
    }
    if (id > 0) {
      seller slr(username, password, 0, id);
      all_seller.push_back(slr);
      cout << "Create successfully!" << endl;
    } else
      cout << "Username alredy in use." << endl;
  }
}
unsigned int Platform::genrate_account_id(int type) {
  unsigned int id;
  if (type == SELLER) {
    id = all_seller.back().Getid() + 1;
  }
  if (type == CONSUMER) {
    id = all_consumer.back().Getid() + 1;
  }
  return id;
}

void Platform::login() {
  cout << "Log in" << endl;
  string username, password;
  int type, loc;
  cout << "account type: 1 for seller,2 for consumer" << endl;
  cin >> type;
  cout << "username" << endl;
  cin >> username;
  cout << "password" << endl;
  cin >> password;

  if (type == SELLER) {
    list<seller>::iterator it = all_seller.begin();
    for (; it != all_seller.end(); it++) {
      if (it->GetName() == username)

        break;
    }
    if (it->GetName() == username) {     // account found
      if (it->checkPassword(password)) { // password correct
        cur_account = &(*it);
        account_type = SELLER;
        cout << "Log in successfully" << endl;
      } else // password incorrect
        cout << "Incorrect password.Please try again." << endl;
    } else {
      // account not found
      cout << "Account not found.please check your input" << endl;
    }
  }
  if (type == CONSUMER) {
    list<consumer>::iterator it = all_consumer.begin();
    for (; it != all_consumer.end(); it++) {
      if (it->GetName() == username)
        break;
    }
    if (it->GetName() == username) {     // account found
      if (it->checkPassword(password)) { // password correct
        cur_account = &(*it);
        account_type = CONSUMER;
        cout << "Log in successfully" << endl;
      } else // password incorrect
        cout << "Incorrect password.Please try again." << endl;
    } else {
      // account not found
      cout << "Account not found.please check your input" << endl;
    }
  }
}

void Platform::change_password() {
  cout << "Change password" << endl;
  string old_pswd, new_pswd;
  cout << "old passowrd" << endl;
  cin >> old_pswd;
  cout << "new password" << endl;
  cin >> new_pswd;
  if (cur_account->changePassword(old_pswd, new_pswd)) // oldpassowrd is corrct
  {
    cout << "Change Successfully" << endl;
  } else
    cout << "incorrect password,please try again" << endl;
}
void Platform::top_up() {
  cout << "top up" << endl;
  float add;
  cout << "amount you want to add:" << endl;
  cin >> add;
  cur_account->AddBalance(add);
  cout << "add successfully" << endl;
}

void Platform::purchase_pdt() {
  cout << "Purchasing product" << endl;
  unsigned int id, amount;
  int type, found = 0;
  product *cur_pdt = NULL;
  print_all_pdt(FOOD);
  print_all_pdt(CLOTH);
  print_all_pdt(BOOK);
  cout << "please enter the product id you want " << endl;
  cin >> id;
  cout << "please enter number you want to buy" << endl;
  cin >> amount;
  type = id / MAX_PRODUCT;

  if (type == FOOD)

  {
    list<food>::iterator it = all_food.begin();
    for (; it != all_food.end(); it++) {
      if (it->GetId() == id) {
        found = 1;
        break;
      }
    }
    if (it == all_food.end()) // not found
    {
      cout << "Product not found" << endl;
    } else
      cur_pdt = &(*it);
  }
  if (type == CLOTH)

  {
    list<cloth>::iterator it = all_cloth.begin();
    for (; it != all_cloth.end(); it++) {
      if (it->GetId() == id) {
        found = 1;
        break;
      }
    }

    if (it == all_cloth.end()) // not found
    {
      cout << "Product not found" << endl;
    } else
      cur_pdt = &(*it);
  }
  if (type == BOOK)

  {
    list<book>::iterator it = all_book.begin();
    for (; it != all_book.end(); it++) {
      if (it->GetId() == id) {
        found = 1;
        break;
      }
    }
    if (it == all_book.end()) // not found
    {
      cout << "Product not found" << endl;
    } else
      cur_pdt = &(*it);
  }
  if (found) { // found
    if (cur_account->GetBalence() >= cur_pdt->GetPrice() * amount) {
      if (cur_pdt->GetStock() >= amount) {
        cur_pdt->ChangeStock(-1 * amount);
        cur_account->SubBalance(amount * cur_pdt->GetPrice());
        cur_pdt->GetSellerAccount()->AddBalance(cur_pdt->GetPrice() * amount);
        cout << "Purchase successfully" << endl;
      } else
        cout << "Not enough product in stock" << endl;
    } else
      cout << "Not enough balance" << endl;
  }
}
void Platform::add_pdt() {
  cout << "adding product" << endl;
  string dscrip;
  int type, stock;
  float price;
  unsigned int id, sellerid;
  cout << "type,11 for food,12 for cloth,13 for book" << endl;
  cin >> type;
  cout << "description" << endl;
  cin >> dscrip;
  cout << "stock" << endl;
  cin >> stock;
  cout << "price" << endl;
  cin >> price;

  id = genrate_pdt_id(type);
  sellerid = cur_account->Getid();

  if (type == FOOD) {
    food fod(dscrip, price, stock, id, sellerid);
    fod.SetSellerAccount((seller *)cur_account);
    all_food.push_back(fod);
    cout << "Add product successfully" << endl;
  } else if (type == CLOTH) {
    cloth clth(dscrip, price, stock, id, sellerid);
    clth.SetSellerAccount((seller *)cur_account);
    all_cloth.push_back(clth);
    cout << "Add product successfully" << endl;
  } else if (type == BOOK) {
    book bok(dscrip, price, stock, id, sellerid);
    bok.SetSellerAccount((seller *)cur_account);
    all_book.push_back(bok);
    cout << "Add product successfully" << endl;
  } else {
    cout << "invalid type" << endl;
  }
}

unsigned int Platform::genrate_pdt_id(int type) {

  if (type == FOOD) {
    if (!all_food.empty())
      return all_food.back().GetId() + 1;
    else
      return FOOD * MAX_PRODUCT;
  }
  if (type == CLOTH) {
    if (!all_cloth.empty())
      return all_cloth.back().GetId() + 1;
    else
      return CLOTH * MAX_PRODUCT;
  }
  if (type == BOOK) {
    if (!all_book.empty())
      return all_book.back().GetId();
    else
      return BOOK * MAX_PRODUCT;
  }

  return 0;
}
void Platform::del_pdt() {
  cout << "delete product" << endl;
  print_my_product(FOOD);
  print_my_product(BOOK);
  print_my_product(CLOTH);
  unsigned int id;
  int type, deleted;
  deleted = 0;
  cout << "enter id" << endl;
  cin >> id;
  type = id / MAX_PRODUCT;

  if (type == FOOD) {
    for (list<food>::iterator it = all_food.begin(); it != all_food.end();
         it++) {
      if (it->GetId() == id) {
        it = all_food.erase(it);
        deleted = 1;
      }
    }
  }
  if (type == CLOTH) {
    for (list<cloth>::iterator it = all_cloth.begin(); it != all_cloth.end();
         it++) {
      if (it->GetId() == id) {
        it = all_cloth.erase(it);
        deleted = 1;
        break;
      }
    }
  }
  if (type == BOOK) {
    for (list<book>::iterator it = all_book.begin(); it != all_book.end();
         it++) {
      if (it->GetId() == id) {
        it = all_book.erase(it);
        deleted = 1;
      }
    }

    if (deleted == 1) {
      cout << "delete successfully" << endl;

    } else
      cout << "target not found" << endl;
  }
}
void Platform::edt_pdt() {
  cout << "editing product" << endl;
  int type, pdt_type;
  unsigned int id;
  string descrip;
  product *cur_pdt = NULL;
  float price = -1;
  int stock = -1;
  print_my_product(FOOD);
  print_my_product(BOOK);
  print_my_product(CLOTH);
  cout << "enter type.1 descrip,2 price,3 stock" << endl;
  cin >> type;
  cout << "enter product id" << endl;
  cin >> id;
  pdt_type = id / MAX_PRODUCT;
  switch (type) {
  case 1:
    cout << "new descrip" << endl;
    cin >> descrip;
    break;
  case 2:
    cout << "new price" << endl;
    cin >> price;
    break;
  case 3:
    cout << "new stock" << endl;
    cin >> stock;
    break;
  }

  search_my_pdt(pdt_type, id, cur_pdt, (seller *)cur_account);
  if (cur_pdt) {
    if (price > 0) {
      cur_pdt->ChangePrice(price);
      cout << "change price done" << endl;
    } else if (stock > 0) {
      cur_pdt->ChangeStock(stock);
      cout << "change stock done" << endl;
    } else {
      cur_pdt->ChangeDscrip(descrip);
      cout << "change description done" << endl;
    }
  } else
    cout << "fail to find product" << endl;
}
void Platform::search_my_pdt(int type, unsigned int id, product *(&cur_pdt),
                             seller *cur_account) {
  list<food>::iterator it_f;
  list<book>::iterator it_b;
  list<cloth>::iterator it_c;

  if (type == FOOD) {
    it_f = all_food.begin();
    while (it_f->GetSellerId() != cur_account->Getid()) {
      it_f++;
    }

    for (; it_f->GetSellerId() == cur_account->Getid(); it_f++) {
      if (it_f->GetId() == id) {
        cur_pdt = (product *)(&(*it_f));
        break;
      }
    }
  }

  if (type == BOOK) {
    it_b = all_book.begin();
    while (it_b->GetSellerId() != cur_account->Getid()) {
      it_b++;
    }

    for (; it_b->GetSellerId() == cur_account->Getid(); it_b++) {
      if (it_b->GetId() == id) {
        cur_pdt = (product *)(&(*it_b));
        break;
      }
    }
  }
  if (type == CLOTH) {
    it_c = all_cloth.begin();
    while (it_c->GetSellerId() != cur_account->Getid()) {
      it_c++;
    }

    for (; it_c->GetSellerId() == cur_account->Getid(); it_c++) {
      if (it_c->GetId() == id) {
        cur_pdt = (product *)(&(*it_c));
        break;
      }
    }
  }
}
void Platform ::print_my_product(int type) {
  list<food>::iterator it_f;
  list<book>::iterator it_b;
  list<cloth>::iterator it_c;

  if (type == FOOD) {
    it_f = all_food.begin();
    while (it_f != all_food.end()) {
      if (it_f->GetDscrip().empty()) {
        type = -1;
        break;
      }
      if (it_f->GetSellerId() == cur_account->Getid())
        break;
      it_f++;
    }
    if (it_f == all_food.end()) {
      type = -1;
    }
    if (type > 0) {
      cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING MY FOOD"
           << setw(FORMAT_BAR_RARE) << "" << endl
           << setfill(' ');

      cout << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID)
           << "Price" << setw(FORMAT_PRICE_WID) << "STOCK"
           << setw(FORMAT_PRICE_WID) << "ID" << setw(FORMAT_PRICE_WID)
           << "SELLER_ID" << endl;
      for (; it_f->GetSellerId() == cur_account->Getid();) {
        cout << setw(FORMAT_NAME_WID) << it_f->GetDscrip()
             << setw(FORMAT_PRICE_WID) << it_f->GetPrice()
             << setw(FORMAT_PRICE_WID) << it_f->GetStock()
             << setw(FORMAT_PRICE_WID) << it_f->GetId()
             << setw(FORMAT_PRICE_WID) << it_f->GetSellerId() << endl;
        cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINT"
             << setw(FORMAT_BAR_RARE) << "" << endl
             << setfill(' ');
        it_f++;
        if (it_f == all_food.end())
          break;
      }
    }
  }

  if (type == BOOK) {
    it_b = all_book.begin();
    while (it_b != all_book.end()) {
      if (it_b->GetDscrip().empty()) {
        type = -1;
        break;
      }
      if (it_b->GetSellerId() == cur_account->Getid())
        break;
      it_b++;
    }
    if (it_b == all_book.end()) {
      type = -1;
    }
    if (type > 0) {
      cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING MY BOOK"
           << setw(FORMAT_BAR_RARE) << "" << endl
           << setfill(' ');

      cout << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID)
           << "Price" << setw(FORMAT_PRICE_WID) << "STOCK"
           << setw(FORMAT_PRICE_WID) << "ID" << setw(FORMAT_PRICE_WID)
           << "SELLER_ID" << endl;
      for (; it_b->GetSellerId() == cur_account->Getid();) {
        cout << setw(FORMAT_NAME_WID) << it_b->GetDscrip()
             << setw(FORMAT_PRICE_WID) << it_b->GetPrice()
             << setw(FORMAT_PRICE_WID) << it_b->GetStock()
             << setw(FORMAT_PRICE_WID) << it_b->GetId()
             << setw(FORMAT_PRICE_WID) << it_b->GetSellerId() << endl;
        cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINT"
             << setw(FORMAT_BAR_RARE) << "" << endl
             << setfill(' ');
        it_b++;
        if (it_b == all_book.end())
          break;
      }
    }
  }
  if (type == CLOTH) {
    it_c = all_cloth.begin();
    while (it_c != all_cloth.end()) {
      if (it_c->GetDscrip().empty()) {
        type = -1;
        break;
      }
      if (it_c->GetSellerId() == cur_account->Getid())
        break;
      it_c++;
    }
    if (it_c == all_cloth.end()) {
      type = -1;
    }
    if (type > 0) {
      cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING MY CLOTH"
           << setw(FORMAT_BAR_RARE) << "" << endl
           << setfill(' ');

      cout << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID)
           << "Price" << setw(FORMAT_PRICE_WID) << "STOCK"
           << setw(FORMAT_PRICE_WID) << "ID" << setw(FORMAT_PRICE_WID)
           << "SELLER_ID" << endl;
      for (; it_c->GetSellerId() == cur_account->Getid();) {
        cout << setw(FORMAT_NAME_WID) << it_c->GetDscrip()
             << setw(FORMAT_PRICE_WID) << it_c->GetPrice()
             << setw(FORMAT_PRICE_WID) << it_c->GetStock()
             << setw(FORMAT_PRICE_WID) << it_c->GetId()
             << setw(FORMAT_PRICE_WID) << it_c->GetSellerId() << endl;
        cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINT"
             << setw(FORMAT_BAR_RARE) << "" << endl
             << setfill(' ');
        it_c++;
        if (it_c == all_cloth.end())
          break;
      }
    }
  }
}

//----------------------------------------------------------
// CART FEATURE
void Platform::add_pdt_to_cart() {
  int id, count;

  product *pdt_ptr;
  consumer *cur_act;
  print_all_pdt(FOOD);
  print_all_pdt(CLOTH);
  print_all_pdt(BOOK);
  pdt_ptr = NULL;
  cur_act = (consumer *)cur_account;
  cout << "Please enter product id you want to add" << endl;
  cin >> id;
  cout << "Please enter num of product" << endl;
  cin >> count;
  int type = id / MAX_PRODUCT;
  if (type == FOOD) {
    list<food>::iterator it = all_food.begin();
    while (it != all_food.end()) {
      if (it->GetId() == id) {
        pdt_ptr = &(*it);
        break;
      }
      it++;
    }
  }
  if (type == CLOTH) {
    list<cloth>::iterator it = all_cloth.begin();
    while (it != all_cloth.end()) {
      if (it->GetId() == id) {
        pdt_ptr = &(*it);
        break;
      }
      it++;
    }
  }
  if (type == BOOK) {
    list<book>::iterator it = all_book.begin();
    while (it != all_book.end()) {
      if (it->GetId() == id) {
        pdt_ptr = &(*it);
        break;
      }
      it++;
    }
  }

  if (pdt_ptr) { // product found

    if (cur_act->cart_.add_pdt(pdt_ptr, count))
      cout << "sucessfully add product to cart" << endl;
    else
      cout << "fail to add product" << endl;
  } else
    cout << "product not found" << endl;
}
void Platform::remov_pdt_cart() {
  consumer *cur_act;
  int seq;
  cur_act = (consumer *)cur_account;
  cur_act->cart_.show_cart();
  cout << "enter the seq num you want to remove" << endl;
  cin >> seq;

  if (cur_act->cart_.remove_pdt(seq))
    cout << "remove successfully" << endl;
  else
    cout << "fail to remove" << endl;
}

void Platform::change_pdt_cart() {
  consumer *cur_act;
  int seq, num;
  cur_act = (consumer *)cur_account;
  cout << "please enter seq number you want to change" << endl;
  cin >> seq;
  cout << "enter number you want to change" << endl;
  cin >> num;

  if (cur_act->cart_.change_pdt_num(seq, num)) {
    cout << "change successfully" << endl;
  } else
    cout << "fail to change" << endl;
}

int cart::add_pdt(product *pdt_ptr, int num) {
  list<cart_pdt>::iterator it;
  it = pdt_lst.begin();
  int dup;
  dup = 0;
  while (it != pdt_lst.end()) {
    if (it->pdt_ptr == pdt_ptr) { // found duplicate
      dup = 1;
      break;
    }
    it++;
  }

  if (dup) {
    if (change_pdt_num(it->seq, num))
      return 2;
    else
      return 0;
  } else {
    if (pdt_ptr->GetStock() >= num && pdt_lst.size() < CART_SIZE) {
      pdt_ptr->ChangeStock(-1 * num);
      pdt_lst.push_back(cart_pdt(pdt_ptr, num, pdt_lst.size() + 1));
      return 1;
    } else
      return 0;
  }
  return 0;
}
int cart::remove_pdt(int seq) {
  list<cart_pdt>::iterator it;
  it = pdt_lst.begin();
  while (it != pdt_lst.end()) {
    if (it->seq == seq) {
      break;
    }
  }
  if (it == pdt_lst.end()) { // not found;
    return 0;
  } else {
    it->pdt_ptr->ChangeStock(it->num); // return frozed stock
    pdt_lst.erase(it);
    return 1;
  }
}

void cart::show_cart() {
  list<cart_pdt>::iterator it;
  it = pdt_lst.begin();
  cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING CART"
       << setw(FORMAT_BAR_RARE) << "" << endl
       << setfill(' ');
  cout << setw(FORMAT_SEQ_WID) << "Sequence" << setw(FORMAT_NAME_WID)
       << "Description" << setw(FORMAT_PRICE_WID) << "Price"
       << setw(FORMAT_PRICE_WID) << " ID" << setw(FORMAT_PRICE_WID) << "NUM"
       << setw(FORMAT_PRICE_WID) << "selected" << endl;
  while (it != pdt_lst.end()) {
    cout << setw(FORMAT_SEQ_WID) << it->seq << ". " << setw(FORMAT_NAME_WID)
         << it->pdt_ptr->GetDscrip() << setw(FORMAT_PRICE_WID)
         << it->pdt_ptr->GetPrice() << setw(FORMAT_PRICE_WID)
         << it->pdt_ptr->GetId() << setw(FORMAT_PRICE_WID) << it->num
         << setw(FORMAT_PRICE_WID) << it->selected << endl;
    it++;
  }
}

void cart::renew_seq() {
  int q = 1;
  list<cart_pdt>::iterator it;
  it = pdt_lst.begin();
  while (it != pdt_lst.end()) {
    it->seq = q;
    q++;
    it++;
  }
}

bool cart::is_empty() { return !(pdt_lst.size()); }

int cart::change_pdt_num(int seq, int num) {
  list<cart_pdt>::iterator it;
  it = pdt_lst.begin();
  while (it != pdt_lst.end()) {
    if (it->seq == seq) { // found
      if (it->num + num >= 0 && it->pdt_ptr->GetStock() - num >= 0) {
        it->num += num;
        it->pdt_ptr->ChangeStock(-1 * num);
        return 1;
        break;
      }
    }
    it++;
  }
  return 0;
}
int cart::genrate_order(consumer *cur_act) {
  int input;

  while (true) {

    show_cart();
    cout << "-1 for quitting, -2 for checking out,-3 for selecting all" << endl;
    cin >> input;
    if (input == -1) {
      break;
    }
    if (input == -2) {

      return (check_out_order(cur_act));
    }
    if (input == -3) {
      list<cart_pdt>::iterator it = pdt_lst.begin();
      while (it != pdt_lst.end()) {
        it->selected = 1;
        it++;
      }
    }

    if (input > 0 && input <= pdt_lst.size()) { // is a valid input
      list<cart_pdt>::iterator it = pdt_lst.begin();
      while (it != pdt_lst.end()) {
        if (it->seq == input) {
          if (it->selected)
            it->selected = 0;
          else
            it->selected = 1;
          break;
        }
        it++;
      }
    }
  }
  return 0;
}

int cart::check_out_order(consumer *cur_act) {
  list<cart_pdt>::iterator it = pdt_lst.begin();
  while (it != pdt_lst.end()) {
    if (it->selected) {

      if (it->pdt_ptr->GetPrice() * it->num <= cur_act->GetBalence()) {
        it->pdt_ptr->ChangeStock(-1 * it->num);
        cur_act->SubBalance(it->num * it->pdt_ptr->GetPrice());
        it->pdt_ptr->GetSellerAccount()->AddBalance(it->num *
                                                    it->pdt_ptr->GetPrice());
        it = pdt_lst.erase(it);

      } else
        return -2;
    } else
      it++;
  }
  return 1;
}

void Platform::check_out_cart() {
  int rtval;
  consumer *cur_act = (consumer *)cur_account;
  rtval = cur_act->cart_.genrate_order(cur_act);
  if (rtval == 1)
    cout << "Check out successfully" << endl;
  if (rtval == -1) {
    cout << "Not enough stock to check out" << endl;
    cur_act->cart_.show_cart();
  }
  if (rtval == -2) {
    cout << "not enough balance" << endl;
    cout << cur_account->GetBalence();
  }
}
void Platform::free_cart() {
  list<consumer>::iterator it;
  it = all_consumer.begin();

  while (it != all_consumer.end()) {
    it->cart_.delete_cart();
    it++;
  }
}
void cart::delete_cart() {
  list<cart_pdt>::iterator it;
  it = pdt_lst.begin();
  while (it != pdt_lst.end()) {
    it->pdt_ptr->ChangeStock(it->num);
    it = pdt_lst.erase(it);
  }
}
#endif