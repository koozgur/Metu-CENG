#ifndef TREEMAP_H
#define TREEMAP_H

#include <iostream>
#include <vector>

#include "KeyValuePair.h"
#include "ScapegoatTree.h"

template<class K, class V>
class TreeMap {
public: // DO NOT CHANGE THIS PART.
    TreeMap();

    void clear();

    const V &get(const K &key) const;

    bool pop(const K &key);

    bool update(const K &key, const V &value);

    const KeyValuePair<K, V> &ceilingEntry(const K &key);

    const KeyValuePair<K, V> &floorEntry(const K &key);

    const KeyValuePair<K, V> &firstEntry();

    const KeyValuePair<K, V> &lastEntry();

    void pollFirstEntry();

    void pollLastEntry();

    std::vector<KeyValuePair<K, V> > subMap(K fromKey, K toKey) const;

    void print() const;
  
  

private: // DO NOT CHANGE THIS PART.
    ScapegoatTree<KeyValuePair<K, V> > stree;
};

template<class K, class V>
TreeMap<K, V>::TreeMap() {}

template<class K, class V>
void TreeMap<K, V>::clear() {
    stree.removeAllNodes();
}

template<class K, class V>
const V &TreeMap<K, V>::get(const K &key) const 
{
    KeyValuePair<K, V> kvp(key);
    return stree.get(kvp).getValue();
}

template<class K, class V>
bool TreeMap<K, V>::pop(const K &key) 
{
    KeyValuePair<K, V> kvp(key);
    return stree.remove(kvp);
}

template<class K, class V>
bool TreeMap<K, V>::update(const K &key, const V &value) 
{
    KeyValuePair<K, V> kvp(key,value);
    return stree.insert(kvp);
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::ceilingEntry(const K &key) 
{
    KeyValuePair<K, V> kvp(key);
    return stree.getCeiling(kvp);
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::floorEntry(const K &key) 
{
    KeyValuePair<K, V> kvp(key);
    return stree.getFloor(kvp);
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::firstEntry() 
{
    return stree.getMin();
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::lastEntry() 
{
    return stree.getMax();
}

template<class K, class V>
void TreeMap<K, V>::pollFirstEntry() 
{
    stree.remove(firstEntry());
}

template<class K, class V>
void TreeMap<K, V>::pollLastEntry() 
{
    stree.remove(lastEntry());
}

template<class K, class V>
std::vector<KeyValuePair<K, V> > TreeMap<K, V>::subMap(K fromKey, K toKey) const 
{
    std::vector <KeyValuePair <K, V> > v;
    K i = fromKey;
    for(;;i <= toKey)
    {
        KeyValuePair<K, V> kvp(i);
        v.push_back(stree.getCeiling(kvp));
        try 
        {
            i = stree.getNext(kvp).getKey();
        }
        catch(...)
        {
          
            break;
        }
    }
  
    return v;
}

template<class K, class V>
void TreeMap<K, V>::print() const {

    std::cout << "# Printing the tree map ..." << std::endl;

    std::cout << "# ScapegoatTree<KeyValuePair<K, V> > stree:" << std::endl;
    stree.printPretty();

    std::cout << "# Printing is done." << std::endl;
}

#endif //TREEMAP_H
