#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <chrono>
#include <random>

class IntSequence {
private:
    int value;
public:
    IntSequence(int initialValue) : value(initialValue) {}
    int operator() () {
        return value++;
    }
};

template <typename T>
void print(const T& t){
    for (auto elem : t)
        std::cout << elem << " ";
    std::cout << std::endl;
}

class RandSequence {
private:
        std::binomial_distribution<int> d;
        std::default_random_engine e;
public:
    RandSequence()  {
        d = std::binomial_distribution<int> (100, 0.5);
        e = std::default_random_engine (std::chrono::system_clock::now().time_since_epoch().count());
    }
    int operator() () {
        return this->d(this->e);
    }
};

int main() {

    //generate sequence 1 - 10
    std::vector <int> v;
    std::generate_n(back_inserter(v),
            10,
            IntSequence(1));
    print(v);

    //add few numbers from cin
    std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), back_inserter(v));
    print(v);

    //shuffle elments
    std::shuffle(v.begin(), v.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
    print(v);

    //delete duplicates
    std::vector <int> unique_elem;
    std::copy(v.begin(), v.end(), back_inserter(unique_elem));
    std::sort(unique_elem.begin(), unique_elem.end());
    std::vector <int> helper;
    std::copy(unique_elem.begin(), unique_elem.end(), back_inserter(helper));
    unique_elem.erase(std::unique(unique_elem.begin(), unique_elem.end()), unique_elem.end());
    std::vector <int> to_delete;
    std::set_difference(helper.begin(), helper.end(), unique_elem.begin(), unique_elem.end(), std::inserter(to_delete, to_delete.begin()));
    print(to_delete);
    auto c = std::remove_if(v.begin(), v.end(), [&to_delete](int elem){
        auto pos1 = std::find(to_delete.begin(), to_delete.end(), elem);
        if (pos1 != to_delete.end()) {
            to_delete.erase(pos1);
            return true;
        }
        else
            return false;
    });
    v.erase(c, v.end());
    print(v);

    //count quantity of numbers % 2 != 0
    int num = std::count_if(v.begin(), v.end(), [](int elem){
        return elem % 2 == 1;
    });
    std::cout << num << std::endl;

    //find min and max values
    auto mm = std::minmax(v.begin(), v.end());
    //std::cout << "min = " << *(mm.first) << "; max = " << *(mm.second) << std::endl;
    std::cout << "min = " << *(std::min_element(v.begin(), v.end())) << " ; max = " << *(std::max_element(v.begin(), v.end())) << std::endl;

    //find prime number
    std::cout << *(std::find_if(v.begin(), v.end(), [](int elem){
        for(int i = 2; i <= sqrt(elem); ++i)
            if (elem % i == 0)
                return false;
            return true;
    }));

    //replace all elems to elems*elems
    std::for_each(v.begin(), v.end(), [](int& elem){
        elem = elem * elem;
    });
    print(v);

    //create vector from random numbers
    std::vector <int> v1;
    std::generate_n(back_inserter(v1), v.size(), RandSequence());
    print(v1);

    //sum of elems of v1
    int sum = 0;
    std::for_each(v1.begin(), v1.end(), [&sum](const int& elem){
        sum += elem;
    });
    std::cout << sum << std::endl;

    //replace few first numbers of v1
    std::replace_if(v1.begin(), v1.begin() + 3, [](int elem){return true;}, 1);
    print(v1);

    //create vector difference betweeen v and v1
    std::vector <int> v2;
    std::set_difference(v.begin(), v.end(), v1.begin(), v1.end(), std::back_inserter(v2));
    print(v2);

    //replace all elems < 0 in v2 to 0
    std::replace_if(v2.begin(), v2.end(), [](int elem){return elem < 0;}, 0);
    print(v2);

    //delete all elems = 0 from v2
    auto pos = std::remove_if(v2.begin(), v2.end(), [](int elem){return elem == 0;});
    v2.erase(pos, v2.end());
    print(v2);

    //reverse v2
    std::reverse(v2.begin(), v2.end());
    print(v2);

    //find top3 greatest elems
    std::nth_element(v2.begin(), v2.begin(), v2.end(), std::greater<int>());
    std::cout << "The first largest element is " << v2[0] << '\n';
    std::nth_element(v2.begin(), v2.begin()+1, v2.end(), std::greater<int>());
    std::cout << "The second largest element is " << v2[1] << '\n';
    std::nth_element(v2.begin(), v2.begin()+2, v2.end(), std::greater<int>());
    std::cout << "The third largest element is " << v2[2] << '\n';

    //sort v and v1
    std::sort(v.begin(), v.end());
    std::sort(v1.begin(), v1.end());
    print(v);
    print(v1);

    //create v4 like merge of v and v1
    std::vector <int> v3;
    std::merge(v.begin(), v.end(), v1.begin(), v1.end(), std::back_inserter(v3));
    print(v3);

    //range for ordered insert
    auto p = std::equal_range(v3.begin(), v3.end(), 1);
    std::cout << *(p.first) << " - " << *(p.second) << std::endl;

    //cout all vectors
    print(v);
    print(v1);
    print(v2);
    print(v3);
}