#pragma once

#include <iostream>
#include <memory>

namespace tree {

/**
 * Implementation of the AVL Binary Search Tree class.
 *
 * AVL is balanced Binary Search Tree (BST), where difference in height between
 * left and right nodes, for each node, can not be more than 1. Operations like
 * insert, delete and search nodes in BST have cost that is proportional to tree
 * height, O(h) or logN, where N is number of nodes in tree, O(logN). The cost
 * of these operations can become O(N). By balancing the tree after every
 * insertion, we can make sure that the cost remains O(logN). Based on
 * https://users.cs.fiu.edu/~weiss/dsaa_c++4/code/AvlTree.h
 *
 * @tparam V type of data stored in AVL BST
 */
template <typename V> class AVL {
private:
  /**
   * Implementation of the Node structure.
   *
   * Each Node carries a id, data inserted in node, height of node that is set
   * to 0, and a pointer to left child and right child node in tree structure.
   *
   * @param id id of node
   * @tparam V data type in node
   * @param height node height, needed for tree balancing, set to 0 when node is
   * constructed
   * @param lchild pointer to left child node in tree structure, set to nullptr
   * @param rchild pointer to right child node in tree structure, set to nullptr
   */
  struct Node {
    int id;
    V data;
    int height = 0;
    std::unique_ptr<Node> lchild = nullptr;
    std::unique_ptr<Node> rchild = nullptr;

    /**
     * Node constructor.
     * Each node is constructed using id value and data of node
     * node.
     *
     * @param id node id
     * @tparam data node data
     */
    explicit Node(int id, V &&data) : id(id), data(std::forward<V>(data)) {}
  };

  /**
   * Function for tree balancing.
   * This function is called after each insert or delete operation. The function
   * covers four basic scenarios for balancing, that require following
   * rotations: 1) LLRotation 2) LRRotation 3) RRRotation 4) RLRotation
   *
   * @param node pointer to node that is to be balanced
   */
  void balanceTree(std::unique_ptr<Node> &node);

  /**
   * Node height.
   * This function returns node height. If the node is nullptr it returns -1.
   *
   * @param node pointer to node for which we search height
   *
   * @return height of node if node exists, if not, it returns -1
   */
  const int nodeHeight(const std::unique_ptr<Node> &node) const;

  /**
   * LLRotation function.
   * This function is called on node if height difference of node's left child
   * and right child is greater than 1 and height of node's left
   * child of left child is greater or equal to height of right child node's
   * left child (https://www.geeksforgeeks.org/avl-tree-set-1-insertion/)
   *
   * @param node pointer to node that is to be balanced
   */
  void LLRotation(std::unique_ptr<Node> &node);

  /**
   * LRRotation function.
   * This function is called on node if height difference of node's left child
   * and right child is greater than 1
   * (https://www.geeksforgeeks.org/avl-tree-set-1-insertion/)
   *
   * @param node pointer to node that is to be balanced
   */
  void LRRotation(std::unique_ptr<Node> &node);

  /**
   * RRRotation function.
   * This function is called on node if height difference of node's right child
   * and left child is greater than 1 and height of node's right
   * child of right child is greater or equal to height of left child node's
   * right child (https://www.geeksforgeeks.org/avl-tree-set-1-insertion/)
   *
   * @param node pointer to node that is to be balanced
   */
  void RRRotation(std::unique_ptr<Node> &node);

  /**
   * RLRotation function.
   * This function is called on node if height difference of node's right child
   * and left child is greater than 1
   * (https://www.geeksforgeeks.org/avl-tree-set-1-insertion/)
   *
   * @param node pointer to node that is to be balanced
   */
  void RLRotation(std::unique_ptr<Node> &node);

  /**
   * Returns id of smallest node in subtree.
   *
   * @param node pointer to node for which we search smallest node in subtree.
   *
   * @return id of smallest node in subtree
   */
  const int findMin(const std::unique_ptr<Node> &node) const;

  /**
   * Allowed max height difference of node's left child
   * and right child, used for balanceTree calculation
   */
  static constexpr int allowedHeightDifference = 1;

public:
  /**
   * Constructor of AVL
   *
   */
  AVL();

  /**
   * Destructor of AVL
   *
   * Default implementation
   *
   */
  ~AVL() = default;

  /**
   * Copy Constructor of AVL
   *
   * Creates new head with rhs head data
   */
  AVL(const AVL &rhs) : head(nullptr) {
    if (rhs.head)
      head = std::make_unique<Node>(rhs.head->id,
                                    std ::forward<V>(rhs.head->data));
  }

  /**
   * Copy Assignment of AVL
   *
   * Resets head if rhs head is nullptr and then it creates new head with rhs
   * head data. If rhs head is not nullptr, it swaps head with rhs head.
   */
  AVL &operator=(const AVL &rhs) {
    if (!rhs.head) {
      head.reset();
    } else if (!head) {
      head = std::make_unique<Node>(rhs.head->id,
                                    std ::forward<V>(rhs.head->data));
    } else {
      std::swap(*head, *rhs.head);
    }
    return *this;
  }

  /**
   * Move Constructor of AVL
   *
   * Swaps head node of origin with new head
   */
  AVL(AVL &&rhs) noexcept : head(std::move(rhs.head)) {}

  /**
   * Move Assignment of AVL
   *
   * Swaps head node of origin with new head
   */
  AVL &operator=(AVL &&rhs) noexcept {
    head = std::move(rhs.head);
    return *this;
  }

  /**
   * Head node.
   */
  std::unique_ptr<Node> head = nullptr;

  /**
   * Inserts node in AVL BST.
   * During first insert, head is still nullptr, so first insert creates head
   * node. After that, node is insreted as left child, if node's id is smaller
   * then head's node or right child, if id is greater. This is done
   * recursively. After each insert, tree is balanced.
   *
   * @param node pointer to head node
   * @param id node's id
   * @tparam data node's data
   */
  void insertNode(std::unique_ptr<Node> &node, int id, V &&data);

  /**
   * Delete node from AVL BST.
   * Function uses recursive delete, until it reaches node with requested id,
   * then it checks if this node has only one child, or both, left an right
   * children. If there are two children, findMin is called to find minimum item
   * in this subtree, on which delete is called recursively. This leaves only
   * one child case, which checks if the left child is nullptr, if not, node
   * is set as old nodes's left child, if yes, then it is set as nodes's right
   * child. After this, balance is called.
   *
   * @param id node's id
   * @param node pointer to head node
   */
  void deleteNode(int id, std::unique_ptr<Node> &node);

  /**
   * Search node's id in AVL BST.
   *
   * @param id node's id
   *
   * @return  return true if the node with this id is found, else return false
   */
  bool searchNode(int id) const;
};

template <typename V> AVL<V>::AVL() {}

template <typename V>
void AVL<V>::insertNode(std::unique_ptr<Node> &node, int id, V &&data) {
  if (!node) {
    node = std::make_unique<Node>(id, std::forward<V>(data));
  }

  if (id < node->id) {
    insertNode(node->lchild, id, std::forward<V>(data));
  } else if (id > node->id) {
    insertNode(node->rchild, id, std::forward<V>(data));
  }

  balanceTree(node);
}

template <typename V>
void AVL<V>::deleteNode(int id, std::unique_ptr<Node> &node) {
  if (node == nullptr)
    return;

  if (id < node->id) {
    deleteNode(id, node->lchild);
  } else if (id > node->id) {
    deleteNode(id, node->rchild);
  } else if (node->lchild != nullptr &&
             node->rchild != nullptr) { // two children
    node->id = findMin(node->rchild);
    deleteNode(node->id, node->rchild);
  } else { // one child
    std::unique_ptr<Node> oldNode = std::move(node);
    node = (oldNode->lchild != nullptr) ? std::move(oldNode->lchild)
                                        : std::move(oldNode->rchild);
  }
  balanceTree(node);
}

template <typename V> bool AVL<V>::searchNode(int id) const {
  AVL<V>::Node *tempNode = head.get();
  while (tempNode != nullptr) {
    if (id < tempNode->id) {
      tempNode = tempNode->lchild.get();
    } else if (id > tempNode->id) {
      tempNode = tempNode->rchild.get();
    } else {
      return true;
    }
  }
  return false;
}

template <typename V> void AVL<V>::balanceTree(std::unique_ptr<Node> &node) {
  if (node == nullptr)
    return;

  if (nodeHeight(node->lchild) - nodeHeight(node->rchild) >
      allowedHeightDifference) {
    if (nodeHeight(node->lchild->lchild) >= nodeHeight(node->lchild->rchild))
      LLRotation(node);
    else
      LRRotation(node);
  } else if (nodeHeight(node->rchild) - nodeHeight(node->lchild) >
             allowedHeightDifference) {
    if (nodeHeight(node->rchild->rchild) >= nodeHeight(node->rchild->lchild))
      RRRotation(node);
    else
      RLRotation(node);
  }

  node->height =
      std::max(nodeHeight(node->lchild), nodeHeight(node->rchild)) + 1;
}

template <typename V>
const int AVL<V>::nodeHeight(const std::unique_ptr<Node> &node) const {
  return node == nullptr ? -1 : node->height;
}

template <typename V>
const int AVL<V>::findMin(const std::unique_ptr<Node> &node) const {
  AVL<V>::Node *tempNode = node.get();

  if (tempNode != nullptr)
    while (tempNode->lchild != nullptr)
      tempNode = tempNode->lchild.get();

  return tempNode->id;
}

template <typename V> void AVL<V>::LLRotation(std::unique_ptr<Node> &node) {
  std::unique_ptr<Node> nodeL = std::move(node->lchild);
  std::swap(node->lchild, nodeL->rchild);
  node->height =
      std::max(nodeHeight(node->lchild), nodeHeight(node->rchild)) + 1;
  nodeL->height = std::max(nodeHeight(nodeL->lchild), node->height) + 1;
  std::swap(nodeL->rchild, node);
  std::swap(node, nodeL);
}

template <typename V> void AVL<V>::LRRotation(std::unique_ptr<Node> &node) {
  RRRotation(node->lchild);
  LLRotation(node);
}

template <typename V> void AVL<V>::RRRotation(std::unique_ptr<Node> &node) {
  std::unique_ptr<Node> nodeR = std::move(node->rchild);
  std::swap(node->rchild, nodeR->lchild);
  node->height =
      std::max(nodeHeight(node->lchild), nodeHeight(node->rchild)) + 1;
  nodeR->height = std::max(nodeHeight(nodeR->rchild), node->height) + 1;
  std::swap(nodeR->lchild, node);
  std::swap(node, nodeR);
}

template <typename V> void AVL<V>::RLRotation(std::unique_ptr<Node> &node) {
  LLRotation(node->rchild);
  RRRotation(node);
}
} // namespace tree
