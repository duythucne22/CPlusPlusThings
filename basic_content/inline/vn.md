Đây là bản dịch Tiếng Việt của đoạn văn bản Markdown:

# Về những điều liên quan đến inline


## 1. Inline trong lớp

Khai báo phương thức trong header:

```c++
class A
{
public:
    void f1(int x);

    /**
     * @brief Các hàm được định nghĩa trong lớp là các hàm inline隐式,
     * để khai báo trở thành hàm inline, cần phải thêm từ khóa inline vào khi định nghĩa (triển khai).
     *
     * @param x
     * @param y
     */
    void Foo(int x, int y) ///< Định nghĩa => Hàm inline隐式!
    {
    };
    void f2(int x); ///< Khai báo, để trở thành hàm inline, cần phải thêm từ khóa inline vào khi định nghĩa.
};
```

Định nghĩa hàm inline trong file triển khai:

```c++
#include <iostream>
#include "inline.h"

using namespace std;

/**
 * @brief Từ khóa inline phải được sử dụng khi định nghĩa hàm, không phải khi khai báo,
 * inline là từ khóa "dùng để triển khai, chứ không phải dùng để khai báo".
 *
 * @param x
 * @param y
 *
 * @return 
 */
int Foo(int x, int y);  // Khai báo hàm
inline int Foo(int x, int y) // Định nghĩa hàm
{
    return x+y;
}

// Thêm từ khóa inline khi định nghĩa, cách viết này được khuyến khích!
inline void A::f1(int x){

}

int main()
{
    cout<<Foo(1,2)<<endl;
}
/**
 * Các bước xử lý của trình biên dịch đối với hàm inline:
 * Sao chép nội dung hàm inline vào chỗ gọi hàm;
 * Cấp phát bộ nhớ cho các biến cục bộ trong hàm inline;
 * Ánh xạ tham số đầu vào và giá trị trả về của hàm inline vào biến cục bộ của chỗ gọi hàm;
 * Nếu hàm inline có nhiều điểm trả về, chuyển thành nhánh (dùng GOTO) ở cuối khối mã của hàm.
 */
```

Inline có thể tăng hiệu suất hàm, nhưng không phải tất cả các hàm đều nên định nghĩa thành hàm inline! Inline là đánh đổi bằng cách tăng kích thước mã (sao chép), chỉ tiết kiệm được chi phí gọi hàm, từ đó tăng hiệu suất hàm.

- Nếu thời gian thực thi mã bên trong hàm lớn hơn chi phí gọi hàm, thì lợi ích tăng hiệu suất sẽ ít hơn!

- Mặt khác, mỗi lần gọi hàm inline đều phải sao chép mã, sẽ làm tăng tổng kích thước mã chương trình, tiêu tốn thêm bộ nhớ.

Các trường hợp không nên dùng inline:

(1) Nếu mã bên trong hàm khá dài, inline sẽ gây ra mức tiêu tốn bộ nhớ cao.

(2) Nếu hàm có chứa vòng lặp, thời gian thực thi mã bên trong hàm sẽ lớn hơn chi phí gọi hàm.

## 2. Hàm ảo (virtual) có thể là hàm inline không?

- Hàm ảo có thể là hàm inline, từ khóa inline có thể được dùng để định nghĩa hàm ảo, nhưng khi hàm ảo thể hiện tính đa hình, thì không thể inline.
- Inline là đề nghị với trình biên dịch inline ở thời điểm biên dịch, còn tính đa hình của hàm ảo xảy ra ở thời gian chạy, trình biên dịch không thể biết được hàm nào sẽ được gọi ở thời gian chạy, vì vậy hàm ảo thể hiện tính đa hình (chạy) thì không thể inline.
- `inline virtual` chỉ có thể inline khi trình biên dịch biết được đối tượng được gọi là đối tượng của lớp nào (ví dụ `Base::who()`), điều này chỉ xảy ra khi trình biên dịch có được đối tượng cụ thể, chứ không phải con trỏ hoặc tham chiếu đến đối tượng.

```c++
#include <iostream>  
using namespace std;
class Base
{
public:
    inline virtual void who()
    {
        cout << "I am Base\n";
    }
    virtual ~Base() {}
};
class Derived : public Base
{
public:
    inline void who()  // Không viết inline cũng ngầm định là inline
    {
        cout << "I am Derived\n";
    }
};

int main()
{
    // Ở đây, hàm ảo who() được gọi thông qua đối tượng cụ thể (b) của lớp, nên có thể inline, nhưng việc inline cuối cùng vẫn phụ thuộc vào trình biên dịch.
    Base b;
    b.who();

    // Ở đây, hàm ảo được gọi thông qua con trỏ, thể hiện tính đa hình, nên không thể inline.
    Base *ptr = new Derived();
    ptr->who();

    // Vì Base có hàm huỷ ảo (virtual ~Base() {}), nên khi xoá, sẽ gọi hàm huỷ của lớp Derived trước, sau đó mới gọi hàm huỷ của lớp Base, tránh rò rỉ bộ nhớ.
    delete ptr;
    ptr = nullptr;

    return 0;
} 
```