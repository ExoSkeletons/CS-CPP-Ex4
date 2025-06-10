//
// Created by Aviad Levine on 1/06/2025.
//

#ifndef CONTAINERS_HPP
#define CONTAINERS_HPP

#include <algorithm>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <iterator>

namespace containers {
    /* Container */
    template<typename T>
    class MyContainer {
        std::vector<T> data;

    public:
        MyContainer() = default;

        MyContainer(const MyContainer &other) { *this = other; }

        MyContainer &operator=(const MyContainer &other) {
            data.clear();
            for (const auto &d: other.data) data.push_back(d);
            return *this;
        }

        ~MyContainer() = default;

        /* Element Modify methods*/

        void add(const T &value) { data.push_back(value); }

        void remove(const T &value) {
            bool found = false;
            for (auto it = data.begin(); it != data.end();) {
                if (*it == value) {
                    it = data.erase(it);
                    found = true;
                } else ++it;
            }
            if (!found) throw std::runtime_error("Value not found in container");
        }

        size_t size() const { return data.size(); }

        /* Operators */

        T &operator[](size_t index) {
            if (index >= data.size()) throw std::runtime_error("Index out of range");
            return data.at(index);
        }

        const T &operator[](size_t index) const {
            if (index >= data.size()) throw std::runtime_error("Index out of range");
            return data.at(index);
        }

        friend std::ostream &operator<<(std::ostream &os, const MyContainer &c) {
            for (const auto &item: c.data) os << item << " ";
            return os;
        }

        /* Iterators */

    private:
        class Iterator {
        protected:
            int pos = 0;
            std::vector<T> data;

        public:
            explicit Iterator(MyContainer &c, const bool reverse = false) {
                pos = 0;
                data.clear();
                data.reserve(c.data.size());
                for (const auto &d: c.data) data.emplace_back(d);
                if (reverse) std::reverse(data.begin(), data.end());
            }

            Iterator(const Iterator &other) { *this = other; }

            Iterator &operator=(const Iterator &other) {
                pos = other.pos;
                data.clear();
                for (const auto &v: other.data) data.push_back(v);
                return *this;
            }

            virtual ~Iterator() = default;

            Iterator &begin() {
                pos = 0;
                return *this;
            }

            Iterator &end() {
                pos = data.size();
                return *this;
            }

            explicit operator bool() const { return pos < data.size(); }
            explicit operator int() const { return pos; }

            T &operator[](const int i) {
                const auto index = i + pos;
                if (index >= data.size() || index < 0) throw std::out_of_range("Iterator out of range");
                return data[index];
            }

            const T &operator[](const int i) const {
                const auto index = i + pos;
                if (index >= data.size() || index < 0) throw std::out_of_range("Iterator out of range");
                return data[index];
            }

            T &operator*() { return (*this)[0]; }

            auto &operator++() {
                pos++;
                return *this;
            }

            auto operator++(int) {
                Iterator tmp = *this;
                pos++;
                return tmp;
            }

            auto &operator--() {
                pos--;
                return *this;
            }

            auto operator--(int) {
                Iterator tmp = *this;
                pos--;
                return tmp;
            }

            bool operator==(const Iterator &other) const = default;

            bool operator!=(const Iterator &other) const = default;
        };

    public:
        class Order : public Iterator {
        public:
            explicit Order(MyContainer &c) : Iterator(c, false) {}
        };

        class ReverseOrder : public Iterator {
        public:
            explicit ReverseOrder(MyContainer &c) : Iterator(c, true) {}
        };

    private:
        class SortedIterator : public Order {
        public:
            explicit SortedIterator(MyContainer &c, const bool asc = true) : Order(c) {
                sort(this->data.begin(), this->data.end());
                if (!asc) std::reverse(this->data.begin(), this->data.end());
            }
        };

    public:
        class AscendingOrder : public SortedIterator {
        public:
            explicit AscendingOrder(MyContainer &c) : SortedIterator(c, true) {}
        };

        class DescendingOrder : public SortedIterator {
        public:
            explicit DescendingOrder(MyContainer &c) : SortedIterator(c, false) {}
        };

        class SideCrossOrder final : public AscendingOrder {
        public:
            explicit SideCrossOrder(MyContainer &c) : AscendingOrder(c) {
                std::vector<T> tmp;
                const int n = this->data.size();
                tmp.reserve(n);
                for (size_t i = 0; i < n; ++i) {
                    int sc_index = i % 2 == 0 ? i / 2 : n - 1 - i / 2;
                    tmp.push_back(this->data[sc_index]);
                }
                this->data = std::move(tmp);
            }
        };

        class MiddleOutOrder final : public AscendingOrder {
        public:
            explicit MiddleOutOrder(MyContainer &c) : AscendingOrder(c) {
                std::vector<T> tmp;
                const int n = this->data.size(), mid = n / 2;
                tmp.reserve(n);
                for (int i = 0; i < n; ++i) {
                    int mo_index = i % 2 == 0 ? mid + i / 2 : mid - i / 2 - 1;
                    tmp.push_back(this->data[mo_index]);
                }
                this->data = std::move(tmp);
            }
        };


        Order begin_order() {
            auto it = Order(*this);
            it.begin();
            return it;
        }

        Order end_order() {
            auto it = Order(*this);
            it.end();
            return it;
        }

        ReverseOrder begin_reverse_order() {
            auto it = ReverseOrder(*this);
            it.begin();
            return it;
        }

        ReverseOrder end_reverse_order() {
            auto it = ReverseOrder(*this);
            it.end();
            return it;
        }

        AscendingOrder begin_ascending_order() {
            auto it = AscendingOrder(*this);
            it.begin();
            return it;
        }

        AscendingOrder end_ascending_order() {
            auto it = AscendingOrder(*this);
            it.end();
            return it;
        }

        DescendingOrder begin_descending_order() {
            auto it = DescendingOrder(*this);
            it.begin();
            return it;
        }

        DescendingOrder end_descending_order() {
            auto it = DescendingOrder(*this);
            it.end();
            return it;
        }

        SideCrossOrder begin_side_cross_order() {
            auto it = SideCrossOrder(*this);
            it.begin();
            return it;
        }

        SideCrossOrder end_side_cross_order() {
            auto it = SideCrossOrder(*this);
            it.end();
            return it;
        }

        MiddleOutOrder begin_middle_out_order() {
            auto it = MiddleOutOrder(*this);
            it.begin();
            return it;
        }

        MiddleOutOrder end_middle_out_order() {
            auto it = MiddleOutOrder(*this);
            it.end();
            return it;
        }
    };

    template class MyContainer<int>;
    template class MyContainer<double>;
    template class MyContainer<char>;
    template class MyContainer<std::string>;
} // namespace containers


#endif //CONTAINERS_HPP
