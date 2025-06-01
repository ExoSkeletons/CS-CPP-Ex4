//
// Created by Aviad Levine on 1/06/2025.
//

#ifndef CONTAINERS_HPP
#define CONTAINERS_HPP

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

        MyContainer(const MyContainer &other) { (*this) = other; }

        MyContainer &operator=(const MyContainer &other) {
            data.clear();
            for (auto d: other.data) data.push_back(d);
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

        T &operator[](size_t index) { return data[index]; }
        T &operator[](size_t index) const { return data[index]; }

        friend std::ostream &operator<<(std::ostream &os, const MyContainer &c) {
            for (const auto &item: c.data) os << item << " ";
            return os;
        }

        /* Iterators */

    private:
        template<bool reverse>
        class Iterator {
        protected:
            int pos = 0;
            MyContainer c;

            virtual int map(const int i) { return i; };

        public:
            explicit Iterator(MyContainer &c) { this.c = c; }

            Iterator(const Iterator &other) = default;

            Iterator &operator=(const Iterator &other) = default;

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

            int index(const int i) { return map(!reverse ? pos + i : c.size() - 1 - pos - i); }

            T &operator*() { return c[index(0)]; }
            T *operator->() { return &(*this)[0]; }
            T &operator [](const int i) const { return c[index(i)]; }

            Iterator &operator++() {
                pos++;
                return *this;
            }

            Iterator &operator--() {
                pos--;
                return *this;
            }
        };

        template<bool desc>
        class SortedOrder : public Iterator<desc> {
        public:
            explicit SortedOrder(MyContainer c) : Iterator<desc>(c) { sort(c.data.begin(), c.data.end()); }
        };

    public:
        typedef Iterator<false> Order;
        typedef Iterator<true> ReverseOrder;

        class AscendingOrder : public SortedOrder<false> {
        public:
            explicit AscendingOrder(const MyContainer &c) : SortedOrder<false>(c) {}
        };

        class DescendingOrder : public SortedOrder<true> {
        public:
            explicit DescendingOrder(const MyContainer &c) : SortedOrder<true>(c) {}
        };

        class SideCrossOrder final : public AscendingOrder {
        protected:
            int map(const int i) override { return i % 2 != 0 ? i : this->c.size() - 1 - i; }
        };

        class MiddleOutOrder final : public AscendingOrder {
        protected:
            int map(const int i) override {
                auto mid = this->c.size() / 2;
                return i % 2 == 0 ? mid + i : mid - i;
            }
        };


        Order begin_order() { return Order(*this).begin(); }
        Order end_order() { return Order(*this).end(); }
        ReverseOrder begin_reverse_order() { return Order(*this).begin(); }
        ReverseOrder end_reverse_order() { return Order(*this).end(); }
        AscendingOrder begin_ascending_order() { return AscendingOrder(*this).begin(); }
        AscendingOrder end_ascending_order() { return AscendingOrder(*this).end(); }
        DescendingOrder begin_descending_order() { return DescendingOrder(*this).begin(); }
        DescendingOrder end_descending_order() { return DescendingOrder(*this).end(); }
        SideCrossOrder begin_side_cross_order() { return SideCrossOrder(*this).begin(); }
        SideCrossOrder end_side_cross_order() { return SideCrossOrder(*this).end(); }
        MiddleOutOrder begin_middle_out_order() { return MiddleOutOrder(*this).begin(); }
        MiddleOutOrder end_middle_out_order() { return MiddleOutOrder(*this).end(); }
    };
} // namespace containers


#endif //CONTAINERS_HPP
