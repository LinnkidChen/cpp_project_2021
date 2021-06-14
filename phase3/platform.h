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
  if (!fin.is_open()) {
    skt.out_ << "FAIL TO OPEN account.txt" << endl;
    skt.send_();
  }

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
  if (!fin.is_open()) {
    skt.out_ << "FAIL TO OPEN account.txt" << endl;
    skt.send_();
  } else {
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

  // skt.out_ << all_seller[0].fst_book->GetDscrip() << endl;
  //   print_all_act(SELLER);
  //   print_all_pdt(FOOD);
  //   print_all_pdt(CLOTH);
  // print_all_pdt(BOOK);
}

void Platform ::print_all_act(int type) {

  if (type == SELLER) {
    skt.out_ << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING ALL SELLER"
             << setw(FORMAT_BAR_RARE) << "" << endl
             << setfill(' ');

    skt.out_ << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID)
             << "BALANCE" << setw(FORMAT_PRICE_WID) << "ID" << endl;
    // skt.send_();
    list<seller>::iterator it = all_seller.begin();
    for (; it != all_seller.end(); it++) {
      skt.out_ << setw(FORMAT_NAME_WID) << it->GetName()
               << setw(FORMAT_PRICE_WID) << it->GetBalence()
               << setw(FORMAT_PRICE_WID) << it->Getid() << endl;
      //   skt.send_();
    }
    skt.out_ << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINTING"
             << setw(FORMAT_BAR_RARE) << "" << endl
             << setfill(' ');
    skt.send_();
  }

  if (type == CONSUMER) {
    skt.out_ << setw(FORMAT_BAR_FRONT) << setfill('-')
             << "PRINTING ALL CONSUMER" << setw(FORMAT_BAR_RARE) << "" << endl
             << setfill(' ');

    skt.out_ << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID)
             << "BALANCE" << setw(FORMAT_PRICE_WID) << "ID" << endl;
    // skt.send_();
    for (list<consumer>::iterator it = all_consumer.begin();
         it != all_consumer.end(); it++) {
      skt.out_ << setw(FORMAT_NAME_WID) << it->GetName()
               << setw(FORMAT_PRICE_WID) << it->GetBalence()
               << setw(FORMAT_PRICE_WID) << it->Getid() << endl;
      //   skt.send_();
    }
    skt.out_ << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINTING"
             << setw(FORMAT_BAR_RARE) << "" << endl
             << setfill(' ');
    skt.send_();
  }
}

void Platform ::print_all_pdt(int type) {

  if (type == BOOK) {
    skt.out_ << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING ALL BOOKS"
             << setw(FORMAT_BAR_RARE) << "" << endl
             << setfill(' ');

    skt.out_ << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID)
             << "Price" << setw(FORMAT_PRICE_WID) << "Stock"
             << setw(FORMAT_PRICE_WID) << "ID" << setw(FORMAT_PRICE_WID)
             << "SELLER_ID" << endl;
    // skt.send_();
    for (list<book>::iterator it = all_book.begin(); it != all_book.end();
         it++) {
      skt.out_ << setw(FORMAT_NAME_WID) << it->GetDscrip()
               << setw(FORMAT_PRICE_WID) << it->GetPrice()
               << setw(FORMAT_PRICE_WID) << it->GetStock()
               << setw(FORMAT_PRICE_WID) << it->GetId()
               << setw(FORMAT_PRICE_WID) << it->GetSellerId() << endl;
      //   skt.send_();
    }
    skt.out_ << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINTING"
             << setw(FORMAT_BAR_RARE) << "" << endl
             << setfill(' ');
    skt.send_();
  }
  if (type == CLOTH) {
    skt.out_ << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING ALL CLOTHES"
             << setw(FORMAT_BAR_RARE) << "" << endl
             << setfill(' ');

    skt.out_ << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID)
             << "Price" << setw(FORMAT_PRICE_WID) << "Stock"
             << setw(FORMAT_PRICE_WID) << "ID" << setw(FORMAT_PRICE_WID)
             << "SELLER_ID" << endl;
    // skt.send_();
    for (list<cloth>::iterator it = all_cloth.begin(); it != all_cloth.end();
         it++) {
      skt.out_ << setw(FORMAT_NAME_WID) << it->GetDscrip()
               << setw(FORMAT_PRICE_WID) << it->GetPrice()
               << setw(FORMAT_PRICE_WID) << it->GetStock()
               << setw(FORMAT_PRICE_WID) << it->GetId()
               << setw(FORMAT_PRICE_WID) << it->GetSellerId() << endl;
      //   skt.send_();
    }
    skt.out_ << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINTING"
             << setw(FORMAT_BAR_RARE) << "" << endl
             << setfill(' ');
    skt.send_();
  }
  if (type == FOOD) {
    skt.out_ << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING ALL FOOD"
             << setw(FORMAT_BAR_RARE) << "" << endl
             << setfill(' ');

    skt.out_ << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID)
             << "Price" << setw(FORMAT_PRICE_WID) << "Stock"
             << setw(FORMAT_PRICE_WID) << "ID" << setw(FORMAT_PRICE_WID)
             << "SELLER_ID" << endl;
    // skt.send_();
    for (list<food>::iterator it = all_food.begin(); it != all_food.end();
         it++) {
      skt.out_ << setw(FORMAT_NAME_WID) << it->GetDscrip()
               << setw(FORMAT_PRICE_WID) << it->GetPrice()
               << setw(FORMAT_PRICE_WID) << it->GetStock()
               << setw(FORMAT_PRICE_WID) << it->GetId()
               << setw(FORMAT_PRICE_WID) << it->GetSellerId() << endl;
      //   skt.send_();
    }
    skt.out_ << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINTING"
             << setw(FORMAT_BAR_RARE) << "" << endl
             << setfill(' ');
    skt.send_();
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
    skt.out_ << "unable to open account.txt";
    skt.send_();
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
    skt.out_ << "unable to open product.txt";
    skt.send_();
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

  skt.out_ << i << ". show all product" << endl; // 1
  i++;
  skt.out_ << i << ". search product " << endl; // 2
  i++;
  if (account_type == -1) {               // not signed in{
    skt.out_ << i << ". sign in" << endl; // 3
    i++;
    skt.out_ << i << ". log in" << endl; // 4
    i++;
  } else {                                        // signed in
    skt.out_ << i << ". change password" << endl; // 3
    i++;
    skt.out_ << i << ". show balance" << endl; // 4
    i++;
    skt.out_ << i << ". log out" << endl; // 5
    i++;
  }

  if (account_type == CONSUMER) {
    skt.out_ << i << ".  top up" << endl; // 6
    i++;
    skt.out_ << i << ". buy product" << endl; // 7
    i++;
  }
  if (account_type == SELLER) {
    skt.out_ << i << ". add product" << endl; // 6
    i++;
    skt.out_ << i << ". delete product" << endl; // 7
    i++;
    skt.out_ << i << ". edit product" << endl; // 8
    i++;
  }

  if (account_type == CONSUMER) {
    skt.out_ << i << ". add product to cart" << endl; // 8
    i++;
    consumer *act;
    act = (consumer *)cur_account;
    if (!(act->cart_.is_empty())) {
      skt.out_ << i << ". remove product" << endl; // 9
      i++;
      skt.out_ << i << ". change product number" << endl; // 10
      i++;
      skt.out_ << i << ". show cart" << endl; // 11
      i++;
      skt.out_ << i << ". genrate_order" << endl; // 12
      i++;
    }
  }
  //   skt.out_ << i << ". back to option page" << endl;
  skt.out_ << "q.quiting\n";
  skt.out_ << "\n"
           << "Please enter your choice number" << endl;
  skt.send_();
  skt.recv_();
  if (skt.in_.peek() == 'q') {

    return -1;
  }
  skt.in_ >> choice;
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
    skt.out_ << "your balance is : " << cur_account->GetBalence() << endl;
    skt.send_();
    break;
  case 7:
    cur_account = NULL;
    account_type = -1;
    skt.out_ << "log out successfully" << endl;
    skt.send_();
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
    curact->cart_.show_cart(skt);
    break;
  case 17:
    check_out_cart();
    break;
  }
}

void Platform::search_product() {
  skt.out_ << "Please enter the info you want to search" << endl;
  skt.send_();
  string input;
  unsigned int id, flag;
  skt.recv_();
  skt.in_ >> input;
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
        skt.out_ << setw(FORMAT_NAME_WID) << it->GetDscrip()
                 << setw(FORMAT_PRICE_WID) << it->GetPrice()
                 << setw(FORMAT_PRICE_WID) << it->GetId()
                 << setw(FORMAT_PRICE_WID) << it->GetSellerId() << endl;
      }
    }
    skt.send_();
    for (list<cloth>::iterator it = all_cloth.begin(); it != all_cloth.end();
         it++) {
      if (it->GetDscrip().find(input) != string::npos ||
          it->GetId() == id) { // found a match
        flag++;
        skt.out_ << setw(FORMAT_NAME_WID) << it->GetDscrip()
                 << setw(FORMAT_PRICE_WID) << it->GetPrice()
                 << setw(FORMAT_PRICE_WID) << it->GetId()
                 << setw(FORMAT_PRICE_WID) << it->GetSellerId() << endl;
      }
    }
    skt.send_();
    for (list<food>::iterator it = all_food.begin(); it != all_food.end();
         it++) {

      if (it->GetDscrip().find(input) != string::npos ||
          it->GetId() == id) { // found a match
        flag++;
        skt.out_ << setw(FORMAT_NAME_WID) << it->GetDscrip()
                 << setw(FORMAT_PRICE_WID) << it->GetPrice()
                 << setw(FORMAT_PRICE_WID) << it->GetId()
                 << setw(FORMAT_PRICE_WID) << it->GetSellerId() << endl;
      }
    }
    skt.send_();
    if (!flag)
      skt.out_ << "Cant find target product " << endl;
    skt.send_();
  }
}

void Platform ::create_new_act() {
  skt.out_ << "Creating new account" << endl;
  string username, password;
  skt.send_();
  unsigned int id;
  int type;
  skt.out_ << "Type.1 for seller,2 for consumer" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> type;
  skt.out_ << "username" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> username;
  skt.out_ << "password" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> password;

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
      skt.out_ << "Create successfully!" << endl;
      //   skt.send_();
    } else {
      skt.out_ << "Username alredy in use." << endl;
    }
    skt.send_();
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
      skt.out_ << "Create successfully!" << endl;
      //   skt.send_();
    } else {
      skt.out_ << "Username alredy in use." << endl;
    }
    skt.send_();
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
  skt.out_ << "Log in" << endl;
  skt.send_();
  string username, password;
  int type, loc;
  skt.out_ << "account type: 1 for seller,2 for consumer" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> type;
  skt.out_ << "username" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> username;
  skt.out_ << "password" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> password;

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
        skt.out_ << "Log in successfully" << endl;
        // skt.send_();
      } else // password incorrect
      {
        skt.out_ << "Incorrect password.Please try again." << endl;
        // skt.send_();
      }
    } else {
      // account not found
      skt.out_ << "Account not found.please check your input" << endl;
    }
    skt.send_();
  } else if (type == CONSUMER) {
    list<consumer>::iterator it = all_consumer.begin();
    for (; it != all_consumer.end(); it++) {
      if (it->GetName() == username)
        break;
    }
    if (it->GetName() == username) {     // account found
      if (it->checkPassword(password)) { // password correct
        cur_account = &(*it);
        account_type = CONSUMER;
        skt.out_ << "Log in successfully" << endl;
        skt.send_();
      } else // password incorrect
      {
        skt.out_ << "Incorrect password.Please try again." << endl;
        skt.send_();
      }
    } else {
      // account not found
      {
        skt.out_ << "Account not found.please check your input" << endl;
        skt.send_();
      }
    }
  } else
    skt.out_ << "error account type" << endl;
  skt.send_();
}

void Platform::change_password() {
  skt.out_ << "Change password" << endl;
  skt.send_();
  string old_pswd, new_pswd;
  skt.out_ << "old passowrd" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> old_pswd;
  skt.out_ << "new password" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> new_pswd;
  if (cur_account->changePassword(old_pswd, new_pswd)) // oldpassowrd is corrct
  {
    skt.out_ << "Change Successfully" << endl;
    skt.send_();
  } else {
    skt.out_ << "incorrect password,please try again" << endl;
    skt.send_();
  }
}
void Platform::top_up() {
  skt.out_ << "top up" << endl;
  skt.send_();
  float add;
  skt.out_ << "amount you want to add:" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> add;
  cur_account->AddBalance(add);
  skt.out_ << "add successfully" << endl;
  skt.send_();
}

void Platform::purchase_pdt() {
  skt.out_ << "Purchasing product" << endl;
  skt.send_();
  unsigned int id, amount;
  int type, found = 0;
  product *cur_pdt = NULL;
  print_all_pdt(FOOD);
  print_all_pdt(CLOTH);
  print_all_pdt(BOOK);
  skt.out_ << "please enter the product id you want " << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> id;
  skt.out_ << "please enter number you want to buy" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> amount;
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
      skt.out_ << "Product not found" << endl;
      skt.send_();
    } else
      cur_pdt = &(*it);
  } else if (type == CLOTH)

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
      skt.out_ << "Product not found" << endl;
      skt.send_();
    } else
      cur_pdt = &(*it);
  } else if (type == BOOK)

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
      skt.out_ << "Product not found" << endl;
      skt.send_();
    } else
      cur_pdt = &(*it);
  } else {
    skt.out_ << "Product not found" << endl;
    skt.send_();
  }
  if (found) { // found
    if (cur_account->GetBalence() >= cur_pdt->GetPrice() * amount) {
      if (cur_pdt->GetStock() >= amount) {
        cur_pdt->ChangeStock(-1 * amount);
        cur_account->SubBalance(amount * cur_pdt->GetPrice());
        cur_pdt->GetSellerAccount()->AddBalance(cur_pdt->GetPrice() * amount);
        skt.out_ << "Purchase successfully" << endl;
      } else
        skt.out_ << "Not enough balance" << endl;
    } else
      skt.out_ << "Not enough product in stock" << endl;
  }
  skt.send_();
}
void Platform::add_pdt() {
  skt.out_ << "adding product" << endl;
  skt.send_();
  string dscrip;
  int type, stock;
  float price;
  unsigned int id, sellerid;
  skt.out_ << "type,11 for food,12 for cloth,13 for book" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> type;
  skt.out_ << "description" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> dscrip;
  skt.out_ << "stock" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> stock;
  skt.out_ << "price" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> price;

  id = genrate_pdt_id(type);
  sellerid = cur_account->Getid();

  if (type == FOOD) {
    food fod(dscrip, price, stock, id, sellerid);
    fod.SetSellerAccount((seller *)cur_account);
    all_food.push_back(fod);
    skt.out_ << "Add product successfully" << endl;
  } else if (type == CLOTH) {
    cloth clth(dscrip, price, stock, id, sellerid);
    clth.SetSellerAccount((seller *)cur_account);
    all_cloth.push_back(clth);
    skt.out_ << "Add product successfully" << endl;
  } else if (type == BOOK) {
    book bok(dscrip, price, stock, id, sellerid);
    bok.SetSellerAccount((seller *)cur_account);
    all_book.push_back(bok);
    skt.out_ << "Add product successfully" << endl;
  } else {
    skt.out_ << "Invalid type" << endl;
  }

  skt.send_();
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

  skt.out_ << "delete product" << endl;
  skt.send_();
  print_my_product(FOOD);
  print_my_product(BOOK);
  print_my_product(CLOTH);
  unsigned int id;
  int type, deleted;
  deleted = 0;
  skt.out_ << "enter id" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> id;
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
      skt.out_ << "delete successfully" << endl;

    } else
      skt.out_ << "target not found" << endl;
    skt.send_();
  }
}
void Platform::edt_pdt() {
  skt.out_ << "editing product" << endl;
  skt.send_();
  int type, pdt_type;
  unsigned int id;
  string descrip;
  product *cur_pdt = NULL;
  float price = -1;
  int stock = -1;
  print_my_product(FOOD);
  print_my_product(BOOK);
  print_my_product(CLOTH);
  skt.out_ << "enter type.1 descrip,2 price,3 stock" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> type;
  skt.out_ << "enter product id" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> id;
  pdt_type = id / MAX_PRODUCT;
  switch (type) {
  case 1:
    skt.out_ << "new descrip" << endl;
    skt.send_();
    skt.recv_();
    skt.in_ >> descrip;
    break;
  case 2:
    skt.out_ << "new price" << endl;
    skt.send_();
    skt.recv_();
    skt.in_ >> price;
    break;
  case 3:
    skt.out_ << "new stock" << endl;
    skt.send_();
    skt.recv_();
    skt.in_ >> stock;
    break;
  }

  search_my_pdt(pdt_type, id, cur_pdt, (seller *)cur_account);
  if (cur_pdt) {
    if (price > 0) {
      cur_pdt->ChangePrice(price);
      skt.out_ << "change price done" << endl;
    } else if (stock > 0) {
      cur_pdt->ChangeStock(stock);
      skt.out_ << "change stock done" << endl;
    } else {
      cur_pdt->ChangeDscrip(descrip);
      skt.out_ << "change description done" << endl;
    }
    skt.send_();
  } else {
    skt.out_ << "fail to find product";
    skt.send_();
  }
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
      skt.out_ << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING MY FOOD"
               << setw(FORMAT_BAR_RARE) << "" << endl
               << setfill(' ');

      skt.out_ << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID)
               << "Price" << setw(FORMAT_PRICE_WID) << "STOCK"
               << setw(FORMAT_PRICE_WID) << "ID" << setw(FORMAT_PRICE_WID)
               << "SELLER_ID" << endl;
      //   skt.send_();
      for (; it_f->GetSellerId() == cur_account->Getid();) {
        skt.out_ << setw(FORMAT_NAME_WID) << it_f->GetDscrip()
                 << setw(FORMAT_PRICE_WID) << it_f->GetPrice()
                 << setw(FORMAT_PRICE_WID) << it_f->GetStock()
                 << setw(FORMAT_PRICE_WID) << it_f->GetId()
                 << setw(FORMAT_PRICE_WID) << it_f->GetSellerId() << endl;
        skt.out_ << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINT"
                 << setw(FORMAT_BAR_RARE) << "" << endl
                 << setfill(' ');
        //
        it_f++;
        if (it_f == all_food.end())
          break;
      }
      skt.send_();
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
      skt.out_ << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING MY BOOK"
               << setw(FORMAT_BAR_RARE) << "" << endl
               << setfill(' ');

      skt.out_ << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID)
               << "Price" << setw(FORMAT_PRICE_WID) << "STOCK"
               << setw(FORMAT_PRICE_WID) << "ID" << setw(FORMAT_PRICE_WID)
               << "SELLER_ID" << endl;
      //   skt.send_();
      for (; it_b->GetSellerId() == cur_account->Getid();) {
        skt.out_ << setw(FORMAT_NAME_WID) << it_b->GetDscrip()
                 << setw(FORMAT_PRICE_WID) << it_b->GetPrice()
                 << setw(FORMAT_PRICE_WID) << it_b->GetStock()
                 << setw(FORMAT_PRICE_WID) << it_b->GetId()
                 << setw(FORMAT_PRICE_WID) << it_b->GetSellerId() << endl;
        skt.out_ << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINT"
                 << setw(FORMAT_BAR_RARE) << "" << endl
                 << setfill(' ');

        it_b++;
        if (it_b == all_book.end())
          break;
      }
      skt.send_();
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
      skt.out_ << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING MY CLOTH"
               << setw(FORMAT_BAR_RARE) << "" << endl
               << setfill(' ');

      skt.out_ << setw(FORMAT_NAME_WID) << "Name" << setw(FORMAT_PRICE_WID)
               << "Price" << setw(FORMAT_PRICE_WID) << "STOCK"
               << setw(FORMAT_PRICE_WID) << "ID" << setw(FORMAT_PRICE_WID)
               << "SELLER_ID" << endl;
      // skt.send_();
      for (; it_c->GetSellerId() == cur_account->Getid();) {
        skt.out_ << setw(FORMAT_NAME_WID) << it_c->GetDscrip()
                 << setw(FORMAT_PRICE_WID) << it_c->GetPrice()
                 << setw(FORMAT_PRICE_WID) << it_c->GetStock()
                 << setw(FORMAT_PRICE_WID) << it_c->GetId()
                 << setw(FORMAT_PRICE_WID) << it_c->GetSellerId() << endl;
        skt.out_ << setw(FORMAT_BAR_FRONT) << setfill('-') << "END OF PRINT"
                 << setw(FORMAT_BAR_RARE) << "" << endl
                 << setfill(' ');
        it_c++;

        if (it_c == all_cloth.end())
          break;
      }
      skt.send_();
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
  skt.out_ << "Please enter product id you want to add" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> id;
  skt.out_ << "Please enter num of product" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> count;
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
      skt.out_ << "sucessfully add product to cart" << endl;
    else
      skt.out_ << "fail to add product" << endl;
  } else
    skt.out_ << "product not found" << endl;
  skt.send_();
}
void Platform::remov_pdt_cart() {
  consumer *cur_act;
  int seq;
  cur_act = (consumer *)cur_account;
  cur_act->cart_.show_cart(skt);
  skt.out_ << "enter the seq num you want to remove" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> seq;

  if (cur_act->cart_.remove_pdt(seq))
    skt.out_ << "remove successfully" << endl;
  else
    skt.out_ << "fail to remove" << endl;
  skt.send_();
}

void Platform::change_pdt_cart() {
  consumer *cur_act;
  int seq, num;
  cur_act = (consumer *)cur_account;
  skt.out_ << "please enter seq number you want to change" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> seq;
  skt.out_ << "enter number you want to change" << endl;
  skt.send_();
  skt.recv_();
  skt.in_ >> num;

  if (cur_act->cart_.change_pdt_num(seq, num)) {
    skt.out_ << "change successfully" << endl;
  } else
    skt.out_ << "fail to change" << endl;
  skt.send_();
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

void cart::show_cart(sockt &skt) {
  list<cart_pdt>::iterator it;
  it = pdt_lst.begin();
  skt.out_ << setw(FORMAT_BAR_FRONT) << setfill('-') << "PRINTING CART"
           << setw(FORMAT_BAR_RARE) << "" << endl
           << setfill(' ');
  skt.out_ << setw(FORMAT_SEQ_WID) << "Sequence" << setw(FORMAT_NAME_WID)
           << "Description" << setw(FORMAT_PRICE_WID) << "Price"
           << setw(FORMAT_PRICE_WID) << " ID" << setw(FORMAT_PRICE_WID) << "NUM"
           << setw(FORMAT_PRICE_WID) << "selected" << endl;
  //   skt.send_();
  while (it != pdt_lst.end()) {
    skt.out_ << setw(FORMAT_SEQ_WID) << it->seq << ". " << setw(FORMAT_NAME_WID)
             << it->pdt_ptr->GetDscrip() << setw(FORMAT_PRICE_WID)
             << it->pdt_ptr->GetPrice() << setw(FORMAT_PRICE_WID)
             << it->pdt_ptr->GetId() << setw(FORMAT_PRICE_WID) << it->num
             << setw(FORMAT_PRICE_WID) << it->selected << endl;
    it++;
  }
  skt.send_();
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
int cart::genrate_order(consumer *cur_act, sockt &skt) {
  int input;

  while (true) {

    show_cart(skt);
    skt.out_ << "-1 for quitting, -2 for checking out,-3 for selecting all"
             << endl;
    skt.send_();
    skt.recv_();
    skt.in_ >> input;
    if (input == -1) {
      break;
    }
    if (input == -2) {

      return (check_out_order(cur_act, skt));
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

int cart::check_out_order(consumer *cur_act, sockt &skt) {
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
  rtval = cur_act->cart_.genrate_order(cur_act, skt);
  if (rtval == 1)
    skt.out_ << "Check out successfully" << endl;
  if (rtval == -1) {
    skt.out_ << "Not enough stock to check out" << endl;
    cur_act->cart_.show_cart(skt);
  }
  if (rtval == -2) {
    skt.out_ << "not enough balance" << endl;
    skt.out_ << cur_account->GetBalence();
  }
  skt.send_();
}

void sockt::init_skt() {

  int opt = 1;
  addrlen = sizeof(address);

  // Creating socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // Forcefully attaching socket to the port 8080
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  // Forcefully attaching socket to the port 8080
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }
  if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                           (socklen_t *)&addrlen)) < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }
  opt = 65535;
  if (setsockopt(new_socket, SOL_SOCKET, SO_RCVBUF, &opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
  opt = 65535;
  if (setsockopt(new_socket, SOL_SOCKET, SO_SNDBUF, &opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
}
void sockt::send_() {
  int retval;
  char buff[BUFFER_SIZE];
  memcpy(buff, out_.str().c_str(), out_.str().size() + 1);
  retval = send(new_socket, buff, out_.str().size() + 1, 0);
  if (retval == -1)
    perror("send");
  if (retval > 0) {
    cout << buff;
  }
  out_.str("");
  usleep(100);
}
void sockt::recv_() {
  char buffer[BUFFER_SIZE];
  memset(buffer, 0, BUFFER_SIZE);
  //   in_.str("");
  int len = -1;
  std::stringstream ss;
  len = recv(new_socket, buffer, BUFFER_SIZE, 0);
  if (len == -1)
    perror("recv");
  else if (len) {

    in_ = std::stringstream();
    ss << buffer;
    in_ << ss.rdbuf();
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