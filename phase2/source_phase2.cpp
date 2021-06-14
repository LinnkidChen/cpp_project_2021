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

 支持对同一品类下所有产品打折的活动
 已经优化，让商家知道自己每个品类第一个位置在哪。可以优化for循环中的搜索算法-->行不通
用于储存containner某一位置的的iterator是不可靠的 debug到delete product

ver2
退出程序的时候会交还所有账户冻结的商品
新增购物车功能
    购物车数量==0 -> 增加商品到购物车 输入id 数量 帮助冻结商品
    购物车数量>0 -> 增加商品
                    减少某个商品固定数量->若输入数量大于等于购物车内数量，在购物车内删除整个商品
                ->删除整个商品
                ->生成订单 选择商品生成订单 ->在购物车结构体内定义selected
                                        ->支持全选结账
                                        结账后刷新整个购物车的seq

当前进度/：用list替换vector 仍在进行中

*/
#include "definition.h"
#include "platform.h"

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
  int choice;

  platform.init_load_file();
  platform.test();
  while (true) {
    choice = platform.Get_option();
    if (choice == -1) {
      cout << "Exiting program." << endl;
      break;
    } else if (choice <= CHOISE_COUNT) {
      platform.process_choice(choice);
    }
  }
  platform.write_back_file();

  return 0;
}

void Platform::test() {
  account_type = CONSUMER;
  cur_account = &all_consumer.front();
  //   add_pdt_to_cart();
  //   cur_account = &all_consumer[2];
  //   ((consumer *)(cur_account))->cart_.add_pdt(1, (product *)(&all_book[2]));
}