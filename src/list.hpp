#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

/**************************************** 
 * Simple sorted linked list.
 ****************************************/ 
template<typename T>
inline typename LinkedList<T>::iterator LinkedList<T>::iterator::operator++(void)
{
    act = act->next;
    return *this;
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::iterator::operator++(int)
{
    iterator tmp = *this;
    operator++();
    return tmp;
}

template<typename T>
inline bool LinkedList<T>::iterator::operator==(const LinkedList<T>::iterator &i) const
{
    return act == i.act;
}

template<typename T>
inline bool LinkedList<T>::iterator::operator!=(const LinkedList<T>::iterator &i) const
{
    return !(*this == i);
}

template<typename T>
inline T& LinkedList<T>::iterator::operator*(void)
{
    if (act) return act->data; 
    else throw ListException("Dereference exception");
}

template<typename T>
inline T* LinkedList<T>::iterator::operator->(void) 
{
    if (act) return &act->data;
    else throw ListException("Dereference exception");
}

/** 
 * @brief Constructor sets the pivot elements.
 */
template<typename T>
inline LinkedList<T>::LinkedList(void)
{
    firstItem = endItem = new ListItem;
}

template<typename T>
inline LinkedList<T>::~LinkedList(void)
{
    deleteall();
    delete endItem;
}

template<typename T>
inline typename LinkedList<T>::iterator LinkedList<T>::begin(void)
{
    return iterator(firstItem);
}

template<typename T>
inline typename LinkedList<T>::iterator LinkedList<T>::end(void)
{
    return iterator(endItem);
}

/** 
 * @brief Inserts one item in the linked list.
 * 
 * @param data Value of the new item.
 */
template<typename T> 
void LinkedList<T>::insert(const T& data)
{
    iterator it;
    for (it = begin(); it != end() && Cmp<T>::lt(*it, data); it++)
        ;

    if (!(Cmp<T>::eq(*it, data))) {
        ListItem *newItem = new ListItem(it.act->next);
        if (it == end()) endItem = newItem;
        newItem->data = *it;  
        *it = data;
        it.act->next = newItem;
    }
}

/** 
 * @brief Removes one element from linked list.
 * 
 * @param data Value of the deleted item
 */
template<typename T>
void LinkedList<T>::remove(const T& data)
{
    iterator it;
    iterator temp;
    for (it = begin(); it != end() && !(Cmp<T>::eq(*it, data)); it++)
        temp = it;

    if(Cmp<T>::eq(*it, data)) {
        if (firstItem == it.act)
            firstItem = it.act->next;
        else
            temp.act->next = it.act->next;

        delete it.act;
    }
}

/** 
 * @brief Deletes all element in linked list, except pivot item.
 */
template<typename T>
void LinkedList<T>::deleteall(void)
{
    iterator it;
    for (it = begin(); it != end(); it++)
        delete it.act;
    firstItem = it.act;
}

/** 
 * @brief Prints the list to standard output.
 */
template<typename T>
void LinkedList<T>::print(void)
{ 
    iterator it;
    for (it = begin(); it != end(); it++)
        std::cout << *it << '\n';
}


/****************************************
 * Two-level linked list.
 ****************************************/ 
template<typename R, typename T>
inline typename RootLinkedList<R, T>::iterator RootLinkedList<R, T>::iterator::operator++(void)
{
    act = act->next;
    return *this;
}

template<typename R, typename T>
typename RootLinkedList<R, T>::iterator RootLinkedList<R, T>::iterator::operator++(int)
{
    iterator tmp = *this;
    operator++();
    return tmp;
}

template<typename R, typename T>
inline bool RootLinkedList<R, T>::iterator::operator==(const iterator &i) const 
{
    return act == i.act;
}

template<typename R, typename T>
inline bool RootLinkedList<R, T>::iterator::operator!=(const iterator &i) const 
{
    return !(*this == i);
}

template<typename R, typename T>
inline R& RootLinkedList<R, T>::iterator::operator*(void)
{
    if (act) return act->data; 
    else throw ListException("Dereference exception");
}

template<typename R, typename T>
inline R* RootLinkedList<R, T>::iterator::operator->(void) 
{
    if (act) return &act->data;
    else throw ListException("Dereference exception");
}

/** 
 * @brief Containing list
 * 
 * @return pointer to the containing list 
 */
template<typename R, typename T>
LinkedList<T> *RootLinkedList<R, T>::iterator::getList(void)
{
    return act->nextList;
}

/** 
 * @brief Constructor sets pivot elements
 */
template<typename R, typename T>
inline RootLinkedList<R, T>::RootLinkedList(void)
{
    firstItem = endItem = new ListItem;
}

template<typename R, typename T>
inline RootLinkedList<R, T>::~RootLinkedList(void)
{
    deleteall();
    delete endItem->nextList; //must delete pivot element's LinkedList object
    delete endItem;
}

template<typename R, typename T>
inline typename RootLinkedList<R, T>::iterator RootLinkedList<R, T>::begin(void)
{
    return iterator(firstItem);
}

template<typename R, typename T>
inline typename RootLinkedList<R, T>::iterator RootLinkedList<R, T>::end(void)
{
    return iterator(endItem);
}

/** 
 * @brief Inserts an element into the list
 * 
 * @param data Value of the new item
 */
template<typename R, typename T>
void RootLinkedList<R, T>::insert(const R& data)
{
    iterator it;
    for (it = begin(); it != end() && Cmp<T>::lt(*it,  data); it++)
        ;

    if (!(Cmp<T>::eq(*it, data))) {
        ListItem *newItem = new ListItem(it.act->next);
        if (it == end()) endItem = newItem;
        LinkedList<T> *tmp_listptr = it.getList(); //swap pointers to LinkedList object.
        it.act->nextList = newItem->nextList;
        it.act->next = newItem;

        newItem->data = *it;  
        newItem->nextList = tmp_listptr;
        *it = data;
    }
}

/** 
 * @brief Inserts one element in the containing list
 */
template<typename R, typename T>
void RootLinkedList<R, T>::insert(const R& r_data, const T& t_data)
{
    insert(r_data);

    iterator it;
    for (it = begin(); it != end() && !(Cmp<T>::eq(*it, r_data)); it++)
        ; 
    it.getList()->LinkedList<T>::insert(t_data);
}

template<typename R, typename T>
void RootLinkedList<R, T>::remove(const R& data)
{
    iterator it;
    iterator temp;
    for (it = begin(); it != end() && !(Cmp<R>::eq(*it, data)); it++)
        temp = it;

    if(Cmp<R>::eq(*it, data)) {
        if (firstItem == it.act)
            firstItem = it.act->next;
        else
            temp.act->next = it.act->next;

        delete it.getList();
        delete it.act;
    }
}

template<typename R, typename T>
void RootLinkedList<R, T>::remove(const R& r_data, const T& t_data)
{
    iterator it;
    iterator temp;
    for (it = begin(); it != end() && !(Cmp<R>::eq(*it, r_data)); it++)
        temp = it;

    if(Cmp<R>::eq(*it, r_data)) //TODO maybe exception handling
        it.getList()->remove(t_data);
}

template<typename R, typename T>
void RootLinkedList<R, T>::deleteall(void)
{
    iterator it;
    for (it = begin(); it != end(); it++) {
        delete it.getList();
        delete it.act;
    }
    firstItem = it.act;
}

template<typename R, typename T>
void RootLinkedList<R, T>::print(void)
{
    iterator it;
    typename LinkedList<T>::iterator lit;
    typename LinkedList<T>::iterator l_end;

    for (it = begin(); it != end(); it++) {
        std::cout << *it << '\n';
        l_end = it.getList()->end();

        for (lit = it.getList()->begin(); lit != l_end; lit++)
            std::cout << "|_ " << *lit << '\n';
    }
}

/****************************************
 * Three-level linked list
 ****************************************/ 

template<typename R, typename S, typename T>
inline typename MainLinkedList<R, S, T>::iterator MainLinkedList<R, S, T>::iterator::operator++(void)
{
    act = act->next;
    return *this;
}

template<typename R, typename S, typename T>
typename MainLinkedList<R, S, T>::iterator MainLinkedList<R, S, T>::iterator::operator++(int)
{
    iterator tmp = *this;
    operator++();
    return tmp;
}

template<typename R, typename S, typename T>
inline bool MainLinkedList<R, S, T>::iterator::operator==(const iterator &i) const 
{
    return act == i.act;
}

template<typename R, typename S, typename T>
inline bool MainLinkedList<R, S, T>::iterator::operator!=(const iterator &i) const 
{
    return !(*this == i);
}

template<typename R, typename S, typename T>
inline R& MainLinkedList<R, S, T>::iterator::operator*(void)
{
    if (act) return act->data; 
    else throw ListException("Dereference exception");
}

template<typename R, typename S, typename T>
inline R* MainLinkedList<R, S, T>::iterator::operator->(void) 
{
    if (act) return &act->data;
    else throw ListException("Dereference exception");
}

template<typename R, typename S, typename T>
inline RootLinkedList<S, T> *MainLinkedList<R, S, T>::iterator::getList(void)
{
    return act->nextList;
}

template<typename R, typename S, typename T>
inline MainLinkedList<R, S, T>::MainLinkedList(void)
{
    firstItem = endItem = new ListItem;
}

template<typename R, typename S, typename T>
inline MainLinkedList<R, S, T>::~MainLinkedList(void)
{
    deleteall();
    delete endItem->nextList;
    delete endItem;
}

template<typename R, typename S, typename T>
inline typename MainLinkedList<R, S, T>::iterator MainLinkedList<R, S, T>::begin(void)
{
    return iterator(firstItem);
}

template<typename R, typename S, typename T>
inline typename MainLinkedList<R, S, T>::iterator MainLinkedList<R, S, T>::end(void)
{
    return iterator(endItem);
}

template<typename R, typename S, typename T>
void MainLinkedList<R, S, T>::insert(const R& data)
{
    iterator it;
    it = begin();
    for (it = begin(); it != end() && Cmp<T>::lt(*it, data); it++)
        ;

    if (!(Cmp<T>::eq(*it, data))) {
        ListItem *newItem = new ListItem(it.act->next);
        if (it == end()) endItem = newItem;
        RootLinkedList<S, T> *tmp_listptr = it.getList(); //swap pointers to RootLinkedList object.

        it.act->nextList = newItem->nextList;
        it.act->next = newItem;

        newItem->data = *it;
        newItem->nextList = tmp_listptr;
        *it = data;
    }
}

template<typename R, typename S, typename T>
void MainLinkedList<R, S, T>::insert(const R& r_data, const S& s_data)
{
    insert(r_data);

    iterator it;
    for (it = begin(); it != end() && !(Cmp<T>::eq(*it, r_data)); it++)
        ; 
    it.getList()->insert(s_data);
}

template<typename R, typename S, typename T>
void MainLinkedList<R, S, T>::insert(const R& r_data, const S& s_data, const T& t_data)
{
    insert(r_data, s_data);
    iterator itr;
    for (itr = begin(); itr != end() && *itr != r_data; itr++)
        ;
    typename RootLinkedList<S, T>::iterator its;
    typename RootLinkedList<S, T>::iterator ends = itr.getList()->end();
    for (its = itr.getList()->begin(); its != ends && *its != s_data; its++)
        ;
    its.getList()->insert(t_data);
}

template<typename R, typename S, typename T>
void MainLinkedList<R, S, T>::remove(const R& data)
{
    iterator it;
    iterator temp;
    for (it = begin(); it != end() && !(Cmp<R>::eq(*it, data)); it++)
        temp = it;

    if(Cmp<R>::eq(*it, data)) {
        if (firstItem == it.act)
            firstItem = it.act->next;
        else
            temp.act->next = it.act->next;

        delete it.getList();
        delete it.act;
    }
}

template<typename R, typename S, typename T>
void MainLinkedList<R, S, T>::remove(const R& r_data, const S& s_data)
{
    iterator it;
    iterator temp;
    for (it = begin(); it != end() && !(Cmp<R>::eq(*it, r_data)); it++)
        temp = it;

    if(Cmp<R>::eq(*it, r_data))
        it.getList()->remove(s_data);
        
}

template<typename R, typename S, typename T>
void MainLinkedList<R, S, T>::remove(const R& r_data, const S& s_data, const T& t_data)
{
    iterator it;
    iterator temp;
    for (it = begin(); it != end() && !(Cmp<R>::eq(*it, r_data)); it++)
        temp = it;

    if(Cmp<R>::eq(*it, r_data))
        it.getList()->remove(s_data, t_data);
}

template<typename R, typename S, typename T>
void MainLinkedList<R, S, T>::deleteall(void)
{
    iterator it;
    for (it = begin(); it != end(); it++) {
        delete it.getList();
        delete it.act;
    }
    firstItem = it.act;
}

template<typename R, typename S, typename T>
void MainLinkedList<R, S, T>::print(void)
{
    iterator it;
    typename RootLinkedList<S, T>::iterator rit;
    typename LinkedList<T>::iterator lit;

    typename RootLinkedList<S, T>::iterator r_end;
    typename LinkedList<T>::iterator l_end;

    for (it = begin(); it != end(); it++) {
        std::cout << *it << '\n';
        r_end = it.getList()->end();

        for (rit = it.getList()->begin(); rit != r_end; rit++) {
            std::cout << "|_ " <<*rit << '\n';
            l_end = rit.getList()->end();

            for (lit = rit.getList()->begin(); lit != l_end; lit++) 
                std::cout << "   |_ " << *lit << '\n';
        }
        std::cout << '\n';
    }
}

#endif
