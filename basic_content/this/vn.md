# Chuyện về con trỏ `this`

## 1. Con trỏ `this`


Tôi tin rằng nhiều bạn đang học Python, trong Python có `self`, tương tự trong C++ chính là con trỏ `this`. Cùng phân tích sâu cách dùng `this` trong lớp nhé.

Trước hết, hãy nói về tác dụng của `this`:

(1) Con trỏ `this` của một đối tượng không phải là một phần nội tại của chính đối tượng, nên không ảnh hưởng đến kết quả của `sizeof(đối_tượng)`.

(2) Phạm vi hoạt động của `this` nằm bên trong lớp. Khi truy cập các thành viên không phải là static trong một hàm thành viên không phải static của lớp, trình biên dịch sẽ tự động truyền địa chỉ của đối tượng đó như một tham số ngầm vào hàm. Tức là, dù bạn không viết `this` ra, trình biên dịch vẫn tự thêm nó vào trong quá trình biên dịch, làm tham số ngầm của hàm thành viên không phải static, toàn bộ việc truy cập các thành viên đều thông qua `this`.


Tiếp theo là cách dùng `this`:

(1) Khi hàm thành viên không phải static muốn trả lại chính đối tượng đó, hãy dùng `return *this` trực tiếp.

(2) Khi tên tham số trùng với tên biến thành viên, hãy viết `this->n = n` (không thể viết `n = n`).

Ngoài ra, trên mạng bạn có thể thấy người ta nói `this` bị biên dịch thành `A *const` hoặc `A const *`, vậy cái nào đúng? Ta phân tích qua ví dụ debug bên dưới.

Ví dụ như sau:

```cpp
#include <iostream>
#include <cstring>

using namespace std;

class Person {
public:
    typedef enum {
        BOY = 0,
        GIRL
    } SexType;

    Person(char *n, int a, SexType s) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        age = a;
        sex = s;
    }

    int get_age() const {
        return this->age;
    }

    Person& add_age(int a) {
        age += a;
        return *this;
    }

    ~Person() {
        delete [] name;
    }

private:
    char *name;
    int age;
    SexType sex;
};

int main() {
    Person p("zhangsan", 20, Person::BOY);
    cout << p.get_age() << endl;
    cout << p.add_age(10).get_age() << endl;
    return 0;
}
```

Một chương trình đơn giản như thế này chắc bạn không khó hiểu: định nghĩa một lớp, khởi tạo qua hàm tạo, rồi lấy tuổi, tăng tuổi, lại lấy tuổi.

Để kiểm tra `this` có dạng gì, ta đặt breakpoint tại `add_age` và chạy chương trình:

![thiscontrust](./img/thiscontrust.png)

![genthis](./img/genthis.png)

Ta thấy trình biên dịch tự thêm `A* const` cho `this`, chứ không phải `A const*`.

Tiếp theo, đoạn trên còn có một hàm `const`. Nếu đặt breakpoint tại `get_age`, ta được:

![constthis](./img/constthis.png)

Ở đây, `this` bị biên dịch thành `const A* const`. Điều này cũng hợp lý, vì hàm `get_age` là `const`, chỉ được đọc các thành viên `const` mà không được sửa, nên `this` phải trỏ tới vùng nhớ không được sửa, tức `const A*`. Mà bản thân `this` đã là con trỏ `const`, nên kiểu đầy đủ là `const A* const`.


**Tóm lại:** Con trỏ `this` được tạo ngầm trước khi hàm thành viên bắt đầu chạy, và được dọn dẹp sau khi hàm kết thúc. Nói cách khác:

- `get_age` được biên dịch thành `get_age(const A* const this)`.
- `add_age` được biên dịch thành `add_age(A* const this, int a)`.

Trong C++, khác biệt duy nhất giữa class và struct là thành viên của class mặc định là `private`, còn của struct mặc định là `public`. `this` là con trỏ đến class; nếu thay bằng struct thì `this` là con trỏ đến struct đó.