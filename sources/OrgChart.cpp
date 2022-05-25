#include "OrgChart.hpp"

namespace ariel {

OrgNode *OrgChart::search(OrgNode *root, const std::string &data) {
    if (root == nullptr) {
        return nullptr;
    }
    if (root->get_data() == data) {
        return root;
    }
    for (OrgNode *child : root->get_subordinates()) {
        OrgNode *found = this->search(child, data);
        if (found != nullptr) {
            return found;
        }
    }
    return nullptr;
}

OrgNode *OrgChart::get_root() const {
    return root_;
}

OrgChart &OrgChart::add_root(const std::string &data) {
    if (root_ == nullptr) {
        root_ = new OrgNode(data);
    } else {
        root_->set_data(data);
    }
    return *this;
}

OrgChart &OrgChart::add_sub(const std::string &parent_data, const std::string &data) {
    if (root_ == nullptr) {
        throw std::runtime_error("No root node");
    }
    OrgNode *parent = this->search(root_, parent_data);
    if (parent == nullptr) {
        throw std::runtime_error("Parent node not found");
    }
    parent->add_subordinate(new OrgNode(data));
    return *this;
}

std::ostream &print_tree(std::ostream &os, const OrgNode *node) {
    if (node == nullptr) {
        return os;
    }
    os << node->get_data();
    for (OrgNode *child : node->get_subordinates()) {
        os << " ";
        print_tree(os, child);
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const OrgChart &chart) {
    print_tree(os, chart.root_);
    return os;
}

std::ostream &operator<<(std::ostream &os, const OrgChart *chart) {
    print_tree(os, chart->root_);
    return os;
}

OrgChart::OrgLevelOrderIterator OrgChart::begin() const {
    if (root_ == nullptr) {
        throw std::runtime_error("No root node");
    }
    return OrgChart::OrgLevelOrderIterator(root_);
}

OrgChart::OrgLevelOrderIterator OrgChart::end() const {
    if (root_ == nullptr) {
        throw std::runtime_error("No root node");
    }
    return OrgChart::OrgLevelOrderIterator(nullptr);
}

OrgChart::OrgLevelOrderIterator OrgChart::begin_level_order() const {
    if (root_ == nullptr) {
        throw std::runtime_error("No root node");
    }
    return OrgChart::OrgLevelOrderIterator(root_);
}

OrgChart::OrgLevelOrderIterator OrgChart::end_level_order() const {
    if (root_ == nullptr) {
        throw std::runtime_error("No root node");
    }
    return OrgChart::OrgLevelOrderIterator(nullptr);
}

OrgChart::OrgReverseLevelOrderIterator OrgChart::begin_reverse_order() const {
    if (root_ == nullptr) {
        throw std::runtime_error("No root node");
    }
    return OrgChart::OrgReverseLevelOrderIterator(root_);
}

OrgChart::OrgReverseLevelOrderIterator OrgChart::reverse_order() const {
    if (root_ == nullptr) {
        throw std::runtime_error("No root node");
    }
    return OrgChart::OrgReverseLevelOrderIterator(nullptr);
}

OrgChart::OrgPreOrderIterator OrgChart::begin_preorder() const {
    if (root_ == nullptr) {
        throw std::runtime_error("No root node");
    }
    return OrgChart::OrgPreOrderIterator(root_);
}

OrgChart::OrgPreOrderIterator OrgChart::end_preorder() const {
    if (root_ == nullptr) {
        throw std::runtime_error("No root node");
    }
    return OrgChart::OrgPreOrderIterator(nullptr);
}

std::string *OrgChart::OrgIterator::operator->() const {
    return &(this->node_->get_data());
}

std::string &OrgChart::OrgIterator::operator*() const {
    return this->node_->get_data();
}

bool OrgChart::OrgIterator::operator==(const OrgChart::OrgIterator &other) const {
    return this->node_ == other.node_;
}

bool OrgChart::OrgIterator::operator!=(const OrgChart::OrgIterator &other) const {
    return !(*this == other);
}

OrgChart::OrgIterator &OrgChart::OrgIterator::operator++(int) {
    OrgChart::OrgIterator &iter = *this;
    ++(*this);
    return iter;
}

OrgChart::OrgLevelOrderIterator &OrgChart::OrgLevelOrderIterator::operator++() {
    if (this->node_ == nullptr) {
        return *this;
    }
    if (!this->started_) {
        this->queue_.push(this->node_);
    }
    if (!this->queue_.empty()) {
        OrgNode *node = this->queue_.front();
        this->queue_.pop();
        for (OrgNode *subordinate : node->get_subordinates()) {
            this->queue_.push(subordinate);
        }
        this->node_ = node;
    } else {
        this->node_ = nullptr;
    }
    if (!this->started_) {
        this->started_ = true;
        ++(*this);
    }
    return *this;
}
OrgChart::OrgReverseLevelOrderIterator::OrgReverseLevelOrderIterator(OrgNode *node) : OrgChart::OrgIterator(node), stack_(std::stack<OrgNode *>()), queue_(std::queue<OrgNode *>()) {
    if (node != nullptr) {
        this->queue_.push(this->node_);
        while (!this->queue_.empty()) {
            OrgNode *node = this->queue_.front();
            this->queue_.pop();
            std::vector<OrgNode *> subordinates = node->get_subordinates();
            for (std::vector<OrgNode *>::reverse_iterator it = subordinates.rbegin(); it != subordinates.rend(); ++it) {
                this->queue_.push(*it);
            }
            this->stack_.push(node);
        }
        ++(*this);
    }
}
OrgChart::OrgReverseLevelOrderIterator &OrgChart::OrgReverseLevelOrderIterator::operator++() {
    if (this->node_ == nullptr) {
        return *this;
    }
    if (!this->stack_.empty()) {
        this->node_ = this->stack_.top();
        this->stack_.pop();
    } else {
        this->node_ = nullptr;
    }
    return *this;
}

OrgChart::OrgPreOrderIterator &OrgChart::OrgPreOrderIterator::operator++() {
    if (this->node_ == nullptr) {
        return *this;
    }
    if (!this->started_) {
        this->stack_.push(this->node_);
    }
    if (!this->stack_.empty()) {
        OrgNode *node = this->stack_.top();
        this->stack_.pop();
        std::vector<OrgNode *> subordinates = node->get_subordinates();
        for (std::vector<OrgNode *>::reverse_iterator it = subordinates.rbegin(); it != subordinates.rend(); ++it) {
            this->stack_.push(*it);
        }
        this->node_ = node;
    } else {
        this->node_ = nullptr;
    }
    if (!this->started_) {
        this->started_ = true;
        ++(*this);
    }
    return *this;
}

}  // namespace ariel