/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Heap.h
 * Author: LTSACH
 *
 * Created on 22 August 2020, 18:18
 */

#ifndef HEAP_H
#define HEAP_H
#include <memory.h>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "heap/IHeap.h"
using namespace std;
/*
 * function pointer: int (*comparator)(T& lhs, T& rhs)
 *      compares objects of type T given in lhs and rhs.
 *      return: sign of (lhs - rhs)
 *              -1: lhs < rhs
 *              0 : lhs == rhs
 *              +1: ls > rhs
 *
 * function pointer: void (*deleteUserData)(Heap<T>* pHeap)
 *      remove user's data in case that T is a pointer type
 *      Users should pass &Heap<T>::free for "deleteUserData"
 *
 */
template <class T>
class Heap : public IHeap<T> {
 public:
  class Iterator;  // forward declaration

 protected:
  T* elements;   // a dynamic array to contain user's data
  int capacity;  // size of the dynamic array
  int count;     // current count of elements stored in this heap
  int (*comparator)(T& lhs, T& rhs);       // see above
  void (*deleteUserData)(Heap<T>* pHeap);  // see above

 public:
  Heap(int (*comparator)(T&, T&) = 0, void (*deleteUserData)(Heap<T>*) = 0);

  Heap(const Heap<T>& heap);                // copy constructor
  Heap<T>& operator=(const Heap<T>& heap);  // assignment operator

  ~Heap();

  // Inherit from IHeap: BEGIN
  void push(T item);
  T pop();
  const T peek();
  void remove(T item, void (*removeItemData)(T) = 0);
  bool contains(T item);
  int size();
  void heapify(T array[], int size);
  void clear();
  bool empty();
  string toString(string (*item2str)(T&) = 0);
  // Inherit from IHeap: END

  void println(string (*item2str)(T&) = 0) {
    cout << toString(item2str) << endl;
  }

  Iterator begin() { return Iterator(this, true); }
  Iterator end() { return Iterator(this, false); }

 public:
  /* if T is pointer type:
   *     pass the address of method "free" to Heap<T>'s constructor:
   *     to:  remove the user's data (if needed)
   * Example:
   *  Heap<Point*> heap(&Heap<Point*>::free);
   *  => Destructor will call free via function pointer "deleteUserData"
   */
  static void free(Heap<T>* pHeap) {
    for (int idx = 0; idx < pHeap->count; idx++) delete pHeap->elements[idx];
  }

 private:
  bool aLTb(T& a, T& b) { return compare(a, b) < 0; }
  int compare(T& a, T& b) {
    if (comparator != 0)
      return comparator(a, b);
    else {
      if (a < b)
        return -1;
      else if (a > b)
        return 1;
      else
        return 0;
    }
  }

  void ensureCapacity(int minCapacity);
  void swap(int a, int b);
  void reheapUp(int position);
  void reheapDown(int position);
  int getItem(T item);

  void removeInternalData();
  void copyFrom(const Heap<T>& heap);

  //////////////////////////////////////////////////////////////////////
  ////////////////////////  INNER CLASSES DEFNITION ////////////////////
  //////////////////////////////////////////////////////////////////////

 public:
  // Iterator: BEGIN
  class Iterator {
   private:
    Heap<T>* heap;
    int cursor;

   public:
    Iterator(Heap<T>* heap = 0, bool begin = 0) {
      this->heap = heap;
      if (begin && (heap != 0)) cursor = 0;
      if (!begin && (heap != 0)) cursor = heap->size();
    }
    Iterator& operator=(const Iterator& iterator) {
      this->heap = iterator.heap;
      this->cursor = iterator.cursor;
      return *this;
    }

    T& operator*() { return this->heap->elements[cursor]; }
    bool operator!=(const Iterator& iterator) {
      return this->cursor != iterator.cursor;
    }
    // Prefix ++ overload
    Iterator& operator++() {
      cursor++;
      return *this;
    }
    // Postfix ++ overload
    Iterator operator++(int) {
      Iterator iterator = *this;
      ++*this;
      return iterator;
    }
    void remove(void (*removeItemData)(T) = 0) {
      this->heap->remove(this->heap->elements[cursor], removeItemData);
    }
  };
  // Iterator: END
};

//////////////////////////////////////////////////////////////////////
////////////////////////     METHOD DEFNITION      ///////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
Heap<T>::Heap(int (*comparator)(T&, T&), void (*deleteUserData)(Heap<T>*)) {
  //constructor
  this->capacity = 10;
  this->count = 0;
  this->elements = new T[capacity];
  this->comparator = comparator;
  this->deleteUserData = deleteUserData;
}

template <class T>
Heap<T>::Heap(const Heap<T>& heap) {
    //copy constructor
    this->capacity = heap.capacity;
    this->count = heap.count;
    this->elements = new T[capacity];
    this->comparator = heap.comparator;
    this->deleteUserData = heap.deleteUserData;
    //copy elements
    for (int i = 0; i < count; i++) {
        if constexpr (std::is_pointer<T>::value) {
            elements[i] = new std::remove_pointer_t<T>(*heap.elements[i]); 
        } else {
            elements[i] = heap.elements[i]; 
        }
    }
    
}

template <class T>
Heap<T>& Heap<T>::operator=(const Heap<T>& heap) {
    if (this != &heap) { //kiểm trong gán chính nó
        removeInternalData(); //xóa dữ liệu cũ xong mới gán mới
        capacity = heap.capacity;
        count = heap.count;
        elements = new T[capacity];
        comparator = heap.comparator;
        deleteUserData = heap.deleteUserData;
        //copy elements
        for (int i = 0; i < count; i++) {
             if constexpr (std::is_pointer<T>::value) {
                elements[i] = new std::remove_pointer_t<T>(*heap.elements[i]); 
            } 
             else {
                elements[i] = heap.elements[i]; 
            }
        }
        
    }
    return *this;
}

template <class T>
Heap<T>::~Heap() {
  removeInternalData();
}

template <class T>
void Heap<T>::push(T item) {  
  ensureCapacity(count + 1);//mở rộng
  elements[count] = item; // gán từng phần tử vào mảng
  reheapUp(count);
  count++;
  // ensureCapacity(size+1);
  //   data[size++]=key;
  //   reHeapUp(size-1);
  
}

template <class T>
T Heap<T>::pop() {
  if(count == 0) throw std::underflow_error("Calling to peek with the empty heap.");
  T item = elements[0];//lấy phần tử đầu tiên
  elements[0] = elements[count - 1];//gán phần tử cuối vào đầu
  count--;
  reheapDown(0);
  return item;
}


template <class T>
const T Heap<T>::peek() {
  if(count == 0) throw std::underflow_error("Calling to peek with the empty heap.");
  return elements[0];
}

template <class T>
void Heap<T>::remove(T item, void (*removeItemData)(T)) {
  int position = getItem(item);//lấy vị trí của phần tử
  if(position == -1) return;//nếu không tìm thấy thì thoát
  if(removeItemData != nullptr) removeItemData(elements[position]);//xóa phần tử
  elements[position] = elements[count - 1];//gán phần tử cuối vào vị trí cần xóa
  count--;
  reheapDown(position);
}

template <class T>
bool Heap<T>::contains(T item) {
  return getItem(item) != -1;//nếu tìm thấy trả về true
}

template <class T>
int Heap<T>::size() {
  return count;
}

template <class T>
void Heap<T>::heapify(T array[], int size) {
  for(int idx = 0; idx < size; idx++) {//duyệt qua từng phần tử
    push(array[idx]);//thêm phần tử vào heap
  }
}

template <class T>
void Heap<T>::clear() {
  removeInternalData();//xóa dữ liệu
  //gán lại tạo mới
  count = 0;
  capacity = 10;
  elements = new T[capacity];
}

template <class T>
bool Heap<T>::empty() {
  return count == 0;
}

template <class T>
string Heap<T>::toString(string (*item2str)(T&)) {
  stringstream os;
  if (item2str != 0) {
    os << "[";
    for (int idx = 0; idx < count - 1; idx++)
      os << item2str(elements[idx]) << ",";
    if (count > 0) os << item2str(elements[count - 1]);
    os << "]";
  } else {
    os << "[";
    for (int idx = 0; idx < count - 1; idx++) os << elements[idx] << ",";
    if (count > 0) os << elements[count - 1];
    os << "]";
  }
  return os.str();
}

//////////////////////////////////////////////////////////////////////
//////////////////////// (private) METHOD DEFNITION //////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
void Heap<T>::ensureCapacity(int minCapacity) {
  if (minCapacity >= capacity) {
    // re-allocate
    int old_capacity = capacity;
    capacity = old_capacity + (old_capacity >> 2);
    try {
      T* new_data = new T[capacity];
      // OLD: memcpy(new_data, elements, capacity*sizeof(T));
      memcpy(new_data, elements, old_capacity * sizeof(T));
      delete[] elements;
      elements = new_data;
    } catch (std::bad_alloc e) {
      e.what();
    }
  }
}

template <class T>
void Heap<T>::swap(int a, int b) {
  T temp = this->elements[a];
  this->elements[a] = this->elements[b];
  this->elements[b] = temp;
}


template <class T>
void Heap<T>::reheapUp(int position) {
  int parent = (position - 1) / 2;//trong array parent = (i-1)/2
  while (position > 0 && compare(elements[position], elements[parent])<0) {//nếu tồn tại phần tử và phần tử hiện tại nhỏ hơn phần tử cha
        swap(position, parent); // Hoán đổi phần tử hiện tại với phần tử cha
        position = parent;      // Cập nhật vị trí mới của phần tử
        parent = (position - 1) / 2; // Tính lại vị trí cha
    }
}

template <class T>
void Heap<T>::reheapDown(int position) {
    int leftChild = 2 * position + 1;//con trái
    int rightChild = 2 * position + 2;//con phải
    int smallest = position;

    if (leftChild < count && compare(elements[leftChild], elements[smallest])<0) {
      //con trái nhỏ hơn cha và nhỏ nhất
        smallest = leftChild;
    }
    if (rightChild < count && compare(elements[rightChild], elements[smallest])<0) {
      //con phải nhỏ hơn cha và nhỏ nhất
        smallest = rightChild;
    }

    if (smallest != position) {//nếu nhỏ nhất khác vị trí hiện tại
        swap(position, smallest);//đổi
        reheapDown(smallest);//reheapdown
    }
}

template <class T>
int Heap<T>::getItem(T item) {
  // Tìm và trả về chỉ số của phần tử item trong heap.
  for (int idx = 0; idx < count; idx++) {
    if (compare(elements[idx], item) == 0) return idx;
  }
  return -1;
}

template <class T>
void Heap<T>::removeInternalData() {
  if (this->deleteUserData != 0)
    deleteUserData(this);  // clear users's data if they want
  delete[] elements;
}
// file võ tiến
// template <class T>
// void Heap<T>::copyFrom(const Heap<T>& heap) {
//   capacity = heap.capacity;
//   count = heap.count;
//   elements = new T[capacity];
//   this->comparator = heap.comparator;
//   //this->deleteUserData = heap.deleteUserData;//trong file trường
//   this->deleteUserData = NULL;//file võ tiến
//   // Copy items from heap:
//   for (int idx = 0; idx < count; idx++) {//heap.size() thay = count
//     this->elements[idx] = heap.elements[idx];
//   }
// }

//file trường
template <class T>
void Heap<T>::copyFrom(const Heap<T>& heap) {
  capacity = heap.capacity;
  count = heap.count;
  elements = new T[capacity];
  this->comparator = heap.comparator;
  this->deleteUserData = heap.deleteUserData;//trong file trường
  // Copy items from heap:
  for (int idx = 0; idx < heap.size(); idx++) {//heap.size() thay = count
    this->elements[idx] = heap.elements[idx];
  }
}

#endif /* HEAP_H */
