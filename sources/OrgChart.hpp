#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

#include "OrgNode.hpp"

namespace ariel {
class OrgChart {
   private:
    OrgNode *root_;

   public:
    OrgChart() : root_(nullptr) {}
    ~OrgChart() {
        delete root_;
    }

    OrgChart(OrgChart &org) = default;
    OrgChart(OrgChart &&org) = default;
    OrgChart &operator=(OrgChart &&) = default;
    OrgChart &operator=(const OrgChart &org) = default;

    OrgNode *search(OrgNode *root, const std::string &data);
    OrgNode *get_root() const;
    OrgChart &add_root(const std::string &data);
    OrgChart &add_sub(const std::string &parent_data, const std::string &data);

    friend std::ostream &operator<<(std::ostream &os, const OrgChart &chart);
    friend std::ostream &operator<<(std::ostream &os, const OrgChart *chart);

    class OrgIterator {
        // TODO: tidy is yelling at this because of protected variables, to fix make them private and define getters and setters
        //    protected:
        //     OrgNode *node_;
        //     bool started_;

       public:
        OrgNode *node_;
        bool started_;
        OrgIterator() : node_(nullptr), started_(false) {}            // default constructor
        OrgIterator(OrgNode *node) : node_(node), started_(false) {}  // constructor

        virtual OrgIterator &operator++() = 0;  // prefix increment operator
        OrgIterator &operator++(int);           // postfix increment operator

        std::string *operator->() const;  // returns the node
        std::string &operator*() const;   // returns the node

        bool operator!=(const OrgIterator &other) const;  // returns true if both iterators point to different nodes
        bool operator==(const OrgIterator &other) const;  // returns true if both iterators point to the same node
    };

    class OrgLevelOrderIterator : public OrgIterator {
       public:
        OrgLevelOrderIterator() : queue_(std::queue<OrgNode *>()) {}                                  // constructor
        OrgLevelOrderIterator(OrgNode *node) : OrgIterator(node), queue_(std::queue<OrgNode *>()) {}  // constructor

        OrgLevelOrderIterator &operator++() override;  // prefix increment operator
       private:
        std::queue<OrgNode *> queue_;
    };

    class OrgReverseLevelOrderIterator : public OrgIterator {
       public:
        OrgReverseLevelOrderIterator() : stack_(std::stack<OrgNode *>()), queue_(std::queue<OrgNode *>()) {}  // constructor
        OrgReverseLevelOrderIterator(OrgNode *node);                                                          // cconstructor                                                               // constructor

        OrgReverseLevelOrderIterator &operator++() override;  // prefix increment operator
       private:
        std::stack<OrgNode *> stack_;
        std::queue<OrgNode *> queue_;
    };

    class OrgPreOrderIterator : public OrgIterator {
       public:
        OrgPreOrderIterator() : stack_(std::stack<OrgNode *>()) {}                                  // constructor
        OrgPreOrderIterator(OrgNode *node) : OrgIterator(node), stack_(std::stack<OrgNode *>()) {}  // constructor

        OrgPreOrderIterator &operator++() override;  // prefix increment operator
       private:
        std::stack<OrgNode *> stack_;
    };

    OrgLevelOrderIterator begin() const;
    OrgLevelOrderIterator end() const;

    OrgLevelOrderIterator begin_level_order() const;
    OrgLevelOrderIterator end_level_order() const;

    OrgReverseLevelOrderIterator begin_reverse_order() const;
    OrgReverseLevelOrderIterator reverse_order() const;

    OrgPreOrderIterator begin_preorder() const;
    OrgPreOrderIterator end_preorder() const;
};
}  // namespace ariel