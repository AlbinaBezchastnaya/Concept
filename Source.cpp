#include <iostream>
#include <string>
#include <type_traits>

// Концепт
template <typename T>
concept ComplexConcept = (!std::is_polymorphic_v<T> || std::is_final_v<T>) &&  //  Класс должен быть полиморфным, либо финальным, что исключает виртуальный деструктор
    requires (const T v)
{
    { v.hash() } -> std::convertible_to<long>;                                 //  Метод, возвращающий тип, который может быть конвертирован в "long"
    { v.toString() } -> std::same_as<std::string>;                             //  Метод, возварщающий тип "string"                 
};

// Класс, который соответствует требованиям концепта "ComplexConcept"
class ConceptClass
{
public:
    long hash() const                                                          // Функция "hash", которая возвращает тип, конвертируемый в "long"
    {
        return 1'000'000'000;
    }
    std::string toString() const                                               // Функция "toString", которая возвращает тип "string"
    {
        return "ConceptClass is OK";
    }
};
// Класс, который не соответствует требованиям концепта "ComplexConcept"
class NonConceptClass
{
public:
    /*long hash() const                                                        // Функция "hash", которая возвращает тип, конвертируемый в "long"
    {
        return 1'000'000'000;
    }*/
    std::string toString() const                                               // Функция "toString", которая возвращает тип "string"
    {
        return "NonConceptClass is OK";
    }
};

// Функция для проверки соответствия класса требованиям концепта
template <ComplexConcept T>
void checkClass(const T& example)
{
    std::cout << example.toString() << std::endl;                              // Вывести сообщение о соответствии класса требованиям концепта
}

int main() {
    ConceptClass example;
    NonConceptClass example2;
    checkClass(example);                                                       // Проверить соответствие класса требованиям концепта
    //checkClass(example2);                                                    // Попытка использовать класс, кототый не соответствует требованиям концепта
    return 0;
}