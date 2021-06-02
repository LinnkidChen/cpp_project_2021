/* notes
1. 全部函数，变量用类封装 不要使用全局变量
options
1. login -->change password check balance
            for seller -> add product
                        -> manage product=>add sub stock
                                            change description
                                            add new product
                                            delete product

2.sign in
3.show product
4. search product
*/
#include "definition.h"
#include "platform.h"
#include <iostream>
/*-------------------------------------------------------*/
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
/*-----------------------------------------------------*/

int main() {
  Platform platform;

  platform.init_load_file();
  cout << "\n" << platform.Get_option() << endl;

  //   string input;
  //   while (true) {
  //     cin >> input;
  //   }
  return 0;
}
