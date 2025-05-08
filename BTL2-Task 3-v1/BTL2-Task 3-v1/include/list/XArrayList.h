/*
 * File:   XArrayList.h
 */

#ifndef XARRAYLIST_H
#define XARRAYLIST_H
#include "list/IList.h"
#include <memory.h>
#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class XArrayList : public IList<T>
{
public:
    class Iterator; // forward declaration

protected:
    T *data;                                 // dynamic array to store the list's items
    int capacity;                            // size of the dynamic array
    int count;                               // number of items stored in the array
    bool (*itemEqual)(T &lhs, T &rhs);       // function pointer: test if two items (type: T&) are equal or not
    void (*deleteUserData)(XArrayList<T> *); // function pointer: be called to remove items (if they are pointer type)

public:
    XArrayList(
        void (*deleteUserData)(XArrayList<T> *) = 0,
        bool (*itemEqual)(T &, T &) = 0,
        int capacity = 10);
    XArrayList(const XArrayList<T> &list);
    XArrayList<T> &operator=(const XArrayList<T> &list);
    ~XArrayList();

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
    // Inherit from IList: BEGIN

    void println(string (*item2str)(T &) = 0)
    {
        cout << toString(item2str) << endl;
    }
    void setDeleteUserDataPtr(void (*deleteUserData)(XArrayList<T> *) = 0)
    {
        this->deleteUserData = deleteUserData;
    }

    Iterator begin()
    {
        return Iterator(this, 0);
    }
    Iterator end()
    {
        return Iterator(this, count);
    }

    /** free:
     * if T is pointer type:
     *     pass THE address of method "free" to XArrayList<T>'s constructor:
     *     to:  remove the user's data (if needed)
     * Example:
     *  XArrayList<Point*> list(&XArrayList<Point*>::free);
     *  => Destructor will call free via function pointer "deleteUserData"
     */
    static void free(XArrayList<T> *list)
    {
        typename XArrayList<T>::Iterator it = list->begin();
        while (it != list->end())
        {
            delete *it;
            it++;
        }
    }

protected:
    void checkIndex(int index);     // check validity of index for accessing
    void ensureCapacity(int index); // auto-allocate if needed

    /** equals:
     * if T: primitive type:
     *      indexOf, contains: will use native operator ==
     *      to: compare two items of T type
     * if T: object type:
     *      indexOf, contains: will use native operator ==
     *      to: compare two items of T type
     *      Therefore, class of type T MUST override operator ==
     * if T: pointer type:
     *      indexOf, contains: will use function pointer "itemEqual"
     *      to: compare two items of T type
     *      Therefore:
     *      (1): must pass itemEqual to the constructor of XArrayList
     *      (2): must define a method for comparing
     *           the content pointed by two pointers of type T
     *          See: definition of "equals" of class Point for more detail
     */
    static bool equals(T &lhs, T &rhs, bool (*itemEqual)(T &, T &))
    {
        if (itemEqual == 0)
            return lhs == rhs;
        else
            return itemEqual(lhs, rhs);
    }

    void copyFrom(const XArrayList<T> &list);

    void removeInternalData();

    //////////////////////////////////////////////////////////////////////
    ////////////////////////  INNER CLASSES DEFNITION ////////////////////
    //////////////////////////////////////////////////////////////////////
public:
    // Iterator: BEGIN
    class Iterator
    {
    private:
        int cursor;
        XArrayList<T> *pList;

    public:
        Iterator(XArrayList<T> *pList = 0, int index = 0)
        {
            this->pList = pList;
            this->cursor = index;
        }
        Iterator &operator=(const Iterator &iterator)
        {
            cursor = iterator.cursor;
            pList = iterator.pList;
            return *this;
        }
        void remove(void (*removeItemData)(T) = 0)
        {
            T item = pList->removeAt(cursor);
            if (removeItemData != 0)
                removeItemData(item);
            cursor -= 1; // MUST keep index of previous, for ++ later
        }

        T &operator*()
        {
            return pList->data[cursor];
        }
        bool operator!=(const Iterator &iterator)
        {
            return cursor != iterator.cursor;
        }
        // Prefix ++ overload
        Iterator &operator++()
        {
            this->cursor++;
            return *this;
        }
        // Postfix ++ overload
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
    };
    // Iterator: END
};

//////////////////////////////////////////////////////////////////////
////////////////////////     METHOD DEFNITION      ///////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
XArrayList<T>::XArrayList(
    void (*deleteUserData)(XArrayList<T> *),
    bool (*itemEqual)(T &, T &),
    int capacity)
{
    this->capacity = capacity;//gán capacity
    this->data = new T[this->capacity];//tạo mảng mới
    this->count = 0;//đếm số phần tử
    this->deleteUserData = deleteUserData;//gán hàm xóa dữ liệu
    this->itemEqual = itemEqual;//gán hàm equal
}

template <class T>
void XArrayList<T>::copyFrom(const XArrayList<T> &list)
{
    /*
     * Copies the contents of another XArrayList into this list.
     * Initializes the list with the same capacity as the source list and copies all elements.
     * Also duplicates user-defined comparison and deletion functions, if applicable.
     */
    capacity = list.capacity;
    count = list.count;
    itemEqual = list.itemEqual;
    deleteUserData = list.deleteUserData;

    data = new T[capacity];
    for (int i = 0; i < count; i++) {
        data[i] = list.data[i];
    }
}

template <class T>
void XArrayList<T>::removeInternalData()
{
    /*
     * Clears the internal data of the list by deleting the dynamic array and any user-defined data.
     * If a custom deletion function is provided, it is used to free the stored elements.
     * Finally, the dynamic array itself is deallocated from memory.
     */
    if (deleteUserData != nullptr) {
    deleteUserData(this); // Use custom deletion function if provided
    } else {
        delete[] data; // Otherwise, just delete the dynamic array
    }
    data = nullptr; // Set data pointer to nullptr for safety
    count = 0; // Reset count
    capacity = 0; // Reset capacity
}

template <class T>
XArrayList<T>::XArrayList(const XArrayList<T> &list)
{
    this->data =nullptr;
    copyFrom(list);//copy từ list
}

template <class T>
XArrayList<T> &XArrayList<T>::operator=(const XArrayList<T> &list)
{
    if (this != &list) { 
    copyFrom(list); 
    }
    return *this;
}

template <class T>
XArrayList<T>::~XArrayList()
{
    if (deleteUserData != nullptr) {
    deleteUserData(this); // Use custom deletion function if provided
    }
    delete[] data; // Otherwise, just delete the dynamic array
    data = nullptr;
    capacity = 0;
    count = 0;
}

template <class T>
void XArrayList<T>::add(T e)
{
    ensureCapacity(count);//kiểm tra xem có đủ chỗ không nếu khong thì tăng capacity count+1
    data[count] = e;//chèn e vào cuối mảng
    count++;//tăng số phần tử
}

template <class T>
void XArrayList<T>::add(int index, T e)
{
    if (index < 0 || index > count) { // Check the index bounds
        throw std::out_of_range("Index is out of range!");
    }
    ensureCapacity(count);//kiểm tra xem có đủ chỗ không nếu khong thì tăng capacity count+1
    for (int i = count; i > index; i--) {//duyệt từ count đến index
        data[i] = data[i - 1];//gán giá trị từ i-1 sang i
    }
    data[index] = e;//gán giá trị
    count++;//tăng count lên 1
}

template <class T>
T XArrayList<T>::removeAt(int index)
{
    checkIndex(index);//kiểm tra index có nằm trong khoảng hợp lí không
    T itemToRemove=data[index];//lấy giá trị từ data
    for(int i=index;i<count-1;i++){
        data[i]=data[i+1];//dịch chuyển phần tử sau lên trước
    }
    if (count > 0) {
        count--;//giảm count đi 1
    }
    return itemToRemove;//trả về giá trị
}

template <class T>
bool XArrayList<T>::removeItem(T item, void (*removeItemData)(T))
{
    int i = indexOf(item);//tìm vị trí của item
    if (i == -1) {//nếu không tìm thấy thì trả về false
        return false;
    }

    T ItemToRemove = data[indexOf(item)];//lấy giá trị từ data
    if (removeItemData != nullptr) {// nếu removeItemData khác null thì removeItemData
        removeItemData(ItemToRemove);
    }
    removeAt(i);//xóa item
    return true; // item đc tìm thấy r remove

}

template <class T>
bool XArrayList<T>::empty()
{
    return count == 0 ? true : false;//nếu count=0 thì trả về true
}

template <class T>
int XArrayList<T>::size()
{
    return count;//trả về count
}

template <class T>
void XArrayList<T>::clear()
{
    if (deleteUserData != nullptr) {
        deleteUserData(this); 
    }
    delete[] data;     
    count = 0; 
    data=new T [capacity];
}

template <class T>
T &XArrayList<T>::get(int index)
{
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index is out of range!");
    }
    return data[index];//trả về giá trị
}

template <class T>
int XArrayList<T>::indexOf(T item)
{
    for (int i = 0; i < this->count; i++) {//duyệt từ 0 đến count
        if (data[i] == item) {//nếu giá trị tại i bằng item thì trả về i 
            return i;
        }
        if (itemEqual != nullptr) {
            if (itemEqual(data[i], item)) {//nếu giá trị tại i bằng item thì trả về i 
                return i;
            }
        }   
    }
    return -1;
}
template <class T>
bool XArrayList<T>::contains(T item)
{
    if(indexOf(item)==-1){
        return false;
    }
    return true;
}

template <class T>
string XArrayList<T>::toString(string (*item2str)(T &))
{
    /**
     * Converts the array list into a string representation, formatting each element using a user-defined function.
     * If no function is provided, it uses the default string representation for each element.
     * Example: Given an array list with elements {1, 2, 3} and a function that converts integers to strings, calling toString would return "[1, 2, 3]".
     *
     * @param item2str A function pointer for converting items of type T to strings. If null, default to the string conversion of T.
     * @return A string representation of the array list with elements separated by commas and enclosed in square brackets.
     */

    if(count == 0){//nếu rỗng thì trả về 
        return "[]";
    }
    stringstream tostringofitem; 
    stringstream tostring;

    if(item2str != nullptr){//nếu item2str!=null thì trả về
        tostringofitem << "[";
        for(int i = 0; i < count; i++){
            tostringofitem << item2str(data[i]);
            if(i< count-1){
                tostringofitem <<", ";
            }
        }
        tostringofitem <<"]";
    } 

    else{
        tostringofitem<<"[";
        for(int i=0;i<count;i++){
            tostring<<data[i];
            if(i<count-1){
                tostring<<", ";
            }
        }
        tostringofitem<<tostring.str();
        tostringofitem<<"]";
    }
    return tostringofitem.str();

}

//////////////////////////////////////////////////////////////////////
//////////////////////// (private) METHOD DEFNITION //////////////////
//////////////////////////////////////////////////////////////////////
template <class T>
void XArrayList<T>::checkIndex(int index)
{
    /**
     * Validates whether the given index is within the valid range of the list.
     * Throws an std::out_of_range exception if the index is negative or exceeds the number of elements.
     * Ensures safe access to the list's elements by preventing invalid index operations.
     */
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index is out of range!");
    }
}
template <class T>
void XArrayList<T>::ensureCapacity(int index)
{
    /**
     * Ensures that the list has enough capacity to accommodate the given index.
     * If the index is out of range, it throws an std::out_of_range exception. If the index exceeds the current capacity,
     * reallocates the internal array with increased capacity, copying the existing elements to the new array.
     * In case of memory allocation failure, catches std::bad_alloc.
     */
    if(index<0){
        throw std::out_of_range("Index is out of range!");
    }
    if (index >=capacity) {
        try{
        int newCapacity = capacity * 2 + 1;
        T* newData = new T[newCapacity];
        for (int i = 0; i < count; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
        } catch (const std::bad_alloc& ) {}
    }
}

#endif /* XARRAYLIST_H */
