/*
 * File:   DLinkedList.h
 */

#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include <iostream>
#include <sstream>
#include <type_traits>


#include "list/IList.h"
using namespace std;

template <class T>
class DLinkedList : public IList<T> {
 public:
  class Node;         // Forward declaration
  class Iterator;     // Forward declaration
  class BWDIterator;  // Forward declaration

 protected:
  Node *head;
  Node *tail;
  int count;
  bool (*itemEqual)(T &lhs, T &rhs);
  void (*deleteUserData)(DLinkedList<T> *);

 public:
  DLinkedList(void (*deleteUserData)(DLinkedList<T> *) = 0,
              bool (*itemEqual)(T &, T &) = 0);
  DLinkedList(const DLinkedList<T> &list);
  DLinkedList<T> &operator=(const DLinkedList<T> &list);
  ~DLinkedList();

  // Inherit from IList: BEGIN
  void add(T e);
  void add(int index, T e);
  T removeAt(int index);
  bool removeItem(T item, void (*removeItemData)(T) = 0);
  bool empty();
  int size();
  void clear();
  T &get(int index);
  int indexOf(T item);
  bool contains(T item);
  string toString(string (*item2str)(T &) = 0);
  // Inherit from IList: END

  void println(string (*item2str)(T &) = 0) {
    cout << toString(item2str) << endl;
  }
  void setDeleteUserDataPtr(void (*deleteUserData)(DLinkedList<T> *) = 0) {
    this->deleteUserData = deleteUserData;
  }

  bool contains(T array[], int size) {
    int idx = 0;
    for (DLinkedList<T>::Iterator it = begin(); it != end(); it++) {
      if (!equals(*it, array[idx++], this->itemEqual)) return false;
    }
    return true;
  }

  Iterator begin() { return Iterator(this, true); }
  Iterator end() { return Iterator(this, false); }

  BWDIterator bbegin() { return BWDIterator(this, true); }
  BWDIterator bend() { return BWDIterator(this, false); }

 protected:
  void copyFrom(const DLinkedList<T> &list);
  void removeInternalData();
  Node *getPreviousNodeOf(int index);

  //! FUNTION STATIC
 public:
  static void free(DLinkedList<T> *list) {
    typename DLinkedList<T>::Iterator it = list->begin();
    while (it != list->end()) {
      delete *it;
      it++;
    }
  }

 protected:
  static bool equals(T &lhs, T &rhs, bool (*itemEqual)(T &, T &)) {
    if (itemEqual == 0)
      return lhs == rhs;
    else
      return itemEqual(lhs, rhs);
  }

 public:
  class Node {
   public:
    T data;
    Node *next;
    Node *prev;
    friend class DLinkedList<T>;

   public:
    Node(Node *next = 0, Node *prev = 0) {
      this->next = next;
      this->prev = prev;
    }
    Node(T data, Node *next = 0, Node *prev = 0) {
      this->data = data;
      this->next = next;
      this->prev = prev;
    }
  };

 public:
  class Iterator {
   private:
    DLinkedList<T> *pList;
    Node *pNode;

   public:
    Iterator(DLinkedList<T> *pList = 0, bool begin = true) {
      if (begin) {
        if (pList != 0)
          this->pNode = pList->head->next;
        else
          pNode = 0;
      } else {
        if (pList != 0)
          this->pNode = pList->tail;
        else
          pNode = 0;
      }
      this->pList = pList;
    }

    Iterator &operator=(const Iterator &iterator) {
      this->pNode = iterator.pNode;
      this->pList = iterator.pList;
      return *this;
    }
    void remove(void (*removeItemData)(T) = 0) {
      pNode->prev->next = pNode->next;
      pNode->next->prev = pNode->prev;
      Node *pNext = pNode->prev;  // MUST prev, so iterator++ will go to end
      if (removeItemData != 0) removeItemData(pNode->data);
      delete pNode;
      pNode = pNext;
      pList->count -= 1;
    }

    T &operator*() { return pNode->data; }
    bool operator!=(const Iterator &iterator) {
      return pNode != iterator.pNode;
    }
    // Prefix ++ overload
    Iterator &operator++() {
      pNode = pNode->next;
      return *this;
    }
    // Postfix ++ overload
    Iterator operator++(int) {
      Iterator iterator = *this;
      ++*this;
      return iterator;
    }
  };

  class BWDIterator {
    private:
    DLinkedList<T> *pList;
    Node *pNode;

   public:
    BWDIterator(DLinkedList<T> *pList = 0, bool begin = true) {
      if (begin) {
        if (pList != 0)
          this->pNode = pList->tail->prev;
        else
          pNode = 0;
      } else {
        if (pList != 0)
          this->pNode = pList->head;
        else
          pNode = 0;
      }
      this->pList = pList;
    }

    BWDIterator &operator=(const BWDIterator &iterator) {
      this->pNode = iterator.pNode;
      this->pList = iterator.pList;
      return *this;
    }

    void remove(void (*removeItemData)(T) = 0) {
      pNode->prev->next = pNode->next;
      pNode->next->prev = pNode->prev;
      Node *pNext = pNode->next;  // MUST next, so iterator-- will go to end
      if (removeItemData != 0) removeItemData(pNode->data);
      delete pNode;
      pNode = pNext;
      pList->count -= 1;
    }

    T &operator*() { return pNode->data; }

    bool operator!=(const BWDIterator &iterator) {
      return pNode != iterator.pNode;
    }

    // Prefix -- overload
    BWDIterator &operator++() {
      pNode = pNode->prev;
      return *this;
    }

    // Postfix -- overload
    BWDIterator operator++(int) {
      BWDIterator iterator = *this;
      ++*this;
      return iterator;
    }
  };
};

template <class T>
using List = DLinkedList<T>;

//! ////////////////////////////////////////////////////////////////////
//! //////////////////////     METHOD DEFNITION      ///////////////////
//! ////////////////////////////////////////////////////////////////////

template <class T>
DLinkedList<T>::DLinkedList(void (*deleteUserData)(DLinkedList<T> *),
                            bool (*itemEqual)(T &, T &)) {
  //tạo node head và tail
  this->head = new Node();
  this->tail = new Node();
  //gán next của head là tail và prev của tail là head
  this->head->next = this->tail;
  this->tail->prev = this->head;
  count = 0;//đếm số phần tử
  //gán hàm xóa dữ liệu và hàm equal
  this->deleteUserData = deleteUserData;//gán hàm xóa dữ liệu
  this->itemEqual = itemEqual;//gán hàm equal
}


template <class T>
DLinkedList<T>::DLinkedList(const DLinkedList<T> &list) {
  //tạo node head và tail
  this->head = new Node();
  this->tail = new Node();
  //gán next của head là tail và prev của tail là head
  this->head->next = this->tail;
  this->tail->prev = this->head;

  // this->deleteUserData = list.deleteUserData;
  // this->itemEqual = list.itemEqual;
  count = 0;

  //copyFrom(list);
  Node *current = list.head->next;//con trỏ current trỏ đến head->next
  while (current != list.tail) {//chạy từ head->next đến tail
    add(current->data);//thêm phần tử theo thứ tự đến tail
    current = current->next;//chuyển con trỏ current sang phần tử tiếp theo
  }
}

template <class T>
DLinkedList<T> &DLinkedList<T>::operator=(const DLinkedList<T> &list) {
  if (this != &list) {
    clear();
    //copyFrom(list);
    Node *current = list.head->next;
    while (current != list.tail) {
      add(current->data);
      current = current->next;
    }
  }
  //   this->deleteUserData = list.deleteUserData;
  //   this->itemEqual = list.itemEqual;

  //   Node *current = list.head->next;
  //   while (current != list.tail) {
  //     this->add(current->data);
  //     current = current->next;
  //   }
  // }
  return *this;
}

template <class T>
DLinkedList<T>::~DLinkedList() {
  //removeInternalData();
  
  clear();
  Node *current = head->next;
  while (current != tail) {
    Node *next = current->next;
    if (deleteUserData) {
      deleteUserData(this);
    } else {
      delete current;
    }
    current = next;
  }
  head->next = tail;
  tail->prev = head;
  count = 0;

  delete head;
  delete tail;
}

template <class T>
void DLinkedList<T>::add(T e) {
  Node *newNode = new Node(e, tail, tail->prev);
  tail->prev->next = newNode;
  tail->prev = newNode;
  count++;
}

template <class T>
void DLinkedList<T>::add(int index, T e) {
  if (index < 0 || index > count) {
    throw std::out_of_range("Index is out of range!");
  }

  
  // if (count == 0) {add(e);}
  // while to index node
  // new node();
  // index node -> prev -> next = new Node();
  // index node -> prev = new_node;
  // new_node -> next = index node;
  // new_node -> prev = index node-> prev;
  // Node *prevNode = getPreviousNodeOf(index);
  // Node *nextNode = prevNode->next;

  Node*prev=this->head;
  for(int i=-1;i < index-1;i++){
      prev=prev->next;
  }
  Node*fakeNode=new Node(e,prev->next,prev);
  fakeNode->prev->next=fakeNode;
  fakeNode->next->prev=fakeNode;
  count++;

  // Node* newNode = new Node(e);
  //   if (index == 0) {
  //       // Insert at the head
  //       newNode->next = head->next;
  //       newNode->prev = head;
  //       head->next->prev = newNode;
  //       head->next = newNode;
  //   } else if (index == count) {
  //       // Insert at the tail
  //       newNode->prev = tail->prev;
  //       newNode->next = tail;
  //       tail->prev->next = newNode;
  //       tail->prev = newNode;
  //   } else {
  //       // Insert in the middle
  //       Node* current = head;
  //       for (int i = 0; i < index; ++i) {
  //           current = current->next;
  //       }
  //       newNode->next = current->next;
  //       newNode->prev = current;
  //       current->next->prev = newNode;
  //       current->next = newNode;
  //   }
  //   count++;

  // Node *newNode = new Node(e);  

  //   if (index == count) {
  //       // If inserting at the end, directly update tail pointers
  //       newNode->prev = tail->prev;
  //       newNode->next = tail;
  //       tail->prev->next = newNode;
  //       tail->prev = newNode;
  //   } else if (index == 0) {
  //       // If inserting at the beginning, update head pointers
  //       newNode->next = head->next;
  //       newNode->prev = head;
  //       head->next->prev = newNode;
  //       head->next = newNode;
  //   } else {
  //       // For insertion in the middle, decide whether to start from the head or tail
  //       Node *current;
  //       if (index < count / 2) {
  //           // Traverse from the head if index is in the first half
  //           current = head->next;
  //           for (int i = 0; i < index; ++i) {
  //               current = current->next;
  //           }
  //       } else {
  //           // Traverse from the tail if index is in the second half
  //           current = tail;
  //           for (int i = count; i > index; --i) {
  //               current = current->prev;
  //           }
  //       }

  //       // Insert new node before `current`
  //       newNode->next = current;
  //       newNode->prev = current->prev;
  //       current->prev->next = newNode;
  //       current->prev = newNode;
  //   }

  //   count++;  

}

template <class T>
T DLinkedList<T>::removeAt(int index) {
  if (index < 0 || index >= count) {
    throw std::out_of_range("Index is out of range!");
  }
    Node*temporaryNode;
    if(index<count/2){
    temporaryNode=head;
    for(int i=-1;i<index;i++){
        temporaryNode=temporaryNode->next;
    }
    }
    else{
        temporaryNode=tail;
        for(int i=count;i>index;i--){
            temporaryNode=temporaryNode->prev;
        }
    }
    Node*current=temporaryNode;
    current->prev->next=current->next;
    current->next->prev=current->prev;
    current->next=current->prev=NULL;
    T data=current->data;
    delete current;
    count--;
    return data;
  // Node *prevNode = getPreviousNodeOf(index);
  // Node *nodeToRemove = prevNode->next;
  // Node *nextNode = nodeToRemove->next;

  // prevNode->next = nextNode;
  // nextNode->prev = prevNode;

  // T data = nodeToRemove->data;
  // delete nodeToRemove;
  // count--;

  // return data;
}

template <class T>
bool DLinkedList<T>::empty() {
  return count == 0 ? true : false;//nếu count=0 thì trả về true
}

template <class T>
int DLinkedList<T>::size() {
  return count;
}

template <class T>
void DLinkedList<T>::clear() {
  Node *current = head->next;
  Node *nodeNext;
  while (current != tail) {
    nodeNext = current->next;
    delete current;
    current = nodeNext;
  }
  head->next = tail;
  tail->prev = head;
  count = 0;
}

template <class T>
T &DLinkedList<T>::get(int index) {
  if (index < 0 || index >= count) {
    throw std::out_of_range("Index is out of range!");
  }

  Node *current = head->next;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }

  return current->data;
}

template <class T>
int DLinkedList<T>::indexOf(T item) {
  Node *current = head->next;
  int index = 0;
  while (current != tail) {
    if (equals(current->data, item, this->itemEqual)) {
      return index;
    }
    current = current->next;
    index++;
  }
  return -1;
}

template <class T>
bool DLinkedList<T>::removeItem(T item, void (*removeItemData)(T)) {
  Node *current = head->next;
  while (current != tail) {
    if (equals(current->data, item, this->itemEqual)) {
      Node *prevNode = current->prev;
      Node *nextNode = current->next;

      prevNode->next = nextNode;
      nextNode->prev = prevNode;

      if (removeItemData) {
        removeItemData(current->data);
      }

      delete current;
      count--;
      return true;
    }
    current = current->next;
  }
  return false;
}

template <class T>
bool DLinkedList<T>::contains(T item) {
  // Node *current = head->next;
  // while (current != tail) {
  //   if (equals(current->data, item, this->itemEqual)) {
  //     return true;
  //   }
  //   current = current->next;
  // }
  // return false;
    return indexOf(item) == -1 ? false : true;//nếu indexof khác -1 thì trả về true

}

template <class T>
string DLinkedList<T>::toString(string (*item2str)(T &)) {
  if (empty()==true) {
    return "[]";
  }
  stringstream tostringofitem; 
  stringstream tostring;
  if (item2str != nullptr) {
    tostringofitem << "[";
    Node *current = head->next;
    while (current != tail) {
      tostringofitem << item2str(current->data);
      if (current->next != tail) {
        tostringofitem << ", ";
      }
      current = current->next;
    }
    tostringofitem << "]";
  } 
  else {
    Node *current = head->next;
    tostringofitem << "[";
    while (current != tail) {
      tostring << current->data;
      if (current->next != tail) {
        tostring << ", ";
      }
      current = current->next;
    }
    tostringofitem << tostring.str();
    tostringofitem << "]";
  }
  return tostringofitem.str();
// stringstream oss;
// oss << "[";
// Node* pNode = head->next; // Bắt đầu từ nút đầu tiên sau head
// while (pNode != tail) {
//   if (item2str != nullptr) {
//     oss << item2str(pNode->data); // Sử dụng hàm itemstr nếu có
//   } else {
//     oss << pNode->data; // Sử dụng cách chuyển đổi mặc định
//   }
//   pNode = pNode->next; 
//   if (pNode != tail) {
//     oss<<", "; // Thêm dấu phẩy giữa các phần tử
//   }
// }
// oss << "]";
// return oss.str(); // Trả về chuỗi kết quả
}


//! ////////////////////////////////////////////////////////////////////
//! ////////////////////// (private) METHOD DEFNITION //////////////////
//! ////////////////////////////////////////////////////////////////////
template <class T>
void DLinkedList<T>::copyFrom(const DLinkedList<T> &list) {
  /**
   * Copies the contents of another doubly linked list into this list.
   * Initializes the current list to an empty state and then duplicates all data
   * and pointers from the source list. Iterates through the source list and
   * adds each element, preserving the order of the nodes.
   */
  // Clear the current list
  //clear();

  // Copy each element from the source list
  Node *current = list.head->next;
  while (current != list.tail) {
    add(current->data);
    current = current->next;
  }
}

template <class T>
void DLinkedList<T>::removeInternalData() {
  /**
   * Clears the internal data of the list by deleting all nodes and user-defined
   * data. If a custom deletion function is provided, it is used to free the
   * user's data stored in the nodes. Traverses and deletes each node between
   * the head and tail to release memory.
   */
  clear();
  Node *current = head->next;
  while (current != tail) {
    Node *next = current->next;
    if (deleteUserData) {
      deleteUserData(this);
    } else {
      delete current;
    }
    current = next;
  }
  head->next = tail;
  tail->prev = head;
  count = 0;
}

template <class T>
typename DLinkedList<T>::Node *DLinkedList<T>::getPreviousNodeOf(int index) {
  if (index < 0 || index >= count) {
    throw std::out_of_range("Index is out of range!");
  }

  Node *current;
  current = head;
    for (int i = 0; i < index; ++i) {
      current = current->next;
    }
   

  return current;
}

#endif /* DLINKEDLIST_H */
