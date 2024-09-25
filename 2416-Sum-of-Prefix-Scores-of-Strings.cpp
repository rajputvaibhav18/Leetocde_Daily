struct TrieNode {
    int isCount;         // Tracks count of prefixes at this node
    TrieNode* child[26]; // Pointers to child nodes (for each letter 'a' to 'z')

    // Constructor initializes count and child pointers
    TrieNode() {
        isCount = 0;
        for (int i = 0; i < 26; i++) {
            child[i] = NULL;
        }
    }
};

class Trie {
private:
    TrieNode* root; // Root of the Trie

public:
    Trie() {
        root = new TrieNode(); // Initialize Trie root
    }

    // Inserts a word into the Trie
    void Insert(string s) {
        TrieNode* crawl = root;
        for (auto ch : s) {
            int idx = ch - 'a';
            if (!crawl->child[idx]) {
                crawl->child[idx] =
                    new TrieNode(); // Create child if it doesn't exist
            }
            crawl = crawl->child[idx];
            crawl->isCount++; // Increment count at each node
        }
    }

    // Solves for prefix scores for each word in words
    vector<int> solve(vector<string>& words) {
        vector<int> result;
        for (auto word : words) {
            int count = 0;
            TrieNode* crawl = root;
            for (auto ch : word) {
                int idx = ch - 'a';
                if (!crawl->child[idx]) {
                    break; // If the prefix doesn't exist, then further will
                           // also not exist, stop
                }
                crawl = crawl->child[idx];
                count += crawl->isCount; // Add count of prefixes
            }
            result.push_back(count);
        }
        return result;
    }
};

class Solution {
public:
    vector<int> sumPrefixScores(vector<string>& words) {
        Trie t; // Create a Trie
        for (auto word : words) {
            t.Insert(word); // Insert each word into the Trie
        }
        return t.solve(words); // Compute and return the prefix scores
    }
};