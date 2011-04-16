#ifndef LIST_H
#define LIST_H
#include <iterator>
#include <iostream>
#include <string>


/** 
 * @brief Compare template class.
 * Compare class containing 2 predicate functions (equals, less than)
 * In some cases specialization is needed.
 */
template<typename T>
class Cmp {
public:
    bool static eq(const T& a, const T& b) { return a == b; }
    bool static lt(const T& a, const T& b) { return a < b; }
};


/** 
 * @brief Linked list class.
 * Simple sorted linked list class.
 */
template<typename T>
class LinkedList {
protected:
    /** 
     * @brief Linked list's item.
     */
    struct ListItem {
        T data;
        ListItem *next;
        ListItem(ListItem *item = 0) : next(item) { }
    };

    ListItem *firstItem;
    ListItem *endItem;

public:
    /** 
     * @brief Iterator class
     */
    class iterator : public std::iterator<std::forward_iterator_tag, T> {
    public:
        iterator(void) : act(0) { }
        iterator operator++(void);
        iterator operator++(int);
        bool operator==(const iterator &i) const; 
        bool operator!=(const iterator &i) const; 
        T& operator*(void);
        T* operator->(void); 

        friend class LinkedList<T>;

    protected:
        iterator(ListItem *li) : act(li) { }
        ListItem *act;
    };

    LinkedList(void);
    ~LinkedList(void);
    void insert(const T& data);
    void remove(const T& data);
    void deleteall(void);
    iterator begin(void);
    iterator end(void); 
    void print(void);

    friend class LinkedList<T>::iterator;
};


/**
 * @brief 2 level Root Linked List. 
 * Each list item has one child list.
 */
template<typename R, typename T> 
class RootLinkedList : public LinkedList<R> {
protected:
    /** 
     * @brief Root Linked list's item.
     */
    struct ListItem : public LinkedList<R>::ListItem {
        R data;
        ListItem *next;
        LinkedList<T> *nextList;
        ListItem(ListItem *item = 0) : next(item) { nextList = new LinkedList<T>; }
    };
    ListItem *firstItem;
    ListItem *endItem;

public:
    /** 
     * @brief Iterator class
     */
    class iterator : public LinkedList<R>::iterator {
    public:
        iterator(void) : act(0) { }
        iterator operator++(void);
        iterator operator++(int);
        bool operator==(const iterator &i) const;
        bool operator!=(const iterator &i) const;
        R& operator*(void);
        R* operator->(void); 
        LinkedList<T> *getList(void);

        friend class RootLinkedList<R, T>;

    protected:
        ListItem *act;
        iterator(ListItem *li) : act(li) { }
    };

    RootLinkedList(void);
    ~RootLinkedList(void);
    void insert(const R& r_data);
    void insert(const R& r_data, const T& t_data);
    void remove(const R& data);
    void remove(const R& r_data, const T& t_data);
    void deleteall(void);
    iterator begin(void);
    iterator end(void);
    void print(void);

    friend class RootLinkedList<R, T>::iterator;
};


/** 
 * @brief Three-level linked list.
 */
template<class R, class S, class T> class MainLinkedList : public RootLinkedList<R, S> {
protected:
    /** 
     * @brief Three-level Linked list's item.
     */
    struct ListItem : public LinkedList<R>::ListItem {
        R data;
        ListItem *next;
        RootLinkedList<S, T> *nextList;
        ListItem(ListItem *item = 0) : next(item) { nextList = new RootLinkedList<S, T>; }
    };
    ListItem *firstItem;
    ListItem *endItem;

public:
    /** 
     * @brief Iterator class
     */
    class iterator : public RootLinkedList<R, S>::iterator {
    public:
        iterator(void) : act(0) { }
        iterator operator++(void);
        iterator operator++(int);
        bool operator==(const iterator &i) const;
        bool operator!=(const iterator &i) const;
        R& operator*(void);
        R* operator->(void); 
        RootLinkedList<S, T> *getList(void);

        friend class MainLinkedList<R, S, T>;

    protected:
        ListItem *act;
        iterator(ListItem *li) : act(li) { }
    };

    MainLinkedList(void);
    ~MainLinkedList(void);
    void insert(const R& r_data);
    void insert(const R& r_data, const S& S_data);
    void insert(const R& r_data, const S& S_data, const T& T_data);
    void remove(const R& data);
    void remove(const R& r_data, const S& t_data);
    void remove(const R& r_data, const S& S_data, const T& T_data);
    void deleteall(void);
    iterator begin(void);
    iterator end(void);
    void print(void);

    friend class MainLinkedList<R, S, T>::iterator;
};

class ListException {
public:
    ListException(const char *err_) : err(err_) { }

    ~ListException() { }
    virtual const char *what() const { return err.c_str(); }
private:
    std::string err;
};

#include "list.hpp"

#endif
