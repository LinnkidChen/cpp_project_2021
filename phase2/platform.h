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
        auto it = all_seller.begin();
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
        auto it = all_seller.begin();
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
        auto it = all_seller.begin();
        for (; it != all_seller.end(); it++) {
          if (it->Getid() == seller_id) {
            bok.SetSellerAccount(&(*it));
            break;
          }
        }
        all_book.push_back(bok);
      }
      type = -1;
    }
  }
  list<product>::iterator it;
  std::sort(all_food.begin(), all_food.end());
  std::sort(all_cloth.begin(), all_cloth.end());
  std::sort(all_book.begin(), all_book.end());

  // cout << all_seller[0].fst_book->GetDscrip() << endl;
  print_all_act(SELLER);
  print_all_pdt(FOOD);
  print_all_pdt(CLOTH);
  print_all_pdt(BOOK);
}

void Platform ::print_all_act(int type) {

  if (type == SELLER) {
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING ALL SELLER"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');

    cout << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID)
         << "BALANCE" << setw(FORMAT_PRICE_WID) << "ID" << endl;
    auto it = all_seller.begin();
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
    for (auto it = all_consumer.begin(); it != all_consumer.end(); it++) {
      cout << setw(FORMAT_NAME_WID) << it->GetName() << setw(FORMAT_PRICE_WID)
           << it->GetBalence() << setw(FORMAT_PRICE_WID) << it->Getid() << endl;
    }
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINTING"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');
  }
}

void Platform ::print_all_pdt(int type) {
  switch (type) {
  case BOOK:
    cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING ALL BOOKS"
         << setw(FORMAT_BAR_RARE) << "" << endl
         << setfill(' ');

    cout << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID) << "Price"
         << setw(FORMAT_PRICE_WID) << "Stock" << setw(FORMAT_PRICE_WID) << "ID"
         << setw(FORMAT_PRICE_WID) << "SELLER_ID" << endl;
    for (auto it = all_book.begin(); it != all_book.end(); it++) {
      cout << setw(FORMAT_NAME_WID) << it->GetDscrip() << setw(FORMAT_PRICE_WID)
           << it->GetPrice() << setw(FORMAT_PRICE_WID) << it->GetStock()
           << setw(FORMAT_PRICE_WID) << it->GetId() << setw(FORMAT_PRICE_WID)
           << it->GetSellerId() << endl;
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
         << setw(FORMAT_PRICE_WID) << "Stock" << setw(FORMAT_PRICE_WID) << "ID"
         << setw(FORMAT_PRICE_WID) << "SELLER_ID" << endl;
    for (auto it = all_cloth.begin(); it != all_cloth.end(); it++) {
      cout << setw(FORMAT_NAME_WID) << it->GetDscrip() << setw(FORMAT_PRICE_WID)
           << it->GetPrice() << setw(FORMAT_PRICE_WID) << it->GetStock()
           << setw(FORMAT_PRICE_WID) << it->GetId() << setw(FORMAT_PRICE_WID)
           << it->GetSellerId() << endl;
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
         << setw(FORMAT_PRICE_WID) << "Stock" << setw(FORMAT_PRICE_WID) << "ID"
         << setw(FORMAT_PRICE_WID) << "SELLER_ID" << endl;
    for (auto it = all_food.begin(); it != all_food.end(); it++) {
      cout << setw(FORMAT_NAME_WID) << it->GetDscrip() << setw(FORMAT_PRICE_WID)
           << it->GetPrice() << setw(FORMAT_PRICE_WID) << it->GetStock()
           << setw(FORMAT_PRICE_WID) << it->GetId() << setw(FORMAT_PRICE_WID)
           << it->GetSellerId() << endl;
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
    for (auto it = all_seller.begin(); it != all_seller.end(); it++)
      fout << it->GetUserType() << " " << it->GetName() << " " << it->GetPswd()
           << " " << it->GetBalence() << " " << it->Getid() << endl;

    for (auto it = all_consumer.begin(); it != all_consumer.end(); it++)
      fout << it->GetUserType() << " " << it->GetName() << " " << it->GetPswd()
           << " " << it->GetBalence() << " " << it->Getid() << endl;
  }
  fout.close();
  fout.open("product.txt");
  if (!fout.is_open()) {
    cout << "unable to open product.txt";
  } else {
    for (auto it = all_food.begin(); it != all_food.end(); it++) {
      fout << it->GetProductType() << " " << it->GetDscrip() << " "
           << it->GetPrice() << " " << it->GetStock() << " " << it->GetId()
           << " " << it->GetSellerId() << endl;
    }
    for (auto it = all_cloth.begin(); it != all_cloth.end(); it++) {
      fout << it->GetProductType() << " " << it->GetDscrip() << " "
           << it->GetPrice() << " " << it->GetStock() << " " << it->GetId()
           << " " << it->GetSellerId() << endl;
      for (auto it = all_book.begin(); it != all_book.end(); it++) {
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

*/
int Platform::Get_option() {
  int i = 1;
  int choice;

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
  //   cout << i << ". back to option page" << endl;
  cout << "q.quiting\n";
  cout << "\n"
       << "Please enter your choice number" << endl;
  if (cin.peek() == 'q') {
    return -1;
  }
  cin >> choice;
  if (choice >= i)
    return 20; // skip the swithch branch
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
    11. delete product -->
    12.  edit product--seller
    changd descrip/ change stock/ change price

*/
void Platform ::process_choice(int choice) {
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
  }
}

void Platform::search_product() {
  cout << "Please enter the info you want to search" << endl;
  string input;
  unsigned int id, flag;
  cin >> input;
  stringstream degree(input);
  degree >> id;
  flag = 0;

  if (!input.compare("FOOD")) // print all products under one catagory
    print_all_pdt(FOOD);
  else if (!input.compare("CLOTH"))
    print_all_pdt(CLOTH);
  else if (!input.compare("BOOK"))
    print_all_pdt(BOOK);
  else {
    for (auto it = all_book.begin(); it != all_book.end(); it++) {
      if (it->GetDscrip().find(input) != string::npos ||
          it->GetId() == id) { // found a match
        flag++;
        cout << setw(FORMAT_NAME_WID) << it->GetDscrip()
             << setw(FORMAT_PRICE_WID) << it->GetPrice()
             << setw(FORMAT_PRICE_WID) << it->GetId() << setw(FORMAT_PRICE_WID)
             << it->GetSellerId() << endl;
      }
    }
    for (auto it = all_cloth.begin(); it != all_cloth.end(); it++) {
      if (it->GetDscrip().find(input) != string::npos ||
          it->GetId() == id) { // found a match
        flag++;
        cout << setw(FORMAT_NAME_WID) << it->GetDscrip()
             << setw(FORMAT_PRICE_WID) << it->GetPrice()
             << setw(FORMAT_PRICE_WID) << it->GetId() << setw(FORMAT_PRICE_WID)
             << it->GetSellerId() << endl;
      }
    }
    for (auto it = all_food.begin(); it != all_food.end(); it++) {

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
  if (id == 0)
    cout << "username already in use" << endl;
  if (password.empty() || username.empty()) {
    cout << "invalid input" << endl;
    id = 0;
  }
  if (type == CONSUMER) {
    for (auto it = all_consumer.begin(); it != all_consumer.end(); it++) {
      if (username == it->GetName()) {
        id = 0;
        break;
      }
    }
    if (id > 0) {
      consumer csmr(username, password, 0, id);
      all_consumer.push_back(csmr);
      cout << "Create successfully!" << endl;
    }
  }
  if (type == SELLER) {
    for (auto it = all_seller.begin(); it != all_seller.end(); it++) {
      if (username == it->GetName()) {
        id = 0;
        break;
      }
    }
    if (id > 0) {
      seller slr(username, password, 0, id);
      all_seller.push_back(slr);
      cout << "Create successfully!" << endl;
    }
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
    auto it = all_seller.begin();
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
    auto it = all_consumer.begin();
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
  list<product>::iterator it;
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
    auto it = all_food.begin();
    for (; it != all_food.end(); it++) {
      if (it->GetId() == id) {
        found = 1;
        break;
      }
    }
    if (it == all_food.end()) // not found
    {
      cout << "Product not found" << endl;
    }
  }
  if (type == CLOTH)

  {
    auto it = all_cloth.begin();
    for (; it != all_cloth.end(); it++) {
      if (it->GetId() == id) {
        found = 1;
        break;
      }
    }
    if (it == all_cloth.end()) // not found
    {
      cout << "Product not found" << endl;
    }
  }
  if (type == BOOK)

  {
    auto it = all_book.begin();
    for (; it != all_book.end(); it++) {
      if (it->GetId() == id) {
        found = 1;
        break;
      }
    }
    if (it == all_book.end()) // not found
    {
      cout << "Product not found" << endl;
    }
  }

  if (found) { // found
    if (cur_account->GetBalence() >= it->GetPrice() * amount) {
      if (it->GetStock() >= amount) {
        it->ChangeStock(-1 * amount);
        cur_account->SubBalance(amount * it->GetPrice());
        it->GetSellerAccount()->AddBalance(it->GetPrice() * amount);
        cout << "Purchase successfully" << endl;
      } else
        cout << "Not enough balance" << endl;
    } else
      cout << "Not enough product in stock" << endl;
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
  }
  if (type == CLOTH) {
    cloth clth(dscrip, price, stock, id, sellerid);
    clth.SetSellerAccount((seller *)cur_account);
    all_cloth.push_back(clth);
  }
  if (type == BOOK) {
    book bok(dscrip, price, stock, id, sellerid);
    bok.SetSellerAccount((seller *)cur_account);
    all_book.push_back(bok);
  }
  cout << "Add product successfully" << endl;
}

unsigned int Platform::genrate_pdt_id(int type) {
  switch (type) {
  case FOOD:
    if (!all_food.empty())
      return all_food.back().GetId() + 1;
    else
      return FOOD * MAX_PRODUCT;
    break;
  case CLOTH:
    if (!all_cloth.empty())
      return all_cloth.back().GetId() + 1;
    else
      return CLOTH * MAX_PRODUCT;
    break;
  case BOOK:
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

  switch (type) {
  case FOOD:
    for (auto it = all_food.begin(); it != all_food.end(); it++) {
      if (it->GetId() == id) {
        all_food.erase(all_food.begin() + i);
        deleted = 1;
      }
    }
    break;
  case CLOTH:
    for (auto it = all_cloth.begin(); it != all_cloth.end(); it++) {
      if (it->GetId() == id) {
        all_cloth.erase(all_cloth.begin() + i);
        deleted = 1;
      }
    }
  case BOOK:
    for (auto it = all_book.begin(); it != all_book.end(); it++) {
      if (it->GetId() == id) {
        all_book.erase(all_book.begin() + i);
        deleted = 1;
      }
    }
  }
  if (deleted == 1) {
    cout << "delete successfully" << endl;

  } else
    cout << "target not found" << endl;
}

void Platform::edt_pdt() {
  cout << "editing product" << endl;
  int type, pdt_type;
  unsigned int id;
  string descrip;
  list<product>::iterator cur_pdt;
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
}
void Platform::search_my_pdt(int type, unsigned int id,
                             list<product>::iterator &cur_pdt,
                             seller *cur_account) {
  list<food>::iterator it_f;
  list<book>::iterator it_b;
  list<cloth>::iterator it_c;

  switch (type) {

  case FOOD:
    it_f = all_food.begin();
    while (it_f->GetSellerId() != cur_account->Getid()) {
      it_f++;
    }

    for (; it_f->GetSellerId() == cur_account->Getid(); it_f++) {
      if (it_f->GetId() == id) {
        cur_pdt = it_f;
        break;
      }
    }
    break;

  case BOOK:
    it_b = all_book.begin();
    while (it_b->GetSellerId() != cur_account->Getid()) {
      it_b++;
    }

    for (; it_b->GetSellerId() == cur_account->Getid(); it_b++) {
      if (it_b->GetId() == id) {
        cur_pdt = it_b;
        break;
      }
    }
    break;
  case CLOTH:
    it_c = all_cloth.begin();
    while (it_c->GetSellerId() != cur_account->Getid()) {
      it_c++;
    }

    for (; it_c->GetSellerId() == cur_account->Getid(); it_c++) {
      if (it_c->GetId() == id) {
        cur_pdt = it_c;
        break;
      }
    }
  }
}
void Platform ::print_my_product(int type) {
  list<food>::iterator it_f;
  list<book>::iterator it_b;
  list<cloth>::iterator it_c;
  switch (type) {
  case FOOD:
    it_f = all_food.begin();
    while (it_f->GetSellerId() != cur_account->Getid()) {
      it_f++;
      if (it_f == all_food.end()) {
        type = -1;
        break;
      } else if (it_f->GetDscrip().empty()) {
        type = -1;
        break;
      }
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

    break;

  case BOOK:
    it_b = all_book.begin();
    while (it_b->GetSellerId() != cur_account->Getid()) {
      it_b++;
      if (it_b == all_book.end()) {
        type = -1;
        break;
      } else if (it_b->GetDscrip().empty()) {
        type = -1;
        break;
      }
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

    break;
  case CLOTH:
    it_c = all_cloth.begin();
    while (it_c->GetSellerId() != cur_account->Getid()) {
      it_c++;
      if (it_c == all_cloth.end()) {
        type = -1;
        break;
      } else if (it_c->GetDscrip().empty()) {
        type = -1;
        break;
      }
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

    break;

  default:
    type = -1;
    break;
  }
}

#endif