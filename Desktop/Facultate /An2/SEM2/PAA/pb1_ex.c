/*A search engine needs to implement an autocomplete feature for millions of search queries. 
Users type partial queries and expect to see the most relevant completions instantly. The system must:

Handle prefix matching for any partial input
Return the top 10 most frequent completions for each prefix
Support real-time updates when new search terms become popular
Efficiently store queries that share common prefixes
Given a dataset of search queries with their frequency counts, design an algorithm to build and 
query this autocomplete system. Consider memory efficiency since common prefixes like "how to" appear 
in thousands of queries.*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 128
#define MAX_TOP 10

typedef struct {
    char word[100];
    int freq;
} WordFreq;

typedef struct TrieNode {
    struct TrieNode *children[MAX_CHAR];
    int is_end;
    int freq;
    WordFreq top10[MAX_TOP];
    int top_count;
} TrieNode;

TrieNode* create_node() {
    TrieNode *node = (TrieNode*)malloc(sizeof(TrieNode));
    for (int i = 0; i < MAX_CHAR; i++)
        node->children[i] = NULL;
    node->is_end = 0;
    node->freq = 0;
    node->top_count = 0;
    return node;
}

void update_top10(TrieNode *node, const char *word, int freq) {
    int found = 0;
    for (int i = 0; i < node->top_count; i++) {
        if (strcmp(node->top10[i].word, word) == 0) {
            node->top10[i].freq = freq;
            found = 1;
            break;
        }
    }

    if (!found) {
        if (node->top_count < MAX_TOP) {
            strcpy(node->top10[node->top_count].word, word);
            node->top10[node->top_count].freq = freq;
            node->top_count++;
        } else if (freq > node->top10[MAX_TOP - 1].freq) {
            strcpy(node->top10[MAX_TOP - 1].word, word);
            node->top10[MAX_TOP - 1].freq = freq;
        }
    }

    // Sortează top10 descrescător după frecvență
    for (int i = 0; i < node->top_count - 1; i++) {
        for (int j = i + 1; j < node->top_count; j++) {
            if (node->top10[i].freq < node->top10[j].freq) {
                WordFreq temp = node->top10[i];
                node->top10[i] = node->top10[j];
                node->top10[j] = temp;
            }
        }
    }
}

void insert(TrieNode *root, const char *word, int freq) {
    TrieNode *node = root;
    while (*word) {
        if (node->children[(int)*word] == NULL)
            node->children[(int)*word] = create_node();
        node = node->children[(int)*word];
        update_top10(node, word, freq);
        word++;
    }
    node->is_end = 1;
    node->freq = freq;
}

void autocomplete(TrieNode *root, const char *prefix) {
    TrieNode *node = root;
    while (*prefix) {
        if (node->children[(int)*prefix] == NULL) {
            printf("Nicio completare pentru: %s\n", prefix);
            return;
        }
        node = node->children[(int)*prefix];
        prefix++;
    }

    printf("Sugestii pentru prefix:\n");
    for (int i = 0; i < node->top_count; i++) {
        printf(" - %s (%d)\n", node->top10[i].word, node->top10[i].freq);
    }
}
