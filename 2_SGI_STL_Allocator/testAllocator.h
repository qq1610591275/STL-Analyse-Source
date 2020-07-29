/**
  *  测试 Allocator，理解用法
 */
#ifndef _TESTALLOCATOR
#define _TESTALLOCATOR

#include <new>          // for placement new
#include <cstddef>      // ptrdiff_t, size_t
#include <cstdlib>      // for exit()
#include <climits>      // for UNIX_MAX
#include <iostream>     // for cerr

/**
 * 1、在全局命空间中有一个自带的、隐藏的operator new 专门来分配内存。
 * 2、默认情况下，编译器会将new这个关键字翻译成operator new 和相应的构造函数，
 *    但在有的情况下，用户自己会在类中重载operator new,这种情况下，编译器会选择
 *    重载的。（寻找规则：编译器从命名空间由内向外寻找想要的函数）
 * 3、若载重载了之后还想继续使用默认的operator new,就该写成:: operator new, 调用最外层的
 *    ，但是最外层（默认的）也是可以被重载，通过这种返方式可以改变new的部分行为。
 */  
namespace WG
{

  /**
   * 分配空间，存储n个T对象，返回空间地址
   */
  template <class T>
  inline T* _allocate(ptrdiff_t size, T*) {
      // 设置new_p指向的函数为new操作或new[]操作失败时调用的处理函数
      // 该函数指针所指的函数应为空参数列表且返回值类型为void
      // 实际：set_new_handler(callback_function) 是指申请内存失败时会回调callback_function函数，该函数必须是
      // 无参且返回值为void，此处是直接返回给一个0，而非函数，这样也行。
      std::set_new_handler(0);
      T* tmp = (T*) (::operator new((size_t) (size * sizeof(T) )));

      if(tmp == 0) {
        cerr<<"out of memory" <<endl;
        std::exit(1);
      }
      return tmp;
  }

  // 释放先前配置的空间，buffer指向的
  template <class T>
  inline void _deallocate(T* buffer){
      ::operator delete(buffer);
  }
  
  /**
   *  在已有的空间中再分配一个空间存储T1对象，T1对象内容是通过T2对象内容转化过来的
   *  具体：在p指向的内存空间中重新分配一个空间用于存储T1对象，并且T1对象是通过T2
   *        对象赋值过来的（可能翻译存在问题）
   *  等同于：new (const void*) p) T(x)
   */ 
  template<class T1, class T2>
  inline void _construct(T1* p, const T2& value) {
      new (p) T1(value); // palceent new, invoke ctor of T1
  }

  // 调用析构函数
  template <class T>
  inline void _destroy(T* prt){
      prt->~T();
  }
   
   /**
    * 自己实现 allocator类
    */ 
   template <class T>
    class allocator {
    public:
        typedef T          value_type;
        typedef T *        pointer;
        typedef const T *  const_pointer;
        typedef T &        reference;
        typedef const T &  const_reference;
        typedef size_t     size_type;
        typedef ptrdiff_t  difference_type;

        // rebind allocator of type U
        template <class U>
        struct rebind {
            typedef allocator<U> other;
        };

        // hint used for locality. ref. [Austern], p189
        pointer allocate(size_type n, const void* hint=0) {
            return _allocate((difference_type)n, (pointer)0);
        }

        void deallocate(pointer p, size_type n) {
            _deallocate(p);
        }

        void construct(pointer p, const T& value) {
            _construct(p, value);
        }

        void destroy(pointer p) {
            _destroy(p);
        }

        // 传回某个对象的地址。a.address(x)等同于 &x
        pointer address(reference x) {
            return (pointer)&x;
        }

        // 传回某个 const对象的地址。a.address(x)等同于 &x
        const_pointer const_address(const_reference x) {
            return (const_pointer)&x;
        }

        // 传回可成功配置的最大量
        size_type max_size() const {
            return size_type(UINT_MAX / sizeof(T));
        }
    };

} // namespace 


#endif