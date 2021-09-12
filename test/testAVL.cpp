#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "avl.h"
#include <catch.hpp>

TEST_CASE("AVL insert into tree 1") {
  tree::AVL<int> tree;
  tree.insertNode(tree.head, 10, 10);
  CHECK(tree.searchNode(10) == true);
  CHECK(tree.head->id == 10);
  CHECK(tree.head->height == 0);
  CHECK(tree.head->lchild == nullptr);
  CHECK(tree.head->rchild == nullptr);

  tree.insertNode(tree.head, 20, 20);
  CHECK(tree.searchNode(20) == true);
  CHECK(tree.head->id == 10);
  CHECK(tree.head->height == 1);
  CHECK(tree.head->lchild == nullptr);
  CHECK(tree.head->rchild->id == 20);

  tree.insertNode(tree.head, 5, 5);
  CHECK(tree.searchNode(5) == true);
  CHECK(tree.head->id == 10);
  CHECK(tree.head->height == 1);
  CHECK(tree.head->lchild->id == 5);
  CHECK(tree.head->rchild->id == 20);

  tree.insertNode(tree.head, 25, 25);
  CHECK(tree.searchNode(25) == true);
  CHECK(tree.head->id == 10);
  CHECK(tree.head->height == 2);
  CHECK(tree.head->lchild->id == 5);
  CHECK(tree.head->rchild->id == 20);
  CHECK(tree.head->rchild->rchild->id == 25);

  tree.insertNode(tree.head, 7, 7);
  CHECK(tree.searchNode(7) == true);
  CHECK(tree.head->id == 10);
  CHECK(tree.head->height == 2);
  CHECK(tree.head->lchild->id == 5);
  CHECK(tree.head->rchild->id == 20);
  CHECK(tree.head->rchild->rchild->id == 25);
  CHECK(tree.head->lchild->rchild->id == 7);

  // RR rotation around node 2
  tree.insertNode(tree.head, 2, 2);
  tree.insertNode(tree.head, 3, 3);
  tree.insertNode(tree.head, 4, 4);
  CHECK(tree.searchNode(2) == true);
  CHECK(tree.searchNode(3) == true);
  CHECK(tree.searchNode(4) == true);

  CHECK(tree.head->id == 10);
  CHECK(tree.head->height == 3);
  CHECK(tree.head->lchild->id == 5);
  CHECK(tree.head->rchild->id == 20);
  CHECK(tree.head->lchild->rchild->id == 7);
  CHECK(tree.head->lchild->lchild->id == 3);
  CHECK(tree.head->lchild->lchild->lchild->id == 2);
  CHECK(tree.head->lchild->lchild->rchild->id == 4);

  // RL rotation around node 20 -> LL rotation around 25, RR rotation around 20
  tree.insertNode(tree.head, 23, 23);
  CHECK(tree.searchNode(23) == true);
  CHECK(tree.head->id == 10);
  CHECK(tree.head->height == 3);
  CHECK(tree.head->rchild->id == 23);
  CHECK(tree.head->rchild->lchild->id == 20);
  CHECK(tree.head->rchild->rchild->id == 25);

  // LL rotation around node 20
  tree.insertNode(tree.head, 19, 19);
  tree.insertNode(tree.head, 18, 18);
  CHECK(tree.searchNode(23) == true);
  CHECK(tree.searchNode(23) == true);
  CHECK(tree.head->id == 10);
  CHECK(tree.head->height == 3);
  CHECK(tree.head->rchild->id == 23);
  CHECK(tree.head->rchild->lchild->id == 19);
  CHECK(tree.head->rchild->rchild->id == 25);
  CHECK(tree.head->rchild->lchild->lchild->id == 18);
  CHECK(tree.head->rchild->lchild->rchild->id == 20);

  // LL rotation around node 23
  tree.insertNode(tree.head, 14, 14);
  // LR rotation around node 18 -> RR rotation around 14, LL rotation around 18
  tree.insertNode(tree.head, 16, 16);
  CHECK(tree.head->id == 10);
  CHECK(tree.head->height == 3);
  CHECK(tree.head->rchild->id == 19);
  CHECK(tree.head->rchild->lchild->id == 16);
  CHECK(tree.head->rchild->rchild->id == 23);
  CHECK(tree.head->rchild->lchild->lchild->id == 14);
  CHECK(tree.head->rchild->lchild->rchild->id == 18);
  CHECK(tree.head->rchild->rchild->rchild->id == 25);
}

TEST_CASE("AVL insert into tree 2 - change head and delete nodes") {
  tree::AVL<int> tree;
  tree.insertNode(tree.head, 20, 20);
  CHECK(tree.searchNode(20) == true);

  CHECK(tree.head->id == 20);
  CHECK(tree.head->height == 0);
  CHECK(tree.head->lchild == nullptr);
  CHECK(tree.head->rchild == nullptr);

  tree.insertNode(tree.head, 12, 12);
  tree.insertNode(tree.head, 3, 3);
  CHECK(tree.searchNode(12) == true);
  CHECK(tree.searchNode(3) == true);

  CHECK(tree.head->id == 12);
  CHECK(tree.head->rchild->id == 20);
  CHECK(tree.head->lchild->id == 3);
  CHECK(tree.head->height == 1);

  tree.deleteNode(20, tree.head);
  CHECK(tree.searchNode(20) == false);
  tree.deleteNode(12, tree.head);
  CHECK(tree.searchNode(12) == false);
  CHECK(tree.head->id == 3);

  tree.deleteNode(3, tree.head);
  CHECK(tree.searchNode(3) == false);
}

TEST_CASE(
    "AVL insert into tree 3, TestStringObject - change head and delete nodes") {
  struct TestStringObject {
    std::string name;
    int age;
  };
  struct TestStringObject a = {"Ana", 25};
  struct TestStringObject l = {"Lily", 30};
  struct TestStringObject j = {"Joe", 35};

  tree::AVL<TestStringObject> tree;
  tree.insertNode(tree.head, a.age, std::forward<TestStringObject>(a));
  CHECK(tree.searchNode(25) == true);

  CHECK(tree.head->id == 25);
  CHECK(tree.head->height == 0);
  CHECK(tree.head->lchild == nullptr);
  CHECK(tree.head->rchild == nullptr);

  tree.insertNode(tree.head, l.age, std::forward<TestStringObject>(l));
  tree.insertNode(tree.head, j.age, std::forward<TestStringObject>(j));
  CHECK(tree.searchNode(25) == true);
  CHECK(tree.searchNode(30) == true);

  CHECK(tree.head->id == 30);
  CHECK(tree.head->rchild->id == 35);
  CHECK(tree.head->lchild->id == 25);
  CHECK(tree.head->height == 1);

  tree.deleteNode(25, tree.head);
  CHECK(tree.searchNode(25) == false);
  tree.deleteNode(30, tree.head);
  CHECK(tree.searchNode(30) == false);
  CHECK(tree.head->id == 35);

  tree.deleteNode(35, tree.head);
  CHECK(tree.searchNode(35) == false);
}

TEST_CASE("AVL Check Copy and Move Constructors/Assignment "
          "operators") {
  tree::AVL<int> tree;
  tree.insertNode(tree.head, 1, 1);
  REQUIRE(tree.searchNode(1) == true);

  tree::AVL<int> tree1{tree};
  REQUIRE(tree1.head->id == 1);

  tree::AVL<int> tree2;
  tree2 = tree1;
  REQUIRE(tree2.head->id == 1);

  tree::AVL<int> tree3{std::move(tree2)};
  REQUIRE(tree3.head->id == 1);

  tree::AVL<int> tree4;
  tree4 = std::move(tree3);
  REQUIRE(tree4.head->id == 1);
}

TEST_CASE("AVL insert and search - Benchmark") {
  tree::AVL<int> tree;
  BENCHMARK("Add 100.000 nodes in tree") {
    for (int j = 0; j < 100000; j++) {
      tree.insertNode(tree.head, j, std::forward<int>(j));
    }
  };

  BENCHMARK("Search 100 nodes in tree of 100.000 nodes") {
    for (int j = 0; j < 10; j++) {
      tree.searchNode(j + 11);
      tree.searchNode(j + 23);
      tree.searchNode(j + 97);
      tree.searchNode(j + 123);
      tree.searchNode(j + 217);
      tree.searchNode(j + 313);
      tree.searchNode(j + 457);
      tree.searchNode(j + 1117);
      tree.searchNode(j + 38928);
      tree.searchNode(j + 78922);
    }
  };
}
