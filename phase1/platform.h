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
      type = -1;
    }
  }
  vector<product>::iterator it;
  std::sort(all_food.begin(), all_food.end());
  std::sort(all_cloth.begin(), all_cloth.end());
  std::sort(all_book.begin(), all_book.end());

  int i, q;
  q = 0;
  i = 0;
  while (i < all_book.size() && q < all_seller.size()) {
    if (all_book[i].GetSellerId() == all_seller[q].Getid()) {
      all_seller[q].fst_book = all_book.begin() + i;
      while (all_book[i].GetSellerId() == all_seller[q].Getid()) {
        i++;
        if (i == all_book.size())
          break;
      }
      q++;
    }
    if (i == all_book.size())
      break;
    if (all_book[i].GetSellerId() > all_seller[q].Getid())
      q++;
    if (all_book[i].GetSellerId() > all_seller[q].Getid())
      i++;
    if (i == all_book.size())
      break;
  }
  q = 0;
  i = 0;
  while (i < all_cloth.size() && q < all_seller.size()) {
    if (all_cloth[i].GetSellerId() == all_seller[q].Getid()) {
      all_seller[q].fst_clth = all_cloth.begin() + i;
      while (all_cloth[i].GetSellerId() == all_seller[q].Getid()) {
        i++;
        if (i == all_cloth.size())
          break;
      }
      q++;
    }
    if (i == all_cloth.size())
      break;
    if (all_cloth[i].GetSellerId() > all_seller[q].Getid())
      q++;
    if (all_cloth[i].GetSellerId() > all_seller[q].Getid())
      i++;
    if (i == all_cloth.size())
      break;
  }
  q = 0;
  i = 0;
  while (i < all_food.size() && q < all_seller.size()) {
    if (all_food[i].GetSellerId() == all_seller[q].Getid()) {
      all_seller[q].fst_fod = all_food.begin() + i;
      while (all_food[i].GetSellerId() == all_seller[q].Getid()) {
        i++;
        if (i == all_food.size())
          break;
      }
      q++;
    }
    if (i == all_food.size())
      break;
    if (all_food[i].GetSellerId() > all_seller[q].Getid())
      q++;
    if (all_food[i].GetSellerId() > all_seller[q].Getid())
      i++;
    if (i == all_food.size())
      break;
  }

  // cout << all_seller[0].fst_book->GetDscrip() << endl;
  print_all_act(SELLER);
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
         << setw(FORMAT_PRICE_WID) << "Stock" << setw(FORMAT_PRICE_WID) << "ID"
         << setw(FORMAT_PRICE_WID) << "SELLER_ID" << endl;
    for (int i = 0; i < all_book.size(); i++) {
      cout << setw(FORMAT_NAME_WID) << all_book[i].GetDscrip()
           << setw(FORMAT_PRICE_WID) << all_book[i].GetPrice()
           << setw(FORMAT_PRICE_WID) << all_book[i].GetStock()
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
         << setw(FORMAT_PRICE_WID) << "Stock" << setw(FORMAT_PRICE_WID) << "ID"
         << setw(FORMAT_PRICE_WID) << "SELLER_ID" << endl;
    for (int i = 0; i < all_cloth.size(); i++) {
      cout << setw(FORMAT_NAME_WID) << all_cloth[i].GetDscrip()
           << setw(FORMAT_PRICE_WID) << all_cloth[i].GetPrice()
           << setw(FORMAT_PRICE_WID) << all_cloth[i].GetStock()
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
         << setw(FORMAT_PRICE_WID) << "Stock" << setw(FORMAT_PRICE_WID) << "ID"
         << setw(FORMAT_PRICE_WID) << "SELLER_ID" << endl;
    for (int i = 0; i < all_food.size(); i++) {
      cout << setw(FORMAT_NAME_WID) << all_food[i].GetDscrip()
           << setw(FORMAT_PRICE_WID) << all_food[i].GetPrice()
           << setw(FORMAT_PRICE_WID) << all_food[i].GetStock()
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
  fout.open("product.txt");
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
  //   cout << i << ". back to option page" << endl;
  cout << "q.quiting\n";
  cout << "\n"
       << "Please enter your choice number" << endl;
  if (cin.peek() == 'q') {

    return -1;
  }
  cin >> choice;
  if (choice == i)
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
    for (int i = 0; i < all_book.size(); i++) {
      if (all_book[i].GetDscrip().find(input) != string::npos ||
          all_book[i].GetId() == id) { // found a match
        flag++;
        cout << setw(FORMAT_NAME_WID) << all_book[i].GetDscrip()
             << setw(FORMAT_PRICE_WID) << all_book[i].GetPrice()
             << setw(FORMAT_PRICE_WID) << all_book[i].GetId()
             << setw(FORMAT_PRICE_WID) << all_book[i].GetSellerId() << endl;
      }
    }
    for (int i = 0; i < all_cloth.size(); i++) {
      if (all_cloth[i].GetDscrip().find(input) != string::npos ||
          all_cloth[i].GetId() == id) { // found a match
        flag++;
        cout << setw(FORMAT_NAME_WID) << all_cloth[i].GetDscrip()
             << setw(FORMAT_PRICE_WID) << all_cloth[i].GetPrice()
             << setw(FORMAT_PRICE_WID) << all_cloth[i].GetId()
             << setw(FORMAT_PRICE_WID) << all_cloth[i].GetSellerId() << endl;
      }
    }
    for (int i = 0; i < all_food.size(); i++) {

      if (all_food[i].GetDscrip().find(input) != string::npos ||
          all_food[i].GetId() == id) { // found a match
        flag++;
        cout << setw(FORMAT_NAME_WID) << all_food[i].GetDscrip()
             << setw(FORMAT_PRICE_WID) << all_food[i].GetPrice()
             << setw(FORMAT_PRICE_WID) << all_food[i].GetId()
             << setw(FORMAT_PRICE_WID) << all_food[i].GetSellerId() << endl;
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
    for (int i = 0; i < all_consumer.size(); i++) {
      if (username == all_consumer[i].GetName()) {
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
    for (int i = 0; i < all_seller.size(); i++) {
      if (username == all_seller[i].GetName()) {
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
    for (loc = 0; loc < all_seller.size(); loc++) {
      if (all_seller[loc].GetName() == username)
        break;
    }
    if (all_seller[loc].GetName() == username) {     // account found
      if (all_seller[loc].checkPassword(password)) { // password correct
        cur_account = &all_seller[loc];
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
    for (loc = 0; loc < all_consumer.size(); loc++) {
      if (all_consumer[loc].GetName() == username)
        break;
    }
    if (all_consumer[loc].GetName() == username) {     // account found
      if (all_consumer[loc].checkPassword(password)) { // password correct
        cur_account = &all_consumer[loc];
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
  vector<product>::iterator it;
  cout << "please enter the product id you want " << endl;
  cin >> id;
  cout << "please enter number you want to buy" << endl;
  cin >> amount;
  type = id / MAX_PRODUCT;
  switch (type) {
  case FOOD:
    it = find(all_food.begin(), all_food.end(), id);
    if (it == all_food.end()) // not found
    {
      cout << "Product not found" << endl;

    } else
      found = 1;

    break;
  case CLOTH:
    it = find(all_cloth.begin(), all_cloth.end(), id);
    if (it == all_cloth.end()) // not found
    {
      cout << "Product not found" << endl;

    } else
      found = 1;

    break;
  case BOOK:
    it = find(all_book.begin(), all_book.end(), id);
    if (it == all_book.end()) // not found
    {
      cout << "Product not found" << endl;

    } else
      found = 1;
    break;
  }
  if (found) { // found
    if (cur_account->GetBalence() >= it->GetPrice() * amount) {
      if (it->GetStock() > amount) {
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
  print_my_product((seller *)cur_account);
  unsigned int id;
  int type, deleted;
  deleted = 0;
  cout << "enter id" << endl;
  cin >> id;
  type = id / MAX_PRODUCT;

  switch (type) {
  case FOOD:
    for (int i = 0; i < all_food.size(); i++) {
      if (all_food[i].GetId() == id) {
        all_food.erase(all_food.begin() + i);
        deleted = 1;
      }
    }
    break;
  case CLOTH:
    for (int i = 0; i < all_cloth.size(); i++) {
      if (all_cloth[i].GetId() == id) {
        all_cloth.erase(all_cloth.begin() + i);
        deleted = 1;
      }
    }
  case BOOK:
    for (int i = 0; i < all_book.size(); i++) {
      if (all_book[i].GetId() == id) {
        all_book.erase(all_book.begin() + i);
        deleted = 1;
      }
    }
    if (deleted) {
      cout << "delete successfully" << endl;

    } else
      cout << "target not found" << endl;

  default:
    break;
  }
}

void Platform::edt_pdt() {
  cout << "editing product" << endl;
  int type, pdt_type;
  unsigned int id;
  string descrip;
  vector<product>::iterator cur_pdt;
  float price = -1;
  int stock = -1;

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
  if (price) {
    cur_pdt->ChangePrice(price);
  } else if (stock) {
    cur_pdt->ChangeStock(stock);
  } else
    cur_pdt->ChangeDscrip(descrip);
}
void Platform::search_my_pdt(int type, unsigned int id,
                             vector<product>::iterator &cur_pdt,
                             seller *cur_account) {
  vector<product>::iterator it;
  switch (type) {

  case FOOD:
    for (it = cur_account->fst_fod; it->GetSellerId() == cur_account->Getid();
         it++) {
      if (it->GetId() == id) {
        cur_pdt = it;
        break;
      }
    }
    break;

  case BOOK:
    for (it = cur_account->fst_book; it->GetSellerId() == cur_account->Getid();
         it++) {
      if (it->GetId() == id) {
        cur_pdt = it;
        break;
      }
    }
  case CLOTH:
    for (it = cur_account->fst_clth; it->GetSellerId() == cur_account->Getid();
         it++) {
      if (it->GetId() == id) {
        cur_pdt = it;
        break;
      }
    }
  }
}
void Platform ::print_my_product(seller *cur_act) {
  vector<product>::iterator it;
  cout << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING MY CLOTHES"
       << setw(FORMAT_BAR_RARE) << "" << endl
       << setfill(' ');

  cout << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID) << "Price"
       << setw(FORMAT_PRICE_WID) << "STOCK" << setw(FORMAT_PRICE_WID) << "ID"
       << setw(FORMAT_PRICE_WID) << "SELLER_ID" << endl;
  for (it = cur_act->fst_clth; it->GetSellerId() == cur_account->Getid();
       it++) {
    cout << setw(FORMAT_NAME_WID) << it->GetDscrip() << setw(FORMAT_PRICE_WID)
         << it->GetPrice() << setw(FORMAT_PRICE_WID) << it->GetStock()
         << setw(FORMAT_PRICE_WID) << it->GetId() << setw(FORMAT_PRICE_WID)
         << it->GetSellerId() << endl;
  }
}
#endif