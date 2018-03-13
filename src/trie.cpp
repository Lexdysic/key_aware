#include <key_aware/key_aware.h>
#include <stack>

namespace key_aware {

void Trie::Add (const StringView & str) {
    Node * node = &m_root;
    
    int32_t i = 0;
    for (; i < str.Length(); ++i) {
        auto it = node->children.find(str[i]);
        if (it != node->children.end()) {
            node = it->second;
        }
        else {
            break;
        }
    }

    for (; i < str.Length(); ++i) {
        Node * newNode = new Node();
        node->children[str[i]] = newNode;
        node = newNode;
    }

    node->value = std::string(str.Ptr(), (size_t)str.Length());
}

void Trie::Search (const StringView & prefix, std::set<std::string> * output) {
    Node * node = &m_root;

    int32_t i = 0;
    for (; i < prefix.Length(); ++i) {
        auto it = node->children.find(prefix[i]);
        if (it != node->children.end()) {
            node = it->second;
        }
        else {
            std::stack<Node *> stack;
            stack.push(node);


            while (!stack.empty()) {
                node = stack.top();
                stack.pop();

                for (const auto & kv : node->children) {
                    stack.push(kv.second);
                }

                output->emplace(node->value);
            }

            break;
        }
    }
}

} // namespace key_aware