#include <bits/stdc++.h>

bool isEqual(const std::vector<int>& data, int l, int r) {
    for (int i = l + 1; i < r; ++i)
        if (data[i] != data[l]) return false;
    return true;
}

enum class NodeType { NONE, CONCAT, SHUFFLE, SORTED };

struct Node {
    NodeType type;
    int l, r;
    Node* left;
    Node* right;

    void visit(std::vector<int>& data, std::vector<std::pair<int, int>>& seq) {
        switch (type) {
            case NodeType::NONE:
                break;
            case NodeType::CONCAT: {
                left->visit(data, seq);
                right->visit(data, seq);
                break;
            }
            case NodeType::SHUFFLE: {
                if (!isEqual(data, l, r)) {
                    std::sort(&data[l], &data[r]);
                    seq.emplace_back(l, r);
                }
                break;
            }
            case NodeType::SORTED: {
                std::sort(&data[l], &data[r]);
                break;
            }
        }
    }
};

const int MAXN = 1010000;

char str[MAXN];

Node* parse(std::stringstream& ss, std::vector<int>& data) {
    if (ss.peek() == '[') {
        ss.get();
        int l = data.size();
        while (true) {
            int x;
            ss >> x;
            data.push_back(x);
            if (ss.peek() == ']') break;
            ss.get();
        }
        ss.get();
        int r = data.size();
        auto node = new Node{NodeType::NONE};
        node->l = l, node->r = r;
        return node;

    } else {
        std::string op;
        std::getline(ss, op, '(');
        if (op == "concat") {
            auto left = parse(ss, data);
            ss.get();
            auto right = parse(ss, data);
            ss.get();
            auto node = new Node{NodeType::CONCAT};
            node->l = left->l, node->r = right->r;
            node->left = left, node->right = right;
            return node;

        } else if (op == "shuffle") {
            auto nn = parse(ss, data);
            ss.get();
            auto node = new Node{NodeType::SHUFFLE};
            node->l = nn->l, node->r = nn->r;
            node->left = nn;
            return node;

        } else if (op == "sorted") {
            auto nn = parse(ss, data);
            ss.get();
            auto node = new Node{NodeType::SORTED};
            node->l = nn->l, node->r = nn->r;
            node->left = nn;
            return node;
        }
    }
    assert(0);
    return {};
}

int main() {
    std::vector<int> data[2];
    std::vector<std::pair<int, int>> seq[2];
    for (int i = 0; i < 2; ++i) {
        std::fgets(str, sizeof(str), stdin);
        std::stringstream ss(str);
        auto node = parse(ss, data[i]);
        node->visit(data[i], seq[i]);
    }
    std::puts(data[0] == data[1] && seq[0] == seq[1] ? "equal" : "not equal");
}
