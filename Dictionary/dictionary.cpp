#include "dictionary.hpp"

template<class T_KEY, class T_VALUE>
template<typename T>
std::optional<T> dictionary<T_KEY, T_VALUE>::find(T key_or_value, bool search_by_key) const
{
    if (!next.get())
    {
        std::cout << "Dictionary is empty!" << std::endl;
        return std::nullopt;
    }

    dictionary<T_KEY, T_VALUE>* current = next.get();

    while (current->next.get() != nullptr) // melhorar a busca usando árvore dps
    {
        if ((search_by_key && current->key == key_or_value) || (!search_by_key && current->value == key_or_value))
        {
            return search_by_key ? current->value : current->key;
        }
        current = current->next.get();
    }
    std::cout << (search_by_key ? "Key" : "Value") << " not found!" << std::endl;
    return std::nullopt;
}

template<class T_KEY, class T_VALUE>
std::optional<T_KEY> dictionary<T_KEY, T_VALUE>::get_key(T_VALUE value) const
{
    return find(value, false);
}

template<class T_KEY, class T_VALUE>
std::optional<T_VALUE> dictionary<T_KEY, T_VALUE>::get_value(T_KEY key) const
{
    return find(key, true);
}

template<class T_KEY, class T_VALUE>
void dictionary<T_KEY, T_VALUE>::add(T_KEY k, T_VALUE v)
{
    if (!next.get())
    {
        next = std::make_unique<dictionary<T_KEY, T_VALUE>>(k, v);
        return;
    }
    dictionary<T_KEY, T_VALUE>* current = next.get(); //this->next->next.get() deve dar certo também
    while (current->next.get() != nullptr)
    {
        current = current->next.get();
    }
    current->next = std::make_unique<dictionary<T_KEY, T_VALUE>>(k, v);
}

template<class T_KEY, class T_VALUE>
void dictionary<T_KEY, T_VALUE>::show(void) const
{
    const dictionary<T_KEY, T_VALUE>* start = this->next.get();
    std::cout << "{ " << std::endl;
    while (start != nullptr)
    {
        std::cout << " " << start->key << " : " << start->value;
        if (start->next.get() != nullptr)
            std::cout << "," << std::endl;
        start = start->next.get();
    }
    std::cout << " }";
}

template<class T_KEY, class T_VALUE>
class dictionary<T_KEY, T_VALUE>::dict_iterator // iterador para usar no for padrão ex for (it = dict.begin()....
{
private:
    dictionary<T_KEY, T_VALUE>* ptr;

public:
    dict_iterator(dictionary<T_KEY, T_VALUE>* p) : ptr(p)
    {
    }

    dict_iterator& operator++(void)
    {
        this->ptr = this->ptr->next.get();
        return *this;
    }

    bool operator!=(const dict_iterator& obj) const
    {
        return this->ptr != obj.ptr;
    }

    std::pair<T_KEY, T_VALUE>& operator*(void) const
    {
        return std::make_pair(this->ptr->key, this->ptr->value);
    }
};

template<class T_KEY, class T_VALUE>
typename dictionary<T_KEY, T_VALUE>::dict_iterator dictionary<T_KEY, T_VALUE>::begin(void) const
{
    return dict_iterator(this->next.get());
}

template<class T_KEY, class T_VALUE>
typename dictionary<T_KEY, T_VALUE>::dict_iterator dictionary<T_KEY, T_VALUE>::end(void) const
{
    return dict_iterator(nullptr);
}
