#include <iostream>
#include <string>
#include <type_traits>

// �������
template <typename T>
concept ComplexConcept = (!std::is_polymorphic_v<T> || std::is_final_v<T>) &&  //  ����� ������ ���� �����������, ���� ���������, ��� ��������� ����������� ����������
    requires (const T v)
{
    { v.hash() } -> std::convertible_to<long>;                                 //  �����, ������������ ���, ������� ����� ���� ������������� � "long"
    { v.toString() } -> std::same_as<std::string>;                             //  �����, ������������ ��� "string"                 
};

// �����, ������� ������������� ����������� �������� "ComplexConcept"
class ConceptClass
{
public:
    long hash() const                                                          // ������� "hash", ������� ���������� ���, �������������� � "long"
    {
        return 1'000'000'000;
    }
    std::string toString() const                                               // ������� "toString", ������� ���������� ��� "string"
    {
        return "ConceptClass is OK";
    }
};
// �����, ������� �� ������������� ����������� �������� "ComplexConcept"
class NonConceptClass
{
public:
    /*long hash() const                                                        // ������� "hash", ������� ���������� ���, �������������� � "long"
    {
        return 1'000'000'000;
    }*/
    std::string toString() const                                               // ������� "toString", ������� ���������� ��� "string"
    {
        return "NonConceptClass is OK";
    }
};

// ������� ��� �������� ������������ ������ ����������� ��������
template <ComplexConcept T>
void checkClass(const T& example)
{
    std::cout << example.toString() << std::endl;                              // ������� ��������� � ������������ ������ ����������� ��������
}

int main() {
    ConceptClass example;
    NonConceptClass example2;
    checkClass(example);                                                       // ��������� ������������ ������ ����������� ��������
    //checkClass(example2);                                                    // ������� ������������ �����, ������� �� ������������� ����������� ��������
    return 0;
}