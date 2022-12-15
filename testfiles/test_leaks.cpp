#include "vector.hpp"
#include <iostream>
#include <stdexcept>
#include <memory>

int _ratio = 1000;

class B {
public:
    char *l;
    int i;
    B():l(nullptr), i(1) {};
    B(const int &ex) {
        this->i = ex;
        this->l = new char('a');
    };
    virtual ~B() {
        delete this->l;
        this->l = nullptr;
    };
};

class A : public B {
public:
    A():B(){};
    A(const B* ex){
        this->l = new char(*(ex->l));
        this->i = ex->i;
        if (ex->i == -1) throw "n";
    }
    ~A() {
        delete this->l;
        this->l = nullptr;
    };
};

template <typename T>
void insert_test_3(ft::vector<T> vector) {
	// ft::vector<int> tmp;
    // tmp.assign(2600 * _ratio, 1);
    // vector.assign(4200 * _ratio, 1);
    // vector.insert(vector.end() - 1000 * _ratio, tmp.begin(), tmp.end());
    // v.push_back(vector.capacity());

	(void)vector;
    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
	ft::vector<A> vv;
	ft::vector<B*> v1;

    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));
    try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
    catch (...) {
		std::cout << "catch" << std::endl;
		// std::cout << e.what() << std::endl;
        // v.push_back(vv.size());
        // v.push_back(vv.capacity());
    }

}

// int run_vector_unit_test(std::string test_name, std::vector<int> (func1)(std::vector<T>), std::vector<int> (func2)(_vector<T>)) {
//     int    result;
//     int    leaks;
//     time_t t1;
//     time_t t2;
//     std::vector<int > res1;
//     std::vector<int > res2;
//     std::vector<int> vector;
//     _vector<int> my_vector;

//     printElement(test_name);
//     res1 = func1(vector);
//     res2 = func2(my_vector);
//     if (res1 == res2) {
//         printElement("OK");
//         result = 0;
//     }
//     else {
//         printElement("FAILED");
//         result = 1;
//     }
//     t1 = g_end1 - g_start1, t2 = g_end2 - g_start2;
//     (t1 >= t2) ? printElement(GREEN + std::to_string(t2) + "ms" + RESET) : printElement(REDD + std::to_string(t2) + "ms" + RESET);
//     (t1 > t2) ? printElement(REDD + std::to_string(t1) + "ms" + RESET) : printElement(GREEN + std::to_string(t1) + "ms" + RESET);
//     leaks = leaks_test(getpid());
//     cout << endl;

//     return !(!result && !leaks);
// }

#include <cstdlib>

int main(void) {
	ft::vector<int> my_vector;
	insert_test_3(my_vector);
	system("leaks $PPID");
	return (0);
}
