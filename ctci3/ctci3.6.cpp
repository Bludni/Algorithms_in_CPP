#include <iostream>
#include <forward_list>
#include <string>
#include <memory>


typedef enum { CAT, DOG } Animal; 

std::ostream& operator<<(std::ostream& out, Animal& val)
{
    (val == CAT) ? std::cout << "Cat"\
    : std::cout << "Dog";
    return out;
}

struct Pet {
    Animal val;
    std::string name;
    Pet(Animal val, std::string name) : val(val), name(name) {}
    friend std::ostream& operator<<(std::ostream &out, Pet &animal)
    {
        std::cout << animal.val << " " << animal.name;
        return out;
    }
};

class Shelter {
    private: 
        std::forward_list<Pet> adoptable;
    public:
        Shelter(std::forward_list<Pet> lista):adoptable(lista){}
        
        std::forward_list<Pet>& get() {
            return this->adoptable;
        }

        std::shared_ptr<Pet> dequeueAny()
        {
            std::forward_list<Pet>::iterator it1, it2;
            it1 = this->adoptable.begin(); it2 = it1;
            it2++; it2++;
            while (it2 != this->adoptable.end()) {
                it2++; it1++;
            }
            it2 = it1; it2++;
            std::shared_ptr<Pet> temp = std::make_shared<Pet>(it2->val, it2->name);
            this->adoptable.erase_after(it1);
            // home.adoptable.erase_after(std::next(home.adoptable.begin(),\
            std::distance(home.adoptable.begin(), home.adoptable.end()) - 2));
            return temp;
        }
        
        void enqueue(const Pet& val)
        {
            adoptable.push_front(val);
        }

        std::shared_ptr<Pet> dequeueDog()
        {
            std::forward_list<Pet>::iterator it1,it2,dog;
            it1 = this->adoptable.before_begin();
            it2 = this->adoptable.begin();
            while (it2 != this->adoptable.end()) {
                if (it2->val == DOG) dog = it1;
                it1++; it2++;
            }
            it1 = std::next(dog, 2);
            it2 = std::next(dog, 1);
            std::shared_ptr<Pet> temp = std::make_shared<Pet>(it2->val, it2->name);
            this->adoptable.erase_after(dog, it1);
            return temp;
        } 

        std::shared_ptr<Pet> dequeueCat()
        {
            std::forward_list<Pet>::iterator it1,it2,cat;
            it1 = this->adoptable.before_begin();
            it2 = this->adoptable.begin();
            while (it2 != this->adoptable.end()) {
                if (it2->val == CAT) cat = it1;
                it1++; it2++;
            }
            it1 = std::next(cat, 2);
            it2 = std::next(cat, 1);
            std::shared_ptr<Pet> temp = std::make_shared<Pet>(it2->val, it2->name);
            this->adoptable.erase_after(cat, it1);
            return temp;
        } 
};

int main()
{
    std::forward_list<Pet> x = {
                                Pet(DOG, std::string("Roko")),
                                Pet(DOG, std::string("Frojd")),
                                Pet(CAT, std::string("Kitty")),
                                Pet(CAT, std::string("Alf"))
                               };
    //x.erase_after();
    for (std::forward_list<Pet>::iterator it = x.begin(); it != x.end(); it++) {
        std::cout << (*it) << std::endl;
    }
    std::cout << (std::distance(x.begin(), x.end()) + 3) << std::endl;
    Shelter shel(x);
    shel.enqueue(Pet(CAT, std::string("Oli")));
    Pet adopted = (*shel.dequeueAny().get());
    std::cout << "Adopted animal is " << adopted << std::endl;
    adopted = (*shel.dequeueDog().get());
    std::cout << "Adopted dog is " << adopted.name << std::endl;
    adopted = (*shel.dequeueCat().get());
    std::cout << "Adopted cat is " << adopted.name << std::endl;
    for (std::forward_list<Pet>::iterator it = shel.get().begin();\
    it != shel.get().end(); it++) {
        std::cout << (*it) << std::endl;
    }
}