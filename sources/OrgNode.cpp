#include "OrgNode.hpp"

namespace ariel {

size_t OrgNode::degree() const {
    return subordinates_.size();
}

size_t OrgNode::depth() const {
    if (supervisor_ == nullptr) {
        return 0;
    }
    return supervisor_->depth() + 1;
}

size_t OrgNode::height() const {
    if (subordinates_.empty()) {
        return 0;
    }
    size_t max_height = 0;
    for (OrgNode* child : subordinates_) {
        max_height = std::max(max_height, 1 + child->height());
    }
    return max_height;
}

size_t OrgNode::size() const {
    size_t size = 1;
    for (OrgNode* subordinate : subordinates_) {
        size += subordinate->size();
    }
    return size;
}

OrgNode* OrgNode::find(const std::string& data) {
    if (data_ == data) {
        return this;
    }
    for (OrgNode* subordinate : subordinates_) {
        OrgNode* found = subordinate->find(data);
        if (found != nullptr) {
            return found;
        }
    }
    return nullptr;
}

std::string OrgNode::get_data() const {
    return data_;
}

std::string& OrgNode::get_data() {
    return data_;
}

OrgNode* OrgNode::get_supervisor() const {
    return supervisor_;
}

std::vector<OrgNode*> OrgNode::get_subordinates() const {
    return subordinates_;
}

std::vector<OrgNode*>* OrgNode::get_team() const {
    return team_;
}

OrgNode& OrgNode::set_data(const std::string& data) {
    data_ = data;
    return *this;
}

OrgNode& OrgNode::add_subordinate(OrgNode* subordinate) {
    subordinates_.push_back(subordinate);
    subordinate->supervisor_ = this;
    subordinate->team_ = &subordinates_;
    subordinate->team_index_ = subordinates_.size() - 1;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const OrgNode& node) {
    os << node.data_;
    return os;
}

std::ostream& operator<<(std::ostream& os, const OrgNode* node) {
    os << node->data_;
    return os;
}

}  // namespace ariel