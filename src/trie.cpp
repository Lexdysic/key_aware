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
    m_count++;
}

void Trie::Search (const StringView & prefix, std::set<std::string> * output) {
    Node * node = &m_root;

    for (int32_t i = 0; i < prefix.Length(); ++i) {
        auto it = node->children.find(prefix[i]);
        if (it == node->children.end()) {
            return;
        }

        node = it->second;
    }

    std::stack<Node *> stack;
    stack.push(node);

    while (!stack.empty()) {
        node = stack.top();
        stack.pop();

        for (const auto & kv : node->children) {
            stack.push(kv.second);
        }

        if (node->value.length()) {
            output->emplace(node->value);
        }
    }
}

} // namespace key_aware