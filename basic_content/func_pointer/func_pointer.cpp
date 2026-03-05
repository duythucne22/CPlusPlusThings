/**
 * @file func_pointer.cpp
 * @brief Usage of function pointers!
 * @author Guangcheng
 * @version v1
 * @date 2019-07-20
 */

#include <iostream>
using namespace std;

/**
 * @brief
 * Declares a variable `pFun`: this variable is a pointer to a function that
 * returns `void` and takes one `int` parameter!
 */
void (*pFun)(int);

/**
 * @brief This defines a new type alias, not a variable!
 *        So it is different from the above `pFun`.
 */
typedef void (*func)(void);

void myfunc(void) { cout << "asda" << endl; }

void glFun(int a) { cout << a << endl; }

int main() {
    func pfun = myfunc;   /* assignment */
    pfun();               /* call via function pointer */
    pFun = glFun;
    (*pFun)(2);           /* call the function pointed to by `pFun` */
}
