#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <initializer_list>

class LRUcache {
    private:
        struct CacheItem { 
            private:   
                int data;
                std::string key;
            public:
                CacheItem(int k, std::string s): data(k), key(s) {}
                bool operator==(const CacheItem &c) 
                {
                return data == c.data && key == c.key;
                }
                friend class LRUcache;
        };
        CacheItem *head;
        CacheItem *end;
        size_t max_size;
        size_t size;
        std::unordered_map<std::string, std::list<CacheItem>::iterator> keys;
        std::list<CacheItem> cache;
    
    public:       
        LRUcache(std::initializer_list<CacheItem> in_list, int m_s):
        max_size(m_s)
        {
            auto it = in_list.begin();
            this->cache.push_front(*it);
            head = &(*(cache.begin()));
            end = head; size++;
            keys[it->key] = cache.begin();
            while (++it != in_list.end()) {
                if (keys.find(it->key) != keys.end()) {
                    keys[it->key]->data = it->data; //just updating already existing element
                    continue;
                }
                if (size == max_size - 1) {
                    keys.erase(cache.back().key);
                    cache.pop_back();
                    end = &(*(cache.end()));
                    size--;
                }
                this->cache.push_front(*it);
                head = &(*(cache.begin()));
                keys[it->key] = cache.begin(); size++;
            }
        }

        void use(std::string str)
        {
            if (keys.find(str) == keys.end()) {
                std::cout << "No such element in cache!\n";
                return;
            }
            cache.splice(cache.begin(), cache, keys[str]); // pushing to first place
        }

        bool update(CacheItem el)
        {
            if (keys.find(el.key) == keys.end()) {
                std::cout << "No such element in cache," <<
                "please insert it first, then update!\n";
                return false;
            }
            use(el.key); //reuse this code, then just update data of cache.front
            cache.front().data = el.data;
            return true;
        }

        bool insert(CacheItem el)
        {
            if (keys.find(el.key) != keys.end()) {
                std::cout << "Element in cache already." <<
                "please use update to change it!\n";
                return false;
            }           
            if (size == max_size - 1) {
                keys.erase(cache.back().key);
                cache.pop_back();
                end = &(*(cache.end()));
                size--;
            }
            this->cache.push_front(el);
            head = &(*(cache.begin()));
            keys[el.key] = cache.begin(); size++;
            return true;
        }

        void print() 
        {
            for (auto mem : cache)
                if (mem == cache.back())
                    std::cout << "(" << mem.key << "," << 
                    mem.data << ")";
                else
                    std::cout << "(" << mem.key << "," << 
                    mem.data << "), ";
            std::cout << std::endl; 
        }
};

int main()
{
    LRUcache lru(  {{1,"a"},
                    {2,"b"},
                    {3,"c"},
                    {6,"f"},
                    {10,"i"}} , 4); 
    lru.print();
    lru.update({4,"f"});
    lru.print();
    lru.use("c");
    lru.print();
    lru.insert({12,"d"});
    lru.print();
    lru.update({1,"a"});
}