#pragma once
#include <string>
#include <vector>

namespace ariel {
class OrgNode {
   private:
    std::string data_;                    // the data of the node
    OrgNode* supervisor_;                 // pointer to parent node
    std::vector<OrgNode*> subordinates_;  // vector of pointers to children nodes
    std::vector<OrgNode*>* team_;         // pointer to vector of pointers to siblings nodes
    size_t team_index_;                   // index of the node in the vector of siblings nodes

   public:
    OrgNode(const std::string& data) : data_(data), supervisor_(nullptr), team_(nullptr), team_index_(0) {}
    ~OrgNode() {
        for (OrgNode* subordinate : subordinates_) {
            delete subordinate;
        }
    }
    OrgNode(OrgNode& node) = default;
    OrgNode(OrgNode&& node) = default;
    OrgNode& operator=(OrgNode&&) = default;
    OrgNode& operator=(const OrgNode& node) = default;

    // properties
    size_t degree() const;  // number of children
    size_t depth() const;   // number of edges from the current node to the root
    size_t height() const;  // number of edges from the current node to the deepest leaf
    size_t size() const;    // number of nodes in the subtree rooted at the current node

    // methods
    OrgNode* find(const std::string& data);  // find a node with the given data, return nullptr if not found

    // getters
    std::string get_data() const;
    std::string& get_data();
    OrgNode* get_supervisor() const;
    std::vector<OrgNode*> get_subordinates() const;
    std::vector<OrgNode*>* get_team() const;

    // setters
    OrgNode& set_data(const std::string& data);      // sets the data of the node
    OrgNode& add_subordinate(OrgNode* subordinate);  // adds a child to the node

    friend std::ostream& operator<<(std::ostream& os, const OrgNode& node);
    friend std::ostream& operator<<(std::ostream& os, const OrgNode* node);
};
}  // namespace ariel