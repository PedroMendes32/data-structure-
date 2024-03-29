#pragma once
#include <iostream>
#include <memory>
#include <optional>

template<class T_KEY, class T_VALUE>
class dictionary final
{
private:
    T_KEY key;
    T_VALUE value;
    std::unique_ptr<dictionary<T_KEY, T_VALUE>> next;

public:
    explicit dictionary(void) : key(), value(), next(nullptr)
    {
    }
    explicit dictionary(T_KEY _key, T_VALUE _value) : key(_key), value(_value), next(nullptr)
    {
    }
    explicit dictionary(const dictionary<T_KEY, T_VALUE>& ref) : key(ref.key), value(ref.value)
    {
        if (ref.next.get())
        {
            next = std::make_unique<dictionary<T_KEY, T_VALUE>>(*(ref.next));
        }
    }
    ~dictionary()
    {
    }
    dictionary<T_KEY, T_VALUE>& operator=(dictionary<T_KEY, T_VALUE>& ref)
    {
        if (this != &ref)
        {
            this->key = ref.key;
            this->value = ref.value;
            if (ref.next.get())
            {
                this->next = std::make_unique<dictionary<T_KEY, T_VALUE>>(*(ref.next));
            }
            else
            {
                this->next.reset();
            }
        }
        return *this;
    }
private:
    template<typename T>
    std::optional<T> find(T key_or_value, bool search_by_key) const;

public:
    std::optional<T_KEY> get_key(T_VALUE value) const;
    std::optional<T_VALUE> get_value(T_KEY key) const;
    void add(T_KEY k, T_VALUE v);
    void show(void) const;
    class dict_iterator;
    dict_iterator begin(void) const;
    dict_iterator end(void) const;
};

